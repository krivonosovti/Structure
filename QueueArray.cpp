#include <iostream>

typedef int element_t;
constexpr auto QUEUE_MAX = 100;;

struct queue
{
	element_t data[QUEUE_MAX];
	size_t head, tail;
};

queue * queue_alloc()
{
	queue* q = (queue*)malloc(sizeof(*q));
	if (!q) return NULL;
	
	q->head = q->tail = QUEUE_MAX;
	return q;
}

void queue_free(queue* q)
{
	free(q);
}

queue* queue_clone(queue* q)
{
	queue* n = (queue*)malloc(sizeof(*n));
	if (!n)
		return NULL;
	*n = *q;
	return n;
}

int queue_is_empty(queue* q)
{
	return q->head == QUEUE_MAX;
}

int queue_is_full (const queue* q)
{
	return (q->tail - 1) % QUEUE_MAX == q->head;
}

int queue_push(queue* q, element_t e)
{
	if (queue_is_empty(q))
	{
		q->data[0] = e;
		q->head = q->tail = e;
	}
	if (queue_is_full(q))
		return 1;
	q->tail = (q->tail + 1) % QUEUE_MAX;
	q->data[q->tail] = e;
	return 0;
}

int queue_pop(queue* q, element_t* e)
{
	if (queue_is_empty(q))
		return 1;
	if (q->head == q->tail)
	{
		if (e) *e = q->data[q->head];
		q->head = q->tail = QUEUE_MAX;
		return 0;
	}
	if (e)
		*e = q->data[q->head];
	q->head = (q->head + 1) % QUEUE_MAX;
	return 0;
}

const element_t* queue_get_front(const queue* q)
{
	return q->head == QUEUE_MAX ? NULL : &(q->data[q->head]);
}
