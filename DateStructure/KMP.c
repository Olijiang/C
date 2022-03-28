#include <stdio.h>
#include <stdlib.h>


int* getnext(char* s)
{
	int i=0,j=0;
    for (i = 0; s[i]; i++);
    int *next = malloc(sizeof(int)*(i+1));
	for (j = 0; j < i; j++) next[j]=-1;
	next[0] = 0;
    i=1,j=0;
    while(s[i])
	{
        if (j==0 && s[i]!=s[j]){
            if(next[i]==-1) next[i]=0;
        }
		else if(s[i]==s[j])
		{
			if(next[i]==-1) next[i]=next[j];
			++j;
		}
		else{
            if(next[i]==-1) next[i]=j;
            j=0;
        }
		i++;
	}
    return next;
}

int KMP(char* s, char* sub)
{
    if (sub[0]=='\0') return 0;
    int* next = getnext(sub);
	int i=0,j=0;
	while(s[i] && sub[j])
	{
        if (j==0 && s[i]!=sub[j]) i++;
        
		if (s[i]==sub[j])
		{
            j++;
			i++;
		}
		else  j=next[j];
		if (!sub[j]) return i-j;
	}
	return -1;
}

int main(int argc, char const *argv[])
{
    char a[] = "aabaaabaaac";
	char b[] = "aabaaac";

    printf("%d ",KMP(a,b));
    return 0;
}

