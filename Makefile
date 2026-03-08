release:
	cc  -o bin/main main.c grid.c -std=c99 -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lm -lGL  && bin/./main
debug:
	cc -g3 -o bin/main main.c grid.c -std=c99 -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lm -lGL  && gdb bin/main
