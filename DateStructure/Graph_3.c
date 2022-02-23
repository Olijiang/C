#include <stdio.h>
#include <stdlib.h>
#define maxsize 8
#define MAX 100


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

typedef struct
{
	int cost;
	int vex;
}HeapNode;

int DiEdge[maxsize][maxsize]={
	{MAX,2,3,1,MAX,MAX,MAX,MAX},
	{MAX,MAX,MAX,MAX,MAX,4,MAX,MAX},
	{MAX,MAX,MAX,MAX,4,MAX,MAX,MAX},
	{MAX,MAX,MAX,MAX,2,4,MAX,MAX},
	{MAX,MAX,MAX,MAX,MAX,MAX,1,MAX},
	{MAX,MAX,MAX,MAX,MAX,MAX,3,3},
	{MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX},
	{MAX,MAX,MAX,MAX,MAX,MAX,MAX,MAX}};

/* 
	1	5	7
0		3	6
	2	4
 */



AGraph *InitAGraph()
{
	//创建一个邻接表结构的图
	//printf("Begain InitAGraph\n");
	AGraph *G = (AGraph *)malloc(sizeof(AGraph));
	ArcNode *tb = (ArcNode *)malloc(sizeof(ArcNode));
	ArcNode *tn = NULL;
	G->e = G->v = 0;
	for (int i = 0; i < maxsize; ++i)
	{
		G->v++;
		G->Adjlist[i].vex = i;
		G->Adjlist[i].firstarc = NULL;
		for (int j = 0; j < maxsize; ++j)
			if (DiEdge[i][j]<MAX)
			{	// 若边存在,新建一个节点
				G->e++;
				tn = (ArcNode *)malloc(sizeof(ArcNode));
				tn->vex = j;
				tn->cost = DiEdge[i][j];
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
	// 邻接矩阵深度遍历
	// 寻找两点之间的路径
	static int visit[maxsize];
	static int d=0;
	static int path[maxsize];
	static int top=-1;
	visit[v]=1;
	
	path[++top] = v;
	if (v==j)
	{	
		printf("%d->%d  ", path[0],j);
		printf("Lenth:%d  ",d);
		printf("Path:");
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

int MDFS1(int v, int j)
{   // 基于邻接矩阵的遍历
	// 若存在路径，则返回长度。若不存在，则返回-1
	static int visit[maxsize];
	static int d=0;   //记录遍历长度
	static int result=-1;	//记录结果长度
	if(result!=-1) return result; 	//截断遍历
	if(v == j) result = d;
	d++;
	visit[v] = 1;
	for(int k=0; k<maxsize; k++)
		if(DiEdge[v][k] && !visit[k])
			MDFS1(k, j);
	d--;
	return result;
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
	// 基于DFS 检测有向图中是否存在环路;
	static int visit[maxsize];
	static int finished[maxsize];
	static int flag = 0;	//标记位

	if (flag) return 1;	//flag 用于对遍历进行截支，满足条件直接返回，不再继续遍历
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	finished[v] = 1; // finished[i]=1 表示还在本轮遍历之中，再次访问到自己说明存在环路
	//printf("%d ",v);
	while(p!=NULL)
	{	
		if (finished[p->vex]==1)
		{
			flag=1; 	// 同一个节点被再次访问， 说明存在环路；
			return 1;	// 已检测到回路直接返回；
		}
		if(visit[p->vex]==0)
		{
			DetectCircle(G,p->vex);
			finished[p->vex]=0;
		}
		p = p->nextarc;
	}
	return flag;
}


int DetectPath(AGraph *G, int v, int j, int L)
{
	//检测 i， j 点之间是否存在长度为 L 的路径 
	//采用回溯 DFS 算法
	
	static int visit[maxsize];
	static int path[maxsize];
	static int d = 0;	//d 为已经经过的路径长度，初始为 0;
	static int flag = 0;
	//if(flag) return flag;
	ArcNode *p = G->Adjlist[v].firstarc;
	path[d] = v;
	if (v==j && d==L)	//d==L 输出i j之间长度为 L 的路径， d==d 可以输出 i j 之间所有路径；
	{
		for (int i = 0; i <= d; i++)
			printf("%d ",path[i]);
		printf("\n");
		flag = 1;
	}
	visit[v] = 1;
	d++;
	while(p!=NULL)
	{
		//if (!visit[p->vex] || p->vex==j)	//检测是否包含 j 的环路，若存在，则遍历会回到 j，此时visit肯定标记为1，需要强制访问；
			//DetectPath(G,p->vex,j,L);
		
		if (!visit[p->vex])		//检测 v j 不同时的路径
			DetectPath(G,p->vex,j,L);
			
		p = p->nextarc;
	}
	//退出时将visit释放
	visit[v]=0;
	--d;
	return flag;
} 


void TopoSort(AGraph *G, int v)
{	//深度优先拓扑排序
	static int visit[maxsize];
	static int TPstack[maxsize]; 	//排序栈
	static int top = 0;
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	while (p!=NULL)
	{
		if (!visit[p->vex])
			TopoSort(G, p->vex);
		p = p->nextarc;
	}

	TPstack[top++] = v;	//递归退出节点时节点入栈，栈序列为逆拓扑序列
	if (top==maxsize)
	{
		printf("TopoSort:");
		for (int i = maxsize-1; i >= 0; i--)
			printf("%d ", TPstack[i]);
	}
}

void SHeapUpAdjust(HeapNode* Heap, int k)
{	//小顶堆单个元素的上浮过程,k上浮元素位置
	int i=k, j=k/2;
	HeapNode temp = Heap[k];
	while (j>0)
	{
		if (temp.cost < Heap[j].cost)
		{
			Heap[i] = Heap[j];
			i = j;		//继续检查节点是否还需要上浮
			j = j/2;
		}
		else break;
	}
	Heap[i] = temp;
}

void SHeapDownAdjust(HeapNode* Heap, int k, int h)
{   // 小顶堆单个元素的下沉过程，k: 要调整的元素位置;  h: 堆的总长度
	int i = k, j = 2*k;
	HeapNode temp = Heap[i];
	while(j<=h)
	{
		if (j<h && Heap[j].cost > Heap[j+1].cost) j++;
		if (temp.cost > Heap[j].cost)
		{
			Heap[i] = Heap[j];
			i = j;
			j = 2*j;
		}
		else break;
	}
	Heap[i] = temp;
}

void HeapDijkstra(AGraph *G, int v)
{	
	int dist[maxsize], path[maxsize], isJoin[maxsize];
	int num = 0; //堆中有效节点个数
	int pos; //定位节点在堆中的位置
	ArcNode *p;
	HeapNode heap[maxsize+1]; 
	for (int i = 0; i < maxsize+1; i++) //初始化数组
	{
		if (i<maxsize)
		{
			dist[i] = MAX;
			path[i] = -1;
			isJoin[i] = 0;
		}
		heap[i].cost=MAX; // 初始cost为MAX	
		heap[i].vex = -1;	// 节点初始化为-1
	}
	dist[v] = 0;
	path[v] = -1;
	isJoin[v] = 1;
	for (int i = 0; i < G->v - 1; ++i)
	{
		/* 
		思路： 建立一个堆对边按权值进行堆排序，堆内节点为{node;cost}，根据cost排序
		问题：排序完成后边的位置发送了变化，更新权值如何定位到对应的边，遍历堆为最坏情况(结果还是遍历了)
		时间复杂度：
		 */
		p = G->Adjlist[v].firstarc;
		while (p!=NULL)	// 节点入堆
		{
			if(isJoin[p->vex]) //若边已加入，跳过
			{
				p=p->nextarc; 
				continue;
			}
			pos = 0;
			for (int k = 1; k < num+1; k++) //定位节点在heap中的位置
			{
				if(heap[k].vex==p->vex)
				{
					pos = k;
					break;
				}
			}
			if(pos && p->cost + dist[v] < heap[pos].cost)//堆中已有p->vex，且v到p->vex + dist[v] 的距离小于现存距离，更新权值
			{
				heap[pos].cost =  p->cost+dist[v];
				path[p->vex] = v;	//记录新路径
			}
			if(!pos)	// 堆中无p->vex 点， 有效节点数num+1，在新位置填入新节点
			{
				heap[++num].vex = p->vex;
				heap[num].cost = p->cost + dist[v];
				path[p->vex] = v;
			}
			SHeapUpAdjust(heap, num);	// 堆底上浮
			p=p->nextarc; 
		}
		dist[heap[1].vex] = heap[1].cost;	
		v = heap[1].vex; 	// 以堆顶节点开始下一次
		isJoin[v] = 1;
		heap[1] = heap[num--]; 	//换掉堆顶节点，有效节点数-1
		SHeapDownAdjust(heap, 1, num); 	//堆顶下沉
	}
}

void Dijkstra(int v)
{
	//DiEdge为有向矩阵图
	int dist[maxsize];
	int path[maxsize];
	int isJoin[maxsize];
	for (int i = 0; i < maxsize; i++)
	{
		dist[i] = MAX;
		path[i] = -1;
		isJoin[i] = 0;
	}
	
	dist[v] = 0;
	path[v] = -1;
	isJoin[v] = 1;
	int n = v, min = MAX;
	for (int i = 0; i < maxsize-1; ++i)
	{
		for (int i = 0; i < maxsize; ++i)//遍历更新权值
			if(dist[n] + DiEdge[n][i]<dist[i] && !isJoin[i]) //节点n到i的距离+起始节点到n的距离<起始节点到i的距离
			{
				dist[i] = DiEdge[n][i] + dist[n];	// 更新dist， 换更小的
				path[i] = n;	// 路径由n到i
			}
		min = MAX;
		for (int i = 0; i < maxsize; ++i) //找到权值最小的一个 然后加入
			if (dist[i]<min && !isJoin[i]) 
			{
				min = dist[i];
				n = i;
			}
		isJoin[n] = 1;
	}
}

int main()
{
	AGraph *G = InitAGraph();

	DispalyAGraph(G);
	//DFS(G, 0);
	//MDFS(0, 6);
	//printf("lenth：%d \n", MDFS1(0,6));
	printf("Have Path?:%s\n",(DetectPath(G, 0, 4, 2))?"YES":"NO");
	printf("Have Circuit?:%s\n",(DetectCircle(G, 0))?"YES":"NO");
	TopoSort(G, 0);
	Dijkstra(0);
	HeapDijkstra(G, 0);
	return 0;
}