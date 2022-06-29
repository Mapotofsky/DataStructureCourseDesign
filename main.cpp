#include"userTree.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
using namespace std;

int main()
{
	// �����û���½ϵͳ�Ķ�����
	string filename = "userinfos.txt";
	UserTree* tree=new UserTree(filename);
	tree->read();

	//������
	while (1) {
		// ��¼����
		cout << "==================================================\n";
		cout << setfill(' ') << setw(29) << "WELCOME\n";
		cout << "--------------------------------------------------\n\n";
		cout << setfill(' ') << setw(29) << "��1����¼\n";
		cout << setfill(' ') << setw(29) << "��2��ע��\n";
		cout << setfill(' ') << setw(38) << "��3��չʾ���˽ṹ\n\n";
		cout << "��������ѡ��";
		int choose1;
		cin >> choose1;
		cout << "==================================================\n";

		// �û�����
		if (choose1 == 1) {
			bool flag = tree->login();
			if (flag) {
				system("pause");
				system("cls");
				while (1) {
					cout << "==================================================\n";
					cout << setfill(' ') << setw(29) << "�û�����\n";
					cout << "--------------------------------------------------\n\n";
					cout << setfill(' ') << setw(32) << "��1���޸�����\n";
					cout << setfill(' ') << setw(32) << "��2��ɾ���û�\n";
					cout << setfill(' ') << setw(33) << "��3���˳�����\n\n";
					cout << "��������ѡ��";
					int choose2;
					cin >> choose2;
					cout << "--------------------------------------------------\n";

					if (choose2 == 1)
						tree->update();
					else if (choose2 == 2) {
						tree->remove();
					}
					else if (choose2 == 3)
						break;
					else
						cout << "����������������룡\n";

					// ����
					Sleep(1000);
					system("cls");
				}
			}
		}
		else if (choose1 == 2)
			tree->insert();
		else if (choose1 == 3) {
			tree->graph();
			cout << "==================================================\n";
			system("pause");
		}
		else
			cout << "����������������룡\n";

		// ����
		Sleep(1000);
		system("cls");
	}
}