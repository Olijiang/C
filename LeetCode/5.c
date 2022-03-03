#include<stdio.h>
#include<stdlib.h>
//最长回文子串

char * longestPalindrome(char * s){
    
    int n=0, max=0, st=0;

    for (int i = 0; s[i]; i++) n++;

    for (int i = 0; s[i]; i++)
    {
        //中心单元素
        int k=i;
        int r=0;
        while(k-r>=0 && k+r<n && s[k-r]==s[k+r])
        {
            if (max<=r*2+1)
            {
                max = r*2+1;
                st = i-r; 
            }
            r++;
        }
        //中心双元素
        k=i;
        r=0;
        if (s[k]==s[k+1])
        {
            int h = k+1;
            while(k-r>=0 && k+r<n && s[k-r]==s[h+r])
            {
                if (max<=r*2+2)
                {
                    max = r*2+2;
                    st = i-r; 
                }
                r++;
            }
        }
    }
    s[max+st] = '\0';
    return &s[st];
}

int main(int argc, char const *argv[])
{
    char *s = "babad";
    printf("%s", longestPalindrome(s));
    return 0;
}


/* char * longestPalindrome(char * s){
    // 返回首尾相同的最长子串
    int n=0, max=0, st=0;
    int idx[128][2];
    for (int i = 0; i < 128; i++)
    {
        idx[i][0] = -1;
        idx[i][1] = -1;
    }
    for (int i = 0; s[i]; i++)
    {
        if(idx[s[i]][0]==-1) idx[s[i]][0]=i;
        else{
            idx[s[i]][1]=i;
            if (i - idx[s[i]][0] > max) max = i - idx[s[i]][0];
            st = idx[s[i]][0];
        }
    }
    n = max + 2;
    char *res = malloc(sizeof(int)*n);
    for (int k = 0; k < n-1; k++)
        res[k] = s[st+k];
    res[n-1] = '\0';
    return res;
} */