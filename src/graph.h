#ifndef __GRAPH_H__
#define __GRAPH_H__

struct graph;

struct tree_node {
	size_t parent;
	int weight;
};

int graph_init(struct graph **g);
void graph_finit(struct graph *g);
int graph_add_edge(struct graph *g, size_t from, size_t to, int weight);

void graph_bfs(struct graph *g, int start, void (*process_vertex)(size_t));
// TODO: do graph traversal with multiple starting points
// void graph_dfs(struct graph *g, int start, void (*process_vertex)(size_t));

/* in a directed acyclic graph, topological sort traverses a node only when all
 * nodes pointing into that node have been traversed. a graph with cycles
 * can't be topologically sorted.
 *
 * returns an array of nodes sorted in topological order. caller must free
 * the returned array.
 */
size_t *graph_topological_sort(struct graph *g);

/* prim's algorithms returns minimum spanning tree (mst) of a weighted
 * undirected graph. this is a greedy algorithm. returns an array of
 * struct tree_node representing the tree.
 *
 * note that the graph passed in is indeed undirected, i.e. there
 * are two edges between each pair of connected nodes and both
 * edges have same weights.
 */
struct tree_node *graph_prims(struct graph *g);

#endif // __GRAPH_H__
