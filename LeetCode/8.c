#include <stdio.h>

int myAtoi(char * s){
    int k = 0;
    int res = 0, minus = 1;
    for (int i = 0; s[k]==' '; i++) k++;
    switch (s[k])
    {
        case '-':
            minus = -1;
            k++;
            break;
        case '+':
            minus = -1;
            k++;
            break;
        default:
            break;
    }

    if (s[k]<'0' && s[k]>'9') return 0;
    
    while(s[k]>='0' && s[k]<='9')
    {
        if (res*minus>=214748365) return 2147483647;
        if (res*minus==214748364 && (s[k]-'0')>=7) return 2147483647;
        if (res*minus<= -214748365) return -2147483648;
        if (res*minus== -214748364 && (s[k]-'0')>=8) return -2147483648;
        res = res*10 + (s[k++]-'0');
    }
    res *= minus;
    return res; 
}



int main(int argc, char const *argv[])
{
    char *s = "-2147483648";
    printf("%d ",myAtoi(s)) ;
    return 0;
}
