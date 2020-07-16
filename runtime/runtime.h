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
}empty={0,""};

char *__stringBuffer[256];
#endif
