
bin/main: bin/main.o bin/grid.o
	cc -o bin/main bin/main.o bin/grid.o -std=c99 -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lm -lGL && bin/./main

bin/grid.o: grid.c
	cc -c grid.c -o bin/grid.o -std=c99

bin/main.o: main.c
	cc -c main.c -o bin/main.o -std=c99
clean:
	rm -f bin/main bin/main.o bin/grid.o && make

