#include <stdio.h>
#include <stdlib.h>

int main()
{

	char x=1;
    char *p = &x;
	for (; ;)
	{
		printf("%x\n", p);
		printf("%x\n", *p++);//内存分配以页为单位，越界访问发生在 分页 结束位置
	}
	
    return 0;
}

