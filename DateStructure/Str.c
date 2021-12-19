#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mystr
{
	char *ch;
	int len;	
}mystr;

mystr init_mystr(char *a)
{
	mystr* yo = malloc(sizeof(mystr));
	yo->ch = malloc(50*sizeof(char));
	yo->len = 0;
	
	int i=0;
	while(a[i]!='\0')
	{
		yo->ch[yo->len+1] = a[i++];
		yo->len++;
	}
	return *yo;
}

void show_date(mystr yo)
{
	int i=1;
	while(i<=yo.len) printf("%c", yo.ch[i++]);
}

void cop(mystr yo, char *subyo, int n, int m)
{
	int i;
	for (i = 0; i <= m-n; ++i)
	{
		subyo[i] = yo.ch[n+i];
	}
	subyo[i] = '\0';
}

void getnextval(mystr yo, int *nextval)
{
	int i=1,j=0;
	nextval[1] = 0;
	while(i<yo.len)
	{
		if(j==0||yo.ch[i]==yo.ch[j])
		{
			++i;++j;
			if (yo.ch[i]==yo.ch[j]) nextval[i]=nextval[j];
			else nextval[i]=j;
		}
		else j=nextval[j];	//j 指针向前回退
	}
}

int KMP(mystr yo, mystr subyo, int *nextval)
{
	int i=1,j=1;
	while(i<=yo.len&&j<=subyo.len)
	{
		if (j==0||yo.ch[i]==subyo.ch[j])
		{
			i++;
			j++;
		}
		else j=nextval[j];

		if (j>subyo.len) return i-subyo.len;
	}
	return 0;
}

void del(mystr *yo, int start, int spand)
{
	//start:开始位置　　spand:删除长度
	int i=start,j=spand;
	if (i+j > yo->len)
	{
		yo->len = i-1;
		yo->ch[i] = '\0';	
	}
	else
	{
		while(i+j <= yo->len)
			yo->ch[i++] = yo->ch[i+j];
		yo->len = yo->len-j;
	}

}

int main(int argc, char const *argv[])
{
	//char a[] = "man always remenber love becuase of remance only";
	//char b[] = "remance";
	char a[] = "ABDCABABCAC";
	char b[] = "ABCA";
	int nextval[8];
	mystr yoa = init_mystr(a);
	mystr yob = init_mystr(b);

	getnextval(yob, nextval);
	int k = KMP(yoa,yob,nextval);
	printf("start:%d  end:%d\n",k, yob.len+k);
	show_date(yoa);
	printf("\n");
	//del(&yob, 1,4);
	show_date(yob);
	return 0;
}