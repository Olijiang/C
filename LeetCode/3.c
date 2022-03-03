#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char val;
    struct node *next;
}node;

// method one 
int lengthOfLongestSubstring(char * s){
    int max=0, num=0;
    int hash[200]; //标记
    node *tmp, *head=NULL, *tail;
    
    for (int i = 0; i < 200; i++) hash[i] = 0;
    
    for (int i = 0; s[i]; i++)
    {
        if (hash[s[i]])
        {
            max = max>num?max:num;
            while (head->val!=s[i])
            {
                hash[head->val] = 0;
                head = head->next;
                num--;
            }
            head = head->next;
            num--;
        }
        tmp = malloc(sizeof(node));
        tmp->val = s[i];
        tmp->next = NULL;
        if (!head){
            head = tmp;
            tail = tmp;
        }
        else{
            tail->next = tmp;
            tail = tmp;
        }
        hash[s[i]] = 1;
        num++;
    }
    max = max>num?max:num;
    return max;
}

// method two
int LengthOfLongestSubstring(char * s){
    int hash[200];
    int max=0, n=0;
    int st=0;
    for (int i = 0; i < 200; i++) hash[i] = 0;
    for (int i = 0; s[i]; i++,n++)
    {
        if (hash[s[i]]){
            max = max>n?max:n;
            while (s[st]!=s[i]){
                hash[s[st]]=0;
                st++,n--;
            }
            st++,n--;
        }
        hash[s[i]]=1;
    }
    return max>n?max:n;
}

char * longestPalindrome(char * s){
    // 返回字符串
    int hash[128]={0};
    int index[2] = {0,0};
    for (int i = 0; s[i]; i++)
    {
        if(hash[s[i]]){
            int j = index[0];
            while (s[j]!=s[i]) hash[s[j++]]=0;
            hash[s[j]]=0;
            if (index[1]-index[0]<i-j)
            {
                index[0] = j;
                index[1] = i;
            }
        }
        else hash[s[i]] = 1;
    }
    int n = index[1]-index[0]+2;
    char *res = malloc(sizeof(int)*n);
    for (int i = 0; i < n-1; i++)
        res[i] = s[index[0]+i];
    res[n-1] = '\0';
    return res;
}

int main(int argc, char const *argv[])
{
    char* s = "acva";

    printf("%d ", LengthOfLongestSubstring(s));
    return 0;
}
