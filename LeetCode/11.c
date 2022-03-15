#include <stdio.h>



int maxArea(int* height, int heightSize){
    
    int max=0;
    for (int i = 0, j=heightSize-1; i < j;)
    {
        int t = height[i]>height[j]?height[j]:height[i];
        max = max>(t*(j-i))?max:t*(j-i);
        if (height[i]>height[j]) j--;
        else i++;
    }
    return max;
}

int main(int argc, char const *argv[])
{
    int HA[] = {2,3,10,5,7,8,9};
    int Hsize = sizeof(HA)/sizeof(int);
    printf("%d ",maxArea(HA, Hsize));
    return 0;
}
