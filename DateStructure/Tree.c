#include <stdio.h>
#include <stdlib.h>

typedef struct BTnode
{
	//树节点
	int data;
	struct BTnode *lch, *rch;
}BTNode;

typedef struct 
{
	// 计算深度时进入队列的节点，附带一个高度n
	BTNode *p;
	int n;
}st;

BTNode *CreatTree()
{
	//创建一颗空树
	BTNode *s = malloc(sizeof(BTNode));
	s->rch = NULL;
	s->lch = NULL;
	return s;
}

void AddData(BTNode *tree, int a[],  int n)
{
	//接收一个树根节点， 数据数列， 数列长度
	//按二叉排序数插入数据
	int i=1;
	BTNode *s,*p = tree;
	tree->data = a[0];
	while(i<n)
	{
		s = malloc(sizeof(BTNode));
		s->data = a[i];
		s->rch = NULL;
		s->lch = NULL;
		while(s->data<p->data?p->lch!=NULL:p->rch!=NULL)
		{
			if (s->data<p->data) p = p->lch;
			else p = p->rch;
		}
		if (s->data<p->data)
		{
			p->lch = s;
			//printf("stock in left %d\n",a[i]);
		}
		else 
		{
			p->rch = s;
			//printf("stock in right %d\n",a[i]);
		}
		
		i++;
		p = tree;
	}	
}

void postorder1(BTNode *tree)
{	//先序遍历
	if (tree!=NULL)
	{
		printf("%d, ", tree->data);
		postorder1(tree->lch);
		postorder1(tree->rch);
	}
}

void postorder2(BTNode *tree)
{	//中序遍历
	if(tree!=NULL)
	{
		postorder2(tree->lch);
		printf("%d, ", tree->data);
		postorder2(tree->rch);
	}
}

void postorder3(BTNode *tree)
{	//后序遍历
	if(tree!=NULL)
	{
		postorder3(tree->lch);
		postorder3(tree->rch);
		printf("%d ", tree->data);
	}
}

void level(BTNode *tree)
{	//层次遍历
	BTNode *que[10];
	int front=0,rear=1;
	que[1] = tree;
	while(front!=rear)
	{
		front = (front+1)%10;
		printf("%d ", que[front]->data);
		if (que[front]->lch!=NULL)
		{
			rear = (rear+1)%10;
			que[rear] = que[front]->lch;
		}
		if (que[front]->rch!=NULL)
		{
			rear = (rear+1)%10;
			que[rear] = que[front]->rch;
		}
	}
}

int GetWidth(BTNode *tree)
{
	// 获取树的最大宽度，队列辅助
	if (tree==NULL)	return 0;

	st que[10];			//队列，包含一个节点地址和层高标记
	int front=0,rear=1;
	int no=0;			//no用来暂存出队节点层高
	int w[10]={0};		//用来记录每层的宽度

	que[1].p = tree;	//根节点入队
	que[1].n = 1;		//根节点层高为1

	while(front!=rear)
	{
		front = (front+1)%10;
		//printf("%d\n", que[front].p->data);
		no = que[front].n;
		w[no]++;		//每次出队当前层的节点数量+1

		if (que[front].p->lch!=NULL)
		{
			rear = (rear+1)%10;
			que[rear].p = que[front].p->lch;
			que[rear].n = (que[front].n)+1;
		}
		if (que[front].p->rch!=NULL)
		{
			rear = (rear+1)%10;
			que[rear].p = que[front].p->rch;
			que[rear].n = que[front].n+1;
		}
	}
	int max = w[0];
	for (int i = 0; i <= no; ++i)
		max = (max>w[i])?max:w[i];
	return max;
}


int GetWidth2(BTNode *tree)
{
	//遍历方法
	static int width[10]={0};
	static int n=0;
	if (tree!=NULL)
	{
		n++;
		width[n]++;
		GetWidth2(tree->rch);
		GetWidth2(tree->lch);
		n--;
		if (n==0)
		{
			int max = width[1];
			for (int i = 1; width[i] > 0; ++i)
				max = (max>width[i])?max:width[i];
			return max;
		}
	}
}


int GetDeepth(BTNode *tree)
{	
	// 获取树的深度
	int LD, RD;
	if (tree==NULL)
		return 0;
	else
	{
		LD = GetDeepth(tree->lch);
		RD = GetDeepth(tree->rch);
		//printf("%d\n", LD>RD?LD+1:RD+1);
		return LD>RD?LD+1:RD+1;
	}
}

void Traversal1(BTNode *tree)
{	//非递归先序遍历
	BTNode *stack[10];
	BTNode *temp;
	int top=-1;
	stack[++top] = tree;
	while(top!=-1)
	{
		temp = stack[top];
		printf("%d ", stack[top--]->data);
		if (temp->rch!=NULL)
			stack[++top] = temp->rch;

		if (temp->lch!=NULL)
			stack[++top] = temp->lch;
	}
}

void Traversal2(BTNode *tree)
{	//非递归中序遍历
	BTNode *stack[10];
	BTNode *temp=tree;
	int top=-1;
	while(top!=-1||temp!=NULL)
	{
		while(temp!=NULL)
		{
			stack[++top] = temp;
			temp = temp->lch;
		}

		temp = stack[top--];
		printf("%d ", temp->data);
		temp=temp->rch;

	}
}

void Traversal3(BTNode *tree)
{	//非递归后序遍历
	BTNode *stack[10];
	BTNode *temp;
	int top=-1;
	stack[++top] = tree;
	while(top!=-1)
	{
		temp = stack[top];
		printf("%d ", stack[top--]->data);
		if (temp->lch!=NULL)
			stack[++top] = temp->lch;
		if (temp->rch!=NULL)
			stack[++top] = temp->rch;
	}
}

BTNode *CreatBT(int pre[], int in[], int p1,int p2,int i1 ,int i2)
{
	if (p1>p2) return NULL;

	int i;
	BTNode *s = malloc(sizeof(BTNode));
	s->data = pre[p1];

	for (i = i1; i < i2; ++i)
		if(in[i]==pre[p1]) break;

	s->lch = CreatBT(pre, in, p1+1, p1+i-i1, i1 , i-1);
	s->rch = CreatBT(pre, in, p1+i-i1+1, p2, i+1 , i2);

	return s;
}

int  getLenth(BTNode *tree)
{
	//总节点个数
	static int n;
	if(tree==NULL) return 0;

	n++;
	getLenth(tree->rch);
	getLenth(tree->lch);
	return n;
}

int  getSubLenth(BTNode *tree)
{
	//叶子节点个数
	static int m;
	if(tree==NULL) return 0;
	getSubLenth(tree->lch);
	getSubLenth(tree->rch);
	if(tree->rch==NULL&&tree->lch==NULL) m++;

	return m;
}

int *NodeLink(BTNode *tree, BTNode **head, BTNode **tail)
{
	//将叶子节点从左往右连成一个链表
	if (tree==NULL) return 0;

	if(tree->rch==NULL&&tree->lch==NULL)
	{
		if (*head == NULL) 
		{
			*head = tree;
			*tail = tree;
		}
		else
		{
			(*tail)->rch = tree;
			(*tail) = tree;
		}
	}
	NodeLink(tree->lch, &(*head), &(*tail));
	NodeLink (tree->rch, &(*head), &(*tail));
}

int stack[20];
int top = -1;
void PrintPath(BTNode *tree, int k)
{	//先序遍历
	if (tree!=NULL)
	{
		stack[++top]= tree->data;
		if (tree->data==k)
			for (int i = 0; i <= top; i++)
				printf("%d ",stack[i]);
		PrintPath(tree->lch, k);
		PrintPath(tree->rch, k);
		top--;
	}
}


int main(int argc, char const *argv[])
{
	int a[] = {55,31,64,8,24,79,93,43,18,84,57,5};
	int n = 12;
	BTNode *yo = CreatTree();
	AddData(yo, a, n);
	int pre[] = {55, 31, 8, 5, 24, 18, 43, 64, 57, 79, 93, 84};
	int in[] = {5, 8, 18, 24, 31, 43, 55, 57, 64, 79, 84, 93};

	BTNode *bt = CreatBT(pre, in ,0,11,0,11);


	level(bt);
	printf("\n");
	//postorder1(yo);
	//printf("\n");
	//PrintPath(bt, 18);
	printf("wedth:%d\n", GetWidth(yo));
	printf("wedth2:%d\n", GetWidth2(yo));
/* 	printf("\n\ndeepth:%d\n", GetDeepth(yo));
	printf("wedth:%d\n", GetWidth(yo));
	printf("lenth:%d\n", getLenth(yo));
	printf("Sublenth:%d\n", getSubLenth(yo));


	BTNode *head=NULL, *tail=NULL;
	NodeLink(yo, &head, &tail);
	while(head!=tail)
	{
		printf("%d  ", head->data);
		head = head->rch;
	}printf("%d\n", head->data);
	 */
	return 0;

}
