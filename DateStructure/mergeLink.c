#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *next;
}Node;

void initialist(Node **head)
{
	(*head) = (Node *)malloc(sizeof(Node));
	(*head)->next = NULL;
}

void add_data(Node **tail, int *data, int n)
{
	Node *p = NULL;
	for (int i = 0; i < n; ++i)
	{
		p = (Node *)malloc(sizeof(Node));
		p->data = data[i];
		p->next = (*tail)->next;
		(*tail)->next = p;
		(*tail) = p;
	}
}

void showlist(Node *head)
{
	Node *p = head->next;
	while(p->next!=NULL)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("%d ",p->data);
}

void merge(Node *head_a, Node *head_b)
{
	//把两个有序链表合并为一个有序链表， 头节点不存放数据
	Node *a = head_a->next, *b = head_b->next, *t, *pa = head_a;//a,b为遍历节点，pa是a的前驱节点.
	free(head_b);
	while(a->next != NULL && b != NULL) //当a的下一个节点，b节点都不为空时，将b中的元素插入a中，而b->next!=NULL,会遗留下b的最后一个节点未处理.
	{									//这里若采用a！=NULL作为条件，在循环结束时a为NULL，pa为a链表的最后一个节点，没办法在pa节点之前插入数据.
		if(a->data > b->data) //a>b,把b插入到a前面
		{
			t = b->next;
			b->next = pa->next;
			pa->next = b;
			b = t;
			pa = pa->next;
		}
		else if(a->data < b->data)//a<b，换下一个a
		{
			a = a->next;
			pa = pa->next;
		}
		else //a==b，删除b节点，换下一个b
		{
			t = b;
			b = b->next;
			free(t);
		}
		//执行完毕可能的情况 1.不满足条件 b!= NULL，此时b为NULL，说明b中节点全部插入到a中，合并完成
		// 2.不满足条件 a->next != NULL，此时a->next为NULL，a指向a链表的最后一个节点，b指向剩余b链表的第一个节点。还需要判断b的后续节点和a的最后一个节点的大小关系。
	}
	while(b != NULL) //若不满足条件2,确定b的后续节点和a的最后节点的次序
	{
		if(a->data < b->data)//若a小于b的第一个节点，将b连在a后即可
		{
			a->next = b;
			break;
		}
		else if(a->data > b->data) //若a>b，将b连在a前面，换下一个b
		{
			t = b->next;
			b->next = pa->next;
			pa->next = b;
			b = t;
			pa = pa->next;
		}
		else
		{
			t = b;
			b = b->next;
			free(t);
		}
	}
}

void inverse(Node *head)
{
	Node *p=head->next, *r=NULL;
	while(p->next != NULL)
	{
		r = p->next;
		p->next = r->next;
		r->next = head->next;
		head->next = r;
	}
}

int find_Numk(Node *head, int k)
{
	//find 链表的倒数第 k 个数
	Node *r = head;
	int n = 0, i;
	while(r->next!=NULL)
	{
		n++;
		r = r->next;
	}
	if(k>n) return 0;
	r = head;
	for(i=0;i<n-k+1;i++)
		r = r->next;
	printf("%d\n", r->data);
}

void reprint(Node *head)
{
	//逆序打印链表
	if(head->next != NULL)
	{
		reprint(head->next);
		printf("%d ", head->next->data);
	}
}

int main()
{
	int a[] = {1,3,5,7,9,500,600,1000};
	int b[] = {2,3,4,6,8,10,12,50,100,800,1500};

	Node *head_a = NULL;
	Node *tail_a = NULL;

	Node *head_b = NULL;
	Node *tail_b = NULL;

	initialist(&head_a);
	tail_a = head_a;
	initialist(&head_b);
	tail_b = head_b;

	add_data(&tail_a, a, sizeof(a)/sizeof(a[0]));
	add_data(&tail_b, b, sizeof(b)/sizeof(b[0]));
	//showlist(head_a);
	//printf("\n");
	//showlist(head_b);
	//printf("\n");
	merge(head_a, head_b);
	showlist(head_a);
	printf("\n");
	//inverse(head_a);
	//showlist(head_a);
	/* code */
	//find_Numk(head_a, 1);
	//reprint(head_a);
	return 0;
}