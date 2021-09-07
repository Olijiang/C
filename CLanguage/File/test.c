#include <stdio.h>
#include <stdlib.h>


typedef struct tuble
{
    int vex;
    int cost;
}tuble;

void change();

int main()
{

    tuble S[2];
    S[0].vex = 1;
    S[0].cost = 1;
    S[1].vex = 5;
    S[1].cost = 5;

    printf("1:%d %d\n",S[0].vex, S[0].cost);
    printf("2:%d %d\n",S[1].vex, S[1].cost);

    tuble temp;
    temp = S[0];
    S[0] = S[1];
    S[1] = temp;
    
    printf("1:%d %d\n",S[0].vex, S[0].cost);
    printf("2:%d %d\n",S[1].vex, S[1].cost);
    return 0;
}