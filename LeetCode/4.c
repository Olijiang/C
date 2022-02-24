#include<stdio.h>
#include<math.h>

// 寻找两个正序数组的中位数
// 遍历方法
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int k = nums1Size + nums2Size;
    int n1=0,n2=0, res[2]={0,0};
    for (int i = 0; i < k/2+1; i++){
        res[0]=res[1];
        if (n1==nums1Size) res[1] = nums2[n2++];
        else if (n2==nums2Size) res[1] = nums1[n1++];
        else{
            if (nums1[n1]<nums2[n2]) res[1] = nums1[n1++];
            else res[1] = nums2[n2++];
        }
    }
    return (double)(k%2 == 0)?(res[0] + res[1])/2.0:res[1];
}


int main(int argc, char const *argv[])
{
    int nums1[] = {1,2};
    int nums2[] = {-1,3};
    int nums1Size = sizeof(nums1)/sizeof(int);
    int nums2Size = sizeof(nums2)/sizeof(int);
    printf("%.5f ", findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size));

    return 0;
}
