/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};

void SHeapDownAdjust(struct ListNode** heap, int l, int h)
{	//将heap[l]为根节点的子树调整为小顶堆
	//单个 heap[l] 元素的下沉过程
	// l 和 h 为数组调整范围的 起始位 和 结束位
	int i=l, j=2*l;
	struct ListNode* temp = heap[i];
	while (j<=h)
	{
		if (j<h && heap[j]->val > heap[j+1]->val) j++;
		if (temp->val > heap[j]->val)
		{
			heap[i] = heap[j];
			i = j;		//继续检查下沉的节点是否还需要下沉
			j = 2 * i;
		}
		else break;
	}
	heap[i] = temp;
}


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    int k=0;//初始堆大小
    struct ListNode** heap = malloc(sizeof(struct ListNode*)*(listsSize+1));//堆下标从1开始

    for(int i=0; i<listsSize; i++)
        if(lists[i]!=NULL) heap[++k] = lists[i];//链表头节点不空时入堆

    if(k==0) return NULL;    //无有效链表
    if(k==1) return heap[1];    //只有一个有效链表

    for(int i=k/2; i>0; i--) SheapDownAdjust(heap, i, k);//堆初始化

    struct ListNode* head = heap[1];    //保留一个头节点
    struct ListNode* temp = heap[1];
    while(k>1){
        if(heap[1]->next != NULL) heap[1] = heap[1]->next;  // 堆顶最小节点的下一个不空时,替换为下一个
        else heap[1] = heap[k--];   // 下一个为空时,把堆尾节点拿到堆顶,堆大小--;
        SheapDownAdjust(heap, 1, k);   //重新调整堆 
        temp->next = heap[1];   //取下最小节点
        temp = heap[1];
    }
    return head;
}

struct ListNode** init(int nums[][10], int n){
    struct ListNode** lists = malloc(sizeof(struct ListNode*)*n);
    for (int i = 0; i < n; i++)
    {
        struct ListNode* p;
        struct ListNode* t;
        lists[i] = malloc(sizeof(struct ListNode));
        lists[i]->val = nums[i][0];
        lists[i]->next = NULL;
        t = lists[i];
        int k=1;
        while (nums[i][k]!=999)
        {
            p = malloc(sizeof(struct ListNode));
            p->val = nums[i][k++];
            p->next = NULL;
            t->next = p;
            t = p;
        }
    }
    return lists;
}


int main(int argc, char const *argv[])
{
    int nums[6][10] = {{-10,-9,-9,-3,-1,-1,0,999},{-5,999},{4,999},{-8,999},{-9,-6,-5,-4,-2,2,3,999},{-3,-3,-2,-1,0,999}};
    struct ListNode** lists =  init(nums, 6);

    mergeKLists(lists, 6);
    return 0;
}