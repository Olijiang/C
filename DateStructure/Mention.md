
//本文件为平时学习中发现的一些注意事项
```
#include <stdio.h>
#include <stdlib.h>
typedef struct btnode
{
	//树节点
	int data;
	struct btnode *lch, *rch;
}BTNode;
```
// 要在函数内对传入指针做修改 必须 传入指针的指针   但数组是个例外
// InsertBST2(BTNode *bt, int key) 这个例子传入BTNode *（指针）类型的参数为复制传参，无法对原参数进行有效修改，
// 需要传入指针的地址指针,例如 InsertBSTT(BTNode **bt, int key)
```
  _Bool InsertBST(BTNode **bt, int key){;}  //√
  _Bool InsertBST2(BTNode *bt, int key){;}  //×
```
// 而对于数组， 只需要传入数组本身就可以对数组参数有效修改，无需传入数组的指针
// 传入 int a[] 和 int *a 的效果一致，都是指向数组 a 首地址的指针 
```
 int change(int a[])
 {
 	//对 数组 a[] 参数有效修改
 	a[1] = 11;
 	a[2] = 12;
 }
 int change3(int *b)
 {
 	//对 数组 a[] 参数有效修改
 	b[1] = 11;
 	b[2] = 12;
 }

int main()
{
	int a[] = {1,2,3,4};
	change3(a);
	for (int i = 0; i < 4; ++i) printf("%d ", a[i]);
}
```
