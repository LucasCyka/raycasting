obj := bin/main.o bin/grid.o bin/main
CFLAGS := -std=c99 -Wall
LFLAGS := -Wl,-Bstatic -lraylib -Wl,-Bdynamic -lX11 -lm -lGL

bin/main: bin/main.o bin/grid.o 
	cc -o $@ $^ $(CFLAGS) $(LFLAGS) && bin/./main
	
bin/grid.o: grid.c
	cc -c grid.c -o bin/grid.o $(CFLAGS)

bin/main.o: main.c
	cc -c main.c -o bin/main.o $(CFLAGS)
clean:
	rm -f $(obj) && make



