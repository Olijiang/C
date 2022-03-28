#include <stdlib.h>
#include <stdio.h>

int a[10] = {53,17,78,9,45,65,87,32,97,22};
int n = sizeof(a)/sizeof(a[0])-1; //数组最后一个下标,即数组长度-1

void InsertSort();	//插入排序
void HalfSort();	//折半排序
void ShellSort();	//希尔排序
void QuickSort();	//快速排序
void Reverse();		//逆序数组

void InsertSort(int a[])
{
	//
	int i, j, temp;
	for (i = 1; i < n; ++i)
		if (a[i]<a[i-1])
		{
			temp = a[i];
			for (j = i; j>0 && temp<a[j-1]; --j)
				a[j] = a[j-1];
			a[j] = temp;
		}
}

void HalfSort(int a[])
{
	//主要是在寻找新元素插入位置时的方法不同
	int i, j, temp;
	int high, low, mid;
	for (i = 1; i <= n; ++i)
		if (a[i]<a[i-1])
		{
			temp = a[i];

			//差别部分
			low = 0;
			high = i-1;
			while(low<=high)
			{
				mid = (low+high)/2;
				if (a[mid]<=temp)
					low = mid + 1;
				else high = high - 1;
			}

			//最终low会停留在大于key的一边，high在小于等于key的一边
			for (j = i; j > low; --j)//low到i的的元素全体后移一位
				a[j] = a[j-1];
			//将key插入到low位置
			a[low] = temp;
		}
}

void ShellSort(int a[])
{

	int d = 3, temp;
	int i, j;
	while(d>=1)
	{
		for (i = d; i < n; ++i)
			if (a[i]<a[i-d])
			{
				temp = a[i];
				for (j = i; j >=0 && temp<a[j-d]; j=j-d)//注意此处是temp小于a[j-d],而不是 a[j]<a[j-d] ！！！.此处错误不止一次！！
					a[j] = a[j-d];
				a[j] = temp;
			}
		d = d/2;
	}
}

int BubbleSort(int *a, int n)
{
	int i, j, temp;
    int flag=1;
	for (i = 0; i < n; ++i)
    {
        flag=0;
		for (j = 0; j < n-i-1; ++j)
        {
            if(a[j]==a[j+1]) return 1;
			if (a[j]>a[j+1])
			{
                flag=1;
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
        }
        if(!flag) return 0;
    }
}


void QuickSort(int a[], int low, int high)
{
	if (low>=high) return;
	int L = low, H = high;
	int temp = a[L];
	while(L<H)
	{
		while(L<H && a[H]>=temp) --H;
		a[L] = a[H];	//此处不能写成a[L++] = a[H]，因为若本次循环没有比temp小的数，那么有H==L，经过a[L++] = a[H] 会导致 L 比 H 大1，指向错误的位置
		while(L<H && a[L]<=temp) ++L;	//但a[L] = a[H]，会有已经确定的a[L]<temp重复判断一次，但结果是正确的。
		a[H] = a[L];
	}
	a[L] = temp;
	QuickSort(a, low, L-1);
	QuickSort(a, L+1, high);
}

int SNum_k(int *nums, int low, int high, int k)
{
	if (low>high) return -1;
	int L = low, H = high;
	int temp = nums[L];
	while(L<H)
	{
		while(L<H && nums[H]>temp) --H;
		nums[L] = nums[H];	
		while(L<H && nums[L]<temp) ++L;	
		nums[H] = nums[L];
	}
	nums[L] = temp;
	if(L==k-1) printf("%d\n ",temp);	// 数组下标从0开始，第k大的数在k-1的位置
	if(L<k-1) SNum_k(nums, L+1, high, k);	//若当前轴枢位置小于k-1，说明第k大的数在轴枢右边
	else SNum_k(nums, low, L-1, k);		//若当前轴枢位置大于k-1，说明第k大的数在轴枢左边
}

void Reverse(int a[])
{
	int L=0, H=n, temp;
	while(L<H)
	{
		temp = a[L];
		a[L++] = a[H];
		a[H--] = temp;
	}
}

void ReverseT(int a[])
{
	int L=0, H=n;
	while(L<H)
	{
		a[L]+=a[H];
		a[H] = a[L]-a[H];
		a[L++] = a[L]-a[H--];
	}
}

void Show(int a[])
{
	for (int i = 0; i <= n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}




int main()
{
	//InsertSort(a);
	HalfSort(a);
	//ShellSort(a);
	//BubbleSort(a, n);
	Show(a);
	//QuickSort(a,0,n);
	//ReverseT(a);
	SNum_k(a, 0,n,4);
	
	return 0;
}