release:
	cc -g -o main main.c -std=c99 -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lm -lGL
	./main
