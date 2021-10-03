#include <stdio.h>
#include <stdlib.h>

/* 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。 */


int Adjustheap(int *nums, int k, int h)
{   // 将第 k 个元素调整到位， 小顶堆
    int i = k, j = 2*k;
    int temp = nums[k];
    while (j<=h)
    {
        if (j<h && nums[j]>nums[j+1]) j++;
        if (temp>nums[j])  //这里是用temp比，而不是nums[i]
        {
            nums[i] = nums[j];
            i = j;
            j = 2*i;
        }
        else break;  // !!
    }
    nums[i] = temp;
}

int findKthLargest(int* nums, int numsSize, int k){
    int i;
    int dui[k+1];  //堆下标从 1 开始
    for (i = 0; i < k; i++) dui[i+1] = nums[i];
    for (i = k/2; i > 0; i--) Adjustheap(dui, i, k);
    for (i = k; i < numsSize; i++)
    {
        if (nums[i]>dui[1]) 
        {
            dui[1] = nums[i];
            Adjustdui(dui, 1, k);
        }
    }
    return dui[1];
}


int main(int argc, char const *argv[])
{
    int nums[] = {3,2,3,1,2,4,5,5,6};
    int numsSize = sizeof(nums)/sizeof(int);
    int n = findKthLargest(nums, numsSize, 4);
    printf("%d ",n);
    return 0;
}
