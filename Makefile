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
all:  graph backtrack permutations subsets all_paths
clean:
	rm -r bin/*
