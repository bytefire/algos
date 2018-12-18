#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "graph.h"
#include "queue.h"

#define MAX_VERTICES 64

struct vertex {
	size_t id; /* index in array of vertices in the graph */

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
	e->next = NULL;

	return e;
}

/* NOTE: this is best implemented by a heap. we haven't covered heap yet, therefore
 * using this "manual" method.
 */
static struct edge *cheapest_edge_prim(struct graph *g, bool *visited)
{
	int i;
	int lowest_weight = 1000;
	struct edge *cheapest = NULL;

	for (i = 0; i <= g->highest_vertex; i++) {
		if (visited[i]) {
			struct edge *e = g->v[i]->edges;
			while (e) {
				if (e->weight <= lowest_weight &&
						!visited[e->to]) {
					cheapest = e;
					lowest_weight = e->weight;
				}

				e = e->next;
			}
		}
	}

	return cheapest;
}

/* NOTE: this is best implemented by a heap. we haven't covered heap yet, therefore
 * using this "manual" method.
 */
static struct edge *cheapest_edge_kruskal(struct graph *g, bool *visited)
{
	int i;
	int lowest_weight = 1000;
	struct edge *cheapest = NULL;

	for (i = 0; i <= g->highest_vertex; i++) {
		struct edge *e = g->v[i]->edges;
		while (e) {
			if (e->weight <= lowest_weight &&
					!visited[e->to]) {
				cheapest = e;
				lowest_weight = e->weight;
			}

			e = e->next;
		}
	}

	return cheapest;
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
		while (e) {
			if (e->to == to)
				return 0;
			e = e->next;
		}
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

void graph_bfs(struct graph *g, int start, void (*process_vertex)(size_t))
{
	struct vertex *v;
	struct edge *e;
	struct queue *q;
	bool *marked, *processed;

	marked = malloc(g->highest_vertex * sizeof(bool));
	memset(marked, 0, g->highest_vertex * sizeof(bool));
	processed = malloc(g->highest_vertex * sizeof(bool));
	memset(processed, 0, g->highest_vertex * sizeof(bool));
	queue_init(&q);
	v = g->v[start];

	queue_enqueue(q, v);
	marked[v->id] = true;

	while(!queue_is_empty(q)) {
		v = queue_dequeue(q);
		(*process_vertex)(v->id);
		processed[v->id] = true;
		/* now enqueue vertices connected to this one */
		e = v->edges;
		while (e) {
			if (!marked[e->to] && !processed[e->to]) {
				queue_enqueue(q, g->v[e->to]);
				marked[e->to] = true;
			}
			e = e->next;
		}
	}

	free(marked);
	free(processed);
}

size_t *graph_topological_sort(struct graph *g)
{
	int sz = g->highest_vertex + 1;
	size_t *ret = malloc(sizeof(size_t) * sz);
	int *indegree = malloc(sizeof(size_t) * sz);
	bool *processed = malloc(sizeof(size_t) * sz);
	int i, num_sorted = 0;
	int num_vertices = 0;

	memset(ret, -1, sizeof(size_t) * sz);
	memset(indegree, -1, sizeof(size_t) * sz);
	memset(processed, 0, sizeof(size_t) * sz);

	/* first build indregree array */
	for (i = 0; i <= g->highest_vertex; i++) {
		struct edge *e;

		if (!g->v[i])
			continue;

		if (indegree[i] == -1)
			indegree[i] = 0;

		num_vertices++;
		e = g->v[i]->edges;
		while (e) {
			if (indegree[e->to] == -1)
				indegree[e->to] = 0;
			indegree[e->to]++;
			e = e->next;
		}
	}

	while (num_sorted < num_vertices) {
		for (i = 0; i <= g->highest_vertex; i++) {
			struct edge *e;
			if (indegree[i] != 0 || processed[i])
				continue;
			/* here means we found a new vertex with indegree
			 * zero
			 */

			ret[num_sorted] = i;
			num_sorted++;
			processed[i] = true;
			/* decrement indegree of each node which has edge going
			 * from node i
			 */
			e = g->v[i]->edges;
			while (e) {
				indegree[e->to]--;
				e = e->next;
			}

			break;
		}

		if (i > g->highest_vertex) {
			/* we didn't find a new vertex with indegree 0 so there
			 * must be a cycle */
			free(ret);
			ret = NULL;
			goto out;
		}
	}

out:
	free(processed);
	free(indegree);
	return ret;
}

struct edge **graph_prims(struct graph *g, int *len)
{
	struct edge **mst; /* minimum spanning tree */
	int mst_idx = 0; /* next slot to fill in mst */
	bool visited[MAX_VERTICES]; /* true for vertices visited so far */
	int total = g->highest_vertex + 1;
	int vcount = 0; /* number of vertices covered so far */

	mst = malloc(sizeof(struct edge *) * (MAX_VERTICES - 1));
	memset(visited, 0, sizeof(bool) * MAX_VERTICES);

	visited[0] = true;
	vcount++;

	while (vcount < total) {
		struct edge *e = cheapest_edge_prim(g, visited);
		if (!e)
			break;

		mst[mst_idx] = e;
		/* although there is a relation between mst_idx and vcount, we
		 * keep them separate for better readability. after all the
		 * primary aim of this project is educational.
		 */
		mst_idx++;
		visited[e->to] = true;
		vcount++;
	}

	*len = mst_idx + 1;

	return mst;
}

struct edge **graph_kruskal(struct graph *g, int *len)
{
	struct edge **mst; /* minimum spanning tree */
	int mst_idx = 0; /* next slot to fill in mst */
	bool visited[MAX_VERTICES]; /* true for vertices visited so far */
	int total = g->highest_vertex + 1;
	int vcount = 0; /* number of vertices covered so far */

	mst = malloc(sizeof(struct edge *) * (MAX_VERTICES - 1));
	memset(visited, 0, sizeof(bool) * MAX_VERTICES);

	while (vcount < total) {
		struct edge *e = cheapest_edge_kruskal(g, visited);
		if (!e)
			break;

		mst[mst_idx] = e;
		mst_idx++;
		visited[e->to] = true;
		vcount++;

		/* in kruskal, both vertices could be unvisited */
		if (!visited[e->from]) {
			visited[e->from] = true;
			vcount++;
		}
	}

	*len = mst_idx + 1;

	return mst;
}
