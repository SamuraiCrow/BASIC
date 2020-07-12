/*
** Compiler.c
**
** By Samuel D. Crow
*/

#include <stdio.h>
#include "compiler.h"

extern FILE *__output_c;
extern FILE *__labels_h;
void __generateLabel(char *__prefix, unsigned int __currentBlockNumber);
void __generateConditionalJump(char *__prefix, unsigned int __currentBlockNumber, int __condition);
void __initBlock(struct __block *self);
void __endBlock(struct __block *self);
void __initPostTestLoop(struct __postTestLoop *self);
void __endPostTestLoop(struct __postTestLoop *self, int __condition);

void __generateLabel(char *__prefix, unsigned int __currentBlockNumber)
{
    fprintf(__output_c, "case %s%d:\n",__prefix, __currentBlockNumber);
    fprintf(__labels_h, ",\n%s%d",__prefix, __currentBlockNumber);
}

void __generateConditionalJump(char *__prefix, unsigned int __currentBlockNumber, int __condition)
{
    fprintf(__output_c, "if (%d) {\n __state=%s%d;\nbreak;\n}\n", __condition, __prefix, __currentBlockNumber);
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
}
