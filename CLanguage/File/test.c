#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n=0;

int func(int x)
{
    printf("%d ",++n);
    if (x<=3) return 1;
    else return func(x-4)+func(x-2)+1;
}

int main()
{
    func(func(8));
    return 0;
}