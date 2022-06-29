#pragma once
#include<iostream>
#include<string>
using namespace std;

//----- �����û���Ϣ�Ľڵ��� -----
class UserInfo
{
public:
	string userId, userPw;                                    // �û�id������
	int balanceFactor, height;                                // ƽ�����Ӻ͸߶�
	UserInfo* left, * right, * parent;                        // ָ��������Ů��˫�׽ڵ��ָ��

	UserInfo() :balanceFactor(0), height(0),
		left(0), right(0), parent(0) {};                      // Ĭ�Ϲ��캯��
	UserInfo(const string& id, const string& password) :
		userId(id), userPw(password), balanceFactor(0), height(0),
		left(0), right(0), parent(0) {};                      // ��ʽ���캯��
	int getBalanceFactor();                                   // ��ȡ�ڵ��ƽ������
	int getHeight();                                          // ��ȡ�����ĸ߶�
private:
	int getHeightAux(UserInfo* root);                         // getHeight�ĸ�������
};

//--- ��ȡ�����ĸ߶�
inline int UserInfo::getHeight() {
	return getHeightAux(this);
}