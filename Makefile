maze:
	gcc -Wall -O0 -ggdb -o bin/maze src/maze.c
nsteps:
	gcc -Wall -O0 -ggdb -o bin/nsteps src/nsteps.c
array2bst:
	gcc -Wall -O0 -ggdb -o bin/array2bst src/array2bst.c
all_paths:
	gcc -Wall -O0 -ggdb -o bin/all-paths src/all-paths.c
subsets:
	gcc -Wall -O0 -ggdb -o bin/subsets src/subsets.c
permutations:
	gcc -Wall -O0 -ggdb -o bin/permutations src/permutations.c
backtrack:
	gcc -Wall -O0 -ggdb -o bin/backtrack src/backtrack.c
graph:
	gcc -Wall -ggdb -O0 -o bin/driver src/graph.c src/queue.c src/driver.c
all:  graph backtrack permutations subsets all_paths array2bst nsteps maze
clean:
	rm -r bin/*
