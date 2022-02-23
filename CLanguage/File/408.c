#include <stdio.h>
#include <stdlib.h>


// 2010---------------------------------2010
void reverse(int *nums, int i, int j)
{   //i,j 为反转的起始位置
    int temp;
    while(i<j)
    {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        i++;
        if(i<j) j--;
    }
}
void fun2010()
{   
    int nums[9]={1,2,3,4,5,6,7,8,9};
    int p = 4;
    reverse(nums, 0, p);
    reverse(nums, p+1, 8);
    reverse(nums, 0, 8);
    for (int i = 0; i < 9; i++)
        printf("%d ", nums[i]);
}

// 2010---------------------------------2010

int main(int argc, char const *argv[])
{
    
    //fun2010();
    return 0;
}
