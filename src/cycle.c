/* find cycles in undirected graph. basically perform a dfs keeping track of
 * back edges
 */

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

bool dfs(struct graph *g, int root, bool visited[MAX_NODES], int parent[MAX_NODES]);

void get_cycle(struct graph *g)
{
	int i;
	bool visited[MAX_NODES];
	int parent[MAX_NODES];
	memset(visited, 0, sizeof(bool) * MAX_NODES);
	memset(parent, 255, sizeof(int) * MAX_NODES); /* 255 = 1's complement for -1, may not work on all architectures */

	for (i = 0; i < g->n; i++) {
		if (!visited[i]) {
			dfs(g,i, visited, parent);
		}
	}
}

void print_cycle(int parent[MAX_NODES], int last, int repeating)
{
	printf("%d <- ", repeating);

	while (parent[last] != -1) {
		printf("%d <- ", last);
		last = parent[last];
	}
}

/* root = node where to start dfs. we must ensure root is
 * always unvisited when we enter this function
 *
 * this function returns true if a cycle was found
 */
bool dfs(struct graph *g, int root, bool visited[MAX_NODES], int parent[MAX_NODES])
{
	struct edge *e = g->v[root];

	visited[root] = true;

	while (e) {
		if (!visited[e->to]) {
			parent[e->to] = root;
			if (dfs(g, e->to, visited, parent))
				return true;
		} else {
			/* we saw a back edge, but make sure that it is not to the parent
			 * we just came from, which will be the case in undirected graph.
			 *
			 * basically we are searching for a back edge that doesn't point
			 * to its parent.
			 */
			if (parent[e->to] != root) {
				/* now we have a cycle */
				printf("found a cycle: ");
				print_cycle(parent, root, e->to);
				printf("\n");

				return true;
			}
		}
		e = e->next;
	}

	return false;
}

int main(void)
{
	/* TODO: implement a test for this */

	printf("TODO: no test for this yet. please feel free to add one\n");

	return 0;
}
