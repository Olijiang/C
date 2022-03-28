#include <stdio.h>
#include <stdlib.h>

void Qsort(int *nums, int low, int high){
    if (low>=high) return;
    int lf = low, ri = high;
    int temp = nums[lf];
    while (lf<ri)
    {
        while (nums[ri]>=temp && lf<ri) ri--;
        nums[lf] = nums[ri];
        while (nums[lf]<temp && lf<ri) lf++;
        nums[ri] = nums[lf];
    }
    nums[lf] = temp;
    Qsort(nums, low, lf-1);
    Qsort(nums, ri+1, high);
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){
    *returnSize=0;
    if (numsSize<4) return NULL;
    Qsort(nums, 0, numsSize-1);
    int **res = malloc(sizeof(int *)*20000);
    for (int i = 0; i < numsSize ; i++)
    {
        for (int j = i+1; j < numsSize; j++)
        {
            int le =j+1, ri = numsSize-1;
            while (le<ri) 
            {
                if (nums[le]+nums[ri]+nums[i]+nums[j] == target)
                {
                    res[*returnSize] = malloc(sizeof(int)*4);
                    res[*returnSize][0]= nums[i];
                    res[*returnSize][1]= nums[le];
                    res[*returnSize][2]= nums[ri];
                    res[*returnSize][3]= nums[j];
                    (*returnSize)++;
                    while (le<ri && nums[le]==nums[le+1])   le++; 
                    le++;
                    while (le<ri && nums[ri]==nums[ri-1]) ri--;     
                    ri--;
                }
                else if(nums[le]+nums[ri]+nums[i]+nums[j]<target) le++;
                else ri--;
            }
            while (j<numsSize-1 && nums[j]==nums[j+1]) j++; 
        }
        while (i<numsSize-1 && nums[i]==nums[i+1]) i++; // 注：i<numsSize-1 要在 nums[i]==nums[i+1] 的前面,不然会访问到nums[3],越界访问
    }
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = 4;
    return res;
}

void show(int** nums, int Size, int *columsize){
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < columsize[i]; j++)
            printf("%d ", nums[i][j]);
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int nums[] = {1,0,-1,0,-2,2};
    int numsSize = sizeof(nums)/sizeof(int);
    int returnSize=0;
    int *returnColumnSizes;
    int **res = fourSum(nums, numsSize, 0, &returnSize, &returnColumnSizes);
    show(res, returnSize, returnColumnSizes);
    

    return 0;
}
