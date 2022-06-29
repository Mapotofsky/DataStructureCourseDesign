#include "userTree.h"
#include<iomanip>
#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<Windows.h>
using namespace std;

class UserInfo;

//--- ���뺯��
void UserTree::insert()
{
	string id, password, pw;

	// ������Ϣ
	while (1) {
		cout << setfill(' ') << setw(31) << "�½��û���Ϣ\n";
		cout << "--------------------------------------------------\n";
		cout << "�����û�����";
		cin >> id;
		cout << "�������룺";
		cin >> password;
		cout << "ȷ�����룺";
		cin >> pw;
		cout << "--------------------------------------------------\n";
		// ȷ������
		if (password != pw) {
			cout << "�������벻һ�£��Ƿ���Ҫ�������룿\n\n";
			cout << setfill(' ') << setw(28) << "��1����\n";
			cout << setfill(' ') << setw(29) << "��2����\n\n";
			int t;
			cin >> t;
			if (t == 2)
			return;
			system("cls");
		}
		else {
			++n;
			// ��һ��������ʾ�����ʾ��Ϣ
			insertAux(1, id, password);
			break;
		}
	}

	Sleep(1000);
}

//--- ���뺯��
void UserTree::read()
{
	string id, password;

	// �����ӵ������Ϸ��û���Ϣ���ļ�����
	ifstream in(filename.data(), ios::in);
	if (!in.is_open()) {
		cerr << filename << "�ļ��޷���\n";
		exit(1);
	}

	int i;
	in >> i;
	n = i;
	//��ȡ�û���Ϣ
	for (; i > 0; --i) {
		in >> id >> password;
		// ��һ��������ʾ�������ʾ��Ϣ
		insertAux(0, id, password);
	}
}

//--- �������
void UserTree::write(ostream& out)
{
	inorder(out);                                             // �������
}

//--- ��¼����
bool UserTree::login()
{
	string id, password;
	bool found;
	UserInfo* locptr = myRoot;

	// ������Ϣ
	while (1) {
		cout << setfill(' ') << setw(29) << "�û���¼\n";
		cout << "--------------------------------------------------\n";
		cout << "�����û�����";
		cin >> id;
		cout << "�������룺";
		cin >> password;
		cout << "--------------------------------------------------\n";
		// ���ҽڵ�
		search(id, found, locptr);
		if (!found || locptr == 0) {
			cout << "���û������ڣ��Ƿ�ע�����û���\n";
			cout << setfill(' ') << setw(28) << "��1����\n";
			cout << setfill(' ') << setw(29) << "��2����\n\n";
			int t;
			cin >> t;
			cout << "==================================================\n";
			if (t == 1)
				insert();
			else
				return false;
		}
		else if (locptr->userPw != password) {
			cout << "��������Ƿ���Ҫ�������룿\n\n";
			cout << setfill(' ') << setw(28) << "��1����\n";
			cout << setfill(' ') << setw(29) << "��2����\n\n";
			int t;
			cin >> t;
			if (t == 2)
				break;
			system("cls");
		}
		else {
			cout << "��¼�ɹ���\n";
			cout << "==================================================\n";
			return true;
		}
	}
	return false;
}

//--- ɾ������
void UserTree::remove()
{
	string id, password;
	bool draw = false;
	bool found;
	UserInfo* x = myRoot;

	// ������Ϣ
	cout << setfill(' ') << setw(29) << "ɾ���û�\n";
	cout << "--------------------------------------------------\n";
	cout << "�����û�����";
	cin >> id;
	cout << "�������룺";
	cin >> password;
	cout << "--------------------------------------------------\n";

	// ����x��λ��
	search(id, found, x);
	if (!found || x == 0) {
		cout << "���˺Ų����ڣ�\n";
		cout << "==================================================\n";
		return;
	}
	if (password != x->userPw) {
		cout << "�������\n";
		cout << "==================================================\n";
		return;
	}

	// ͼ�����
	cout << "�Ƿ�鿴��ϸ�Ľڵ�ṹ��\n\n";
	cout << setfill(' ') << setw(28) << "��1����\n";
	cout << setfill(' ') << setw(29) << "��2����\n\n";
	int t;
	cin >> t;
	cout << "-------------------------------------------------\n";
	t == 1 ? draw = true : draw = false;
	if (draw) {
		graph();
		cout << "\n-------------------------------------------------\n";
		system("pause");
	}

	// �ýڵ���2����Ůʱ
	if (x->left != 0 && x->right != 0) {
		// ����x��������
		UserInfo* xSucc = x->right;
		while (xSucc->left != 0)                              // �½���������
			xSucc = xSucc->left;
		// ��xSucc����������x���޸�xΪָ�򽫱�ɾ���ĺ��
		x->userId = xSucc->userId;
		x->userPw = xSucc->userPw;
		x = xSucc;
		// �Դ˽����ͳһ��0��1��Ů�ڵ��ɾ��
	}
	// �ýڵ���1����û����Ůʱ
	UserInfo* subtree = x->left;
	if (subtree == 0)
		subtree = x->right;
	if (x->parent == 0)                                       // xΪ����ɾ���ĸ��ڵ�
		myRoot = subtree;                                     // ʵ������������ƽ���������
	else if (x->parent->left == x) {
		x->parent->left = subtree;                            // ��x����\����Ů�����滻
		if(subtree)
			subtree->parent = x->parent;
	}
	else {
		x->parent->right = subtree;
		if(subtree)
			subtree->parent = x->parent;
	}

	// ��ȡ���ڵ��ƽ������
	getBF();

	UserInfo* locptr = x;
	UserInfo* parent = locptr->parent;
	// ����ƽ��
	while (parent) {                                          // ɾ���㲻Ϊ���ڵ�ʱ
		if (parent->balanceFactor == 2) {                     // ��ʱһ�����Ҷ�ɾ��
			// �ӽڵ�ƽ������Ϊ0ʱ��Ҳ��������
			if (parent->left &&
				(parent->left->balanceFactor == 1 || parent->left->balanceFactor == 0))
				RR(parent->left);                             // ����
			else if (parent->left && parent->left->balanceFactor == -1)
				LR(parent->left);                             // ��-����
		}
		else if (parent->balanceFactor == -2) {               // ��ʱһ�������ɾ��
			if (parent->right && parent->right->balanceFactor == 1)
				RL(parent->right);                            // ��-����
			// �ӽڵ�ƽ������Ϊ0ʱ��Ҳ��������
			else if (parent->right &&
				(parent->right->balanceFactor == -1 || parent->right->balanceFactor == 0))
				LL(parent->right);                            // ����
		}

		// ����������ƽ��Ľڵ�ֱ����������
		locptr = parent;
		parent = locptr->parent;
	}

	// �ͷ��ڴ�
	delete x;
	--n;

	// �����ӵ������Ϸ��û���Ϣ���ļ�����
	ofstream out(filename.data());
	if (!out.is_open()) {
		cerr << filename << "�ļ��޷���\n";
		exit(1);
	}
	// �����ļ�����
	out << n << endl;
	write(out);

	// ͼ�����
	if (draw) {
		graph();
		cout << "\n-------------------------------------------------\n";
		system("pause");
	}

	cout << "ɾ���û��ɹ���\n";
	cout << "==================================================\n";
}

//--- �޸����뺯��
void UserTree::update()
{
	// ������Ϣ
	string id, password, newpw;
	cout << setfill(' ') << setw(29) << "�޸�����\n";
	cout << "--------------------------------------------------\n";
	cout << "�����û�����";
	cin >> id;
	cout << "�������룺";
	cin >> password;
	cout << "���������룺";
	cin >> newpw;
	cout << "--------------------------------------------------\n";

	// ����λ��
	bool found;
	UserInfo* x = myRoot;
	search(id, found, x);
	if (!found) {
		cout << "���˺Ų����ڣ�\n";
		cout << "==================================================\n";
		return;
	}

	if (password == x->userPw) {
		x->userPw = newpw;
		
		// �����ӵ������Ϸ��û���Ϣ���ļ�����
		ofstream out(filename.data());
		if (!out.is_open()) {
			cerr << filename << "�ļ��޷���\n";
			exit(1);
		}
		// �����ļ�����
		out << n << endl;
		write(out);

		cout << "�޸�����ɹ���\n";
	}
	else
		cout << "ԭ���벻��ȷ��\n";
	cout << "==================================================\n";
}

//--- ͼ���������
void UserTree::graph() const
{
	if (myRoot != 0) {
		queue<UserInfo*> q;
		int h = myRoot->getHeight();                          // h >= 1
		int n = 0, depth = 0;
		UserInfo* none = new UserInfo(" ", " ");              // �ڵ�ֵΪ�ո�����ռλ

		for (q.push(myRoot); h > 0 && !q.empty(); q.pop()) {
			UserInfo* locptr = q.front();
			int t = 2 * (int(pow(2, h)) - 1);
			int u = t + 4;                                    // ������ÿ�������id��ռ����

			// ����ڵ�
			cout << setfill(' ') << setw(u) << locptr->userId;
			cout << setfill(' ') << setw(t) << ' ';

			if (locptr->left)
				q.push(locptr->left);
			else
				q.push(none);                                 // ��������\����Ů������ո�ڵ�ռλ
			if (locptr->right)
				q.push(locptr->right);
			else
				q.push(none);                                 // ��������\����Ů������ո�ڵ�ռλ

			// λ�ڸò����Ľڵ�ʱ
			if (++n == int(pow(2, depth))) {
				n = 0;
				++depth;
				--h;
				cout << endl;
			}
		}
	}
	else {
		cout << "û�����ݣ�\n";
	}
}

//--- ���Һ���
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

//--- inorder�ĸ�������
void UserTree::inorderAux(ostream& out, UserInfo* subroot) const
{
	if (subroot != 0) {
		inorderAux(out, subroot->left);
		out << subroot->userId << " " << subroot->userPw << endl;
		inorderAux(out, subroot->right);
	}
}

//--- insert�ĸ�������
void UserTree::insertAux(const bool& print, const string& id, const string& password)
{
	bool found = false;
	bool draw = false;
	UserInfo* locptr = myRoot, * parent = 0;

	// ���Ҳ���λ��
	while (!found && locptr != 0) {
		parent = locptr;
		if (id < locptr->userId)
			locptr = locptr->left;
		else if (id > locptr->userId)
			locptr = locptr->right;
		else
			found = true;
	}

	// ����ڵ�
	if (!found) {
		locptr = new UserInfo(id, password);
		if (parent == 0)
			myRoot = locptr;                                       // ����
		else if (id < parent->userId) {
			parent->left = locptr;
			locptr->parent = parent;
		}
		else {
			parent->right = locptr;
			locptr->parent = parent;
		}

		// ͼ�����
		if (print) {
			cout << "�Ƿ�鿴��ϸ�Ľڵ�ṹ��\n\n";
			cout << setfill(' ') << setw(28) << "��1����\n";
			cout << setfill(' ') << setw(29) << "��2����\n\n";
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

		// ��ȡ���ڵ��ƽ������
		getBF();

		// ����ƽ��
		while (parent) {
			// Ĭ�ϲ���ǰ����ƽ��ģ���ƽ������Ϊ0ʱ��Ϊ���������ƽ��
			if (parent->balanceFactor == 0)
				break;
			// ����������ƽ��Ľڵ�
			else if (parent->balanceFactor == 1 || parent->balanceFactor == -1) {
				locptr = parent;
				parent = locptr->parent;
			}
			// �Է��������Ľ�����ת
			// ������������룬�ʲ���ڵ��ϲ�������ӽڵ�ƽ������Ϊ0�����ڵ�Ϊ��2�����
			else {
				if (parent->balanceFactor == 2) {             // ��ʱһ������˲���
					if (locptr->balanceFactor == 1)
						RR(locptr);                           // ����
					else if (locptr->balanceFactor == -1)
						LR(locptr);                           // ��-����
				}
				else if (parent->balanceFactor == -2) {       // ��ʱһ�����Ҷ˲���
					if (locptr->balanceFactor == 1)
						RL(locptr);                           // ��-����
					else if (locptr->balanceFactor == -1)
						LL(locptr);                           // ����
				}
				if (print && draw) {                          // ͼ�����
					graph();
					cout << "\n-------------------------------------------------\n";
					system("pause");
				}
				break;
			}
		}

		if (print) {
			// �����ӵ������Ϸ��û���Ϣ���ļ�����
			ofstream out(filename.data());
			if (!out.is_open()) {
				cerr << filename << "�ļ��޷���\n";
				exit(1);
			}
			// �����ļ���Ϣ
			out << n << endl;
			write(out);

			cout << "�½��û��ɹ����������������档\n";
			cout << "==================================================\n";
		}
	}
	else
		if (print) {
			cout << "���˺��Ѵ��ڣ��������������档\n";
			cout << "==================================================\n";
		}
}

//--- getBF�ĸ�������
void UserTree::getBFAux(UserInfo* subroot)
{
	// ����������ÿ���ڵ��ƽ������
	if (subroot != 0) {
		getBFAux(subroot->left);
		subroot->getBalanceFactor();
		getBFAux(subroot->right);
	}
}

//--- ��������
void UserTree::LL(UserInfo* userB)
{
	UserInfo* userA = userB->parent;
	if (!(userA->right == userB && userB->right != 0)) {
		cerr << "��������������\n";
		return;
	}
	bool flag = false;
	if (userA == myRoot)
		flag = true;
	// A��˫�׽ڵ��Ӧָ��ָ��B
	if (userA->parent != 0) {
		if (userA->parent->left == userA)
			userA->parent->left = userB;
		else
			userA->parent->right = userB;
	}
	// �޸�AB֮���ָ��
	userB->parent = userA->parent;
	userA->parent = userB;
	userA->right = userB->left;
	if (userB->left)
		userB->left->parent = userA;
	userB->left = userA;
	// A�Ǹ��ڵ㣬����ת����ڵ�ָ��ָ��B
	if (flag)
		myRoot = userB;
}

//--- ��������
void UserTree::RR(UserInfo* userB)
{
	UserInfo* userA = userB->parent;
	if (!(userA->left == userB && userB->left != 0)) {
		cerr << "��������������\n";
		return;
	}
	bool flag = false;
	if (userA == myRoot)
		flag = true;
	// A��˫�׽ڵ��Ӧָ��ָ��B
	if (userA->parent != 0) {
		if (userA->parent->left == userA)
			userA->parent->left = userB;
		else
			userA->parent->right = userB;
	}
	// �޸�AB֮���ָ��
	userB->parent = userA->parent;
	userA->parent = userB;
	userA->left = userB->right;
	if (userB->right)
		userB->right->parent = userA;
	userB->right = userA;
	// A�Ǹ��ڵ㣬����ת����ڵ�ָ��ָ��B
	if (flag)
		myRoot = userB;
}

//--- ��-��������
void UserTree::LR(UserInfo* userB)
{
	// ������
	UserInfo* userC = userB->right;
	if (userC == 0) {
		cerr << "��������-��������\n";
		return;
	}
	UserInfo* userA = userB->parent;
	if (userA == 0 || userA->left != userB) {
		cerr << "��������-��������\n";
		return;
	}
	userC->parent = userA;
	userB->parent = userC;
	userB->right = userC->left;
	if (userC->left)
		userC->left->parent = userB;
	userC->left = userB;
	userA->left = userC;
	// ������
	RR(userC);
}

//--- ��-��������
void UserTree::RL(UserInfo* userB)
{
	// ������
	UserInfo* userC = userB->left;
	if (userC == 0) {
		cerr << "��������-��������\n";
		return;
	}
	UserInfo* userA = userB->parent;
	if (userA == 0 || userA->right != userB) {
		cerr << "��������-��������\n";
		return;
	}
	userC->parent = userA;
	userB->parent = userC;
	userB->left = userC->right;
	if (userC->right)
		userC->right->parent = userB;
	userC->right = userB;
	userA->right = userC;
	// ������
	LL(userC);
}

void UserTree::destAux(UserInfo* subroot)
{
	// ��������������ͷ�
	if (subroot != 0) {
		destAux(subroot->left);
		destAux(subroot->right);
		delete subroot;
	}
}
