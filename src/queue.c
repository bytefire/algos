#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "queue.h"

#define QUEUE_MAX_LEN 64

/* implemented as circular buffer */
struct queue {
	void *arr[QUEUE_MAX_LEN];
	/* NOTE that head points to the slot behind the one that
	 * will be dequeued whereas tail points to the slot where
	 * insert will take place. In other words, to dequeue we
	 * increment head first and then return the value where head
	 * points. To enqueue, we insert the value and then increment
	 * tail.
	 */
	size_t head; /* dequeue happens here */
	size_t tail; /* enqueue happens here */
};

static bool is_full(struct queue *q)
{
	return q->tail == q->head;
}

int queue_init(struct queue **q)
{
	*q = malloc(sizeof(struct queue));
	if (!*q)
		return -ENOMEM;
	(*q)->head = QUEUE_MAX_LEN - 1;
	(*q)->tail = 0;

	return 0;
}

int queue_enqueue(struct queue *q, void *val)
{
	if (is_full(q))
		return -ENOMEM;

	q->arr[q->tail] = val;
	q->tail = (q->tail + 1) % QUEUE_MAX_LEN;

	return 0;
}

void *queue_dequeue(struct queue *q)
{
	void *ret;

	if (queue_is_empty(q))
		return NULL;

	q->head = (q->head + 1) % QUEUE_MAX_LEN;
	ret = q->arr[q->head];

	return ret;
}

bool queue_is_empty(struct queue *q)
{
	return q->tail == ((q->head + 1) % QUEUE_MAX_LEN);
}
