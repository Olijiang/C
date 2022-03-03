#include <stdio.h>
#include <math.h>

int reverse(int x){
    // pow(2,31) = 2147483648
    int res=0;
    for (int i = 0; x; i++)
    {
        if (res > 214748364 || res < -214748364) return 0;
        res = res*10 + x%10;
        x /= 10;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int x = 153423646;
    printf("%d \n",reverse(x));

    return 0;
}
 