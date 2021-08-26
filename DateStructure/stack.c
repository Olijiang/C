#include <stdio.h>

int isop(char c)
{
	// c 是操作符返回 1， 否则返回 0；
	return (c=='+'||c=='-'||c=='*'||c=='/')?(1):(0);
}

int comop(char op1, char op2)
{
	//如果 op2 操作符比 op1 操作符优先级高或相等，返回 1 ，否则返回 0；
	//'+', '-', '*', '/' 对应 43 45 42 47 
	if (op1==43||op1==45) return 1;
	if (op1==42&&op2==47||op1==47&&op2==42||op1==op2==42||op1==op2==47) return 1;
	return 0;
}

int scalcu(int a, int b, char c)
{
	//根据操作符 c 返回 a 对 b 进行 c 操作的结果；
	switch(c)
	{
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
		default:return 0;
	}
}

int calcu(char arr[], int n)
{
	char ostack[n/2];
	int nstack[n/2];
	int otop = -1, ntop = -1;
	int i, a, b, c;
	int mark = 0; //数字进栈 mark 为 1， 操作符进栈 mark 为 0；初始为 0！！
	for (int i = 0; i < n-1; ++i)
	{
		if (arr[i]=='(')
			{
				ostack[++otop] = arr[i];
				continue;
			}
		if (arr[i]==')')
		{	
			//遇到右括号就依次计算左括号前面的操作符
			//完成后弹出左括号
			while(ostack[otop]!='(')
			{
				b = nstack[ntop--];
				a = nstack[ntop--];
				c = scalcu(a,b,ostack[otop--]);
				nstack[++ntop] = c;
			}
			--otop;
			continue;
		}
		if (!isop(arr[i]))
		{
			//字符只有0-9，注意大于10的情况
			if(mark) nstack[ntop] = nstack[ntop]*10 + arr[i]-'0';
			else 
			{
				nstack[++ntop] = arr[i]-'0';
				mark = 1;
				//printf("%d into\n", arr[i]-'0');
			}
		}
		else if (isop(arr[i] && otop==-1))
		{
			 ostack[++otop] = arr[i];
			 mark = 0;
		}
		else
		{
			while(otop!=-1 && comop(arr[i], ostack[otop]))
			{
				//当操作符栈的 栈顶操作符 的优先级大于等于 当前操作符 的优先级时
				//取出栈顶操作符 和 两个数字栈顶部的元素进行运算，结果压回数字栈顶
				if(ostack[otop]=='(') break;
				b = nstack[ntop--];
				a = nstack[ntop--];
				c = scalcu(a,b,ostack[otop--]);
				nstack[++ntop] = c;
			}
			ostack[++otop] = arr[i];
			mark = 0;
		}
		//printf("%d\n", c);
	}
	while(otop!=-1)
	{
		//依次对剩下的操作符进行运算
		b = nstack[ntop--];
		a = nstack[ntop--];
		c = scalcu(a,b,ostack[otop--]);
		nstack[++ntop] = c;
	}
	return nstack[ntop];
}

int main(int argc, char const *argv[])
{
	char a[] ="(2+(3-1)*4+2)/2";
	int n = sizeof(a)/sizeof(a[0]);
	int result = calcu(a, n);
	printf("result = %d\n", result);
	//printf("%d %d %d %d \n", '+','-','*','/');
	return 0;
}
