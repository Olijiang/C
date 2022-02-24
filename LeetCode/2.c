/* 
给你两个非空 的链表，表示两个非负的整数。它们每位数字都是按照?逆序?的方式存储的，并且每个节点只能存储?一位?数字。

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
    int more=0;
    int t, n1, n2;
    struct ListNode* l3=NULL;
    struct ListNode* ls=NULL;
    struct ListNode* tmp=NULL;
    while(l1 || l2 ){
        n1 = l1?l1->val:0;
        n2 = l2?l2->val:0;
        t = n1 + n2 + more;
        more = t/10;
        t = t%10;
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = t;
        tmp->next = NULL;
        if(l1) l1 = l1->next;
        if(l2) l2 = l2->next;
        if(!l3) {
            l3 = tmp;
            ls = l3;
            continue;
        }
        ls->next = tmp;
        ls = tmp;
    }
    if (more!=0){
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = more;
        tmp->next = NULL;
        ls->next = tmp;
    }

    return l3;
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
