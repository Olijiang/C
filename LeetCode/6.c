#include <stdio.h>
#include <stdlib.h>

char * convert(char * s, int numRows){
    int n=0, k=0;
    for (int i = 0; s[i]; i++) n++;
    if (numRows==1) return s;
    
    char *se = malloc(sizeof(char)*(n+1));
    for (int i = 0; i < numRows; i++)
    {
        int no = i;
        if (no==0 || no==numRows-1)
        {
            while (no<n)
            {
                se[k++] = s[no];
                no = no+2*numRows-2;
            }
        }
        else
        {
            while (no<n)
            {
                se[k++] = s[no];
                if (no+2*numRows-2-2*i<n)
                {
                    se[k++] = s[no+2*numRows-2-2*i];
                }
                no = no+2*numRows-2;
            }
        }
    }
    se[n] = '\0';
    return se;
}



int main(int argc, char const *argv[])
{
    char *s = "AB";
    int numRows = 1;
    printf("%s ", convert(s, numRows));
    return 0;
}