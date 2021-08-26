#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float abs1(float a);


float sqrt2(float a, float p, float e)
{
	if (abs1(p*p-a)<e) return p;
	p = (p+a/p)/2;
	return sqrt2(a,p,e);
}

float sqrt1(float a, float p, float e)
{
	while(abs1(p*p-a)>=e)
	{
		p = (p+a/p)/2;
	}
	return p;
}

float abs1(float a)
{
	return (a<0)?(a*-1):(a);
}

float run_time()
{
	clock_t start, finish;
	double Total_time;
	start = clock();
	Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\nrun time：%0.3fs \n", Total_time);
	return Total_time;
}

int main(int argc, char const *argv[])
{

	float a = 3;
	printf("srqt2:%f \n", sqrt2(a,1.0,0.001));
	printf("srqt1:%f \n", sqrt1(a,1.0,0.000001));
	run_time();
	return 0;
}