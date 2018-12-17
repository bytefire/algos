#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 32

struct input {
	const char *str;
	int spaces[MAX_LEN];
	int scount;
};

static const char *dictionary[] = { "steal", "i", "stealing", "one", "money" };
static int dictionary_count = 5;

static int is_word(const char *s, int len)
{
	int i;

	for (i = 0; i < dictionary_count; i++)
		if ((strncmp(s, dictionary[i], len) == 0) &&
				len == strlen(dictionary[i]))
			return 1;

	return 0;
}

static int is_solution(struct input *in)
{
	int start = in->spaces[in->scount];
	int len = strlen(in->str) - start;
	/* check that the last word is actually a word. all before it
	 * must be words. that is verified by generate_moves() function
	 * always returning valid words only.
	 */
	return is_word(in->str + start, len);
}

static void print_solution(struct input *in)
{
	int i, j;

	for (i = 1; i <= in->scount; i++) {
		for (j = in->spaces[i - 1]; j < in->spaces[i]; j++)
			printf("%c", in->str[j]);
		printf(" ");
	}

	for (j = in->spaces[in->scount]; j < strlen(in->str); j++)
		printf("%c", in->str[j]);

	printf(".\n");
}

static void generate_moves(struct input *in, int *m, int *count)
{
	int len;
	int start = in->spaces[in->scount];

	*count = 0;
	for (len = 1; len < strlen(in->str) - start; len++) {
		if (is_word(in->str + start, len)) {
			m[*count] = len;
			*count = *count + 1;
		}
	}
}

static void make_move(struct input *in, int m)
{
	in->spaces[in->scount + 1] = in->spaces[in->scount] + m;
	in->scount++;
}

static void unmake_move(struct input *in)
{
	in->scount--;
}

void unconcatenate(struct input *in)
{
	int m[MAX_LEN];
	int count;
	int i;

	if (is_solution(in)) {
		print_solution(in);
		return;
	}

	generate_moves(in, m, &count);
	for (i = 0; i < count; i++) {
		make_move(in, m[i]);
		unconcatenate(in);
		unmake_move(in);
	}
}

int main(void)
{
	struct input in = {
		.str = "stealimoney",
		.spaces = { 0 },
		.scount = 0,
	};

	unconcatenate(&in);

	return 0;
}
