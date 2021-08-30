#include <stdio.h>
#include <stdlib.h>

#define N 20
int Qsort(int* nums, int L, int H, int flag);


int containsDuplicate(int* nums, int numsSize){
    int flag = 0;

    if(Qsort(nums, 0, numsSize-1, flag)) return 1;;
    return 0;
}

int Qsort(int* nums, int L, int H, int flag)
{
    if(L>=H) return 0;
    if (flag) return flag;
    
    int i=L, j=H;
    int temp = nums[L];
    while(i<j)
    {
        if (nums[j]==temp) flag = 1;
        while(i<j && nums[j]>=temp) j--;
        nums[i] = nums[j];
        while(i<j && nums[i]<temp) i++;
        nums[j] = nums[i];
    }
    nums[i] = temp;
    Qsort(nums, L, i-1, flag);
    Qsort(nums, i+1, H, flag);
    return flag;
}
int main()
{

    int nums[] = {1,5,-2,4,0};
    int numsSize = 5;
    int flag = containsDuplicate(nums, numsSize);
    if (flag) printf ("true");
    else printf("false");
    
    
    return 0;
}