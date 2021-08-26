#include <stdio.h>


int a[11] = {0,53,17,78,9,45,65,87,32,22,97};
int n = sizeof(a)/sizeof(a[0])-1; //数组最后一个下标,即数组长度-1


void Down(int i,int k)
{
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

void BuildHeap(int k)
{
	for (int i = k/2; i > 0; --i)
		Down(i,k);
}



void HeapSort()
{
	int temp;
	for (int i = n; i > 0; i--)
	{
		BuildHeap(i);
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
	}
}

int main(){

	HeapSort();
	//BuildHeap(n);
	for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
	return 0;
}

