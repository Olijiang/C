#include <stdio.h>
#include <stdlib.h>
#define mixsize 5

int IsEmpty_Queue();
int IsFull_Queue();

typedef struct queue
{
	int que[mixsize];
	int front;
	int rear;
}Queue;

Queue *InitQueue()
{
	Queue *p = (Queue *)malloc(sizeof(Queue));
	p->front = 0;
	p->rear = 0;
	return p;
}

int In_Queue(Queue *q,int x)
{
	if (IsFull_Queue(*q)) return 0;
	q->rear = ((q->rear+1)%mixsize);
	q->que[q->rear] = x;
	return 1;
}

int Out_Queue(Queue *q)
{
	if (IsEmpty_Queue(*q)) return 0;
	int x;
	q->front = ((q->front+1)%mixsize);
	x = q->que[q->front];
	return x;
}

int IsEmpty_Queue(Queue q)
{
	return (q.front == q.rear)?(1):(0);
}

int IsFull_Queue(Queue q)
{
	return (q.front == (q.rear+1)%mixsize)?(1):(0);
}

int main(int argc, char const *argv[])
{
	int a[] = {1,2,3,4};
	int x;
	int n = sizeof(a)/sizeof(a[0]);
	Queue q = *InitQueue();
	//printf("%s\n",(IsEmpty_Queue(q)?("Empty"):("Not Empty")));

	for (int i = 0; i < n; ++i)	In_Queue(&q,a[i]);

	//printf("rear = %d , front = %d\n", q.rear, q.front);
	//printf("%s\n",(IsFull_Queue(q)?("Full"):("Not Full")));

	while(!IsEmpty_Queue(q)) printf("%d  ", Out_Queue(&q));//全部出队
	printf("\n");

	//printf("%s\n",(IsEmpty_Queue(q)?("Empty"):("Not Empty")));
	In_Queue(&q,5);

	while(!IsEmpty_Queue(q)) printf("%d  ", Out_Queue(&q));

	printf("%d\n", -4%6);

	return 0;
}