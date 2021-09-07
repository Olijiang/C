/* 
��������?�ǿ� ��������ʾ�����Ǹ�������������ÿλ���ֶ��ǰ���?����?�ķ�ʽ�洢�ģ�����ÿ���ڵ�ֻ�ܴ洢?һλ?���֡�

���㽫��������ӣ�������ͬ��ʽ����һ����ʾ�͵�����


 */
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
}Node;

Node *Creat(int a[], int n)
{
    //����һ���������飬��������ͷ�ڵ�
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
{   //��������ͷ�ڵ㣬��ӡ���нڵ�ֵ
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
