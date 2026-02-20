release:
	cc -g3 -o main main.c grid.c -std=c99 -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lm -lGL  && ./main
