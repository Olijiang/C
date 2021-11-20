#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int d;
    struct Node *next;
}Node;


Node *Creat(int a[], int n)
{
    //����һ���������飬��������ͷ�ڵ�
    Node *head = (Node *)malloc(sizeof(Node));
    Node *p, *q = head;
    for (int i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->d = a[i];
        q->next = p;
        q = p;
    }
    p->next = NULL;
    return head;
}

void Show(Node *head)
{   //��������ͷ�ڵ㣬��ӡ���нڵ�ֵ
    Node *p = head->next;
    while (p!=NULL)
    {
        printf("%d",p->d);
        p = p->next;
    }
    printf("\n");
}


Node *Reverse(Node *head)
{   //��������ͷ�ڵ㣬���ط�ת���ͷ�ڵ�
    Node *p = head->next;
    Node *q;
    while (p->next!=NULL)
    {
        q = p->next;
        p->next = q->next;
        q->next = head->next;
        head->next = q;
    }
    return head;
}


Node *Minus(Node *LA, Node *LB)
{
    //LA - LB
    LA = Reverse(LA);   //��ת���� ���ӵ�λ����λ�������
    LB = Reverse(LB);
    int carry=0;    //carryΪ��λ����������ʱ����Ҫ����һλ��λ
    int i;
    Node *pla = LA;
    Node *la = LA->next;
    Node *lb = LB->next;
    while (la && lb)
    {
        if (la->d < lb->d)  //���������������λ
        {
            la->d = la->d - lb->d + 10 - carry;
            carry = 1;
        }
        else
        {
            la->d = la->d - lb->d - carry;
            carry = 0;
        }
        la = la->next;
        lb = lb->next;
        pla = pla->next;
    }
    if (la==NULL) //a ��λ���� b �ٵ�ʱ�� 
    {
        pla->next = lb;
        while (lb!=NULL)
        {
            lb->d = 0 - lb->d + 10 - carry;
            carry = 1;
            lb = lb->next;
        }
    }
    la = LA->next;
    if (carry==1)  //��� carry Ϊ 1 �Ļ�˵�����λ�Բ�����λ �����Ϊ����
    {
        /*  ���� 123 - 456 = -333����ת���Ӧλ������Ϊ 321 - 654 = 766��
            carry=1����ʾ���ս���Ǹ��� ���������� �Ƕ�����λ 9-x����� ��һλ�� +1��
            9-7+1=3�� 9-6=3�� 9-6=3
            ���Ϊ -333��
        */
        while (la!=NULL)
        {
            la->d = 9 - la->d;     //�� 9 ������λ
            la = la->next;
        }
        LA->next->d++; //��λ������
        printf("-");
    }

    la = LA;
    while (la->next->d == 0)    // ��ͷ�ڵ㶨λ����һ���� 0 Ԫ��ǰ��
        la = la->next;
    la = Reverse(la);
    if (carry==1)   // ��ͷ�ڵ�������
        la->d = -1;
    else la->d = 1;

    Show(la); 
    //���ؽ������ͷ�ڵ㣬ͷ�ڵ�Ϊ-1��ʾ���Ϊ������1��ʾ����Ǹ���
    return la;
}


int main()
{
    int ma[10] = {5,0,1,5,4};
    int mb[10] = {2,3,5,0,6,1};
    Node *LA = Creat(ma, 5);
    Node *LB = Creat(mb, 6);

    Show(LA);
    Show(LB);

    Minus(LA, LB);
    return 0;
}
