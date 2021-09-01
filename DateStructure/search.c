#include <stdlib.h>
#include <stdio.h>

int Bsearch(int R[], int low, int high, int key)
{
	//
	int mid;
	while(low<=high)
	{
		mid = (low+high)/2;
		printf("%d ", R[mid]);
		if (R[mid]==key)
			return 1;
		else if (R[mid]>key)
			high = mid-1;
		else
			low = mid+1;
	}
	return 0;
}


int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10,11};
	int B[] = {2,5,6,7,20,15,31};
	int n = sizeof(B)/sizeof(B[0]);
	for (int i = 0; i < n; ++i)
	{
		printf("Search %d\t", B[i]);
		printf("%s\n", Bsearch(a,0,11,B[i])?"Found":"Not Found");
	}
	return 0;
}