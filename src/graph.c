#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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

	/* list of all edges starting from this node */
	struct edge *edges;
};

struct graph {
	struct vertex *v[MAX_VERTICES];
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

static struct vertex *create_vertex(void)
{
	struct vertex *v;

	v = malloc(sizeof(struct vertex));
	if (!v)
		return NULL;
	memset(v, 0, sizeof(struct vertex));

	return v;
}

static struct edge *create_edge(size_t from, size_t to, int weight)
{
	struct edge *e;

	e = malloc(sizeof(struct edge));
	if (!e)
		return NULL;
	e->from = from;
	e->to = to;
	e->weight = weight;

	return e;
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

	for (i = 0; i <= g->highest_vertex; i++) {
		if (g->v[i])
			free_vertex(g->v[i]);
	}

	free(g);
}

int graph_add_edge(struct graph *g, size_t from, size_t to, int weight)
{
	struct edge *e, *new_edge;

	if (from >= MAX_VERTICES || to >= MAX_VERTICES)
		return  -EINVAL;

	/* check if the edge already exists */
	if (g->v[from]) {
		e = g->v[from]->edges;
		while (e)
			if (e->to == to)
				return 0;
	}

	if (!g->v[from]) {
		g->v[from] = create_vertex();
		if (!g->v[from])
			return -ENOMEM;
	}

	g->v[from]->id = from;

	new_edge = create_edge(from, to, weight);
	if (!new_edge)
		return -ENOMEM;

	e = g->v[from]->edges;
	while (e && e->next) e = e->next;

	if (e)
		e->next = new_edge;
	else
		g->v[from]->edges = new_edge;

	if (!g->v[to]) {
		g->v[to] = create_vertex();
		if (!g->v[to])
			return -ENOMEM;
	}
	g->v[to]->id = to;

	if (from > g->highest_vertex) g->highest_vertex = from;
	if (to > g->highest_vertex) g->highest_vertex = to;

	return 0;
}

int main(void)
{
	printf("Placeholder\n");

	return 0;
}