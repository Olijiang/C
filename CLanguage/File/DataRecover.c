
/*--------------------------------------------------------------------------------------
LBR有四个正整数a,b,c,d，他用这四个数字构造了一个3*3矩阵

a	b	a+b
c	d	c+d
a+c	b+d	a+b+c+d

但是实验室的某个diaoren偷偷擦掉了矩阵中的几个数字，现在需要你根据剩下的数字还原整个矩阵

第一行输入一个数字T(T<=12800)，代表数据组数
接下来输入的每组数据包含一个3*3的矩阵
0代表被擦去的数字

对于每组数据
如果可以复原矩阵，第一行输出"YES"，接下来三行输出复原后的矩阵  
否则输出一行"NO"

输入样例#:
3
2 3 0
5 7 0
0 0 0
0 0 5
0 0 12
7 10 17
0 3 5
0 0 0
0 10 17
输出样例#:
YES
2 3 5
5 7 12
7 10 17   
NO
YES
2 3 5
5 7 12
7 10 17
--------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int Check(int ma[3][3]);

int main()
{
    int ma[12800][3][3] = {0};        //enough for fives
    int n=0;      //how much data group
    int i=0,j=0;
    
    scanf("%d",&n);
    for(i=0;i<n;i++)
          for(j=0;j<3;j++)
              scanf("%d %d %d",&ma[i][j][0], &ma[i][j][1], &ma[i][j][2]);


    // int me[3][3] = 
    // {   {2,2,4},
    //     {0,2,0},
    //     {0,0,0},
    // }; 
    for(i=0;i<n;i++)
        Check(ma[i]);
    return 0;
}

int Check(int ma[3][3])     //判断矩阵能否复原
{
    for(int j=0;j<3;j++)        //横向校验数据
        if(ma[j][2] == 2) ma[j][0] = ma[j][1] = 1;
        else if (ma[j][0] && ma[j][1]) ma[j][2] = ma[j][0] + ma[j][1];
        else if (ma[j][0] && ma[j][2]) ma[j][1] = ma[j][2] - ma[j][0];
        else if (ma[j][1] && ma[j][2]) ma[j][1] = ma[j][2] - ma[j][1];
    for(int j=0;j<3;j++)        //纵向校验数据
        if(ma[2][j] == 2) ma[0][j] = ma[1][j] = 1;
        else if (ma[0][j] && ma[1][j]) ma[2][j] = ma[0][j] + ma[1][j];
        else if (ma[0][j] && ma[2][j]) ma[1][j] = ma[2][j] - ma[0][j];
        else if (ma[1][j] && ma[2][j]) ma[0][j] = ma[2][j] - ma[1][j];
    for(int j=0;j<3;j++)        //再次横向校验数据
        if(ma[j][2] == 2) ma[j][0] = ma[j][1] = 1;
        else if (ma[j][0] && ma[j][1]) ma[j][2] = ma[j][0] + ma[j][1];
        else if (ma[j][0] && ma[j][2]) ma[j][1] = ma[j][2] - ma[j][0];
        else if (ma[j][1] && ma[j][2]) ma[j][1] = ma[j][2] - ma[j][1];

    int mark = 1;   //如果还有 0 说明还原不了
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(!ma[i][j])
            {
                mark = 0;
                break;
            }

    if(mark)
    {
        printf("YES\n");
        for(int i=0;i<3;i++)
            printf("%d %d %d\n",ma[i][0], ma[i][1], ma[i][2]);
    }
    else printf("NO\n");

}

