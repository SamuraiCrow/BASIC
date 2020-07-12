/* Runtime.h v0.1 for BASIC
** by Samuel D. Crow
*/

#ifndef __RUNTIME_H__
#define __RUNTIME_H__

/* Base states */
enum __errors
{
	__NORMAL,
	__EXIT,
	__RUNTIME_ERROR
};

/* BASIC strings */
struct __string
{
	unsigned int __length;
	char __body[];
};

struct __subroutine
{
	unsigned int __prev;
	unsigned int __retLabel;
};

#endif
