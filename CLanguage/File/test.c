#include <stdio.h>
#include <stdlib.h>

int main()
{

	char x=1;
    char *p = &x;
	for (; ;)
	{
		printf("%x\n", p);
		printf("%x\n", *p++);//�ڴ������ҳΪ��λ��Խ����ʷ����� ��ҳ ����λ��
	}
	
    return 0;
}

