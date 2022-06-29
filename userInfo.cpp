#include"userInfo.h"
#include<iostream>
using namespace std;

//--- 获取节点的平衡因子
int UserInfo::getBalanceFactor()
{
	// 平衡因子等于该节点左子树高度减去右子树高度
	balanceFactor = this->left->getHeight() - this->right->getHeight();
	return balanceFactor;
}

//--- getHeight的辅助函数
int UserInfo::getHeightAux(UserInfo* root)
{
	if (root == 0) {
		return 0;
	}
	else {
		int a = getHeightAux(root->left) + 1;                 // 递归过程中由0开始逐次加1
		int b = getHeightAux(root->right) + 1;
		height = a > b ? a : b;                               // 每一轮中取较大的作为子树高度
		return height;
	}
}
