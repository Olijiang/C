/* 01. 两数之和 

给定一个整数数组 nums?和一个整数目标值 target，请你在该数组中找出和为目标值 target? 的那?两个?整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现

 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    //暴力循环
    int *re =  (int *)malloc(2*sizeof(int));
    for (int i = 0; i < numsSize; i++){
        for (int j = i+1; j < numsSize; j++){
            if (nums[i]+nums[j]==target){
                re[0] = i;
                re[1] = j;
                *returnSize = 2;
                return re;
            }
        }
    }
    *returnSize=0;
    return re;
}

/* 哈希表开始 */

typedef struct hashnode 
{
    int key;
    int ord;
    struct hashnode *next;
}hashnode;

hashnode* hash_find(hashnode *hashtable, int key, int mod){
    int a = key%mod;
    if (a<0) a = a*-1;
    hashnode* temp = hashtable[a].next;
    while (temp!=NULL){
        if (temp->key == key) return temp;
        temp = temp->next;
    }
    return NULL;
}

void hash_insert(hashnode *hashtable, int key, int ord, int mod){
    int a = key%mod;
    if (a<0) a = a*-1;
    hashnode* temp = hashtable[a].next;
    hashnode* new = malloc(sizeof(hashnode));
    new->key = key;
    new->ord = ord;
    new->next = NULL;
    
    if (temp==NULL)
        temp = &hashtable[a];
    else
        while (temp->next!=NULL)
            temp = temp->next;
    temp->next = new;
    hashtable[a].key++;
}

hashnode* Hashtable(int n){
    hashnode* hashtable = malloc(sizeof(hashnode)*n);
    for (int i = 0; i < n; i++)
    {
        hashtable[i].key = 0;   // 节点计数
        hashtable[i].next = NULL;
    }
    return hashtable;
}

int* TwoSum(int* nums, int numsSize, int target, int* returnSize){
    int n = 10;
    hashnode* hashtable = Hashtable(n);
    hashnode* temp;
    int* res = malloc(sizeof(int)*2);
    for (int i = 0; i < numsSize; i++)
    {
        temp = hash_find(hashtable, target-nums[i], n);
        if(temp){
            res[0] = i;
            res[1] = temp->ord;
            *returnSize = 2;
            return res;
        }
        else hash_insert(hashtable, nums[i], i, n);
    }
    *returnSize = 0;
    return NULL;
}

/* 哈希表结束 */

int main(int argc, char const *argv[])
{
    int nums[] = {-3,4,3,90};
    int numsSize = sizeof(nums)/sizeof(int);
    int target = 0;
    int *res;
    int a;
    res = twoSum(nums, numsSize, target, &a);
    printf("%d %d\n",res[0],res[1]);
    res = TwoSum(nums, numsSize, target, &a);
    printf("%d %d\n",res[0],res[1]);
    return 0;
}

