/* 01. 两数之和 

给定一个整数数组 nums?和一个整数目标值 target，请你在该数组中找出和为目标值 target? 的那?两个?整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现

 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i,j;
    int *re =  NULL;
    for (i = 0; i < numsSize; i++)
    {
        for (j = i; j < numsSize; j++)
        {
            if (nums[i]+nums[j]==target)
            {
                re = (int *)malloc(2*sizeof(int));
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

int main(int argc, char const *argv[])
{
    int nums[] = {2,7,11,15};
    int numsSize = sizeof(nums)/sizeof(int);
    int target = 9;
    int *A;
    int a;
    A = twoSum(nums, numsSize, target, &a);
    printf("%d %d",A[0],A[1]); 
    return 0;
}

