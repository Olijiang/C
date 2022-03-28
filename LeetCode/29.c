#include <stdio.h>
//两数相除,但不能用 / * % 运算符, 环境为严格32位

//-2147483648

int divide(int dividend, int divisor){
    if (divisor==0) return 0;
    if (divisor==1) return dividend;
    if  (divisor==-2147483648){
        if(dividend==-2147483648) return 1;
        else return 0;
    }
    if (divisor==-1) {
        if (dividend==-2147483648) return 2147483647;
        else return -dividend;
    }
    int flag = 1;   //符号，初始为正
    int k=0;    //-2147483648 标记位
    if (dividend==-2147483648) {
        dividend += 1;  //+1后面转正
        k++;
    }
    if (dividend < 0) {
        dividend = -dividend;
        flag ^= 0xfffffffe;    //异或
    }
    if (divisor < 0) {
        divisor = -divisor;
        flag ^= 0xfffffffe;
    }
    if (dividend < divisor) return 0;   // 除数小于被除数

    int temp = divisor;
    int m = 1;
    int mod = 0;

    if (dividend>>1 < divisor) return flag;
    else if (k)
    {   // 之前+1给加少了一个，补回来，但为了避免溢出先减一个divisor
        mod++;
        dividend = dividend-divisor+1;
    }
    while (dividend >= temp)
    {   if (dividend-temp >= temp){
            temp <<= 1;
            m <<= 1;
        }
        if (temp >= dividend>>1)
        {
            mod += m;
            m = 1;
            dividend -= temp;
            temp = divisor;
        }
    }
    return (flag==1)?mod:-mod;
}

int main(int argc, char const *argv[])
{
    
    int a = -2147483648;
    int b = 2;

    printf("%d \n",divide(a,b));
    printf("%d \n\n",a/b);
    
    

    
    

    return 0;
}
