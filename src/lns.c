#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct last {
	bool seen;
	int idx;
};

int lns(const char *str)
{
	int len = strlen(str);
	int l, r;
	int max, curr;
	struct last last[26];

	memset(last, 0, 26 * sizeof(struct last));
	curr = max = 0;

	while (r < len) {
		int c = str[r] - 'a';
		if (last[c].seen && last[c].idx >= l) {
			int delta = last[c].idx - l;
			curr -= (delta + 1);
			l += delta + 1;
		}

		last[c].seen = true;
		last[c].idx = r;
		r++;
		curr++;
		if (curr > max) max = curr;
	}

	return max;
}

int main(void)
{
	const char *input = "abcdefghcijklalljzx";
	int len = lns(input);

	printf("length of longest non-repeating substring = %d\n", len);

	return 0;
}
