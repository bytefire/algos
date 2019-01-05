/* backtracking: a child can climb 1, 2 or 3 stairs in one step. count (we also
 * list) the number of ways in which they can climb n stairs.
 * this is problem 8.1 in cracking coding interview 6th edition.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STEPS 64

struct state {
	int path[MAX_STEPS];
	int k;
	int steps_count;
	int ways;
};

void generate_moves(int moves[3], int *count, int steps_left)
{
	moves[0] = 1;
	moves[1] = 2;
	moves[3] = 3;

	*count = steps_left >= 3 ? 3 : steps_left;
}

void make_move(struct state *s, int move)
{
	s->k++;
	s->path[s->k] = move;
	s->steps_count += move;
}

void unmake_move(struct state *s)
{
	s->steps_count -= s->path[s->k];
	s->k--;
}

void print_path(struct state *s)
{
	int i;

	printf("path %d: ", s->ways);
	for (i = 0; i <= s->k; i++)
		printf("%d, ", s->path[i]);

	printf("\n");
}

void nsteps(struct state *s, int steps_left)
{
	int moves[3];
	int count, i;

	if (steps_left == 0) {
		s->ways++;
		print_path(s);
		return;
	}

	generate_moves(moves, &count, steps_left);

	for (i = 0; i < count; i++) {
		make_move(s, moves[i]);
		nsteps(s, steps_left - moves[i]);
		unmake_move(s);
	}
}

int main(void)
{
	struct state *s = malloc(sizeof(struct state));

	memset(s, 0, sizeof(struct state));
	s->k = -1;
	nsteps(s, 3);

	return 0;
}
