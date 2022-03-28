#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxsum = -99999;

int maxGain(struct TreeNode* root){
    // 递归遍历所有节点并计算他的贡献值,跟算高度差不多
    if (root == NULL) return 0;
    //左树贡献
    int leftGain = maxGain(root->left);
    leftGain = leftGain>0?leftGain:0;
    //右树贡献
    int righttGain = maxGain(root->right);
    righttGain = righttGain>0?righttGain:0;

    int price = root->val + leftGain + righttGain;
    // 更新最大值
    maxsum = maxsum>price?maxsum:price;

    //当前树的最大贡献为本结点贡献加子树中大的一个
    return root->val + (leftGain>righttGain?leftGain:righttGain);//注意括号
}

int maxPathSum(struct TreeNode* root){
    maxsum = -99999;
    maxGain(root);
    return maxsum;
}



int main(int argc, char const *argv[])
{
    
    return 0;
}
