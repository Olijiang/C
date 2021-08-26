#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    int ma[200002];
    while (scanf("%d %d",&a,&b)){
        if (a==0 && b==0) break;
        ma[a]++;
        ma[b+1]--;
    }
    for (int i = 1; i < 200002; i++)
        ma[i] += ma[i-1];
    
    while (scanf("%d %d",&a,&b)){
        if (a==0 && b==0) break;
        for (int j = a; j <= b; j++)
            printf("%d\n",ma[j]);
    }
    return 0;
}