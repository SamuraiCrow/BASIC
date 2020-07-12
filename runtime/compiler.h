/*
** Compiler.h
**
** By Samuel D. Crow
*/

#ifndef __COMPILER_H__
#define __COMPILER_H__

unsigned int __blockCount;
struct __block *__stackTop;

enum __blockType
{
    t_block=0,
    t_postTestLoop,
    t_preTestLoop,
    t_midTestLoop,
    t_condition
};

struct __block
{
    struct __block *__currentStack;
    unsigned int __blockNum;
    enum __blockType __currentType;
};

struct __postTestLoop
{
    struct __block __blockBase;
};

struct __preTestLoop
{
    struct __postTestLoop __loop;
    int __condition;
};

struct __conditional 
{
    struct __block __blockBase;
};

#endif
