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



int** threeSum(int *nums, int numsSize, int* returnSize, int** returnColumnSizes){
    *returnSize=0;
    if (numsSize<3) return NULL;
    Qsort(nums, 0, numsSize-1);
    int **res = malloc(sizeof(int *)*20000);
    for (int i = 0; i < numsSize && nums[i]<=0; i++)
    {
        int le = i+1, ri = numsSize-1;
        while (le<ri) 
        {
            if (nums[le]+nums[ri] == -nums[i])
            {
                res[*returnSize] = malloc(sizeof(int)*3);
                res[*returnSize][0]= nums[i];
                res[*returnSize][1]= nums[le];
                res[*returnSize][2]= nums[ri];
                (*returnSize)++;
                while (le<ri && nums[le]==nums[le+1])   le++; // 同下
                   
                le++;
                while (le<ri && nums[ri]==nums[ri-1]) ri--;     // 同下
                ri--;
            }
            else if(nums[le]+nums[ri] < -nums[i]) le++;
            else ri--;
        }
        while (i<numsSize-1 && nums[i]==nums[i+1])  // 注：i<numsSize-1 要在 nums[i]==nums[i+1] 的前面,不然会访问到nums[3],越界访问
            i++;
    }
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = 3;
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
    int nums[] = {0,0,0};
    int numsSize = sizeof(nums)/sizeof(int);
    int returnSize=0;
    int *returnColumnSizes;
    int **res = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);
    show(res, returnSize, returnColumnSizes);
    

    return 0;
}
