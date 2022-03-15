#include <stdio.h>
#include <string.h>

int romanToInt(char * s){
    char mapc[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int map[] = {1, 5, 10, 50, 100, 500, 1000};

    int num = 0;
    int temp = 9999;    // 记录上一个数，初始为无穷大
    for (int i = 0; s[i]; i++){
        int k=0;
        for (; k < 7; k++){ //找下标
            if (mapc[k] == s[i]){
                num += map[k];
                if (map[k]>temp && (temp==1 || temp==10 || temp==100)) num -= temp*2;  // 特殊情况
                temp = map[k];
                break;
            }
        }
    }
    return num;
}

int romanToInt2(char * s){
    int num=0;
    for (int i = 0; s[i]; i++){
        switch (s[i]){
            case 'I':
                if (s[i+1]=='V' || s[i+1]=='X') num -= 1;
                else num += 1;
                break;
            case 'V':
                num += 5;
                break;
            case 'X':
                if (s[i+1]=='L' || s[i+1]=='C') num -= 10;
                else num += 10;
                break;
            case 'L':
                num += 50;
                break;
            case 'C':
                if (s[i+1]=='D' || s[i+1]=='M') num -= 100;
                else num += 100;
                break;
            case 'D':
                num += 500;
                break;
            case 'M':
                num += 1000;
                break;
            default:
                break;
        }
    }
    return num;
}

int main(int argc, char const *argv[])
{
    char s[] = "III";
    printf("%d ", romanToInt(s));
    return 0;
}
