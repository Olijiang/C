#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input()
{
    // �ַ�����̬��������
    // �����ַ�ָ��
    int n = 0, len=10; 
    char c;
    char *ch = (char *)malloc(len);
    char *sh = NULL;
    while((c = getchar())!='\n')
    {
        if (n<len)
            ch[n++] = c;
        else
        {
            len+=10;
            sh = (char *)malloc(len);
            if (sh==NULL) return NULL;
            strcpy(sh,ch);
            ch = sh;
            ch[n++] = c;
        }
    }
    ch[n++] = '\0';
    return ch;
}


int KHmatch(char *ch)
{
    int i=0, top = -1;
    char stack[20];
    while (ch[i]!='\0')
    {
        if (ch[i] == '(' || ch[i] == '[')
            stack[++top] = ch[i];
        else
        {
            if (ch[i] == ')' && stack[top] == '(') top--;
            else if (ch[i] == ']' && stack[top] == '[') top--;
            else return 0;
        }
        i++;
    }
    if (top == -1) return 1;
    else return 0;
}

int main()
{
    char ch[20];
    //scanf("%s",&ch);
    //printf((KHmatch(ch)?("YES"):("NO")));
    char *sh;
    sh = input();
    printf("%s",sh);
    return 0;
}
