# 1. 两数之和
- 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标。你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
## 方法1：暴力循环
```
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    //暴力循环
    int *re =  (int *)malloc(2*sizeof(int));
    for (int i = 0; i < numsSize; i++){
        for (int j = i+1; j < numsSize; j++){
            if (nums[i]+nums[j]==target){
                re[0] = i;
                re[1] = j;
                *returnSize = 2;
                return re;
            }
        }
    }
    *returnSize=0;
    return re;
}
```
## 方法2：哈希表
```
typedef struct hashnode 
{   // hash节点
    int key;    //值
    int ord;    //当前值的索引
    struct hashnode *next;  // 链地址法解决冲突
}hashnode;

hashnode* hash_find(hashnode *hashtable, int key, int mod){
    // 有则返回对应节点, 否则返回NULL
    int a = key%mod;
    if (a<0) a = a*-1;  //将负数映射到正数上
    hashnode* temp = hashtable[a].next;
    while (temp!=NULL){
        if (temp->key == key) return temp;
        temp = temp->next;
    }
    return NULL;
}

void hash_insert(hashnode *hashtable, int key, int ord, int mod){
    int a = key%mod;
    if (a<0) a = a*-1;
    hashnode* temp = hashtable[a].next;
    hashnode* new = malloc(sizeof(hashnode));
    new->key = key;
    new->ord = ord;
    new->next = NULL;
    
    if (temp==NULL)
        temp = &hashtable[a];
    else
        while (temp->next!=NULL)
            temp = temp->next;
    temp->next = new;
    hashtable[a].key++;
}

hashnode* Hashtable(int n){
    // 建立一个大小为 n 的 hash 表
    hashnode* hashtable = malloc(sizeof(hashnode)*n);
    for (int i = 0; i < n; i++)
    {
        hashtable[i].key = 0;   // 节点计数
        hashtable[i].next = NULL;
    }
    return hashtable;
}

int* TwoSum(int* nums, int numsSize, int target, int* returnSize){
    int n = 10;
    hashnode* hashtable = Hashtable(n);
    hashnode* temp;
    int* res = malloc(sizeof(int)*2);   // return 数组
    for (int i = 0; i < numsSize; i++)
    {
        temp = hash_find(hashtable, target-nums[i], n);
        if(temp){
            res[0] = i;
            res[1] = temp->ord;
            *returnSize = 2;
            return res;
        }
        else hash_insert(hashtable, nums[i], i, n);
    }
    *returnSize = 0;
    return NULL;
}
```
---
# 2. 两数相加
- 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
## 方法：两链表节点对应相加维持一个进位变量即可
```
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int more=0;
    int t, n1, n2;
    struct ListNode* l3=NULL;
    struct ListNode* ls=NULL;
    struct ListNode* tmp=NULL;
    while(l1 || l2 ){
        n1 = l1?l1->val:0;
        n2 = l2?l2->val:0;
        t = n1 + n2 + more;
        more = t/10;    // 进位
        t = t%10;       // 保留数
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = t;
        tmp->next = NULL;
        if(l1) l1 = l1->next;
        if(l2) l2 = l2->next;
        if(!l3) {   // 第一个节点特殊处理
            l3 = tmp;
            ls = l3;
            continue;
        }
        ls->next = tmp;
        ls = tmp;
    }
    if (more!=0){   //最后有进位时
        tmp = malloc(sizeof(struct ListNode));
        tmp->val = more;
        tmp->next = NULL;
        ls->next = tmp;
    }
    return l3;
}
```
---
# 3. 无重复字符的最长子串
- 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
## 方法：
- 遍历串 s ,同时维持一个记录字符是否出现的hash表, 当遇到重复出现的字符时记录一次长度, 并将开始位置定位到当前字符第一次出现位置的下一个字符。
    ```
    int LengthOfLongestSubstring(char * s){
        int hash[200];
        int max=0, n=0;
        int st=0;
        for (int i = 0; i < 200; i++) hash[i] = 0;
        for (int i = 0; s[i]; i++,n++)
        {
            if (hash[s[i]]){
                max = max>n?max:n;
                while (s[st]!=s[i]){
                    hash[s[st]]=0;
                    st++,n--;
                }
                st++,n--;
            }
            hash[s[i]]=1;
        }
        return max>n?max:n; //结束时需再判断一次
    }
    ```
---
# 4. 寻找两个正序数组的中位数
- 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数。算法的时间复杂度应该为 O(log (m+n)) 。
### method:
- 奈何只写的来遍历, 写不来二分查找的。先过一题。
```
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int k = nums1Size + nums2Size;
    int n1=0,n2=0, res[2]={0,0};
    for (int i = 0; i < k/2+1; i++){
        res[0]=res[1];
        if (n1==nums1Size) res[1] = nums2[n2++];
        else if (n2==nums2Size) res[1] = nums1[n1++];
        else{
            if (nums1[n1]<nums2[n2]) res[1] = nums1[n1++];
            else res[1] = nums2[n2++];
        }
    }
    return (double)(k%2 == 0)?(res[0] + res[1])/2.0:res[1];
}

```
---
# 5. 最长回文子串
- 给你一个字符串 s，找到 s 中最长的回文子串。从左到右==从右到左的字符串;
- 中心扩散法，遍历字符串，对每个字符中心扩散；分为中心有一个元素和两个元素两种情况；
```
char * longestPalindrome(char * s){
    
    int n=0, max=0, st=0;

    for (int i = 0; s[i]; i++) n++;

    for (int i = 0; s[i]; i++)
    {
        //中心单元素
        int k=i;
        int r=0;
        while(k-r>=0 && k+r<n && s[k-r]==s[k+r])
        {
            if (max<=r*2+1)
            {
                max = r*2+1;
                st = i-r; 
            }
            r++;
        }
        //中心双元素
        k=i;
        r=0;
        if (s[k]==s[k+1])
        {
            int h = k+1;
            while(k-r>=0 && k+r<n && s[k-r]==s[h+r])
            {
                if (max<=r*2+2)
                {
                    max = r*2+2;
                    st = i-r; 
                }
                r++;
            }
        }
    }
    s[max+st] = '\0';
    return &s[st];
}
```
# 6. Z 字形变换
- 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。称为 N 字形较为合适。
- 观测规律，直接构造元素位置
```
char * convert(char * s, int numRows){
    int n=0, k=0;
    for (int i = 0; s[i]; i++) n++;
    if (numRows==1) return s;
    
    char *se = malloc(sizeof(char)*(n+1));
    for (int i = 0; i < numRows; i++)
    {
        int no = i;
        if (no==0 || no==numRows-1) // 第一行和最后一行
        {
            while (no<n)
            {
                se[k++] = s[no];
                no = no+2*numRows-2;
            }
        }
        else
        {
            while (no<n)
            {
                se[k++] = s[no];
                if (no+2*numRows-2-2*i<n)
                {
                    se[k++] = s[no+2*numRows-2-2*i];
                }
                no = no+2*numRows-2;
            }
        }
    }
    se[n] = '\0';
    return se;
}
```
---
# 7. 整数反转
- 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。如果反转后整数超过 32 位的有符号整数的范围 $[2^{−31},  2^{−31} − 1]$，就返回 0。假设环境不允许存储 64 位整数（有符号或无符号）。
- 主要问题在于值超出范围时的判断，需要预判下一步操作数值是否会越界。而不能在已经越界后再判断是否越界，这个时候的值是不准确的。
```
int reverse(int x){
    int res=0;
    for (int i = 0; x; i++)
    {   // 2^31 = 2147483648
        if (res > 214748364 || res < -214748364) return 0;
        if (res == 214748364 && x%10 > 7) return 0;
        if (res == -214748364 && x%10 <-8) return 0;
        res = res*10 + x%10;
        x = x/10;
    }
    return res;
}
```
---
# 8. 字符串转换整数 (atoi)
- 函数 myAtoi(string s) 的算法如下：
    - 1、读入字符串并丢弃无用的前导空格
    - 2检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
    - 3读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
    - 4将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
    - 5如果整数数超过 32 位有符号整数范围 $[2^{−31},  2^{−31} − 1]$，需要截断这个整数，使其保持在这个范围内。具体来说，小于 $2^{−31}$ 的整数应该被固定为 $-2^{−31}$ ，大于 $2^{−31} − 1$ 的整数应该被固定为 $2^{−31} − 1$ 。
    - 6返回整数作为最终结果。
- 注意：
    - 本题中的空白字符只包括空格字符 ' ' 。
    - 除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
```
int myAtoi(char * s){
    int k = 0;
    int res = 0, minus = 1;
    for (int i = 0; s[k]==' '; i++) k++;
    if (s[k]=='-') {    //确定符号
        minus = -1;
        k++;
    }
    else if (s[k]=='+') {
        minus = 1;
        k++;
    }
    if (s[k]<'0' && s[k]>'9') return 0; //无数字
    
    while(s[k]>='0' && s[k]<='9')
    {
        if (res*minus>=214748365) return 2147483647;
        if (res*minus==214748364 && (s[k]-'0')>=7) return 2147483647;
        if (res*minus<= -214748365) return -2147483648;
        if (res*minus== -214748364 && (s[k]-'0')>=8) return -2147483648;
        res = res*10 + (s[k++]-'0');
    }
    res *= minus;
    return res;
}
```
---
# 9. 回文数 
- 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。
- 思路：反转数字相等
```
bool isPalindrome(int x){
   if (x<0) return 0;   // 负数直接pass
   long int res=0;  // 反转后的数可能超出int的表示范围
   int copy=x;
   while (x)
   {
       res = res*10 + x%10;
       x /= 10;
   }
   return res==copy?1:0;
}
```
---
# 10. 正则表达式匹配
- 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
- '.' 匹配任意单个字符
- '*' 匹配零个或多个前面的那一个元素
- 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

- 动态规划思路
```
public class LD10{
    // leetcode 10 

    public boolean isMatch(String s, String p) {
        int m = s.length();
        int n = p.length();

        boolean[][] f = new boolean[m + 1][n + 1];
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p.charAt(j - 1) == '*') {
                    // 遇到*号时，当f[i][j]与f[i][j-1]不匹配时，f[i][j] 能否匹配直接取决于 f[i][j - 2]的情况;
                    // 当f[i][j]与f[i][j-1]匹配时，f[i][j]是否匹配还取决于f[i-1][j]能否匹配。
                    // 当p[j]=='*'时,若s[i]==p[j-1];那么s[i]属于通配符的范围,可有可无的一个字符,f[i-1][j]匹配f[i][j]就可以匹配;
                    f[i][j] = f[i][j - 2];
                    if (matches(s, p, i, j - 1)) {
                        f[i][j] = f[i][j-2] || f[i-1][j];
                    }
                } else {
                    if (matches(s, p, i, j)) {
                        f[i][j] = f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }

    public boolean matches(String s, String p, int i, int j) {
        if (i == 0) return false;
        if (p.charAt(j - 1) == '.') return true;
        return s.charAt(i - 1) == p.charAt(j - 1);
    }
```
---
# 11. 盛最多水的容器
- 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。返回容器可以储存的最大水量。说明：你不能倾斜容器。

- 双指针法，每次改变较小值的位置，记录过程的max值
```
int maxArea(int* height, int heightSize){
    
    int max=0;
    for (int i = 0, j=heightSize-1; i < j;)
    {
        int t = height[i]>height[j]?height[j]:height[i];
        max = max>(t*(j-i))?max:t*(j-i);
        if (height[i]>height[j]) j--;
        else i++;
    }
    return max;
}
```
---
# 12. 整数转罗马数字
- 由于题要求范围在1-3999; 可以自己编一个对应表以对应罗马数字的0-9;
```
char * intToRoman(int num){
    
    char map[4][10][5] = {
        {"", "I", "II", "III", "IV", "V", "VI" ,"VII", "VIII", "IX"}, // 0-9 个位
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"", "M", "MM", "MMM", "", "", "", "", "", ""},
    };
    char *roman = malloc(sizeof(char)*20);
    roman[0] = '\0';
    int k=1000;
    for (int i = 3; i >= 0; i--)
    {
        int t = num/k;
        strcat(roman, map[i][t]);
        num %= k;
        k /= 10;
    }
    return roman;
}
```
---
# 13. 罗马数字转整数
- 可以挨个字符处理，需要考虑需要考虑两个字符作为一个数字的三种情况;
```
int romanToInt(char * s){
    int num=0;
    for (int i = 0; s[i]; i++){
        switch (s[i]){
            case 'I':
                if (s[i+1]=='V' || s[i+1]=='X') num -= 1;
                else num += 1;
                break;
            case 'V':
                num += 5;
                break;
            case 'X':
                if (s[i+1]=='L' || s[i+1]=='C') num -= 10;
                else num += 10;
                break;
            case 'L':
                num += 50;
                break;
            case 'C':
                if (s[i+1]=='D' || s[i+1]=='M') num -= 100;
                else num += 100;
                break;
            case 'D':
                num += 500;
                break;
            case 'M':
                num += 1000;
                break;
            default:
                break;
        }
    }
    return num;
}
```

