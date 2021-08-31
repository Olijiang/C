#include <stdio.h>
#include <stdlib.h>

//检查数组中是否存在重复元素

void containsDuplicate();//采用快排排序后检查， 在数据五万个原始有序数据时超时。 数据有序时快排时间复杂度达到最差为n2;

int Qsort(int* nums, int L, int H, int flag)
{
    if(L>=H) return 0;
    if (flag) return 0;
    
    int i=L, j=H;
    int temp = nums[L];
    while(i<j)
    {
        
        while(i<j && nums[j]>=temp)
        {
            if (nums[j]==temp) 
            {
                flag = 1;
                return 0;
            }
            j--;
        } 
        nums[i] = nums[j];
        while(i<j && nums[i]<temp) i++;
        nums[j] = nums[i];
    }
    nums[i] = temp;
    Qsort(nums, L, i-1, flag);
    Qsort(nums, i+1, H, flag);
    return flag;
}

void containsDuplicate()
{
    int nums[] = {1,5,-2,4,0};
    int numsSize = sizeof(nums)/sizeof(int);
    int flag = 0;
    flag = Qsort(nums, 0, numsSize, flag);
    if (flag) printf ("true");
    else printf("false");
}


int main()
{
    containsDuplicate();
    return 0;
}