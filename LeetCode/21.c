/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 * 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode {
      int val;
      struct ListNode *next;
}Node;

void add_data(Node **tail, int *data, int n)
{
	Node *p = NULL;
	for (int i = 0; i < n; ++i)
	{
		p = (Node *)malloc(sizeof(Node));
		p->val = data[i];
		p->next = (*tail)->next;
		(*tail)->next = p;
		(*tail) = p;
	}
}


struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){

	struct ListNode *a = l1, *b = l2, *t, *pa;
	while(a!= NULL && b != NULL) 
	{
		if(a->val > b->val) //a>b,把a插入到b后面
		{
            pa = a;
            a = a->next;
            pa->next = b->next;
			b->next = pa;
            b = b->next;
		}
		else//把b插入到a后面
		{
			pa = b;
            b = b->next;
            pa->next = a->next;
            a->next = pa;
            a = a->next;
		}
	}
    if(l1->val > l2->val) return l1;
    else return l2;
}


int main(int argc, char const *argv[])
{
    int A[] = {1,3,4};
    int B[] = {1,2,4};

    return 0;  
}
