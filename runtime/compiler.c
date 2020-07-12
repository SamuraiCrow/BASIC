/*
** Compiler.c
**
** By Samuel D. Crow
*/

#include <stdio.h>
#include "compiler.h"
#include "compiler_protos.h"

extern FILE *__output_c;
extern FILE *states_h;

void __generateLabel(char *__prefix, unsigned int __currentBlockNumber)
{
    fprintf(__output_c, "case %s%u:\n",__prefix, __currentBlockNumber);
    fprintf(states_h, ",\n%s%u",__prefix, __currentBlockNumber);
}

void __generateJump(char *__prefix, unsigned int __currentBlockNumber)
{
    fprintf(__output_c, "__state=%s%u;\nbreak;\n", __prefix, __currentBlockNumber);
}

void __generateConditionalJump(char *__prefix, unsigned int __currentBlockNumber, int __condition)
{
    fprintf(__output_c, "if (%u) {\n __state=%s%u;\nbreak;\n}\n", __condition, __prefix, __currentBlockNumber);
}

void __generateRuntimeError()
{
    fprintf(__output_c, "__state=__RUNTIME_ERROR;\nbreak;\n");
}

void __initBlock(struct __block *self)
{
    /* index block according to count */
    self->__blockNum=__blockCount;
    __blockCount++;

    /* add block to stack */
    self->__currentStack=__stackTop;
    __stackTop=self;
}

void __endBlock(struct __block *self)
{
    __stackTop=self->__currentStack;
}

void __initPostTestLoop(struct __postTestLoop *self) {
    __initBlock((struct __block *)self);
    self->__blockBase.__currentType=t_postTestLoop;
    __generateLabel("loopStart", self->__blockBase.__blockNum);
}

void __endPostTestLoop(struct __postTestLoop *self, int __condition)
{
    __generateConditionalJump("loopStart", self->__blockBase.__blockNum, __condition);
    __generateLabel("loopend", self->__blockBase.__blockNum);
}

/* TODO: convert __cond and __condition to an expression */
void __initPreTestLoop(struct __preTestLoop *self, int __cond)
{
    __initBlock((struct __block *)self);
    self->__loop.__blockBase.__currentType=t_preTestLoop;
    self->__condition=__cond;
    __generateJump("loopinit", self->__loop.__blockBase.__blockNum);
    __generateLabel("loopstart", self->__loop.__blockBase.__blockNum);
}

/*TODO: Convert __condition into an expression */
void __endPreTestLoop(struct __preTestLoop *self)
{
    __endPostTestLoop(self->__loop.__blockBase.__blockNum, self->__condition);
}

void __initMidTestLoop(struct __block *self)
{
    __initBlock(self);
    self->__currentType=t_midTestLoop;
    __generateLabel("loopstart", self->__blockNum);
}

void __endMidTestLoop(struct __block *self)
{
    __generateJump("loopstart", self->__blockNum);
    __generateLabel("loopend", self->__blockNum);
}

void __generateBreak()
{
    if (__stackTop->__currentType==t_midTestLoop ||
        __stackTop->__currentType==t_preTestLoop ||
        __stackTop->__currentType==t_postTestLoop)
    {
        __generateJump("loopend", __stackTop->__blockNum);
    } else if (__stackTop->__currentType==t_condition)
    {
        __generateJump("condend", __stackTop->__blockNum);
    } else
    {
        __generateRuntimeError();
    }
    
}

void __initConditional(struct __conditional *self, int __condition)
{
    __initBlock((struct __block *)self);
    __generateLabel("condstart", self->__blockBase.__blockNum);
    __generateConditionalJump("condelse", self->__blockBase.__blockNum, __condition);
}

void __elseConditional(struct __conditional *self)
{
    __generateJump("condend", self->__blockBase.__blockNum);
    __generateLabel("condelse", self->__blockBase.__blockNum);
}

void __endConditional(struct __conditional *self)
{
    __generateLabel("condend", self->__blockBase.__blockNum);
}

void __generateSubroutineCall(unsigned int __labelNum)
{
    unsigned int __retLabel=__blockCount;
    __blockCount++;
    fprintf(__output_c, 
        "self->__prev=__callstack;\n__callStack=return%u;\n__state=label%u;\nbreak;\n",
        __retLabel, __labelNum);
    __generateLabel("return", __retLabel);
}

void __generateReturn()
{
    fprintf(__output_c, "__state=__callstack;__callstack=self->__prev\nbreak;\n");
}
