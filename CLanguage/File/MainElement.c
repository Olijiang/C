#include <stdio.h>

int main(int argc, char const *argv[])
{
    int ma[10] = {1,5,3,5,5,4,2,5,5,5};
    int c = ma[0], k = 0;
 
    int n = sizeof(ma)/sizeof(int);

    for (int i = 0; i < n; i++)
    { 
        if (ma[i] == c) k++;
        else k--;
        if(k==0)
        {
            c = ma[i];
            k++;
        }
    }
    k=0;
    for (int i = 0; i < n; i++)
        if (ma[i]==c) k++;
    
    if (k > n/2) printf("%d",c);
    else printf("NONE");

    return 0;
}
