#include <stdio.h>
#include <stdlib.h>

char * longestCommonPrefix(char ** strs, int strsSize){
    int n=0;
    int flag=0;
    char c;
    while (1)
    {
        if(strs[0][n]=='\0') break; //最短的一个字符串到位
        else c = strs[0][n];    
        for (int i = 0; i<strsSize; i++)
            if (strs[i][n]!=c){ // 遇到不一样的直接返回
                flag = 1;
                break;
            }
        if (flag) break;
        n++;
    }
    strs[0][n] = '\0';  
    return strs[0];
}

int main(int argc, char const *argv[])
{
    char str[][10] = {"flower","flow","flight"};

    
    return 0;
}
