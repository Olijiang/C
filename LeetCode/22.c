#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate(char **res,int n, int *returnSize, int left, int right, char* s){
    static int k;
    if (left==0 && right==0)
    {   //记录数据
        res[(*returnSize)] = malloc(sizeof(char)*(n*2+1));
        strcpy(res[(*returnSize)], s);
        (*returnSize)++;
        return;
    }
    if (left==right)
    {
        s[k++] = '(';
        generate(res, n, returnSize, left-1, right, s);
        k--;    //退出递归时把值去掉，当前这个值的所有可以已经在递归内部完成
    }
    else{
        s[k++] = ')';
        generate(res, n, returnSize, left, right-1, s);
        k--;
        if (left>0)
        {
            s[k++] = '(';
            generate(res, n, returnSize, left-1, right, s);
            k--;
        }
    }
}

char ** generateParenthesis(int n, int* returnSize){
    char **res = malloc(sizeof(char*)*n*n);
    *returnSize = 0;
    char *s= malloc(sizeof(char)*(2*n+1));
    s[2*n] = '\0';
    generate(res, n, returnSize, n, n, s);
    return res;
}

void show(char** res, int Size){
    for (int i = 0; i < Size; i++) printf("%d:%s \n",i,res[i]);
}


int main(int argc, char const *argv[])
{
    int n = 8;
    int returnSize;
    char **res = generateParenthesis(n, &returnSize);
    show(res, returnSize);
    return 0;
}
