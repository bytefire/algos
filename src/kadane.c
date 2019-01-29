/* Kadane's Algorithm: find max sum of a sub-array */
#include <stdlib.h>
#include <stdio.h>

int kadane(int a[], int len)
{
	int global_max = -9999; /* or a constant representing minimum value */
	int max_ending_here = 0;
	int i;
	int start_index = 0, end_index = 0;
	int curr_start_index = 0;

	for (i = 0; i < len; i++) {
		max_ending_here += a[i];
		if (max_ending_here > global_max) {
			global_max = max_ending_here;
			end_index = i;
			start_index = curr_start_index;
		}

		/* reset if max_so_far is negative as it will only make
		 * the sum smaller
		 */
		if (max_ending_here < 0) {
			max_ending_here = 0;
			curr_start_index = i + 1;
		}
	}

	printf("max = %d, start index = %d, end index = %d\n",
			global_max, start_index, end_index);
	return global_max;
}

int main(void)
{
	int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};

	kadane(a, sizeof(a)/sizeof(a[0]));

	return 0;
}
