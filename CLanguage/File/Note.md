
## scanf 输入案例学习
    可以一次把数据都输入到缓冲区，下一次scanf会直接冲缓冲区获取数据；

int main()
{
    int t, n, k, sum, be;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        sum = 0;
        be = 1;
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&k);
            sum += (be<k)?(6*(k-be)):(4*(be-k)); //问号表达式需要括起来，表达式允许从左到右，不加出错
            be = k;
        }
        printf("%d\n", sum+3*n);
    }
    return 0;
}   