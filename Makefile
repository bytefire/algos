kadane:
	gcc -Wall -O0 -ggdb -o bin/kadane src/kadane.c
cycle-digraph:
	gcc -Wall -O0 -ggdb -o bin/cycle-digraph src/cycle-digraph.c
cycle:
	gcc -Wall -O0 -ggdb -o bin/cycle src/cycle.c
lns:
	gcc -Wall -O0 -ggdb -o bin/lns src/lns.c
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
all:  graph backtrack permutations subsets all_paths array2bst nsteps maze lns cycle cycle-digraph kadane
clean:
	rm -r bin/*
