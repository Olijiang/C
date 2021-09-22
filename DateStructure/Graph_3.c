#include <stdio.h>
#include <stdlib.h>
#define maxsize 8

//Dji ���Ż�

typedef struct ArcNode
{	//�߽ڵ�
	int vex; //��ǰ��ָ��Ľڵ���Ϣ
	int cost; //�ߴ���
	struct ArcNode *nextarc;	//��һ����
}ArcNode;

typedef struct
{	//����ڵ�
	int vex;	//��������
	ArcNode *firstarc;	// ��������ĵ�һ����
}VNode;

typedef struct
{
	//�ڽӱ�
	VNode Adjlist[maxsize];	//��������
	int v,e; //��ǰ����Ķ������ͱ���
}AGraph;	

typedef struct tuble
{	// ��Ԫ�飬������ǰ����͵��������Ĵ���
    int vex;
    int cost;
}tuble;

int DiEdge[maxsize][maxsize]={
	{0,1,0,2,5,0,0,0},
	{0,0,3,0,0,3,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,6,0},
	{0,0,0,0,0,0,0,2},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0}};


AGraph *InitAGraph()
{
	//����һ���ڽӱ�ͼ
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
			{	// ���ߴ���,�½�һ���ڵ�
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
	// ����ڽӱ�ṹ��ͼ
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

void DFS(AGraph *G, int v)
{
	//v��ʾ������ʼ��
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
	static int visit[10];
	static int finished[10];
	static int flag = 0;

	if (flag) return 1;	//�Ա������н�֧����������֮�䷵�أ����ټ�������
	// ����DFS �������ͼ���Ƿ���ڻ�·;
	ArcNode *p = G->Adjlist[v].firstarc;
	visit[v] = 1;
	finished[v] = 1; // finished[i]=1 ��ʾ���ڱ��ֱ���֮�У��ٴη��ʵ��Լ�˵�����ڻ�·
	printf("%d ",v);
	while(p!=NULL)
	{
		
		if (visit[p->vex]==1 && finished[p->vex]==1) flag=1; 	// ͬһ���ڵ㱻�ٴη��ʣ� ˵�����ڻ�·��
		else if(visit[p->vex]==0)
		{
			DetectCircle(G,p->vex);
			finished[p->vex]=0;
			
		}
		
		p = p->nextarc;
	}
	if (flag) return 1;
	return 0;
}


int main()
{
	AGraph *Ayo = InitAGraph();
	printf("Directed AGraph\n");
	DispalyAGraph(Ayo);
	//DFS(Ayo, 0);
	if(DetectCircle(Ayo, 0)) printf("\nHave circle");
	return 0;
}