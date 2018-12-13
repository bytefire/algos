#ifndef __GRAPH_H__
#define __GRAPH_H__

struct graph;

int graph_init(struct graph **g);
void graph_finit(struct graph *g);
int graph_add_edge(struct graph *g, size_t from, size_t to, int weight);

void graph_bfs(struct graph *g, int start, void (*process_vertex)(size_t));
// TODO: do graph traversal with multiple starting points
// void graph_dfs(struct graph *g, int start, void (*process_vertex)(size_t));

#endif // __GRAPH_H__
