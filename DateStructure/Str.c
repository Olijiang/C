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
	mystr* str = malloc(sizeof(mystr));
	str->ch = malloc(50*sizeof(char));
	str->len = 0;
	
	int i=0;
	while(a[i]!='\0')
	{
		str->ch[str->len+1] = a[i++];
		str->len++;
	}
	return *str;
}

void show_date(mystr str)
{
	int i=1;
	while(i<=str.len) printf("%c", str.ch[i++]);
}

void cop(mystr str, char *substr, int n, int m)
{
	int i;
	for (i = 0; i <= m-n; ++i)
	{
		substr[i] = str.ch[n+i];
	}
	substr[i] = '\0';
}

void getnextval(mystr str, int *nextval)
{
	int i=1,j=0;
	nextval[1] = 0;
	while(i<str.len)
	{
		if(j==0||str.ch[i]==str.ch[j])
		{
			++i;++j;
			if (str.ch[i]==str.ch[j]) nextval[i]=nextval[j];
			else nextval[i]=j;
		}
		else j=nextval[j];	//j 指针向前回退
	}
}

int KMP(mystr str, mystr substr, int *nextval)
{
	int i=1,j=1;
	while(i<=str.len&&j<=substr.len)
	{
		if (j==0||str.ch[i]==substr.ch[j])
		{
			i++;
			j++;
		}
		else j=nextval[j];

		if (j>substr.len) return i-substr.len;
	}
	return 0;
}

void del(mystr *str, int start, int spand)
{
	//start:开始位置　　spand:删除长度
	int i=start,j=spand;
	if (i+j > str->len)
	{
		str->len = i-1;
		str->ch[i] = '\0';	
	}
	else
	{
		while(i+j <= str->len)
			str->ch[i++] = str->ch[i+j];
		str->len = str->len-j;
	}

}

int main(int argc, char const *argv[])
{
	//char a[] = "man always remenber love becuase of remance only";
	//char b[] = "remance";
	char a[] = "aaabaaabbbabaa";
	char b[] = "babb";
	int nextval[8];
	mystr stra = init_mystr(a);
	mystr strb = init_mystr(b);

	getnextval(strb, nextval);
	int k = KMP(stra,strb,nextval);
	printf("start:%d  end:%d\n",k, strb.len+k);
	show_date(stra);
	printf("\n");
	//del(&strb, 1,4);
	show_date(strb);
	return 0;
}