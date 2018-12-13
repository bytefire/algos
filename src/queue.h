#ifndef __QUEUE_H__
#define __QUEUE_H__

struct queue;

int queue_init(struct queue **q);
int queue_enqueue(struct queue *q, void *val);
void *queue_dequeue(struct queue *q);
bool queue_is_empty(struct queue *q);

#endif // __QUEUE_H__
