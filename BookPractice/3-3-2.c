#include <stdio.h>

/*--------------------------
第三章思考题：

采用递归求n个字符的全排列
比如：集合{ 1,2,3}的全排列为：
{ 1 2 3 }
{ 1 3 2 }
{ 2 1 3 }
{ 2 3 1 }
{ 3 2 1 }
{ 3 1 2 }

-----------------------------*/
int perm(char a[],int k, int n)
{
	//对前k个字符进行全排列，n为总长度
	int temp;
	if (k==0)
	{
		for(int i = 0; i < n; ++i) printf("%c", a[i]);
		printf("\n");
	}
	else
	{
		for (int i = 0; i < k; ++i)
		{
			temp = a[i];
			a[i] = a[k-1];
			a[k-1] = temp;
			//for(int i = 0; i < 3; ++i) printf("%c ", a[i]);
			//printf("\nn = %d\n", n);
			perm(a, k-1, n);
			temp = a[i];
			a[i] = a[k-1];
			a[k-1] = temp;
		}

	}

}

int main(int argc, char const *argv[])
{
	char a[] = "1234";
	perm(a, 3, 4);
	return 0;
}