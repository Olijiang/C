
#include <stdio.h>
#include <stdlib.h>


char ** letterCombinations(char * digits, int* returnSize){
    int n=0;
    char temp[4][4];
    for (int i = 0; digits[i]; i++,n++){
        switch (digits[i]){
        case '2':
            temp[n][0] = 'a';
            temp[n][1] = 'b';
            temp[n][2] = 'c';
            temp[n][3] = '0';
            break;
        case '3':
            temp[n][0] = 'd';
            temp[n][1] = 'e';
            temp[n][2] = 'f';
            temp[n][3] = '0';
            break;
        case '4':
            temp[n][0] = 'g';
            temp[n][1] = 'h';
            temp[n][2] = 'i';
            temp[n][3] = '0';
            break;
        case '5':
            temp[n][0] = 'j';
            temp[n][1] = 'k';
            temp[n][2] = 'l';
            temp[n][3] = '0';
            break;
        case '6':
            temp[n][0] = 'm';
            temp[n][1] = 'n';
            temp[n][2] = 'o';
            temp[n][3] = '0';
            break;
        case '7':
            temp[n][0] = 'p';
            temp[n][1] = 'q';
            temp[n][2] = 'r';
            temp[n][3] = 's';
            break;
        case '8':
            temp[n][0] = 't';
            temp[n][1] = 'u';
            temp[n][2] = 'v';
            temp[n][3] = '0';
            break;
        case '9':
            temp[n][0] = 'w';
            temp[n][1] = 'x';
            temp[n][2] = 'y';
            temp[n][3] = 'z';
            break;
        default:
            break;
        }
    }
    *returnSize = 0;
    char **res;
    if (n==0) return NULL;

    switch (n)
    {
    case 1:
        res = malloc(sizeof(char *)*(5));
        for (int i = 0; i < 4; i++){
            if (temp[0][i]!='0')
            {
                res[*returnSize] = malloc(sizeof(char)*(n+1));
                res[*returnSize][0] = temp[0][i];
                res[*returnSize][n] = '\0';
                (*returnSize)++;
            }
        }
        break;
    case 2:
        res = malloc(sizeof(char *)*(17));
        for (int i = 0; i < 4; i++){
            if(temp[0][i]!='0')
                for (int j = 0; j < 4; j++)
                    if (temp[1][j]!='0')
                    {
                        res[*returnSize] = malloc(sizeof(char)*(n+1));
                        res[*returnSize][0] = temp[0][i];
                        res[*returnSize][1] = temp[1][j];
                        res[*returnSize][n] = '\0';
                        (*returnSize)++;
                    }
        }
        break;
    case 3:
        res = malloc(sizeof(char *)*(65));
        for (int i = 0; i < 4; i++)
            if(temp[0][i]!='0')
                    for (int k = 0; k < 4; k++)
                        if(temp[1][k]!='0')
                            for (int j = 0; j < 4; j++)
                                if (temp[2][j]!='0')
                                {
                                    res[*returnSize] = malloc(sizeof(char)*(n+1));
                                    res[*returnSize][0] = temp[0][i];
                                    res[*returnSize][1] = temp[1][k];
                                    res[*returnSize][2] = temp[2][j];
                                    res[*returnSize][n] = '\0';
                                    (*returnSize)++;
                                }
        
        break;
     case 4:
        res = malloc(sizeof(char *)*(257));
        for (int i = 0; i < 4; i++)
            if(temp[0][i]!='0')
                    for (int k = 0; k < 4; k++)
                        if(temp[1][k]!='0')
                            for (int j = 0; j < 4; j++)
                                if (temp[2][j]!='0')
                                    for (int l = 0; l < 4; l++)
                                        if (temp[3][l]!='0')
                                        {
                                            res[*returnSize] = malloc(sizeof(char)*(n+1));
                                            res[*returnSize][0] = temp[0][i];
                                            res[*returnSize][1] = temp[1][k];
                                            res[*returnSize][2] = temp[2][j];
                                            res[*returnSize][3] = temp[3][l];
                                            res[*returnSize][n] = '\0';
                                            (*returnSize)++;
                                        }
        
        break; 
    default:
        break;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    char digits[] = "239";
    int returnSize = 0;
    char **res = letterCombinations(digits, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%s \n",res[i]);
    return 0;
}
