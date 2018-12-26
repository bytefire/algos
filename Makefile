permutations:
	gcc -Wall -O0 -ggdb -o bin/permutations src/permutations.c
backtrack:
	gcc -Wall -O0 -ggdb -o bin/backtrack src/backtrack.c
graph:
	gcc -Wall -ggdb -O0 -o bin/driver src/graph.c src/queue.c src/driver.c
all:  graph backtrack permutations
clean:
	rm -r bin/*
