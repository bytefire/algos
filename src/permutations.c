/* This shows how to generate all possible permutations.
 * Technique: Backtracking
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct permut {
	char *a;
	int len;
	int idx;
	bool *taken;
};

void make_move(struct permut *p, int move, char *input)
{
	p->idx++;
	p->a[p->idx] = input[move];
	p->taken[move] = true;
}

void unmake_move(struct permut *p, int move)
{
	p->idx--;
	p->taken[move] = false;
}

void permute(char *input, size_t len, struct permut *p, void (*process_result)(char *, size_t))
{
	int i;

	if (p->idx == p->len - 1) {
		process_result(p->a, p->len);
		return;
	}

	/* our generate_moves() does nothing because p->taken maintains the
	 * info needed for generating moves
	 */
	for (i = 0; i < len; i++) {
		if (p->taken[i])
			continue;

		make_move(p, i, input);
		permute(input, len, p, process_result);
		unmake_move(p, i);
	}
}

static void print_permut(char *s, size_t len)
{
	int i;

	for (i = 0; i < len; i++)
		printf("%c", s[i]);
	printf("\n");
}

int main(void)
{
	char input[5] = { 'a', 'b', 'c', 'd', 'e' };
	struct permut p;
	p.a = malloc(3);
	p.len = 3;
	p.idx = -1;
	p.taken = malloc(5);
	memset(p.taken, 0, 5);

	// TODO: implement print_permut
	permute(input, 5, &p, print_permut);

	return 0;
}
