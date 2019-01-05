/* backtracking: problem 8.2 of cracking coding interview, 6th edition. given a
 * robot in a grid's top left corner, find a path to bottom right corner. robot
 * can only move down or right. some slots in the grid may be no-go.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define DOWN 0
#define RIGHT 1
#define MAX_LEN 32

struct pos {
	int row;
	int column;
};

struct grid {
	bool a[MAX_LEN][MAX_LEN];
	int rows;
	int columns;
};

void generate_moves(int moves[2], int *count, struct pos *p, struct grid *g)
{
	*count = 0;
	if (p->row + 1 < g->rows && g->a[p->row+1][p->column]) {
		moves[*count] = DOWN;
		(*count)++;
	}

	if (p->column + 1 < g->columns && g->a[p->row][p->column + 1]) {
		moves[*count] = RIGHT;
		(*count)++;
	}
}

void make_move(struct pos *p, int dir, int a[], int *k)
{
	if (dir == DOWN)
		p->row++;
	else if (dir == RIGHT)
		p->column++;
	else {
		printf("ERROR: Invalid direction\n");
		return;
	}

	a[*k] = dir;
	(*k)++;
}

void unmake_move(struct pos *p, int dir, int *k)
{
	if (dir == DOWN)
		p->row--;
	else if (dir == RIGHT)
		p->column--;
	else {
		printf("ERROR: Invalid direction\n");
		return;
	}
	(*k)--;
}

bool is_solution(struct grid *g, struct pos *p)
{
	return (p->row == g->rows - 1 && p->column == g->columns - 1);
}

void print_solution(int a[], int k)
{
	int i;
	for (i = 0; i < k; i++) {
		char *m = a[i] == DOWN ? "DOWN" : "RIGHT";
		printf("%s -> ", m);
	}

	printf("END\n");
}

void maze(struct grid *g, struct pos *p, int a[], int k)
{
	static bool found_solution = false;
	int moves[2];
	int count, i;

	if (is_solution(g, p)) {
		found_solution = true;
		print_solution(a, k);

		return;
	}

	generate_moves(moves, &count, p, g);
	for (i = 0; i < count && !found_solution; i++) {
		make_move(p, moves[i], a, &k);
		maze(g, p, a, k);
		unmake_move(p, moves[i], &k);
	}
}

int main(void)
{
	struct grid g;
	struct pos p;
	int a[2*MAX_LEN];
	int k = 0;

	memset(&g, 1, sizeof(struct grid));
	g.rows = g.columns = 4;
	g.a[1][1] = false;
	g.a[1][2] = false;
	g.a[1][3] = false;
	g.a[2][2] = false;

	p.row = p.column = 0;

	maze(&g, &p, a, k);
}
