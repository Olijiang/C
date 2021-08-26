#include <stdio.h>
#include <stdlib.h>
#define maxsize 8


//本部分主要包括邻接矩阵，邻接表的生成 和 图的深度遍历DFS 图的宽度遍历BDF

//图为不带权值的 有向图 和 无向图

typedef struct
{
	int Vex[maxsize];	//顶点表
	int Edge[maxsize][maxsize]; //邻接矩阵，边表
	int v,e; //当前顶点的顶点数和边数
}MGraph;	//邻接矩阵

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

/*  无向表
       1 2 3 4 5 6 7 8
	1 {0,1,0,1,1,0,0,0},
	2 {1,0,1,0,0,1,0,0},
	3 {0,1,0,0,0,0,0,1},
	4 {1,0,0,0,0,0,1,0},
	5 {1,0,0,0,0,0,1,1},
	6 {0,1,0,0,0,0,0,0},
	7 {0,0,0,1,1,0,0,1},
	8 {0,0,1,0,1,0,1,0}};
*/
/*  有向表
       1 2 3 4 5 6 7 8
	1 {0,1,0,1,1,0,0,0},
	2 {0,0,0,0,0,1,0,0},
	3 {0,1,0,0,0,0,0,0},
	4 {0,0,0,0,0,0,1,0},
	5 {0,0,0,0,0,0,0,1},
	6 {0,0,0,0,0,0,0,0},
	7 {0,0,0,0,1,0,0,1},
	8 {0,0,1,0,0,0,0,0}};
*/
int UnEdge[maxsize][maxsize]={
	//无向
	{0,1,0,1,1,1,0,0},
	{1,0,1,0,0,0,0,0},
	{0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,1},
	{0,0,1,0,1,0,1,0}};

int DiEdge[maxsize][maxsize]={
	//有向
	{0,1,0,1,1,0,0,0},
	{0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1},
	{0,0,1,0,0,0,0,0}};

void InitMGraph(MGraph *G, int Edge[maxsize][maxsize])
{
	for(int i=0;i<maxsize;i++)
		for (int j = 0; j < maxsize; ++j)
			G->Edge[i][j] = Edge[i][j];

	for (int i = 0; i < maxsize; ++i)
		G->Vex[i] = i+1;
}

void DisplayMGraph(MGraph G)
{
	for (int i = 0; i < maxsize; ++i)
	{
		printf("%d---", G.Vex[i]);
		for (int j = 0; j < maxsize; ++j)
			if (G.Edge[i][j]==1)
				printf("-%d", G.Vex[j]);
		printf("\n");
	}
}

AGraph *InitAGraph(MGraph MG)
{
	//根据邻接矩阵创建一个邻接表
	//printf("Begain InitAGraph\n");
	AGraph *Ayo = (AGraph *)malloc(sizeof(AGraph));
	ArcNode *tb = (ArcNode *)malloc(sizeof(ArcNode));
	ArcNode *tn = NULL;
	for (int i = 0; i < maxsize; ++i)
	{
		Ayo->Adjlist[i].vex = i+1;
		Ayo->Adjlist[i].firstarc = NULL;
		for (int j = 0; j < maxsize; ++j)
			if (MG.Edge[i][j]==1)
			{	//边存在时连接在后面
				tn = (ArcNode *)malloc(sizeof(ArcNode));
				tn->vex = MG.Vex[j];
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
}

void DFS(AGraph *G, int v)
{
	//v在这里表示顶点的序号
	static int Visit[maxsize] = {0};
	ArcNode *p = G->Adjlist[v-1].firstarc;
	Visit[v-1] = 1;
	printf("%d-", G->Adjlist[v-1].vex);// visit()
	while(p!=NULL)
	{
		if (!Visit[p->vex-1] )
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
	Visit[v-1] = 1;
	stack[++top] = v;
	printf("%d-", G->Adjlist[v-1].vex);// visit()
	while(top!=-1) //栈空时直接return 不考虑循环条件
	{
		p = G->Adjlist[stack[top]-1].firstarc;
		while(p!=NULL && Visit[p->vex-1])	//要确保p最后不指向空指针 才能对其访问，不然出错
			p = p->nextarc; //可能指向空指针

		if (p==NULL)
			top--;
		else
		{
			stack[++top] = p->vex;
			printf("%d-", p->vex);// visit()
			Visit[p->vex-1] = 1;
		}
	}
}

void BFS(AGraph *G, int v)
{
	static int Visit[maxsize+1] = {0};
	int queue[maxsize], front = 0, rear = 0;
	queue[rear++] = G->Adjlist[v-1].vex;
	Visit[v-1] = 1;
	ArcNode *p = NULL;
	while(front<rear)
	{
		p = G->Adjlist[queue[front]-1].firstarc;//保留对头节点的第一条边
		printf("%d-", queue[front++]); //访问对头节点

		while(p!=NULL) //将刚出队的节点后的所以连接节点入队，已经入队则跳过
		{
			if (!Visit[p->vex-1])
			{
				Visit[p->vex-1] = 1;
				queue[rear++] = p->vex;
			}
			p = p->nextarc;
		}
	}
	printf("The last%d\n", queue[front-1]);
}


int HaveEdge(AGraph *G, int v, int j)
{
	//v在这里表示顶点的序号
	static int Visit[maxsize] = {0};
	ArcNode *p = G->Adjlist[v-1].firstarc;
	Visit[v-1] = 1;
	if(Visit[j-1] = 1) return 1; //访问到j号元素说明i，j间存在路径，返回1
	//printf("%d-", G->Adjlist[v-1].vex);// visit()
	while(p!=NULL)
	{

		if (!Visit[p->vex-1])
			return HaveEdge(G,p->vex,j);
		p = p->nextarc;
	}
	return 0;
}

int main()
{
	MGraph Myo;
	InitMGraph(&Myo, UnEdge);
	//printf("Undirected MGraph\n");
	//DisplayMGraph(Myo);
	//printf("---------------------\n");
	MGraph DiMyo;
	//InitMGraph(&DiMyo, DiEdge);
	//printf("Directed MGraph\n");
	//DisplayMGraph(DiMyo);

	//printf("---------------------\n");
	AGraph *Ayo = InitAGraph(Myo);
	printf("Undirected AGraph\n");
	DispalyAGraph(Ayo);
	//printf("---------------------\n");
	//AGraph *DiAyo = InitAGraph(DiMyo);
	//printf("Directed AGraph\n");
	//DispalyAGraph(DiAyo);
	printf("\nDFS---------------------\n");
	DFS(Ayo,2);
	printf("\nDFS1---------------------\n");
	DFS1(Ayo,2);
	printf("\nBFS---------------------\n");
	BFS(Ayo,2);

	printf("%s\n", HaveEdge(Ayo, 1 ,5 )?("Exist 1-5"):("Not Exist 1-5"));

	return 0;
}






