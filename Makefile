all:
	gcc -Wall -ggdb -O0 -o bin/graph src/graph.c
clean:
	rm -r bin/*
