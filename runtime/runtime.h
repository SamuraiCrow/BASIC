/* Runtime.h v0.1 for BASIC
** by Samuel D. Crow
*/

#ifndef __RUNTIME__
#define __RUNTIME__

/* Base structures */
struct __subroutine {
	struct __subroutine *__return;
};

struct __heap {
	struct __subroutine *__callStackBase;
};

/* Base states */
enum __errors {
	__RUNTIME_ERROR,
	__EXIT,
	__NORMAL
};

/* BASIC strings */
struct __string {
	unsigned int __length;
	char __body[];
};
#endif
