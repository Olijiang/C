#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int reverse(int a)  //³­µÄ
{
    int temp = 0;
    while(a!=0)
    {
        temp = temp*10 + a%10;
        a /= 10;
    }
    return temp;
}


int main()
{
    
    int a, b, sum;

    while((scanf("%d %d",&a,&b))!=EOF)
    {
        sum = reverse(a) + reverse(b);
        printf("%d\n", sum); 

    //cal(12, 13);
    }


    return 0;
}