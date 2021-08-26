#include <stdio.h>
#include <stdlib.h>

//通过先序遍历建立二叉树 ， 空树用 # 表示  For：abc##de#g##f###

static int ko=0;    //用全局变量替代递归传参

typedef struct node
{
    char val;
    struct node *LCh;
    struct node *RCh;
}Node,*BTree;

BTree CreatBtree(char ch[], BTree bt)
{
    if (ch[ko]!='\0')
    {
        if (ch[ko]=='#')
        {
            ko++;
            return NULL;
        }

        // 遍历建树模板！！
        bt = malloc(sizeof(Node));
        bt->val = ch[ko++];
        bt->LCh = CreatBtree(ch, bt->LCh);
        bt->RCh = CreatBtree(ch, bt->RCh);
    }
    return bt;
}

void show(BTree bt)
{
    if (bt!=NULL)
    {
        show(bt->LCh);
        printf("%c ",bt->val);
        show(bt->RCh);
    }
}

int main()
{
    char ch[100];
    BTree bt;
    while (scanf("%s",&ch)!=EOF)
    {
        if (ch[0]=='0') break;
        ko=0;
        bt = CreatBtree(ch,bt);
        show(bt);
        printf("\n");
    }
    
    return 0;
}
