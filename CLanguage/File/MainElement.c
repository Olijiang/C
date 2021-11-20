#include <stdio.h>

int main(int argc, char const *argv[])
{
    int ma[] = {1,5,3,5,5,4,2,5,5,5};
    int k = ma[0], n = 0;
 
    int Len = sizeof(ma)/sizeof(int);

    for (int i = 0; i < Len; i++)
    { 
        if (ma[i] == k) n++;    // ==k  计数器++
        else n--;               // 计数器--
        if(n==0)                //  n==0, 
        {
            k = ma[i];  //k 换下一个元素
            n++;    // n 置 1
        }
    }
    n=0;
    for (int i = 0; i < Len; i++)   // 确认 k 是否是主元素
        if (ma[i]==k) n++;
    
    if (k > n/2) printf("%d",k);
    else printf("NONE");

    return 0;
}
/*
    
    设置一个 k 变量和一个计数器 n， k 初始为序列第一个数
    遍历序列，如果下一个数等于 k，n++； 否则 n--；
    当 n = 0 时，把 k 值换为当前值 
    由于主元素个数大于 n/2; 那么 n++ 的次数 肯定比n--的次数多
    即如果存在主元素，那 k 中保留的肯定就是主元素。
    但没有主元素 k 也会有取值，所以还需遍历确认一次
 */