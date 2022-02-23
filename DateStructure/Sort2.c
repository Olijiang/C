#include <stdio.h>

//堆栈排序,时间复杂度为 n*log2n
int nums[11] = {0,53,17,78,9,45,65,87,32,22,97};//堆排序的数组下标需要从1开始存入数据
int n = sizeof(nums)/sizeof(nums[0])-1; //数组最后一个下标,即数组长度-1

void Show();
void Sift();
void SHeapDownAdjust();
void BHeapDownAdjust();

void Down(int Heap[], int i,int k)
{   //j将Heap[i]为根节点的子树调整为大顶堆
	//递归方法实现
    int f;
    if (i>k/2)//节点是叶子节点
		return;
	else if (2*i==k)//节点只有左孩子
		f = 0;
	else f = (Heap[2*i]>Heap[2*i+1])?(0):(1);//节点有左右孩子，取其大者
	if (Heap[i]<Heap[2*i+f])
	{
		Heap[0] = Heap[i];
		Heap[i] = Heap[2*i+f];
		Heap[2*i+f] = Heap[0];
	}
	Down(Heap, 2*i + f, k);
}

void Sift(int Heap[], int l, int h)
{	//j将Heap[l]为根节点的子树调整为大顶堆
	//采用非递归方法
	int i=l, j=2*i;
	int temp = Heap[i];
	while (j<=h)
	{
		if (j<h && Heap[j]<Heap[j+1]) j++;//说明最后一个节点是右节点，取左右节点较大者，若是 j=h ，最后一个节点是左节点，那么访问 2i+1 非法
		if(temp<Heap[j])
		{
			Heap[i] = Heap[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else break;
	}
	Heap[i] = temp;
}

void HeapSort(int Heap[])
{	//首先遍历建堆，将第一个元素与最后一个元素交换，调整第一个元素的位置
	int temp;
	for (int i = n/2; i > 0; --i)
		//Down(i,n);	//递归
		BHeapDownAdjust(Heap, i,n);		//非递归
	for (int i = n; i > 0; i--)
	{	//把第一个和最后一个交换
		temp = Heap[i];
		Heap[i] = Heap[1];
		Heap[1] = temp;
		BHeapDownAdjust(Heap, 1,i-1);	
	}
}


void SHeapDownAdjust(int Heap[], int l, int h)
{	//j将Heap[l]为根节点的子树调整为小顶堆
	//Heap[l] 元素的下沉过程
	// l 和 h 为数组调整范围的 低位 和 高位
	int i=l, j=2*l;
	int temp = Heap[i];
	while (j<=h)
	{
		if (j<h && Heap[j]>Heap[j+1]) j++;
		if (temp>Heap[j])
		{
			Heap[i] = Heap[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else break;
	}
	Heap[i] = temp;
}

void BHeapDownAdjust(int Heap[], int l, int h)
{	//j将Heap[l]为根节点的子树调整为大顶堆
	//Heap[l] 元素的下沉过程
	// l 和 h 为数组调整范围的 低位 和 高位
	int i=l, j=2*l;
	int temp = Heap[i];
	while (j<=h)
	{
		if (j<h && Heap[j]<Heap[j+1]) j++;
		if (temp<Heap[j])
		{
			Heap[i] = Heap[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else break;
	}
	Heap[i] = temp;
}

void PrintNumK(int k, int n)
{
	// 输出第 k 小的数

	// 建立一个长度为 k 的数组堆排序，每次用原数组的下一个元素换掉堆顶最小元素，数组遍历完后堆顶元素就是目标元素；
	int Heap[k+1];
	int i;
	for (i = 0; i < k; i++)  Heap[i+1] = nums[i];
	for (i = k/2; i > 0; i--) BHeapDownAdjust(Heap, i, k);
	for (i = k; i < n; i++)
	{
		if(Heap[1] > nums[i]) Heap[1] = nums[i]; //外部元素比堆顶大时，把堆顶元素换掉  
		else continue;

		BHeapDownAdjust(Heap, 1, k);
	}
	printf("%d",Heap[1]);
}


void Show()
{
	for (int i = 1; i <= n; ++i)
		printf("%d ", nums[i]);
	printf("\n");
}

int main(){
	//{0,53,17,78,9,45,65,87,32,22,97}
	HeapSort(nums);
	Show();
	PrintNumK(3,n+1);
	return 0;
}


