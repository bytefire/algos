all:
	gcc -Wall -ggdb -O0 -o bin/driver src/graph.c src/queue.c src/driver.c
clean:
	rm -r bin/*
