#include <stdio.h>
#include <stdlib.h>
//全排列


int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    static int flag[22];
    static int temp[10];
    static int n, k;
    static int **res;
    if (!n)
    {   //初始化
        *returnSize = 1;
        for (int i = 1; i <= numsSize; i++) *returnSize *= i;
        res = malloc(sizeof(int *)*(*returnSize));  //指向一组指针数组的一个指针，指针数组的每一个指针指向一个序列数组
        *returnColumnSizes = (int *)malloc(sizeof(int)*(*returnSize));
        for (int i = 0; i < *returnSize; i++) 
        {
            (*returnColumnSizes)[i] = numsSize;
            res[i] = malloc(sizeof(int)*numsSize);
        }
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (!flag[nums[i]+10])
        {
            flag[nums[i]+10] = 1;
            temp[k++] = nums[i];
            if (k == numsSize)
            {
                for (int j=0; j < numsSize; j++)
                {
                    res[n++ / numsSize][j] = temp[j];
                    //printf("%d ", temp[j]);
                }
                //printf("\n");
            }
            permute(nums, numsSize, returnSize, returnColumnSizes);
            k--;
            flag[nums[i]+10] = 0;
        }
    }
    return res;
}

void permute2(int* nums, int numsSize, int *res){
    static int flag[22];
    static int temp[10];
    static int n, k;

    for (int i = 0; i < numsSize; i++)
    {
        if (!flag[nums[i]+10])
        {
            flag[nums[i]+10] = 1;
            temp[k++] = nums[i];
            if (k == numsSize)
            {
                for (int j=0; j < numsSize; j++)
                {
                    res[n++] = temp[j];
                    printf("%d ", temp[j]);
                }
                printf("\n");
            }
            permute2(nums, numsSize, res);
            k--;
            flag[nums[i]+10] = 0;
        }
    }
}

void show(int** nums, int Size, int columsize){
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < columsize; j++)
            printf("%d ", nums[i][j]);
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int nums[] = {0,1};
    int numsSize = sizeof(nums)/sizeof(int);
    int returnSize = 0;
    int *returnColumnSizes = malloc(sizeof(int));
    int total = 1;
    for (int i = 1; i <= numsSize; i++) total *= numsSize;
    //int *res = malloc(sizeof(int)*numsSize*total);
    //permute2(nums, numsSize, res);
    int **res = permute(nums, numsSize, &returnSize, &returnColumnSizes);
    show(res, returnSize, *returnColumnSizes);
    return 0;
}
