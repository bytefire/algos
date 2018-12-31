/* convert an array sorted in increasing order, into a binary search tree of
 * minimum height. from cracking coding interview, chapter 4 Trees and Graphs,
 * problem 4.2.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

struct node {
	int val;
	struct node *left;
	struct node *right;
};

struct node *create_node(int val)
{
	struct node *n = malloc(sizeof(struct node));
	n->val = val;
	n->left = NULL;
	n->right = NULL;

	return n;
}

struct node *array2bst(int *arr, size_t len)
{
	struct node *n;
	size_t mid;

	if (len == 0)
		return NULL;
	if (len == 1)
		return create_node(arr[0]);

	mid = len / 2;
	mid += len % 2;

	n = create_node(arr[mid - 1]);
	n->left = array2bst(arr, mid - 1);
	n->right = array2bst(arr + mid, MIN(mid, (len - mid)));

	return n;
}

void inorder(struct node *n)
{
	if (!n)
		return;

	inorder(n->left);
	printf("%d, ", n->val);
	inorder(n->right);
}

int main(void)
{
	int arr[6] = { 1, 4, 5, 6, 8, 10 };
	struct node *n = array2bst(arr, 6);

	inorder(n);
	printf("\n");

	return 0;
}
