#include <stdio.h>
#include <stdlib.h>
#define maxsize 8

//Dji 堆优化

typedef struct ArcNode
{	//边节点
	int vex; //当前边指向的节点信息
	int cost; //边代价
	struct ArcNode *nextarc;	//下一条边
}ArcNode;

typedef struct
{	//顶点节点
	int vex;	//顶点数据
	ArcNode *firstarc;	// 顶点出来的第一条边
}VNode;

typedef struct
{
	//邻接表
	VNode Adjlist[maxsize];	//顶点数组
	int v,e; //当前顶点的顶点数和边数
}AGraph;	

typedef struct tuble
{	// 二元组，包含当前顶点和到这个顶点的代价
    int vex;
    int cost;
}tuble;

int DiEdge[maxsize][maxsize]={
	{0,2,3,1,0,0,0,0},
	{0,0,0,0,0,4,0,0},
	{0,0,0,0,4,0,0,0},
	{0,0,0,0,2,4,0,0},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,3,3},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}};

/* 
	1	5	7
0		3	6
	2	4
 */



AGraph *InitAGraph()
{
	//创建一个邻接表图
	//printf("Begain InitAGraph\n");
	AGraph *Ayo = (AGraph *)malloc(sizeof(AGraph));
	ArcNode *tb = (ArcNode *)malloc(sizeof(ArcNode));
	ArcNode *tn = NULL;
	for (int i = 0; i < maxsize; ++i)
	{
		Ayo->Adjlist[i].vex = i;
		Ayo->Adjlist[i].firstarc = NULL;
		for (int j = 0; j < maxsize; ++j)
			if (DiEdge[i][j]>=1)
			{	// 若边存在,新建一个节点
				tn = (ArcNode *)malloc(sizeof(ArcNode));
				tn->vex = j;
				tn->cost = DiEdge[i][j];
				tn->nextarc=NULL;
				if (Ayo->Adjlist[i].firstarc==NULL)
				{
					Ayo->Adjlist[i].firstarc = tn;
					tb = Ayo->Adjlist[i].firstarc;
					//printf("now inserted %d behind %d \n", Ayo->Adjlist[i].firstarc->vex,G.Vex[i]);
				}
				else
				{
					tb->nextarc = tn;
					tb = tb->nextarc;
					//printf("now inserted %d behind %d \n", tb->nextarc->vex,G.Vex[i]);
				}
			}
	}
	return Ayo;
}

void DispalyAGraph(AGraph *G)
{
	// 输出邻接表结构的图
	ArcNode *t = NULL;
	for (int i = 0; i < maxsize; ++i)
	{
		printf("%d---", G->Adjlist[i].vex);
		t = G->Adjlist[i].firstarc;
		while(t!=NULL)
		{
			printf("-%d(%d)", t->vex, t->cost);
			t = t->nextarc;
		}
		printf("\n");
	}
	printf("-------------over\n");
}

void MDFS(int v, int j)
{
	static int visit[maxsize];
	static int d=0;
	static int path[maxsize];
	static int top=-1;
	visit[v]=1;
	
	path[++top] = v;
	if (v==j)
	{	
		printf("Lenth:%d  ",d);	
		for (int i = 0; i <= d; i++)
			printf("%d ",path[i]);
		printf("\n");
	}
	d++;
	for (int i = 0; i < maxsize; i++)
	{
		if (DiEdge[v][i]!=0 && visit[i]==0)
			MDFS(i, j);
	}
	top--;
	d--;
	
}
void DFS(AGraph *G, int v)
{
	//v表示遍历起始点
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


int DetectCircle(AGraph *G, int v)
{
	static int visit[maxsize];
	static int finished[maxsize];
	static int flag = 0;

	if (flag) return 1;	//flag 用于对遍历进行截支，满足条件直接返回，不再继续遍历
	// 基于DFS 检测有向图中是否存在环路;
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	finished[v] = 1; // finished[i]=1 表示还在本轮遍历之中，再次访问到自己说明存在环路
	printf("%d ",v);
	while(p!=NULL)
	{	
		if (visit[p->vex]==1 && finished[p->vex]==1)
		{
			flag=1; 	// 同一个节点被再次访问， 说明存在环路；
			return 1;	//已检测到回路直接返回；
		}
		if(visit[p->vex]==0)
		{
			DetectCircle(G,p->vex);
			finished[p->vex]=0;
		}
		p = p->nextarc;
	}
	if (flag) return 1;
	return 0;
}


void DetectPath(AGraph *G, int v, int j, int L)
{
	//检测 i， j 点之间是否存在长度为 L 的路径 
	//采用回溯 DFS 算法
	
	static int visit[maxsize];
	static int path[maxsize];
	static int d = 0;	//d 为已经经过的路径长度，初始为 0;
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	path[d] = v;

	if (v==j && d==L)	//d==L 输出i j之间长度为 L 的路径， d==d 可以输出 i j 之间所有路径；
	{
		for (int i = 0; i <= d; i++)
			printf("%d ",path[i]);
		printf("\n");
	}
	d++;
	while(p!=NULL)
	{
		//if (!visit[p->vex-1] || p->vex==j)	//检测是否包含 j 的环路，若存在，则遍历会回到 j，此时visit肯定标记为1，需要强制访问；
			//DetectPath(G,p->vex,j,d,L);
		
		if (!visit[p->vex])		//检测 v j 不同时的路径
			DetectPath(G,p->vex,j,L);
		p = p->nextarc;
	}
	//退出时将visit释放
	visit[v]=0;
	--d;
} 



int main()
{
	AGraph *Ayo = InitAGraph();

	DispalyAGraph(Ayo);
	//DFS(Ayo, 0);
	MDFS(0, 6);
	printf("\n");
	if(DetectCircle(Ayo, 0)) printf("\nHave circle");
	return 0;
}