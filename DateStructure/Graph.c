#include <stdio.h>
#include <stdlib.h>
#define maxsize 6

//本部分主要包括邻接表的生成 和 图的深度遍历DFS 图的宽度遍历BDF

//图为不带权值无向图


typedef struct ArcNode
{	//边节点
	int vex; //当前边指向的节点信息
	struct ArcNode *nextarc;	//下一条边
}ArcNode;

typedef struct
{	//顶点节点
	int vex;	//顶点数据
	ArcNode *firstarc;	// 顶点出来的第一条边
}VNode;
typedef struct
{
	VNode Adjlist[maxsize];	//顶点数组
	int v,e; //当前顶点的顶点数和边数
}AGraph;	//邻接表

int UnEdge[maxsize][maxsize]={
	//无向
	{0,1,1,0,0,0},
	{1,0,1,0,1,0},
	{1,1,0,1,0,0},
	{0,0,1,0,0,1},
	{0,1,0,0,0,0},
	{0,0,0,1,0,0}};


AGraph *InitAGraph()
{
	//创建一个邻接表图
	//printf("Begain InitAGraph\n");
	AGraph *G = (AGraph *)malloc(sizeof(AGraph));
	ArcNode *tb = (ArcNode *)malloc(sizeof(ArcNode));
	ArcNode *tn = NULL;
	for (int i = 0; i < maxsize; ++i)
	{
		G->Adjlist[i].vex = i;
		G->Adjlist[i].firstarc = NULL;
		for (int j = 0; j < maxsize; ++j)
			if (UnEdge[i][j]>=1)
			{	// 若边存在,新建一个节点
				tn = (ArcNode *)malloc(sizeof(ArcNode));
				tn->vex = j;
				tn->nextarc=NULL;
				if (G->Adjlist[i].firstarc==NULL)
				{
					G->Adjlist[i].firstarc = tn;
					tb = G->Adjlist[i].firstarc;
					//printf("now insert %d behind %d \n", G->Adjlist[i].firstarc->vex,G.Vex[i]);
				}
				else
				{
					tb->nextarc = tn;
					tb = tb->nextarc;
					//printf("now insert %d behind %d \n", tb->nextarc->vex,G.Vex[i]);
				}
			}
	}
	return G;
}

void Display(AGraph *G)
{
	// 输出邻接表
	ArcNode *t = NULL;
	for (int i = 0; i < maxsize; ++i)
	{
		printf("%d---", G->Adjlist[i].vex);
		t = G->Adjlist[i].firstarc;
		while(t!=NULL)
		{
			printf("-%d", t->vex);
			t = t->nextarc;
		}
		printf("\n");
	}
	printf("-------------over\n");
}

void DFS(AGraph *G, int v)
{
	static int Visit[maxsize] = {0};
	ArcNode *p = G->Adjlist[v].firstarc;
	Visit[v] = 1;
	printf("%d-", G->Adjlist[v].vex);// visit()
	while(p!=NULL)
	{
		if (!Visit[p->vex] )
			DFS(G,p->vex);
		p = p->nextarc;
	}
}


void DFS1(AGraph *G, int v)
{
	//非递归
	static int Visit[maxsize] = {0};
	ArcNode *p = NULL;
	int stack[maxsize], top=-1;
	Visit[v] = 1;
	stack[++top] = v;
	printf("%d-", G->Adjlist[v].vex);// visit()
	while(top!=-1) //栈空时直接return 不考虑循环条件
	{
		p = G->Adjlist[stack[top]].firstarc;
		while(p!=NULL && Visit[p->vex])	//要确保p最后不指向空指针 才能对其访问，不然出错
			p = p->nextarc; //可能指向空指针

		if (p==NULL)
			top--;
		else
		{
			stack[++top] = p->vex;
			printf("%d-", p->vex);// visit()
			Visit[p->vex] = 1;
		}
	}
}

void BFS(AGraph *G, int v)
{
	static int Visit[maxsize+1] = {0};
	int queue[maxsize], front = 0, rear = 0;
	queue[rear++] = G->Adjlist[v].vex;
	Visit[v] = 1;
	ArcNode *p = NULL;
	while(front<rear)
	{
		p = G->Adjlist[queue[front]].firstarc;//保留对头节点的第一条边
		printf("%d-", queue[front++]); //访问对头节点

		while(p!=NULL) //将刚出队的节点后的所以连接节点入队，已经入队则跳过
		{
			if (!Visit[p->vex])
			{
				Visit[p->vex] = 1;
				queue[rear++] = p->vex;
			}
			p = p->nextarc;
		}
	}
	//printf("The last%d\n", queue[front]);
}

int DetectLoop(AGraph *G, int v)
{
	static int visit[maxsize];
	static int edge, vertex;
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	vertex++;	// 记顶点
	while(p!=NULL)
	{
		edge++;	//记边
		if(visit[p->vex]==0)
			DetectLoop(G, p->vex);
		p = p->nextarc;
	}
	//printf(" %d %d ||", edge, vertex);
	if(edge/2 >= vertex) 
		return 1;
	return 0;
}

int DetectLoop2(AGraph *G, int v, int pre)
{
	static int visit[maxsize];
	static int flag;
	
	if(flag) return flag;
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	while(p!=NULL)
	{
		if(p->vex!=pre && visit[p->vex]) flag = 1;
		if(!visit[p->vex]) DetectLoop2(G, p->vex, v);
		p = p->nextarc;
	}
	return flag;
}

int main()
{

	AGraph *G = InitAGraph();
	Display(G);
	if(DetectLoop(G,0)) printf("DetectLoop:YES\n");
	if(DetectLoop2(G,0,-1)) printf("DetectLoop2:YES");
	return 0;
}



