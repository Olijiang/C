#include <stdio.h>
#include <stdlib.h>
#define maxsize 7
#define _WQ 100
// 本部分 使用有向带权图 求解最小生成树


int AdjMa[maxsize][maxsize] = {
	{_WQ,4,6,6,_WQ,_WQ,_WQ},
	{_WQ,_WQ,1,_WQ,7,_WQ,_WQ},
	{_WQ,_WQ,_WQ,_WQ,6,4,_WQ},
	{_WQ,_WQ,2,_WQ,_WQ,5,_WQ},
	{_WQ,_WQ,_WQ,_WQ,_WQ,_WQ,6},
	{_WQ,_WQ,_WQ,_WQ,1,_WQ,8},
	{_WQ,_WQ,_WQ,_WQ,_WQ,_WQ,_WQ}};


typedef struct
{
	int Vex[maxsize];	//顶点表
	int Edge[maxsize][maxsize]; //邻接矩阵，边表
	int v,e; //当前顶点的顶点数和边数
}MGraph;	//邻接矩阵

void InitMGraph(MGraph *G, int Edge[maxsize][maxsize])
{
	int n;
	for(int i=0;i<maxsize;i++)
		for (int j = 0; j < maxsize; ++j)
		{
			G->Edge[i][j] = Edge[i][j];
			n++;
		}
	G->v = maxsize;
	G->e = n;
	for (int i = 0; i < maxsize; ++i)
		G->Vex[i] = i;
}

void DisplayMGraph(MGraph G)
{
	for (int i = 0; i < maxsize; ++i)
	{
		printf("%d---", G.Vex[i]);
		for (int j = 0; j < maxsize; ++j)
			if (G.Edge[i][j]<_WQ)
				printf("-%d", G.Vex[j]);
		printf("\n");
	}
}

int prim(MGraph G, int v0)
{	//只能用于无向图
	int isJoin[maxsize], lowCost[maxsize];//定义数组时长度只能用常量，G.v属于变量，不可行
	int min=_WQ, n = v0;
	int sum=0;
	for (int i = 0; i < G.v; ++i) lowCost[i]=10, isJoin[i] =0;
	isJoin[n] = 1;
	for (int j = 0; j < G.v-1; ++j)
	{
	    min = _WQ;
		for (int i = 0; i < G.v; ++i)	//用与当前节点连接节点的权值与lowCost中的比较，取较小者保留到lowCost中
			if(G.Edge[n][i]<lowCost[i] && !isJoin[i]) lowCost[i] = G.Edge[n][i];
		for (int i = 0; i < G.v; ++i)	//找到当前lowCost中权值最小节点，加入树中。并以新节点重复这个过程
			if (lowCost[i]<min && !isJoin[i])
			{
				min = lowCost[i];
				n = i;	//主要用n值，最小权值节点的位置，来传递修改
			}
		isJoin[n] = 1;
		sum+=min;
	}
	return sum;
}

void Dijkstra(MGraph G, int v, int dist[], int path[])
{
	int isJoin[maxsize]={0};
	dist[v] = 0;
	path[v] = -1;
	isJoin[v] = 1;
	int n = v, min = _WQ;
	for (int i = 0; i < maxsize-1; ++i)
	{
		for (int i = 0; i < maxsize; ++i)//遍历更新权值
			if(G.Edge[n][i]+dist[n]<dist[i] && !isJoin[i])
			{
				dist[i] = G.Edge[n][i] + dist[n];
				path[i] = n;
			}
		min = _WQ;
		for (int i = 0; i < maxsize; ++i) //找到最小权值 然后加入
			if (dist[i]<min && !isJoin[i]) 
			{
				min = dist[i];
				n = i;
			}
		isJoin[n] = 1;
	}
}

void PrintPath(int path[], int v)
{
	int stack[maxsize], top = -1;
	while(path[v]!=-1) 
	{
		stack[++top] = v;
		v=path[v];
	}
	stack[++top] = v;
	while(top!=-1) printf("%d-", stack[top--]);
}

int main(int argc, char const *argv[])
{
	MGraph Myo;
	InitMGraph(&Myo, AdjMa);
	DisplayMGraph(Myo);
	//printf("%d\n", prim(Myo, 0));
	int dist[maxsize], path[maxsize];
	for (int i = 0; i < maxsize; ++i) dist[i]=_WQ, path[i]=0;
	Dijkstra(Myo, 0, dist, path);
	printf("\n---------DIST-----------\n");
	for (int i = 0; i < maxsize; ++i)
		printf("%d-", dist[i]);
	printf("\n---------PATH-----------\n");
	for (int i = 0; i < maxsize; ++i)
		printf("%d-", path[i]);
	int n = 6;
	printf("\n----PATH--FROM--%d-------\n",n);
	PrintPath(path, n);
	printf("+-+-+-+-DISTANT:%d\n", dist[n]);
	return 0;
}
