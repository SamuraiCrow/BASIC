#BASIC transpiler makefile

debug/mb: obj/mbdebug.o
	gcc obj/mbdebug.o -o debug/mb

release/mb: obj/mb.o
	gcc obj/mb.o -o release/mb

obj/mbdebug.o: mb.c mb.h
	gcc mb.c -g -c -o obj/mbdebug.o -Wall --pedantic -std=gnu99

obj/mb.o: mb.c mb.h
	gcc mb.c -c -Os -o obj/mb.o -Wall --pedantic -std=gnu99

mb.c: src/mattathias.peg
	packcc -omb src/mattathias.peg 

test: debug/mb test/hello.mb
	debug/mb -d <test/hello.mb 2>parsedebug.log

compile: debug/mb runtime/runtime.h runtime/runtime.c
	gcc runtime/runtime.c -g -o hello.exe -std=gnu99

clean:
	rm -f obj/* release/* mb.* debug/*
