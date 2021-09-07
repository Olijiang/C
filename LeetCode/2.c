/* 
给你两个?非空 的链表，表示两个非负的整数。它们每位数字都是按照?逆序?的方式存储的，并且每个节点只能存储?一位?数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。


 */
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
}Node;

Node *Creat(int a[], int n)
{
    //传入一个整型数组，返回链表头节点
    Node *head = (Node *)malloc(sizeof(Node));
    Node *p, *q = head;
    for (int i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->val = a[i];
        q->next = p;
        q = p;
    }
    p->next = NULL;
    return head;
}


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int bo=0, sum=0;
    struct ListNode* a=l1, *b=l2, *prea, *preb, *p;
    p = (struct ListNode*)malloc(sizeof(struct ListNode));
    while(a!=NULL && b!=NULL)
    {
        sum = a->val + b->val + bo;
        bo = sum/10;
        a->val = sum%10;
        prea = a;
        preb = b;
        a = a->next;
        b = b->next;
    }
    if(a!=NULL)
    {
        while(a!=NULL)
        {
            a->val += bo;
            bo = a->val/10;
            a->val = a->val%10; 
            prea = a;
            a=a->next;
        }
    }
    else
    {
        prea->next = b;
        while(b!=NULL)
        {
            b->val += bo;
            bo = b->val/10;
            b->val = b->val%10;
            prea = b; 
            b=b->next;
        }
    }
    if(bo==0) return l1;
    p->val = 1;
    p->next = NULL;
    prea->next = p;
    return l1; 
}

void Show(Node *head)
{   //传入链表头节点，打印所有节点值
    Node *p = head;
    while (p!=NULL)
    {
        printf("%d",p->val);
        p = p->next;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int A[] = {9,9,9,9,9,9,9};
    int B[] = {9,9,9,9};
    Node *la = Creat(A, 7);
    Node *lb = Creat(B, 4);
    la = addTwoNumbers(la->next, lb->next);
    Show(la);
    return 0;
}
