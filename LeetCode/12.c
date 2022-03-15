#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * intToRoman(int num){
    
    
    char map[4][10][5] = {
        {"", "I", "II", "III", "IV", "V", "VI" ,"VII", "VIII", "IX"}, // 0-9 个位
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM", "", "", "", "", "", ""},
    };
    char *roman = malloc(sizeof(char)*20);
    roman[0] = '\0';
    int k=1000;
    for (int i = 3; i >= 0; i--)
    {
        int t = num/k;
        strcat(roman, map[i][t]);
        num %= k;
        k /= 10;
    }
    return roman;
}


int main(int argc, char const *argv[])
{
    int num = 1355;
    printf("%s ", intToRoman(num));
    return 0;
}
