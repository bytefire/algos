#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

static void process_vertex(size_t id)
{
	printf("visited vertex %ld\n", id);
}

int main(void)
{
	struct graph *g;

	graph_init(&g);

	graph_add_edge(g, 0, 1, 0);
	graph_add_edge(g, 0, 4, 0);
	graph_add_edge(g, 0, 5, 0);
	graph_add_edge(g, 1, 4, 0);
	graph_add_edge(g, 1, 2, 0);
	graph_add_edge(g, 4, 3, 0);
	graph_add_edge(g, 2, 3, 0);

	graph_bfs(g, 0, process_vertex);

	graph_finit(g);

	return 0;
}
