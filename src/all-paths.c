/* backtracking problem: list all paths between two nodes in a directed
 * graph. Note that we don't consider paths containing loops as valid. for
 * example in following, A->B->E->F->B->C->D is not a a separate path betweeb
 * A and D. so the only path is A->B->C->D.
 *
 *
 * A -> B -> C -> D
 *     ^  \
 *     |   \
 *     |    v
 *     F <-- E
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VERTICES 64

struct edge {
	int to;
	int weight;
	struct edge *next;
};

struct graph {
	struct edge *nodes[MAX_VERTICES];
};

void generate_moves(struct graph *g, int node, int moves[MAX_VERTICES],
		int *count, bool visited[MAX_VERTICES])
{
	int i = 0;
	struct edge *e;

	e = g->nodes[node];

	while (e) {
		if (!visited[e->to]) {
			moves[i] = e->to;
			i++;
		}

		e = e->next;
	}

	*count = i;
}

void make_move(int a[MAX_VERTICES], int *k, int move, bool visited[MAX_VERTICES])
{
	*k = *k + 1;
	a[*k] = move;
	visited[move] = true;
}

void unmake_move(int *k, int move, bool visited[MAX_VERTICES])
{
	*k = *k - 1;
	visited[move] = false;
}

void print_path(int a[MAX_VERTICES], int len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%d -> ", a[i]);

	printf("[X]\n");
}

/* list all paths from node n1 to node n2 */
void all_paths(struct graph *g, int *a, int k, int target, bool *visited)
{
	int moves[MAX_VERTICES];
	int count, i;

	if (a[k] == target) {
		print_path(a, k + 1);
		return;
	}

	generate_moves(g, a[k], moves, &count, visited);

	for (i = 0; i < count; i++) {
		make_move(a, &k, moves[i], visited);
		all_paths(g, a, k, target, visited);
		unmake_move(&k, moves[i], visited);
	}
}

int main(void)
{
	struct graph *g = malloc(sizeof(struct graph));
	int a[MAX_VERTICES];
	int k, target, start;
	bool visited[MAX_VERTICES];

	/* 0 -> 1 -> 2 -> 3
	 *      |         ^
	 *      |         |
	 *      v         |
	 *      4 -> 5 ---|
	 */
	struct edge e0, e1, e2, e3, e4, e5;

	/* node 0 */
	e0.to = 1;
	e0.next = NULL;
	g->nodes[0] = &e0;

	/* node 1 */
	e1.to = 2;
	e1.next = &e3;
	e3.to = 4;
	e3.next = NULL;
	g->nodes[1] = &e1;

	/* node 2 */
	e2.to = 3;
	e2.next = NULL;
	g->nodes[2] = &e2;

	/* node 3 */
	g->nodes[3] = NULL;

	/* node 4 */
	e4.to = 5;
	e4.next = NULL;
	g->nodes[4] = &e4;

	/* node 5 */
	e5.to = 3;
	e5.next = NULL;
	g->nodes[5] = &e5;

	start = 0;
	target = 3;
	memset(visited, 0, sizeof(bool) * MAX_VERTICES);
	k = 0;
	a[k] = start;
	visited[start] = true;

	all_paths(g, a, k, target, visited);

	free(g);

	return 0;
}
