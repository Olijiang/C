#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    char buf[50];
    getcwd(buf, sizeof(buf));
    printf("%s\n",buf);

    FILE *fp;
    char *ch=NULL;
    if ((fp=fopen("demo.txt","w"))==NULL)//判断文件是否打开成功
    {
        printf("Failure to open demo.txt");
        exit(0);
    }
    //printf("Please input numbers,end up with Enter\n");
    
    ch = "i am a student";
    printf("%c\n",ch[0]);
    printf("%c\n",ch[1]);
    printf("%p\n",*ch);
    printf("%p",ch);
    fputs(ch, fp);
    

    fclose(fp);
    /*
    if ((fp=fopen("demo.bin","rb"))==NULL)
    {
        printf("Failure to open demo.bin");
        exit(0);
    }
    while ((ch = fgetc(fp))!=EOF)
    {
        if (isprint(ch))
        {
           printf("%c\t",ch);
        }
        else printf("%d\t",ch);
    
    }
    fclose(fp);
    */
    //system("pause");
    return 0;
}
