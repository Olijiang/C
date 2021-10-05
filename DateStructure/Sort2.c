#include <stdio.h>

//堆栈排序,时间复杂度为 n*log2n
int a[11] = {0,53,17,78,9,45,65,87,32,22,97};//堆排序的数组下标需要从1开始存入数据
int n = sizeof(a)/sizeof(a[0])-1; //数组最后一个下标,即数组长度-1

void Show();
void Sift();
void SmallSift();

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
		if (j<h && a[j]<a[j+1]) j++;//说明最后一个节点是右节点，取左右节点较大者，若是 j=h ，最后一个节点是左节点，那么访问 2i+1 非法
		if(temp<a[j])
		{
			a[i] = a[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else break;
	}
	a[i] = temp;
}

void HeapSort()
{	//首先遍历建堆，将第一个元素与最后一个元素交换，调整第一个元素的位置
	int temp;
	for (int i = n/2; i > 0; --i)
		//Down(i,n);	//递归
		Sift(i,n);		//非递归
	for (int i = n; i > 0; i--)
	{
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		Sift(1,i-1);
	}
}


void SHeadAdjust(int A[], int l, int h)
{	//j将a[l]为根节点的子树调整为小顶堆
	//单个元素的上浮过程
	// l 和 h 为数组调整范围的 低位 和 高位
	int i=l, j=2*l;
	int temp = A[i];
	while (j<=h)
	{
		if (j<h && A[j]>A[j+1]) j++;
		if (temp>A[j])
		{
			A[i] = A[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else break;
	}
	A[i] = temp;
}

void PrintNumK(int k)
{
	// 输出第 k 小的数

	// 建立一个长度为 k 的数组堆排序，每次用原数组的下一个元素换掉堆顶最小元素，数组遍历完后堆顶元素就是目标元素；
	int A[k+1];
	int i;
	for (i = 1; i < k+1; i++) A[i] = a[i];
	for (i = k/2; i > 0; i--) SHeadAdjust(A, i, k);
	for (i = k+1; i < n; i++)
	{
		A[1] = a[i];

		SHeadAdjust(A, 1, k);
	}
	printf("%d",A[1]);
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
	PrintNumK(5);
	return 0;
}


