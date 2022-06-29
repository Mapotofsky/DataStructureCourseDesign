#pragma once
#include<iostream>
#include<string>
using namespace std;

//----- 包含用户信息的节点类 -----
class UserInfo
{
public:
	string userId, userPw;                                    // 用户id和密码
	int balanceFactor, height;                                // 平衡因子和高度
	UserInfo* left, * right, * parent;                        // 指向左右子女、双亲节点的指针

	UserInfo() :balanceFactor(0), height(0),
		left(0), right(0), parent(0) {};                      // 默认构造函数
	UserInfo(const string& id, const string& password) :
		userId(id), userPw(password), balanceFactor(0), height(0),
		left(0), right(0), parent(0) {};                      // 显式构造函数
	int getBalanceFactor();                                   // 获取节点的平衡因子
	int getHeight();                                          // 获取子树的高度
private:
	int getHeightAux(UserInfo* root);                         // getHeight的辅助函数
};

//--- 获取子树的高度
inline int UserInfo::getHeight() {
	return getHeightAux(this);
}