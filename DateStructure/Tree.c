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


int FindA(BTNode *tree, int a);// 检查tree里有无a值得节点

BTNode *CreatTree(int a[],  int n)
{
	//数据数列， 数列长度
	//按二叉排序数插入数据
	BTNode *tree = malloc(sizeof(BTNode));
	tree->rch = NULL;
	tree->lch = NULL;
	int i=1;
	BTNode *s,*p = tree;
	tree->data = a[0];
	while(i<n)
	{
		s = malloc(sizeof(BTNode));
		s->data = a[i];
		s->rch = NULL;
		s->lch = NULL;
		while(p->lch!=NULL && p->rch!=NULL)	//找到正确位置叶子节点
		{
			if (s->data < p->data) p = p->lch;
			else p = p->rch;
		}
		if (s->data < p->data)  p->lch = s;
		else  p->rch = s;
		
		i++;
		p = tree;
	}	
	return tree;
}

BTNode *CreatTree2(int a[],  int n)
{
	//数据数列， 数列长度
	//完全二叉树
	BTNode *tree = malloc(sizeof(BTNode));
	tree->rch = NULL;
	tree->lch = NULL;
	BTNode *s,*p = tree;
	BTNode* stack[n];
	int top = -1;
	tree->data = a[0];
	for (int i = 0; (i+1)*2 <= n; i++)
	{
		//数组下标以0开始，左孩子为(i+1)*2-1，右孩子为(i+1)*2
		//左孩子
		s = malloc(sizeof(BTNode));
		s->data = a[(i+1)*2-1];
		s->rch = NULL;
		s->lch = NULL;
		p->lch = s;
		stack[++top] = s;
		//右孩子
		s = malloc(sizeof(BTNode));
		s->data = a[(i+1)*2];
		s->rch = NULL;
		s->lch = NULL;
		p->rch = s;
		stack[++top] = s;
		i++;
		p = stack[top--];
		
	}	
	return tree;
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

int Show(BTNode *tree)
{
	// 按层次打印树
	if (tree==NULL)	return 0;

	st que[10];			//队列，包含一个节点地址和层高标记
	int front=0,rear=1;
	int no=0;			//no用来暂存出队节点层高
	int w[10]={0};		//用来记录每层的宽度
	int k = 1;
	que[1].p = tree;	//根节点入队
	que[1].n = 1;		//根节点层高为1

	while(front!=rear)
	{
		front = (front+1)%10;
		if (k != que[front].n)
		{
			printf("\n");
			k++;
		}
		printf("%d\t", que[front].p->data);
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
		// tree->bf = LD - RD;
		return LD>RD?LD+1:RD+1;
	}
}

int GetDeepth2(BTNode *tree)
{	
	// 获取树的深度
	static int max, deep;
	if (tree==NULL)
		return 0;
	else
	{
		deep++;
		GetDeepth2(tree->lch);
		GetDeepth2(tree->rch);
		max = (max>deep?max:deep);
		deep--;
	}
	return max;
}

void Traversal1(BTNode *tree)
{	//非递归先序遍历
	BTNode *stack[10];
	BTNode *p;
	int top=-1;
	stack[++top] = tree;
	while(top!=-1)
	{
		p = stack[top];
		printf("%d ", stack[top--]->data);
		if (p->rch!=NULL)
			stack[++top] = p->rch;

		if (p->lch!=NULL)
			stack[++top] = p->lch;
	}
}

void Traversal2(BTNode *tree)
{	//非递归中序遍历
	BTNode *stack[10];
	BTNode *p=tree;
	int top=-1;
	while(top!=-1||p!=NULL)
	{
		while(p!=NULL)
		{
			stack[++top] = p;
			p = p->lch;
		}

		p = stack[top--];
		printf("%d ", p->data);
		p=p->rch;

	}
}

void Traversal3(BTNode *tree)
{	//非递归后序遍历
	;
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

void RevertTree(BTNode *tree)
{
	if (tree == NULL) return;
	
	BTNode *temp = tree->lch;
	tree->lch = tree->rch;
	tree->rch = temp;
	RevertTree(tree->lch);
	RevertTree(tree->rch);
}

void RevertTree1(BTNode *tree)
{	//非递归先序遍历反转树
	BTNode *stack[10];
	BTNode *p;
	BTNode *temp;
	int top=-1;
	stack[++top] = tree;
	while(top!=-1)
	{
		p = stack[top--];
		temp = p->lch;
		p->lch = p->rch;
		p->rch = temp;
		if (p->rch!=NULL)
			stack[++top] = p->rch;

		if (p->lch!=NULL)
			stack[++top] = p->lch;
	}
}

BTNode *MinRoot(BTNode *tree, int a, int b)
{	// 找 a b 的最小祖先
	while (tree!=NULL)
	{
		if(FindA(tree->lch,a) && FindA(tree->lch,b)) tree = tree->lch;
		else if(FindA(tree->rch,a) && FindA(tree->rch,b)) tree = tree->lch;
		else return tree;
	}
	return NULL;
}

int FindA(BTNode *tree, int a)
{	// 检查tree里有无值为a的节点
	if(tree==NULL) return 0;
	if(tree->data==a) return 1;
	if(FindA(tree->lch,a) || FindA(tree->rch,a)) return 1;
	return 0;
}


int main(int argc, char const *argv[])
{
	int a[] = {55,31,64,8,24,79,93,43,18,84,57,5};
	int n = 12;
	BTNode *yo = CreatTree(a, n);
	BTNode *yoo = CreatTree(a, n);
	int pre[] = {55, 31, 8, 5, 24, 18, 43, 64, 57, 79, 93, 84};
	int in[] = {5, 8, 18, 24, 31, 43, 55, 57, 64, 79, 84, 93};

	BTNode *bt = CreatBT(pre, in ,0,11,0,11);


	Show(bt);
	printf("\n----------------------\n");
	RevertTree(bt);
	Show(bt);
	printf("\n----------------------\n");

	Show(yoo);
	printf("\n----------------------\n");
	RevertTree1(yoo);
	Show(yoo);
	printf("\n----------------------\n");
	//postorder1(yo);
	//printf("\n");
	//PrintPath(bt, 18);

	printf("MinRoot:%d\n",MinRoot(yo,43,8)->data);
	printf("wedth:%d\n", GetWidth(yo));
	printf("wedth2:%d\n", GetWidth2(yo));
	printf("\n\ndeepth:%d\n", GetDeepth(yo));
	printf("\n\ndeepth2:%d\n", GetDeepth2(yo));
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
