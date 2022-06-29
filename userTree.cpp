#include "userTree.h"
#include<iomanip>
#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<Windows.h>
using namespace std;

class UserInfo;

//--- 插入函数
void UserTree::insert()
{
	string id, password, pw;

	// 输入信息
	while (1) {
		cout << setfill(' ') << setw(31) << "新建用户信息\n";
		cout << "--------------------------------------------------\n";
		cout << "输入用户名：";
		cin >> id;
		cout << "输入密码：";
		cin >> password;
		cout << "确认密码：";
		cin >> pw;
		cout << "--------------------------------------------------\n";
		// 确认密码
		if (password != pw) {
			cout << "两次密码不一致，是否需要重新输入？\n\n";
			cout << setfill(' ') << setw(28) << "（1）是\n";
			cout << setfill(' ') << setw(29) << "（2）否\n\n";
			int t;
			cin >> t;
			if (t == 2)
			return;
			system("cls");
		}
		else {
			++n;
			// 第一个参数表示输出提示信息
			insertAux(1, id, password);
			break;
		}
	}

	Sleep(1000);
}

//--- 输入函数
void UserTree::read()
{
	string id, password;

	// 打开连接到包含合法用户信息的文件的流
	ifstream in(filename.data(), ios::in);
	if (!in.is_open()) {
		cerr << filename << "文件无法打开\n";
		exit(1);
	}

	int i;
	in >> i;
	n = i;
	//读取用户信息
	for (; i > 0; --i) {
		in >> id >> password;
		// 第一个参数表示不输出提示信息
		insertAux(0, id, password);
	}
}

//--- 输出函数
void UserTree::write(ostream& out)
{
	inorder(out);                                             // 中序输出
}

//--- 登录函数
bool UserTree::login()
{
	string id, password;
	bool found;
	UserInfo* locptr = myRoot;

	// 输入信息
	while (1) {
		cout << setfill(' ') << setw(29) << "用户登录\n";
		cout << "--------------------------------------------------\n";
		cout << "输入用户名：";
		cin >> id;
		cout << "输入密码：";
		cin >> password;
		cout << "--------------------------------------------------\n";
		// 查找节点
		search(id, found, locptr);
		if (!found || locptr == 0) {
			cout << "该用户不存在，是否注册新用户？\n";
			cout << setfill(' ') << setw(28) << "（1）是\n";
			cout << setfill(' ') << setw(29) << "（2）否\n\n";
			int t;
			cin >> t;
			cout << "==================================================\n";
			if (t == 1)
				insert();
			else
				return false;
		}
		else if (locptr->userPw != password) {
			cout << "密码错误，是否需要重新输入？\n\n";
			cout << setfill(' ') << setw(28) << "（1）是\n";
			cout << setfill(' ') << setw(29) << "（2）否\n\n";
			int t;
			cin >> t;
			if (t == 2)
				break;
			system("cls");
		}
		else {
			cout << "登录成功！\n";
			cout << "==================================================\n";
			return true;
		}
	}
	return false;
}

//--- 删除函数
void UserTree::remove()
{
	string id, password;
	bool draw = false;
	bool found;
	UserInfo* x = myRoot;

	// 输入信息
	cout << setfill(' ') << setw(29) << "删除用户\n";
	cout << "--------------------------------------------------\n";
	cout << "输入用户名：";
	cin >> id;
	cout << "输入密码：";
	cin >> password;
	cout << "--------------------------------------------------\n";

	// 查找x的位置
	search(id, found, x);
	if (!found || x == 0) {
		cout << "该账号不存在！\n";
		cout << "==================================================\n";
		return;
	}
	if (password != x->userPw) {
		cout << "密码错误！\n";
		cout << "==================================================\n";
		return;
	}

	// 图形输出
	cout << "是否查看详细的节点结构？\n\n";
	cout << setfill(' ') << setw(28) << "（1）是\n";
	cout << setfill(' ') << setw(29) << "（2）否\n\n";
	int t;
	cin >> t;
	cout << "-------------------------------------------------\n";
	t == 1 ? draw = true : draw = false;
	if (draw) {
		graph();
		cout << "\n-------------------------------------------------\n";
		system("pause");
	}

	// 该节点有2个子女时
	if (x->left != 0 && x->right != 0) {
		// 查找x的中序后继
		UserInfo* xSucc = x->right;
		while (xSucc->left != 0)                              // 下降到左子树
			xSucc = xSucc->left;
		// 将xSucc的内容移至x，修改x为指向将被删除的后继
		x->userId = xSucc->userId;
		x->userPw = xSucc->userPw;
		x = xSucc;
		// 自此将情况统一于0或1子女节点的删除
	}
	// 该节点有1个或没有子女时
	UserInfo* subtree = x->left;
	if (subtree == 0)
		subtree = x->right;
	if (x->parent == 0)                                       // x为将被删除的根节点
		myRoot = subtree;                                     // 实际上子树本就平衡无需调整
	else if (x->parent->left == x) {
		x->parent->left = subtree;                            // 以x的左\右子女将其替换
		if(subtree)
			subtree->parent = x->parent;
	}
	else {
		x->parent->right = subtree;
		if(subtree)
			subtree->parent = x->parent;
	}

	// 获取各节点的平衡因子
	getBF();

	UserInfo* locptr = x;
	UserInfo* parent = locptr->parent;
	// 重新平衡
	while (parent) {                                          // 删除点不为根节点时
		if (parent->balanceFactor == 2) {                     // 此时一定是右端删除
			// 子节点平衡因子为0时，也采用右旋
			if (parent->left &&
				(parent->left->balanceFactor == 1 || parent->left->balanceFactor == 0))
				RR(parent->left);                             // 右旋
			else if (parent->left && parent->left->balanceFactor == -1)
				LR(parent->left);                             // 左-右旋
		}
		else if (parent->balanceFactor == -2) {               // 此时一定是左端删除
			if (parent->right && parent->right->balanceFactor == 1)
				RL(parent->right);                            // 右-左旋
			// 子节点平衡因子为0时，也采用左旋
			else if (parent->right &&
				(parent->right->balanceFactor == -1 || parent->right->balanceFactor == 0))
				LL(parent->right);                            // 左旋
		}

		// 向上搜索不平衡的节点直到搜索到根
		locptr = parent;
		parent = locptr->parent;
	}

	// 释放内存
	delete x;
	--n;

	// 打开连接到包含合法用户信息的文件的流
	ofstream out(filename.data());
	if (!out.is_open()) {
		cerr << filename << "文件无法打开\n";
		exit(1);
	}
	// 更新文件内容
	out << n << endl;
	write(out);

	// 图形输出
	if (draw) {
		graph();
		cout << "\n-------------------------------------------------\n";
		system("pause");
	}

	cout << "删除用户成功！\n";
	cout << "==================================================\n";
}

//--- 修改密码函数
void UserTree::update()
{
	// 输入信息
	string id, password, newpw;
	cout << setfill(' ') << setw(29) << "修改密码\n";
	cout << "--------------------------------------------------\n";
	cout << "输入用户名：";
	cin >> id;
	cout << "输入密码：";
	cin >> password;
	cout << "输入新密码：";
	cin >> newpw;
	cout << "--------------------------------------------------\n";

	// 查找位置
	bool found;
	UserInfo* x = myRoot;
	search(id, found, x);
	if (!found) {
		cout << "该账号不存在！\n";
		cout << "==================================================\n";
		return;
	}

	if (password == x->userPw) {
		x->userPw = newpw;
		
		// 打开连接到包含合法用户信息的文件的流
		ofstream out(filename.data());
		if (!out.is_open()) {
			cerr << filename << "文件无法打开\n";
			exit(1);
		}
		// 更新文件内容
		out << n << endl;
		write(out);

		cout << "修改密码成功！\n";
	}
	else
		cout << "原密码不正确！\n";
	cout << "==================================================\n";
}

//--- 图形输出函数
void UserTree::graph() const
{
	if (myRoot != 0) {
		queue<UserInfo*> q;
		int h = myRoot->getHeight();                          // h >= 1
		int n = 0, depth = 0;
		UserInfo* none = new UserInfo(" ", " ");              // 节点值为空格，用于占位

		for (q.push(myRoot); h > 0 && !q.empty(); q.pop()) {
			UserInfo* locptr = q.front();
			int t = 2 * (int(pow(2, h)) - 1);
			int u = t + 4;                                    // 包括了每个输出的id所占长度

			// 输出节点
			cout << setfill(' ') << setw(u) << locptr->userId;
			cout << setfill(' ') << setw(t) << ' ';

			if (locptr->left)
				q.push(locptr->left);
			else
				q.push(none);                                 // 发现无左\右子女，插入空格节点占位
			if (locptr->right)
				q.push(locptr->right);
			else
				q.push(none);                                 // 发现无左\右子女，插入空格节点占位

			// 位于该层最后的节点时
			if (++n == int(pow(2, depth))) {
				n = 0;
				++depth;
				--h;
				cout << endl;
			}
		}
	}
	else {
		cout << "没有数据！\n";
	}
}

//--- 查找函数
void UserTree::search(const string& id, bool& found, UserInfo*& locptr) const
{
	found = false;
	while (!found && locptr != 0) {
		if (id < locptr->userId)
			locptr = locptr->left;
		else if (id > locptr->userId)
			locptr = locptr->right;
		else
			found = true;
	}
}

//--- inorder的辅助函数
void UserTree::inorderAux(ostream& out, UserInfo* subroot) const
{
	if (subroot != 0) {
		inorderAux(out, subroot->left);
		out << subroot->userId << " " << subroot->userPw << endl;
		inorderAux(out, subroot->right);
	}
}

//--- insert的辅助函数
void UserTree::insertAux(const bool& print, const string& id, const string& password)
{
	bool found = false;
	bool draw = false;
	UserInfo* locptr = myRoot, * parent = 0;

	// 查找插入位置
	while (!found && locptr != 0) {
		parent = locptr;
		if (id < locptr->userId)
			locptr = locptr->left;
		else if (id > locptr->userId)
			locptr = locptr->right;
		else
			found = true;
	}

	// 插入节点
	if (!found) {
		locptr = new UserInfo(id, password);
		if (parent == 0)
			myRoot = locptr;                                       // 空树
		else if (id < parent->userId) {
			parent->left = locptr;
			locptr->parent = parent;
		}
		else {
			parent->right = locptr;
			locptr->parent = parent;
		}

		// 图形输出
		if (print) {
			cout << "是否查看详细的节点结构？\n\n";
			cout << setfill(' ') << setw(28) << "（1）是\n";
			cout << setfill(' ') << setw(29) << "（2）否\n\n";
			int t;
			cin >> t;
			cout << "-------------------------------------------------\n";
			t == 1 ? draw = true : draw = false;
			if (draw) {
				graph();
				cout << "\n-------------------------------------------------\n";
				system("pause");
			}
		}

		// 获取各节点的平衡因子
		getBF();

		// 重新平衡
		while (parent) {
			// 默认插入前树是平衡的，则平衡因子为0时认为到达根或已平衡
			if (parent->balanceFactor == 0)
				break;
			// 向上搜索不平衡的节点
			else if (parent->balanceFactor == 1 || parent->balanceFactor == -1) {
				locptr = parent;
				parent = locptr->parent;
			}
			// 对符合条件的进行旋转
			// 由于是逐个插入，故插入节点上不会存在子节点平衡因子为0而父节点为±2的情况
			else {
				if (parent->balanceFactor == 2) {             // 此时一定是左端插入
					if (locptr->balanceFactor == 1)
						RR(locptr);                           // 右旋
					else if (locptr->balanceFactor == -1)
						LR(locptr);                           // 左-右旋
				}
				else if (parent->balanceFactor == -2) {       // 此时一定是右端插入
					if (locptr->balanceFactor == 1)
						RL(locptr);                           // 右-左旋
					else if (locptr->balanceFactor == -1)
						LL(locptr);                           // 左旋
				}
				if (print && draw) {                          // 图形输出
					graph();
					cout << "\n-------------------------------------------------\n";
					system("pause");
				}
				break;
			}
		}

		if (print) {
			// 打开连接到包含合法用户信息的文件的流
			ofstream out(filename.data());
			if (!out.is_open()) {
				cerr << filename << "文件无法打开\n";
				exit(1);
			}
			// 更新文件信息
			out << n << endl;
			write(out);

			cout << "新建用户成功，即将返回主界面。\n";
			cout << "==================================================\n";
		}
	}
	else
		if (print) {
			cout << "该账号已存在，即将返回主界面。\n";
			cout << "==================================================\n";
		}
}

//--- getBF的辅助函数
void UserTree::getBFAux(UserInfo* subroot)
{
	// 中序遍历获得每个节点的平衡因子
	if (subroot != 0) {
		getBFAux(subroot->left);
		subroot->getBalanceFactor();
		getBFAux(subroot->right);
	}
}

//--- 左旋操作
void UserTree::LL(UserInfo* userB)
{
	UserInfo* userA = userB->parent;
	if (!(userA->right == userB && userB->right != 0)) {
		cerr << "不符合左旋条件\n";
		return;
	}
	bool flag = false;
	if (userA == myRoot)
		flag = true;
	// A的双亲节点对应指针指向B
	if (userA->parent != 0) {
		if (userA->parent->left == userA)
			userA->parent->left = userB;
		else
			userA->parent->right = userB;
	}
	// 修改AB之间的指针
	userB->parent = userA->parent;
	userA->parent = userB;
	userA->right = userB->left;
	if (userB->left)
		userB->left->parent = userA;
	userB->left = userA;
	// A是根节点，则旋转后根节点指针指向B
	if (flag)
		myRoot = userB;
}

//--- 右旋操作
void UserTree::RR(UserInfo* userB)
{
	UserInfo* userA = userB->parent;
	if (!(userA->left == userB && userB->left != 0)) {
		cerr << "不符合右旋条件\n";
		return;
	}
	bool flag = false;
	if (userA == myRoot)
		flag = true;
	// A的双亲节点对应指针指向B
	if (userA->parent != 0) {
		if (userA->parent->left == userA)
			userA->parent->left = userB;
		else
			userA->parent->right = userB;
	}
	// 修改AB之间的指针
	userB->parent = userA->parent;
	userA->parent = userB;
	userA->left = userB->right;
	if (userB->right)
		userB->right->parent = userA;
	userB->right = userA;
	// A是根节点，则旋转后根节点指针指向B
	if (flag)
		myRoot = userB;
}

//--- 左-右旋操作
void UserTree::LR(UserInfo* userB)
{
	// 先左旋
	UserInfo* userC = userB->right;
	if (userC == 0) {
		cerr << "不符合左-右旋条件\n";
		return;
	}
	UserInfo* userA = userB->parent;
	if (userA == 0 || userA->left != userB) {
		cerr << "不符合左-右旋条件\n";
		return;
	}
	userC->parent = userA;
	userB->parent = userC;
	userB->right = userC->left;
	if (userC->left)
		userC->left->parent = userB;
	userC->left = userB;
	userA->left = userC;
	// 再右旋
	RR(userC);
}

//--- 右-左旋操作
void UserTree::RL(UserInfo* userB)
{
	// 先右旋
	UserInfo* userC = userB->left;
	if (userC == 0) {
		cerr << "不符合右-左旋条件\n";
		return;
	}
	UserInfo* userA = userB->parent;
	if (userA == 0 || userA->right != userB) {
		cerr << "不符合右-左旋条件\n";
		return;
	}
	userC->parent = userA;
	userB->parent = userC;
	userB->left = userC->right;
	if (userC->right)
		userC->right->parent = userB;
	userC->right = userB;
	userA->right = userC;
	// 再左旋
	LL(userC);
}

void UserTree::destAux(UserInfo* subroot)
{
	// 后序遍历，依次释放
	if (subroot != 0) {
		destAux(subroot->left);
		destAux(subroot->right);
		delete subroot;
	}
}
