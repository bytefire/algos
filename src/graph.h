#ifndef __GRAPH_H__
#define __GRAPH_H__

struct graph;

int graph_init(struct graph **g);
void graph_finit(struct graph *g);
int graph_add_edge(int from, int to, int weight);

void graph_bfs(struct graph *g);
void graph_dfs(struct graph *g);

#endif // __GRAPH_H__
