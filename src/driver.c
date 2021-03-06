#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

static void process_vertex(size_t id)
{
	printf("visited vertex %ld\n", id);
}

static void test_bfs(void)
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
}

static void test_topological_sort(void)
{
	struct graph *g;
	size_t *sorted;
	int i;

	graph_init(&g);

	/*
	 *
	 * 1 --> 0---|          |---> 2
	 * |         |---> 5 ---|
	 * |---> 3---|          |---> 4
	 *
	 */

	graph_add_edge(g, 1, 0, 0);
	graph_add_edge(g, 1, 3, 0);
	graph_add_edge(g, 0, 5, 0);
	graph_add_edge(g, 3, 5, 0);
	graph_add_edge(g, 5, 2, 0);
	graph_add_edge(g, 5, 4, 0);

	sorted = graph_topological_sort(g);

	for (i = 0; i < 6; i++)
		printf("%ld -> ", sorted[i]);

	printf("\n");

	free(sorted);
	graph_finit(g);
}

int main(void)
{
	test_bfs();
	test_topological_sort();

	return 0;
}
