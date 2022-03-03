#include <stdio.h>
#include <stdlib.h>

int shoot(int target, int k){
    //target:目标分数  k:打靶次数
    
    static int n=0;   //记录已打靶次数
    static int sum=0;  // sum:种类计数
    static int score=0; // 当前分数
    static int m, *rec;
    if (!n){        // 只在n为0时执行一次，以后不再执行;
        m = k;      // 将打靶次数赋值给m, 在以后遍历中保持不变
        rec=malloc(sizeof(int)*m); //记录每次打靶分数
    }

    if (k>0){
        for (int i = 0; i <= 10; i++){
            if (n*10-score>10) return 0;    // 丢靶分数大于10分的时候可以直接pass,不可能达到90分了
            rec[n++]=i;
            score+=i;
            if (score==target && n==m) {
                sum++;
                //printf("%d :",sum);
                //for (int i = 0; i < m; i++) printf("%d ",rec[i]);
                //printf("\n");
            }
            shoot(target,k-1);
            n--;
            score-=i;
        }
    }
    if (!n) return sum;
}

int main(int argc, char const *argv[])
{
    printf("%d ",shoot(90,10));
    return 0;
}