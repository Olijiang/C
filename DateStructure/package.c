#include <stdio.h>


int merge_array()
// 将两部分分别有序的有序列表合并
{
    int a[] = {1,3,5,7,9,2,4,6,8};
    int m=5, n=4, temp;
    int i,j;
    for(i=m;i<m+n;i++)
    {
        temp = a[i];
        for(j=i-1;j>0&&temp<a[j];j--)
        {
            a[j+1] = a[j];
        }
        a[j+1] = temp;
    }
    for(i=0;i<9;i++) printf("%d ",a[i]);
}


int Factorial_40()
// 计算40的阶乘，结果用数组表示
{
    int a[50]={0}, i, id=0;
    a[0]=1;
    for(i=1;i<=40;i++)
    {
        int j;
        for(j=0;j<=id;j++) a[j] = a[j] * i;
        for(j=0;j<id;j++)
        {
            if(a[j]>=10)
            {
                a[j+1] = a[j+1] + a[j]/10;
                a[j] = a[j]%10;
            }
        }
        while(a[id]>=10)
        {

            a[id+1] = a[id+1] + a[id]/10;
            a[id] = a[id]%10;
            id++;
            //printf("ID:%d\n",id);
        }
        printf("%d!:", i);
        for(j=id;j>=0;j--) printf("%d",a[j]);
        printf("\n");
    }
}

void initialist(Node **head)
//初始化一个链表，接受一个头节点的地址
{
    (*head) = (Node *)malloc(sizeof(Node));
    (*head)->next = NULL;
}

void add_intdata(Node **tail, int *data, int n)
/*
    **tial 尾节点的地址
    *date 要添加的数据  int类型数组
    n 数据个数
*/
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

void add_strdate(LNode **tail, char *name, char *tel_num, int n){   //  尾插法将数据添加到链表，并将tail指向最新的节点
    Node *p = NULL;
    p = (Node *)malloc(sizeof(Node));
    strcpy(p->user.name, name);
    strcpy(p->user.tel_num, tel_num);
    (*tail)->next = p;
    (*tail) = p;
    p->next = NULL;
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