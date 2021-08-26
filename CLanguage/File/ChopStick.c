#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    if (n<8)
        printf("0");
    else
        printf("%d",n/2-n/4-1);
    return 0;
}
 