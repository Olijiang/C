#include <stdio.h>

int isValid(char * s){
     char st[10000];
     int top = -1;
     for(int i=0; s[i]; i++){
        if(top==-1){
            if(s[i]==')' || s[i]==']' || s[i]=='}') return 0;
            else st[++top] = s[i]; // 入栈
            continue;
        }
        if(s[i]==')' && st[top]=='(') top--;
        else if (s[i]==']' && st[top]=='[') top--;
        else if(s[i]=='}' && st[top]=='{') top--;

        
        st[++top] = s[i];
     }
    return (top==-1)?1:0;
}

int main(int argc, char const *argv[])
{
   char *s = "{[]}";
   printf(isValid(s)?"yes":"no");
    return 0;
}
