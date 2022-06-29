#pragma once
#include"userInfo.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//----- ���������û���Ϣ���� -----
class UserTree
{
public:
	//***** ������Ա *****
	UserTree() :myRoot(0), n(0) {}                            // Ĭ�Ϲ��캯��
	UserTree(const string& f) :myRoot(0), filename(f), n(0) {}// ���ع��캯��
	bool empty() const { return myRoot == 0; }                // �пպ���
	void insert();   	                                      // ���뺯��
	void read();                                              // ���뺯��
	void write(ostream& out);                                 // �������
	void inorder(ostream& out) const;                         // �����������
	bool login();	                                          // ��¼����
	void remove();	                                          // ɾ������
	void search(const string& id, bool& found,
		UserInfo*& locptr) const;                             // ���Һ���
	void update();                                            // �޸����뺯��
	void graph() const;	                                      // ͼ���������
	void getBF();                                             // ��ȡ���ڵ��ƽ������
	~UserTree();                                         	  // ��������

private:
	//***** ˽�к�����Ա *****
	void inorderAux(ostream& out, UserInfo* subroot) const;   // inorder�ĸ�������
	void insertAux(const bool& print, 
		const string& id, const string& password);            // insert�ĸ�������
	void getBFAux(UserInfo* subroot);                         // getBF�ĸ�������
	void LL(UserInfo* userB);                                 // ��������
	void RR(UserInfo* userB);                                 // ��������
	void LR(UserInfo* userC);                                 // ��-��������
	void RL(UserInfo* userC);                                 // ��-��������
	void destAux(UserInfo* subtreeRoot);                      // ���������ĸ�������

	//***** ���ݳ�Ա *****
	UserInfo* myRoot;                                         // ָ����ڵ�
	string filename;                                          // �洢���ļ���
	int n;                                                    // �������
};

//--- �����������
inline void UserTree::inorder(ostream& out) const {
	inorderAux(out, myRoot);
}

//--- ��ȡ���ڵ��ƽ������
inline void UserTree::getBF() {
	getBFAux(myRoot);
}

//--- ��������
inline UserTree::~UserTree()
{
	destAux(myRoot);
}
