#include <stdio.h>
#include <stdlib.h>

// 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

//初步思想：




int maxSubArray(int* nums, int numsSize){
    int i, sum = 0;
    int max=nums[0]; 
    for (int i = 0; i < numsSize; i++)
    {

        sum+= nums[i];
        max = (max>sum)?max:sum;
        if (sum<0) sum=0;   //如果sum < 0，sum对后面的贡献是负的， 直接置0；
    }
    return max;
}


int main(int argc, char const *argv[])
{
    int nums[] = {-2,1,-3,4,-1,2,1,-5,4};
    int numsSize = sizeof(nums)/sizeof(int);
    printf("%d",maxSubArray(nums, numsSize)); 

    return 0;
}
