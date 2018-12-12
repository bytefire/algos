#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

#define MAX_VERTICES 64

struct edge {
	int from; /* index of from vertex */
	int to; /* index of to vertex */
	int weight;
	struct edge *next;
};

struct vertex {
	int id; /* index in array of vertices in the graph */
	int data;

	/* list of all edges starting from this node */
	struct edge *edges;
};

struct graph {
	struct vertex *vertices[MAX_VERTICES];
	int highest_vertex; /* biggest index of vertex used so far */
};

static void free_vertex(struct vertex *v)
{
	struct edge *e = v->edges;
	struct edge *temp;

	while (e) {
		temp = e;
		e = e->next;
		free(temp);
	}

	free(v);
}

int graph_init(struct graph **g)
{
	*g = malloc(sizeof(struct graph));
	if (!*g)
	       return -ENOMEM;

	memset(*g, 0, sizeof(struct graph));

	return 0;
}

void graph_finit(struct graph *g)
{
	int i;

	for (i = 0; i <= highest_vertex; i++) {
		if (g->vertices[i])
			free_vertex(g->vertices[i]);
	}

	free(g);
}
