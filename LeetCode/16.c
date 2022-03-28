#include <stdio.h>
#include <math.h>

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

int threeSumClosest(int* nums, int numsSize, int target){
    int min = 9999;
    Qsort(nums, 0, numsSize-1);
    for (int i = 0; i < numsSize; i++)
    {
        int le = i+1, ri = numsSize-1;
        while (le<ri) 
        {
            min = (abs(nums[le]+nums[ri]+nums[i] -target) <= abs(min-target))?(nums[le]+nums[ri]+nums[i]):min;
            if(nums[le]+nums[ri]+nums[i] > target) ri--; //只能把右指针左移减小sum值,才可能和target更接近
            else  le++;
        }
    }
    return min;
}


int main(int argc, char const *argv[])
{
    int nums[] = {1,2,-1,-4};
    int numsSize = sizeof(nums)/sizeof(int);

    int res = threeSumClosest(nums, numsSize, 1);
    printf("%d ",res);
    

     return 0;
}