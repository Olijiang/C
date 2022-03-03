#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *input = "C:\\Users\\Snion\\Desktop\\in.txt";
    char *output = "C:\\Users\\Snion\\Desktop\\out.txt";
    char s[100];
    freopen(input, "r", stdin); //将输入路径定位到input
    scanf("%s", &s);     // 读入 input 中的字符串 s = abcdef
    
    printf("%s\n", s);    //输出到默认输出,cmd窗口
    
    freopen(output, "w", stdout); //将输出路径定位到output
    printf("%s\n", s);    // 输出到output文件

    fclose(stdin);
    fclose(stdout);     // 文件立即写入，不然文件一般在程序执行结束后写入

    freopen("CON", "r", stdin); //将输入重定位到cmd窗口
    scanf("%s", &s);     // 读入cmd输入的字符

    freopen("CON", "w", stdout); //将输出重定位到cmd窗口
    printf("%s\n", s);    // 输出到cmd窗口
    return 0;
}
