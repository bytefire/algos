all:
	gcc -Wall -ggdb -O0 -o bin/graph src/graph.c src/queue.c
clean:
	rm -r bin/*
