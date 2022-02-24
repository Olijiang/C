# 1. 两数之和
- 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
## 方法1：暴力循环
```
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
```
## 方法2：哈希表
```
typedef struct hashnode 
{   // hash节点
    int key;    //值
    int ord;    //当前值的索引
    struct hashnode *next;  // 链地址法解决冲突
}hashnode;

hashnode* hash_find(hashnode *hashtable, int key, int mod){
    // 有则返回对应节点, 否则返回NULL
    int a = key%mod;
    if (a<0) a = a*-1;  //将负数映射到正数上
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
    // 建立一个大小为 n 的 hash 表
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
    int* res = malloc(sizeof(int)*2);   // return 数组
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
```
---
# 2. 两数相加
- 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
## 方法：两链表节点对应相加维持一个进位变量即可
```
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int more=0;
    int t, n1, n2;
    struct ListNode* l3=NULL;
    struct ListNode* ls=NULL;
    struct ListNode* tmp=NULL;
    while(l1 || l2 ){
        n1 = l1?l1->val:0;
        n2 = l2?l2->val:0;
        t = n1 + n2 + more;
        more = t/10;    // 进位
        t = t%10;       // 保留数
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = t;
        tmp->next = NULL;
        if(l1) l1 = l1->next;
        if(l2) l2 = l2->next;
        if(!l3) {   // 第一个节点特殊处理
            l3 = tmp;
            ls = l3;
            continue;
        }
        ls->next = tmp;
        ls = tmp;
    }
    if (more!=0){   //最后有进位时
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = more;
        tmp->next = NULL;
        ls->next = tmp;
    }
    return l3;
}
```
---
# 3. 无重复字符的最长子串
- 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
## 方法：
- 遍历串 s ,同时维持一个记录字符是否出现的hash表, 当遇到重复出现的字符时记录一次长度, 并将开始位置定位到当前字符第一次出现位置的下一个字符。
    ```
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
        return max>n?max:n; //结束时需再判断一次
    }
    ```
---
# 4. 寻找两个正序数组的中位数
- 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数。算法的时间复杂度应该为 O(log (m+n)) 。
### method:
- 奈何只写的来遍历, 写不来二分查找的。先过一题。
```
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int k = nums1Size + nums2Size;
    int n1=0,n2=0, res[2]={0,0};
    for (int i = 0; i < k/2+1; i++){
        res[0]=res[1];
        if (n1==nums1Size) res[1] = nums2[n2++];
        else if (n2==nums2Size) res[1] = nums1[n1++];
        else{
            if (nums1[n1]<nums2[n2]) res[1] = nums1[n1++];
            else res[1] = nums2[n2++];
        }
    }
    return (double)(k%2 == 0)?(res[0] + res[1])/2.0:res[1];
}

```