#include <stdio.h>
#include <stdlib.h>

// 第六章综合练习题6

_Bool true = 1;
_Bool false = 1;

typedef struct btnode
{
	//树节点
	int data;
	struct btnode *lch, *rch;
}BTNode;

typedef struct qnode
{
	BTNode *bt;
	int n;
}Qnode;

_Bool InsertBST(BTNode **bt, int key)
{	
	//printf("InsertBST\n");
	if ((*bt)==NULL)
	{
		(*bt)=(BTNode *)malloc(sizeof(BTNode));
		(*bt)->data = key;
		(*bt)->rch = NULL;
		(*bt)->lch = NULL;
		return true;
	}

	else if ((*bt)->data == key) return false;
	
	else if (key>(*bt)->data)
	{
		return InsertBST(&((*bt)->rch), key);
	}
	else return InsertBST(&((*bt)->lch), key);
}

// InsertBST2(BTNode *bt, int key) 这个例子传入BTNode *（指针）类型的参数为复制传参，无法对原参数进行有效修改，
//需要传入指针的地址指针,例如 InsertBSTT(BTNode **bt, int key)

_Bool InsertBST2(BTNode *bt, int key)
{	
	//错误例子
	;
}

BTNode *CreatBST(int key[], int n)
{
	int i=0;
	BTNode *root=NULL;
	while(i<n)
	{
		// printf("CreatBST\n");
		InsertBST(&root, key[i++]);
	}
	return root;
}

void pre_traverse(BTNode *tree)
{
	//printf("pre_traverse\n");
	if(tree!=NULL)
	{
		printf("%d, ", tree->data);
		pre_traverse(tree->lch);
		pre_traverse(tree->rch);
	}
}

int Get_KeyDeepth(BTNode *tree, int key)
{
	// 返回key所在的层号，root为第一层，0表示未找到key
	Qnode queue[10]; 
	int front = 0, rear = 0;

	queue[++rear].bt = tree;
	queue[rear].n = 1;

	while(front<rear)
	{
		front++;
		if (queue[front].bt->data==key) return queue[front].n;
		if (queue[front].bt->lch!=NULL)
		{
			queue[++rear].bt = queue[front].bt->lch;   
			queue[rear].n = queue[front].n+1;
		}
		if (queue[front].bt->rch!=NULL)
		{ 
			queue[++rear].bt = queue[front].bt->rch;
			queue[rear].n = queue[front].n+1;
		}
	}
	return 0;
}

int Get_KeyDeepth2(BTNode *tree, int key)
{
	// 返回key所在的层号，root为第一层，0表示未找到key
	static int n=1, deepth=0;
	if (tree!=NULL)
	{
		if (tree->data == key) deepth=n;

		n++;
		Get_KeyDeepth2(tree->lch,key);
		Get_KeyDeepth2(tree->rch,key);
		n--;
	}
	return deepth;
}

void PreToRear(int pre[], int l1, int l2, int rear[], int r1, int r2)
{	
	// 将先序遍历转化为后续遍历
	//l1,l2为pre中数组的起末下标，r1,r2为rear数组中的起末下标。
	if(l1<=l2)
	{ 
		rear[r2] = pre[l1];
		PreToRear(pre,l1+1,(l1+l2+1)/2, rear, r1, (r1+r2-1)/2);
		PreToRear(pre,(l1+l2+1)/2+1,l2, rear, (r1+r2-1)/2+1,r2-1);
	}
}

BTNode *Course(BTNode *tree)
{
	//输出每个叶子节点到根节点的路径
	static int stack[10], top=0;
	static BTNode *p;

	if (tree==NULL) return NULL;

	stack[top++] = tree->data;
	if (tree->rch==NULL&&tree->lch==NULL)
    {
		for (int i = 0; i < top; ++i)
			printf("%d, ", stack[i]);
		printf("\n");
        return NULL;
    }


	Course(tree->lch);
	top--;
	Course(tree->rch);
	top--;
	return NULL;
}


BTNode *Course2(BTNode *tree)
{
	//输出每个叶子节点到根节点的路径
	static int stack[10], top=0;

	if (tree==NULL) return NULL;

	stack[top++] = tree->data;
	if (tree->rch==NULL&&tree->lch==NULL)
    {
		for (int i = 0; i < top; ++i)
			printf("%d, ", stack[i]);
		printf("\n");
    }
	Course2(tree->lch);
	Course2(tree->rch);
	top--;
	return NULL;
}

void main()
{
	int a[] = {55,31,64,8,79,43,57};
	int n = sizeof(a)/sizeof(a[0]);
	BTNode *yo = CreatBST(a, n);
	int pre[] = {55, 31, 8, 43, 64, 57, 79};
	int rear[7] = {0};
	pre_traverse(yo);
	

	//前序转后序
	printf("\n");
	PreToRear(pre,0,6, rear,0,6);
	for (int i = 0; i < 7; ++i)
	{
		printf("%d, ", rear[i]);
	}

	//返回key层号
	printf("\n");
	printf("key_deepth:%d", Get_KeyDeepth(yo,79));
	printf("\n");
	printf("key_deepth:%d", Get_KeyDeepth2(yo,79));
	printf("\n");

	Course2(yo);

}