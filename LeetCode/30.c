#include <stdio.h>
#include <stdlib.h>
// 找出 s 中所有由 words 中的单词组成的序列的起始位置
// 朴素算法，遍历 s，对 words 中的单词进行匹配，建立一个words的hash表标记词是否用过
// words在函数内退化为一维数组

int ELFhash(char *key){      // hash函数
    unsigned long h = 0;
    while(*key){
        h = (h<<4) + *key++;
        unsigned long g = h&0Xf0000000L;
        if(g) h ^= g>>24;
        h &= ~g;
    }
    return h % 2147483647;
}

void HalfSort(int *a, int n)
{
	//主要是在寻找新元素插入位置时的方法不同
	int i, j, temp;
	int high, low, mid;
	for (i = 1; i < n; ++i)
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

void QuickSort(int *a, int low, int high)
{
	if (low>=high) return;
	int L = low, H = high;
	int temp = a[L];
	while(L<H)
	{
		while(L<H && a[H]>=temp) --H;
		a[L] = a[H];	//此处不能写成a[L++] = a[H]，因为若本次循环没有比temp小的数，那么有H==L，经过a[L++] = a[H] 会导致 L 比 H 大1，指向错误的位置
		while(L<H && a[L]<temp) ++L;	//但a[L] = a[H]，会有已经确定的a[L]<temp重复判断一次，但结果是正确的。
		a[H] = a[L];
	}
	a[L] = temp;
	QuickSort(a, low, L-1);
	QuickSort(a, L+1, high);
}

int *findSubstring(char*s, char **words, int wordSize, int *returnSize){
    int n;
    int *res = malloc(sizeof(int)*10);
    for (n = 0; words[0][n]; n++);  //计算word长度
    char *key = malloc(sizeof(char)*(n+1));
    int *hash1 = malloc(sizeof(int)*wordSize);
    int *hashs = malloc(sizeof(int)*wordSize);
    for (int i = 0; i < wordSize; i++)
    {
        for (int j = 0; j < n; j++)
            key[j] = words[i][j];
        key[n] = '\0';
        hash1[i] = ELFhash(key);
    }
    //QuickSort(hash1, 0, wordSize-1);
    HalfSort(hash1, wordSize);
    *returnSize = 0;
    for (int i = 0; s[i+n*wordSize-1]; i++){
        int k;
        for (k = 0; k < wordSize; k++){
            for (int j = 0; j < n; j++)
                key[j] = s[i+k*n+j];
            key[n] = '\0';
            hashs[k] = ELFhash(key);
        }
        //QuickSort(hashs, 0, wordSize-1);
        HalfSort(hashs, wordSize);
        for (k = 0; k < wordSize; k++) //比较hashcode
            if (hash1[k]!=hashs[k]) break;
        
        if (k==wordSize) res[(*returnSize)++] = i;  //k==n,说明匹配了n个单词, 即都匹配了
    }
    return res;
}


int main(int argc, char const *argv[])
{
    char *s = "barfoothefoobarman";
    char words[][5] = {"foo","bar"};
    char *p[2];
    for (int i = 0; i < 2; i++) p[i] = words[i];

    int returnSize;
    int *res = findSubstring(s, p, 2, &returnSize);
    for (int i = 0; i<returnSize; i++) printf("%d ", res[i]);
    
    return 0;
}
