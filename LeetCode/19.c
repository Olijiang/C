#include <stdio.h>

typedef struct ListNode
{
	int data;
	struct ListNode *next;
}ListNode, *LinkList;

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode* p1 =head,* p2 =head;
    if(!head->next) return NULL;    //只有一个节点
    
    for(int i=0; i<n-1; i++) p2 = p2->next; //p2先走n-1步
    if (!p2->next) return p1->next; //p2->next;删除节点为头节点
    p2 = p2->next; //p2再走1步，使p2指向最后一个节点时，p1指向倒数第 n 个的前一个
    while(p2->next){
        p1 = p1->next;
        p2 = p2->next;
    }
    p1->next = p1->next->next;
    return head;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
