backtrack:
	gcc -Wall -O0 -ggdb -o bin/backtrack src/backtrack.c
graph:
	gcc -Wall -O0 -ggdb -o bin/backtrack src/backtrack.c
all:  graph backtrack
clean:
	rm -r bin/*
