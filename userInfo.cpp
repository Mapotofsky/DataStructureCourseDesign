#include"userInfo.h"
#include<iostream>
using namespace std;

//--- ��ȡ�ڵ��ƽ������
int UserInfo::getBalanceFactor()
{
	// ƽ�����ӵ��ڸýڵ��������߶ȼ�ȥ�������߶�
	balanceFactor = this->left->getHeight() - this->right->getHeight();
	return balanceFactor;
}

//--- getHeight�ĸ�������
int UserInfo::getHeightAux(UserInfo* root)
{
	if (root == 0) {
		return 0;
	}
	else {
		int a = getHeightAux(root->left) + 1;                 // �ݹ��������0��ʼ��μ�1
		int b = getHeightAux(root->right) + 1;
		height = a > b ? a : b;                               // ÿһ����ȡ�ϴ����Ϊ�����߶�
		return height;
	}
}
