/*
** Compiler_protos.h
** by Samuel D. Crow
** prototypes for compiler
*/
#ifndef __COMPILER_PROTOS_H__
#define __COMPILER_PROTOS_H__

void __generateLabel(char *__prefix, unsigned int __currentBlockNumber);
void __generateJump(char *__prefix, unsigned int __currentBlockNumber);
void __generateConditionalJump(char *__prefix, unsigned int __currentBlockNumber, int __condition);
void __generateRuntimeError();
void __initBlock(struct __block *self);
void __endBlock(struct __block *self);
void __initPostTestLoop(struct __postTestLoop *self);
void __endPostTestLoop(struct __postTestLoop *self, int __condition);
void __initPreTestLoop(struct __preTestLoop *self, int __cond);
void __endPreTestLoop(struct __preTestLoop *self);
void __initMidTestLoop(struct __block *self);
void __endMidTestLoop(struct __block *self);
void __generateBreak();
void __initConditional(struct __conditional *self, int __condition);
void __elseConditional(struct __conditional *self);
void __endConditional(struct __conditional *self);
void __generateSubroutineCall(unsigned int __labelNum);
void __generateReturn();

#endif
