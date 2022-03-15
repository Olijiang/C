#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[] = "i am a student";
	int i;
	for (i = 0; s[i]; i++)
		if (s[i]==' ') s[i-1] -= 32; 
	s[i-1] -= 32; 
	printf("%s", s);
	printf("%c", s[i+1]);
	return 0;
}

