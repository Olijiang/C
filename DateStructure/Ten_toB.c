#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define mixsize 50
int IsEmpty_Stack();
int IsFull_Stack();

typedef struct stack
{
	int a[mixsize];
	int top;
}stack;

stack *InitStack()
{
	stack *p = (stack *)malloc(sizeof(stack));
	p->top = -1;
	return p;
}

int Stack_Pop(stack *s)
{
	if(IsEmpty_Stack(*s)) return 0;
	int x = (s->a)[s->top--];
	return x;
}

int Stack_Push(stack *s, int x)
{
	if(IsFull_Stack(*s)) return 0;
	(s->a)[++s->top] = x;
	return 1;
}

int IsEmpty_Stack(stack s)
{
	return (s.top == -1)?(1):(0);
}

int IsFull_Stack(stack s)
{
	return (s.top == mixsize-1)?(1):(0);
}

void show(stack s)
{
	while(s.top!=-1) printf("%d", (s.a)[s.top--]);
}

int Cacu(stack s)
{
	int a=0, n=0, v=0;
	while(n<=s.top)
	{
		a = (s.a)[n];
		v = v + pow(2, n++)*a;
	}
	return v;
}

int main()
{
	stack s = *InitStack();
	int a = 999;
	int b, c;
	while(a>0)
	{
		Stack_Push(&s, a%2);
		a = a/2;
	}
	show(s);
	printf("\n");
	printf("\nv = %d ", Cacu(s));
	return 0;
}
