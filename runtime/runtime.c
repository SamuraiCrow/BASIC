/* Runtime.c v0.1 for BASIC
** by Samuel D. Crow
*/

#include <stdio.h>
#include "runtime.h"
#include "consts.h"
#include "heap.h"
#include "functions.h"
#include "state.h"

extern int __stateloop();

int main(int argc, char *argv[]) {
	switch (argc) {
		case 1:
			if (__stateloop()<__EXIT) {
				fprintf (stderr, "\n\nRuntime Error Occurred.\n");
				return 1;
			}
			break;
		default:
			fprintf(stderr, "\nIncorrect number of arguments.\n");
			return 1;
			break;
	}
	return 0;
}
