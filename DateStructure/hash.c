#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int MaxSize = 1000;
const int MOD = 986;

typedef struct user{    //  每个用户的数据结构。
    char name[20];
    char tel_num[13];
}User;

typedef struct Node{    //  hash表内每个结点的数据结构。
    User user;
    struct Node *next;
}LNode, *Linklist;


int ELFhash(char *key){      // hash函数
    unsigned long h = 0;
    while(*key){
        h = (h<<4) + *key++;
        unsigned long g = h&0Xf0000000L;
        if(g) h ^= g>>24;
        h &= ~g;
    }
    return h % MOD;
}

int ELFhashInt(int *nums, int n){      // hash函数
    unsigned long h = 0;
    for (int i = 0; i < n; i++)
    {
        h = (h<<4) + nums[i++]*9999;
        unsigned long g = h&0Xfedc0000L;
        if(g) h ^= g>>24;
        h &= ~g;
    }
    return h % 2147483647;
}

void add_date(LNode **tail, char *name, char *tel_num){   //  尾插法将数据添加到链表，并将tail指向最新的节点
    LNode *p = NULL;
    p = (LNode *)malloc(sizeof(LNode));
    strcpy(p->user.name, name);
    strcpy(p->user.tel_num, tel_num);
    (*tail)->next = p;
    (*tail) = p;
    p->next = NULL;
}




void add_record(char *name, LNode *tail, LNode *hashtable[]){   // 计算name的hash值，以hash值为数组下标储存数据Node地址
    int key = ELFhash(name);
    hashtable[key] = tail;
}



char *query(char *name, LNode *hashtable[]){        //  计算要查询name的hash值，然后hash表数组中判断对应下标是否存在
    int key = ELFhash(name);
    if(hashtable[key]!=NULL) return hashtable[key]->user.tel_num;
    return NULL;
}



int main(){
    LNode *hashtable[MaxSize];    // hash表指针数组
    // 链表初始化
    memset(hashtable,0,sizeof(hashtable));
    Linklist head = NULL; //头结点
    Linklist tail = NULL; //尾结点
    head = (LNode *)malloc(sizeof(LNode));
    tail = head;
    int i;
    char name[8], tel_num[13], *result;
    char names[][8] = {"ming", "huang", "tian", "zheng", "qi", "yun", "wang"};
    char tel_nums[][13] = {"13959869247", "15196227587", "17396914413", "15456897789", "13565488896", "13664851136", "993745"};

    // 链表及hash表的初始化
    for(i = 0; i < 7; i++){
        strcpy(name, names[i]);
        strcpy(tel_num, tel_nums[i]);
        add_date(&tail, name, tel_num);//此处需要传入尾指针的地址才能对 tail 值做有效修改
        add_record(name, tail, hashtable);
    }

    while(1){
        printf("请输入要查询的用户名(按0退出): ");
        scanf("%s",name);
        if(!strcmp(name,"0")) break;// 0 作为结束标志
        result = query(name, hashtable);
        if(result==NULL) printf("\n对不起，没有你要查询的用户。" );
        else printf("你所查询用户的电话号码为：%s\n",result);
    }
    return 0;
}
