#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mystr
{
	char *ch;
	int len;	
}mystr;

void init_mystr(mystr *yo)
{
	yo->ch = malloc(50*sizeof(char));
	yo->len = 0;
}

void add_date(mystr *yo, char a[])
{
	int i=0;
	while(a[i]!='\0')
	{
		yo->ch[yo->len+1] = a[i++];
		yo->len++;
	}
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
			if (yo.ch[i]!=yo.ch[j]) nextval[i]=j;
			else nextval[i]=nextval[j];
		}
		else j=nextval[j];
	}
}

int KMP(mystr yo, mystr subyo, int *nextval)
{
	int i=10,j=1,k=1;
	while(i<=yo.len&&j<=subyo.len)
	{
		if (j==0||yo.ch[i]==subyo.ch[j])
		{
			i++;j++;
		}
		else if(yo.ch[i]!=subyo.ch[j]) ++i;
		else j=nextval[j];
		if (j>subyo.len) return i-subyo.len-10;
	}
	return 0;
}

void del(mystr *yo)
{
	int i=2,j=7;
	if (i+j>yo->len)
	{
		yo->len = i-1;
		yo->ch[i] = '\0';	
	}
	else
	{
		while(i+j<=yo->len)
			yo->ch[i++] = yo->ch[i+j];
		yo->len = yo->len-j;
	}

}

int main(int argc, char const *argv[])
{
	char a[] = "man always remenber love becuase of remance only";
	char b[] = "remance";
	int nextval[8];
	//char *pre;
	mystr yoa, yob;
	init_mystr(&yoa);
	init_mystr(&yob);
	add_date(&yoa, a);
	add_date(&yob, b);

	getnextval(yob, nextval);
	int k = KMP(yoa,yob,nextval);
	printf("%d\n",k);
	//for (int i = 1; i < 8; ++i) printf("%d ", nextval[i]);
	show_date(yoa);
	printf("\n");
	del(&yob);
	show_date(yob);
	//show_date(yob);
	return 0;
}