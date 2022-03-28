#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int val;
	struct Node *next;
}Node;

void initialist(Node **head)
{
	(*head) = (Node *)malloc(sizeof(Node));
	(*head)->next = NULL;
}

void add_val(Node **tail, int *val, int n)
{
	Node *p = NULL;
	for (int i = 0; i < n; ++i)
	{
		p = (Node *)malloc(sizeof(Node));
		p->val = val[i];
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
		printf("%d ",p->val);
		p = p->next;
	}
	printf("%d ",p->val);
}

 Node* mergeTwoLists(Node* list1, struct Node* list2){
	//把两个有序链表合并为一个有序链表,头节点存放数据时
    if(list1 == NULL && list2 == NULL) return NULL; 
    if(list1 == NULL) return list2;
    if(list2 == NULL) return list1;

	//struct Node *a = list1->next, *b = list2->next, *t, *prea=list1; //如果带空头节点

	struct Node *a = list1, *b = list2, *t, *prea=NULL;//a的前一个节点
	while(b && a) 
	{
		if(a->val >= b->val) //a>b,把b插入到a前面
		{
			t = b;
            b = b->next;
            t->next = a;

            if(!prea) {
                prea = t;
                list1 = t;  //更新 list1
            }
            else{
                prea->next = t;
                prea = t;
            }

			/* 如果带空头节点
			prea->next = t;
            prea = t;
			 */
		}
		else //a<b，换下一个a
		{
            if(!prea) prea = a;
            else prea = prea->next;
            a = a->next;
			/* 如果带空头节点
			prea = prea->next;
            a = a->next;
			 */
		}
		//执行完毕可能的情况 1. b== NULL，说明b中节点全部插入到a中，合并完成
		// 2. a == NULL，把b连到prea后面即可
	}
    if(!a) prea->next = b;
    return list1;
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
	printf("%d\n", r->val);
}

void reprint(Node *head)
{
	//逆序打印链表
	if(head->next != NULL)
	{
		reprint(head->next);
		printf("%d ", head->next->val);
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

	add_val(&tail_a, a, sizeof(a)/sizeof(a[0]));
	add_val(&tail_b, b, sizeof(b)/sizeof(b[0]));
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