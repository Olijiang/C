#include <stdio.h>
#include <stdlib.h>

#define N 20

int main()
{
    int a,b;
    int n=0;
    int ma[N][2];
    while (scanf("%d %d",&a,&b)){
        if (a==0 && b==0) break;
        ma[n][0] = a;
        ma[n][1] = b;
        n++;
    }
    
    int count=0;
    while (scanf("%d %d",&a,&b)){
        if (a==0 && b==0) break;
        for (int j = a; j <= b; j++){
            count=0;
            for (int i = 0; i < n; i++)
                if (ma[i][0]<=j && ma[i][1]>=j)
                    count++;
            printf("%d\n",count);
        }
    }
    return 0;
}