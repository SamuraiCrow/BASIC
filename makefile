#BASIC transpiler makefile

debug/mb: obj/mbdebug.o
	gcc obj/mbdebug.o -o debug/mb

release/mb: obj/mb.o
	gcc obj/mb.o -o release/mb

obj/mbdebug.o: mb.c mb.h
	gcc mb.c -g -c -o obj/mbdebug.o -Wall --pedantic -std=gnu99

obj/mb.o: mb.c mb.h
	gcc mb.c -c -Os -o obj/mb.o -Wall --pedantic -std=gnu99

obj/runtimedebug.o: debug/mb runtime/runtime.h runtime/runtime.c
	gcc runtime/runtime.c -g -c -std=gnu99 -o obj/runtimedebug.o

mb.c: src/mattathias.peg
	packcc -omb src/mattathias.peg 

test: debug/mb test/hello.mb
	debug/mb -D <test/hello.mb 2>parsedebug.log

build: debug/mb test/hello.mb
	debug/mb <test/hello.mb 2>parsedebug.log

release: release/mb test/hello.mb
	release/mb <test/hello.mb

clean:
	rm -f obj/* release/* debug/* *.log *.c *.h
