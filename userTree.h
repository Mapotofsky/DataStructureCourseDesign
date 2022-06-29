#pragma once
#include"userInfo.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//----- 包含所有用户信息的类 -----
class UserTree
{
public:
	//***** 函数成员 *****
	UserTree() :myRoot(0), n(0) {}                            // 默认构造函数
	UserTree(const string& f) :myRoot(0), filename(f), n(0) {}// 重载构造函数
	bool empty() const { return myRoot == 0; }                // 判空函数
	void insert();   	                                      // 插入函数
	void read();                                              // 输入函数
	void write(ostream& out);                                 // 输出函数
	void inorder(ostream& out) const;                         // 中序遍历函数
	bool login();	                                          // 登录函数
	void remove();	                                          // 删除函数
	void search(const string& id, bool& found,
		UserInfo*& locptr) const;                             // 查找函数
	void update();                                            // 修改密码函数
	void graph() const;	                                      // 图形输出函数
	void getBF();                                             // 获取各节点的平衡因子
	~UserTree();                                         	  // 析构函数

private:
	//***** 私有函数成员 *****
	void inorderAux(ostream& out, UserInfo* subroot) const;   // inorder的辅助函数
	void insertAux(const bool& print, 
		const string& id, const string& password);            // insert的辅助函数
	void getBFAux(UserInfo* subroot);                         // getBF的辅助函数
	void LL(UserInfo* userB);                                 // 左旋操作
	void RR(UserInfo* userB);                                 // 右旋操作
	void LR(UserInfo* userC);                                 // 左-右旋操作
	void RL(UserInfo* userC);                                 // 右-左旋操作
	void destAux(UserInfo* subtreeRoot);                      // 析构函数的辅助函数

	//***** 数据成员 *****
	UserInfo* myRoot;                                         // 指向根节点
	string filename;                                          // 存储的文件名
	int n;                                                    // 结点数量
};

//--- 中序遍历函数
inline void UserTree::inorder(ostream& out) const {
	inorderAux(out, myRoot);
}

//--- 获取各节点的平衡因子
inline void UserTree::getBF() {
	getBFAux(myRoot);
}

//--- 析构函数
inline UserTree::~UserTree()
{
	destAux(myRoot);
}
