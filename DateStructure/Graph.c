#include <stdio.h>
#include <stdlib.h>
#define maxsize 8

//��������Ҫ�����ڽӾ����ڽӱ������ �� ͼ����ȱ���DFS ͼ�Ŀ�ȱ���BDF

//ͼΪ����Ȩֵ�� ����ͼ �� ����ͼ

typedef struct
{
	int Vex[maxsize];	//�����
	int Edge[maxsize][maxsize]; //�ڽӾ��󣬱߱�
	int v,e; //��ǰ����Ķ������ͱ���
}MGraph;	//�ڽӾ���

typedef struct ArcNode
{	//�߽ڵ�
	int vex; //��ǰ��ָ��Ľڵ���Ϣ
	struct ArcNode *nextarc;	//��һ����
}ArcNode;

typedef struct
{	//����ڵ�
	int vex;	//��������
	ArcNode *firstarc;	// ��������ĵ�һ����
}VNode;
typedef struct
{
	VNode Adjlist[maxsize];	//��������
	int v,e; //��ǰ����Ķ������ͱ���
}AGraph;	//�ڽӱ�

typedef struct tuble
{	// ��Ԫ�飬������ǰ����͵��������Ĵ���
    int vex;
    int cost;
}tuble;



int DetectCircle(AGraph *G, int v);// ����DFS �������ͼ���Ƿ���ڻ�·;
void DetectPath(AGraph *G, int v, int j, int L) ;//��� i�� j ��֮���Ƿ���ڳ���Ϊ L ��·�� 

/*  �����
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
/*  �����
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
	//����
	{0,1,0,1,1,1,0,0},
	{1,0,1,0,0,0,0,0},
	{0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,1},
	{0,0,1,0,1,0,1,0}};

int DiEdge[maxsize][maxsize]={
	//����
	{0,1,0,1,1,0,0,0},
	{0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1},
	{0,0,1,0,0,0,1,0}};

void InitMGraph(MGraph *G, int Edge[maxsize][maxsize])
{
	// �����ڽӾ����ͼ
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
	//�����ڽӾ��󴴽�һ���ڽӱ�ͼ
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
			{	//�ߴ���ʱ�����ں���
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
	// ����ڽӱ�ṹ��ͼ
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
	//v�������ʾ��������
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
	//�ǵݹ�
	static int Visit[maxsize] = {0};
	ArcNode *p = NULL;
	int stack[maxsize], top=-1;
	Visit[v-1] = 1;
	stack[++top] = v;
	printf("%d-", G->Adjlist[v-1].vex);// visit()
	while(top!=-1) //ջ��ʱֱ��return ������ѭ������
	{
		p = G->Adjlist[stack[top]-1].firstarc;
		while(p!=NULL && Visit[p->vex-1])	//Ҫȷ��p���ָ���ָ�� ���ܶ�����ʣ���Ȼ����
			p = p->nextarc; //����ָ���ָ��

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
		p = G->Adjlist[queue[front]-1].firstarc;//������ͷ�ڵ�ĵ�һ����
		printf("%d-", queue[front++]); //���ʶ�ͷ�ڵ�

		while(p!=NULL) //���ճ��ӵĽڵ����������ӽڵ���ӣ��Ѿ����������
		{
			if (!Visit[p->vex-1])
			{
				Visit[p->vex-1] = 1;
				queue[rear++] = p->vex;
			}
			p = p->nextarc;
		}
	}
	//printf("The last%d\n", queue[front-1]);
}


int HaveEdge(AGraph *G, int v, int j)
{
	//��� i j ֮���Ƿ����·��
	static int Visit[maxsize] = {0};
	ArcNode *p = G->Adjlist[v-1].firstarc;
	Visit[v-1] = 1;
	if(Visit[j-1] = 1) return 1; //���ʵ�j��Ԫ��˵��i��j�����·��������1
	//printf("%d-", G->Adjlist[v-1].vex);// visit()
	while(p!=NULL)
	{

		if (!Visit[p->vex-1])
			return HaveEdge(G,p->vex,j);
		p = p->nextarc;
	}
	return 0;
}



void DetectPath(AGraph *G, int v, int j, int L)
{
	//��� i�� j ��֮���Ƿ���ڳ���Ϊ L ��·�� 
	//���û��� DFS �㷨
	
	static int visit[10];
	static int path[10];
	static int d = 0;	//d Ϊ�Ѿ�������·�����ȣ���ʼΪ 0;
	ArcNode *p = G->Adjlist[v-1].firstarc;
	visit[v-1] = 1;
	path[d] = v;

	if (v==j && d==L)	//d==L ���i j֮�䳤��Ϊ L ��·���� d==d ������� i j ֮������·����
	{
		for (int i = 0; i <= d; i++)
			printf("%d ",path[i]);
		printf("\n");
	}
	d++;
	while(p!=NULL)
	{
		//��� v j ��ͬʱ��·��, ������Ƿ���� j �Ļ�·�������ڣ��������ص� j����ʱvisit�϶����Ϊ1����Ҫǿ�Ʒ��ʣ�
		//if (!visit[p->vex-1] || p->vex==j)	
			//DetectPath(G,p->vex,j,d,L);

		//��� v j ��ͬʱ��·��
		if (!visit[p->vex-1])		
			DetectPath(G,p->vex,j,L);

		p = p->nextarc;
	}
	//�˳�ʱ��visit�ͷ�
	visit[v-1]=0;
	--d;
} 



int DetectCircle(AGraph *G, int v)
{
	static int visit[10];
	static int finished[10];
	static int flag = 0;

	if (flag) return 1;	//�Ա������н�֧����������֮�䷵�أ����ټ�������
	// ����DFS �������ͼ���Ƿ���ڻ�·;
	ArcNode *p = G->Adjlist[v-1].firstarc;
	visit[v-1] = 1;
	finished[v-1] = 1; // finished[i]=1 ��ʾ���ڱ��ֱ���֮�У��ٴη��ʵ��Լ�˵�����ڻ�·
	while(p!=NULL)
	{
		if (visit[p->vex-1] && finished[p->vex-1]) 
		{
			flag=1; 	// ͬһ���ڵ㱻�ٴη��ʣ� ˵�����ڻ�·��
			return 1;
		}
		else if(visit[p->vex-1]==0)
		{
			DetectCircle(G,p->vex);
			finished[p->vex-1]=0;
		}
		p = p->nextarc;
	}
	if (flag) return 1;
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
	InitMGraph(&DiMyo, DiEdge);
	//printf("Directed MGraph\n");
	//DisplayMGraph(DiMyo);

	//printf("---------------------\n");
	AGraph *Ayo = InitAGraph(DiMyo);
	printf("Undirected AGraph\n");
	DispalyAGraph(Ayo);
	DetectPath(Ayo, 1, 8, 4);
	if(DetectCircle(Ayo, 1)) printf("Have circle");

/* 	for (int i = 0; i < 8; i++) visit[i] =0;
	if(DetectCircle(Ayo, 5)) printf("yes");
	else printf("None"); */

	//printf("---------------------\n");
	//AGraph *DiAyo = InitAGraph(DiMyo);
	//printf("Directed AGraph\n");
	//DispalyAGraph(DiAyo);
/* 	printf("\nDFS---------------------\n");
	DFS(Ayo,2);
	printf("\nDFS1---------------------\n");
	DFS1(Ayo,2);
	printf("\nBFS---------------------\n");
	BFS(Ayo,2); */

	//printf("%s\n", HaveEdge(Ayo, 1 ,5 )?("Exist 1-5"):("Not Exist 1-5"));

	return 0;
}






