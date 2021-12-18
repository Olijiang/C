#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int d;
    struct Node *next;
}Node;

char *input();
void Show(Node *head);


Node *Creat(char *s)
{
    
    int n = strlen(s);
    //printf("%d",n);
    Node *head = (Node *)malloc(sizeof(Node));
    Node *p, *q = head;
    head->d = 0;
    for (int i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->d = s[i]-'0';
        q->next = p;
        q = p;
    }
    p->next = NULL;
    return head;
}

char *input()
{
    // 字符串动态长度输入
    // 返回字符指针
    int n = 0, len=10; 
    char c;
    char *ch = (char *)malloc(len);
    char *sh = NULL;
    while((c = getchar())!='\n')
    {
        if (n<len)
            ch[n++] = c;
        else
        {
            len+=10;
            sh = (char *)malloc(len);
            if (sh==NULL) return NULL;
            strcpy(sh,ch);
            ch = sh;
            ch[n++] = c;
        }
    }
    ch[n++] = '\0';
    return ch;
}

void Show(Node *head)
{   //传入链表头节点，打印所有节点值，头节点值反映负号
    Node *p = head->next;
    if (head->d == -1) printf("-");    
    while (p!=NULL)
    {
        printf("%d",p->d);
        p = p->next;
    }
    //printf("\n");
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
    LA = Reverse(LA);   //反转数组 ，从底位到高位依次相减
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
    if (la==NULL) //case1：a 的位数比 b 少的时候， 把剩下的 b 接到 a 后面
    {
        pla->next = lb;
        while (lb!=NULL)
        {
            lb->d = 0 - lb->d + 10 - carry;
            carry = 1;
            lb = lb->next;
        }
    }
    else    //case2：a 的位数比 b 多的时候，
    {
        while (la!=NULL && carry)
        {
            if(la->d==0)  la->d = la->d + 10 - carry;
            else 
            {
                la->d = la->d - carry;
                carry=0;
            }
            la = la->next;
        }
    }
    la = LA->next;
    if (carry==1)  //最后 carry 为 1 的话说明最高位仍产生借位 ，结果为负数
    {
        /*  
        * 比如 123 - 456 = -333，反转后对应位相减结果为 321 - 654 = 766；
        * carry=1，表示最终结果是负数；处理方法是对所有位 9-x；第一位再 +1；
        * 9-7+1=3； 9-6=3； 9-6=3
        * 结果为 -333；
        */
        while (la!=NULL)
        {
            la->d = 9 - la->d;     //用 9 减所有位
            la = la->next;
        }
        LA->next->d++; //个位数修正
    }

    la = LA;
    la = Reverse(la);
    while (la->next->d == 0)    // 将头节点定位到第一个非 0 元素前面,结果为0要特殊考虑
        {
            if(la->next->next!=NULL) la = la->next; 
            else   
            {
                la->next->d = 0;
                break;
            }
        }
    if (carry==1)   // 用头节点标记正负
        la->d = -1;
    else la->d = 1;

    Show(la); 
    //返回结果链表头节点，头节点为-1表示结果为负数，1表示结果非负；
    return la;
}

int main()
{
    while (1)
    {
        printf("Input a:");
        char *sa = input();
        if (sa[0] == '\0') break;
        Node *LA = Creat(sa);

        printf("Input b:");
        char *sb = input();
        if (sb[0] == '\0') break;
        Node *LB = Creat(sb);


        printf("%s - %s = ",sa,sb);
        Minus(LA, LB);
        printf("\n\n");
    }

    return 0;
}
