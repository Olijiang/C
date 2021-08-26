#include <stdio.h>

//堆栈排序
int a[11] = {0,53,17,78,9,45,65,87,32,22,97};//堆排序的数组下标需要从1开始存入数据
int n = sizeof(a)/sizeof(a[0])-1; //数组最后一个下标,即数组长度-1

void Show();
void Sift();


void Down(int i,int k)
{   //j将a[i]为根节点的子树调整为大顶堆
	//递归方法实现
    int f;
    if (i>k/2)//节点是叶子节点
		return;
	else if (2*i==k)//节点只有左孩子
		f = 0;
	else f = (a[2*i]>a[2*i+1])?(0):(1);//节点有左右孩子，取其大者
	if (a[i]<a[2*i+f])
	{
		a[0] = a[i];
		a[i] = a[2*i+f];
		a[2*i+f] = a[0];
	}
	Down(2*i + f, k);
}
void Sift(int l, int h)
{	//j将a[l]为根节点的子树调整为大顶堆
	//采用非递归方法
	int i=l, j=2*i;
	int temp = a[i];
	while (j<=h)
	{
		if (j<h && a[j]<a[j+1])//说明最后一个节点是右节点，取左右节点较大者，若是 j=h ，最后一个节点是左节点，那么访问 2i+1 非法
			j++;
		if(a[i]<a[j])
		{
			a[i] = a[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else
			break;
		a[i] = temp;
	}
}

void BuildHeap(int k)//将一颗树的前k个节点构建成大堆顶排序
{	
	for (int i = k/2; i > 0; --i)
		//Down(i,k);	//递归
		Sift(i,k);		//非递归
}

void HeapSort()
{
	int temp;
	BuildHeap(n);
	for (int i = n; i > 0; i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		Sift(1,i-1);
		
	}
}

void Show()
{
	for (int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}

int main(){
	//{0,53,17,78,9,45,65,87,32,22,97}
	HeapSort();
	//BuildHeap(n);
	Show();
	return 0;
}

