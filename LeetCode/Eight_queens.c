#include <stdio.h>
#include <stdlib.h>

// 

void Withdraw(int x, int y);
void Mark(int x, int y);
int Check(int x, int y);


int queen[9][9];
int n;
void Init() {for (int i = 1; i < 9; i++) for (int j = 1; j < 9; j++) queen[i][j] = 0;}
    
void display() 
{   
    printf("\n %d \n",++n);
    for (int i = 1; i < 9; i++)
    {
        for (int j = 1; j < 9; j++) 
            printf(" %c",(queen[i][j]==9)?('H'):('-'));
        printf("\n");
    }
}

void placeQueen(int k)
{
    if(k>8) return;
    int flag, i;
    for (i = 1; i < 9; i++)
    {
        flag = Check(k,i);
        if (!flag)
        {
            Mark(k,i);
            queen[k][i]=9;  // 占位
            placeQueen(k+1);
            if (k==8) display();
            Withdraw(k,i);
        }
    }
}

int Check(int x, int y)
{   //

    int i, k, l;
    for (i = 0; i < 9; i++) if(queen[i][y]==9) return 1;
    for (i = 0; i < 9; i++) if(queen[x][i]==9) return 1;
    for (k=x,l=y; k<9 && l<9; k++,l++) if (queen[k][l]==9) return 1;
    for (k=x,l=y; k>0 && l<9; k--,l++) if (queen[k][l]==9) return 1;
    for (k=x,l=y; k>0 && l>0; k--,l--) if (queen[k][l]==9) return 1;
    for (k=x,l=y; k<9 && l>0; k++,l--) if (queen[k][l]==9) return 1;

    return 0;
}

void Mark(int x, int y)
{
    int i, k, l;
    for (i = 0; i < 9; i++) queen[i][y]=1;
    for (i = 0; i < 9; i++) queen[x][i]=1;
    for (k=x,l=y; k<9 && l<9; k++,l++) queen[k][l]=1;
    for (k=x,l=y; k>0 && l<9; k--,l++) queen[k][l]=1;
    for (k=x,l=y; k>0 && l>0; k--,l--) queen[k][l]=1;
    for (k=x,l=y; k<9 && l>0; k++,l--) queen[k][l]=1;
}

void Withdraw(int x, int y)
{
    int i, k, l;
    for (i = 0; i < 9; i++) queen[i][y]=0;
    for (i = 0; i < 9; i++) queen[x][i]=0;
    for (k=x,l=y; k<9 && l<9; k++,l++) queen[k][l]=0;
    for (k=x,l=y; k>0 && l<9; k--,l++) queen[k][l]=0;
    for (k=x,l=y; k>0 && l>0; k--,l--) queen[k][l]=0;
    for (k=x,l=y; k<9 && l>0; k++,l--) queen[k][l]=0;
}


int main(int argc, char const *argv[])
{
    Init();
    //display();
    placeQueen(1);
    return 0;
}
