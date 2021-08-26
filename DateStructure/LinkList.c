#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *next;
}Node, *LinkList;

LinkList Initialist()
{
    //����������һ��ͷ�ڵ�
    Node *p = (Node *)malloc(sizeof(Node));
	p->next = NULL;
    return p;
}

void Add_data(Node **tail, int *data, int n)
{
    //�� tail�ڵ� �� ������ݣ�data Ϊ�������飬n Ϊ���ݸ���
    //�˴���ΪҪ��tailβ�ڵ���ͬ���޸ģ�ʹ��tail�� ��ַ ����
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

int Delete_MinNode(LinkList head)
{
    Node *p = head->next;
    int min = p->data;
    Node *po = p; //������Сֵ�ڵ㣬��ʼΪ��һ��
    while (p->next!=NULL)
    {
        if (min > p->next->data)
        {
            min = p->next->data;
            po = p;
            p = p->next;
        }
        else p = p->next;
    }
    //ɾ���ڵ�
    p = po->next;
    po->next = po->next->next;
    free(p);
}


void Showlist(Node *head)
{
	Node *p = head->next;
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p = p->next;
	}
}


int main()
{
	int a[] = {6,3,15,2,9,5,13,1};

	Node *head = NULL;
	Node *tail = NULL;

	head = Initialist();
	tail = head;

	Add_data(&tail, a, sizeof(a)/sizeof(a[0]));
	Showlist(head);
    printf("\n");
    Delete_MinNode(head);
    Showlist(head);
	return 0;
}