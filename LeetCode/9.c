#include <stdio.h>


int isPalindrome(int x){
   if (x<0) return 0;
   long int res=0;
   int copy=x;
   while (x)
   {
       res = res*10 + x%10;
       x /= 10;
   }
   
   return res==copy?1:0;
    
}

int main(int argc, char const *argv[])
{
    printf(isPalindrome(12)?"yes":"no");
    return 0;
}
