/* Another backtracking algo: generate all subsets of a given set of
 * characters. this is done by finding all permutations of an array of bools
 * where each slot in that array determines whether the element at
 * corresponding index in input array will be selected for inclusion in each
 * subset.
 */

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

void make_move(bool *selection, bool move, int *step)
{
	(*step)++;
	selection[*step] = move;
}

void unmake_move(int *step)
{
	(*step)--;
}

void subsets(char *input, size_t len, bool *selection, int idx,
		void (*process_result)(char *, bool *, size_t))
{
	bool moves[] = { false, true };
	int i;

	if (idx == len - 1) {
		process_result(input, selection, len);
		return;
	}

	/* no need to generate moves. there are only two moves at every step */
	for (i = 0; i < 2; i++) {
		make_move(selection, moves[i], &idx);
		subsets(input, len, selection, idx, process_result);
		unmake_move(&idx);
	}
}

void print_subset(char *input, bool *s, size_t len)
{
	int i;

	printf("{ ");
	for (i = 0; i < len; i++)
		if (s[i])
			printf("%c", input[i]);

	printf(" }\n");
}

int main(void)
{
	char input[] = { 'a', 'b', 'c', 'd' };
	bool selection[4] = { 0 };
	int step = -1;

	subsets(input, 4, selection, step, print_subset);

	return 0;
}
