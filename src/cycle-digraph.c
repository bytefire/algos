/* find cycle in a directed graph */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 64

struct edge {
        int to;
        int weight;
        struct edge *next;
};

struct graph {
        struct edge *v[MAX_NODES];
        int n;
};

bool is_back_edge(int parent[], int curr, int repeating)
{
	while (parent[curr] != -1) {
		if (repeating == curr)
			return true;
		curr = parent[curr];
	}

	return false;
}

void print_cycle(int parent[MAX_NODES], int last, int repeating)
{
        printf("%d <- ", repeating);

        while (parent[last] != -1) {
                printf("%d <- ", last);
                last = parent[last];
        }
}

bool dfs(struct graph *g, int curr, bool visited[MAX_NODES], int parent[MAX_NODES])
{
	struct edge *e = g->v[curr];

	visited[curr] = true;

	while (e) {
		if (!visited[e->to]) {
			parent[e->to] = curr;
			if (dfs(g, e->to, visited, parent))
				return true;
		} else {
			/* potential cycle */
			if (is_back_edge(parent, curr, e->to)) {
				/* this is a cycle */
				print_cycle(parent, curr, e->to);
				return true;
			}
		}

		e = e->next;
	}

	return false;
}

// TODO: wrapper to call dfs
bool dfs(struct graph *g, int curr, bool visited[MAX_NODES], int parent[MAX_NODES]);

void get_cycle(struct graph *g)
{
	int i;
	bool visited[MAX_NODES];
	int parent[MAX_NODES];

	memset(visited, 0, sizeof(bool) * MAX_NODES);
	/* 255 will set each int to all 1's, which is 2's complement for -1.
	 * this may not work on all machines
	 */
	memset(parent, 255, sizeof(int) * MAX_NODES);

	for (i = 0; i < g->n; i++) {
		if (!visited[i])
			if (dfs(g, i, visited, parent)) {
				printf("found cycle. exiting\n");
				return;
			}
	}
}

int main(void)
{
	/* TODO: write a test for this */
	printf("TODO: need to write a test for this. please feel free to add it.\n");

	return 0;
}
