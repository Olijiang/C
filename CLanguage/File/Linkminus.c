#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int d;
    struct Node *next;
}Node;


Node *Creat(int a[], int n)
{
    //传入一个整型数组，返回链表头节点
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
{   //传入链表头节点，打印所有节点值
    Node *p = head->next;
    while (p!=NULL)
    {
        printf("%d",p->d);
        p = p->next;
    }
    printf("\n");
}


Node *Reverse(Node *head)
{   //传入链表头节点，返回反转后的头节点
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
    LA = Reverse(LA);   //反转数组 ，从地位到高位依次相减
    LB = Reverse(LB);
    int carry=0;    //carry为借位，不够减的时候需要向下一位借位
    int i;
    Node *pla = LA;
    Node *la = LA->next;
    Node *lb = LB->next;
    while (la && lb)
    {
        if (la->d < lb->d)  //如果不够减产生借位
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
    if (la==NULL) //a 的位数比 b 少的时候， 
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
    if (carry==1)  //最后 carry 为 1 的话说明最高位仍产生借位 ，结果为负数
    {
        /*  比如 123 - 456 = -333，反转后对应位相减结果为 321 - 654 = 766；
            carry=1，表示最终结果是负数 ；处理方法是 是对所有位 9-x；最后 第一位再 +1；
            9-7+1=3； 9-6=3； 9-6=3
            结果为 -333；
        */
        while (la!=NULL)
        {
            la->d = 9 - la->d;     //用 9 减所有位
            la = la->next;
        }
        LA->next->d++; //个位数修正
        printf("-");
    }

    la = LA;
    while (la->next->d == 0)    // 将头节点定位到第一个非 0 元素前面
        la = la->next;
    la = Reverse(la);
    if (carry==1)   // 用头节点标记正负
        la->d = -1;
    else la->d = 1;

    Show(la); 
    //返回结果链表头节点，头节点为-1表示结果为负数，1表示结果非负；
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
