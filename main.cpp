#include"userTree.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
using namespace std;

int main()
{
	// 创建用户登陆系统的二叉树
	string filename = "userinfos.txt";
	UserTree* tree=new UserTree(filename);
	tree->read();

	//主界面
	while (1) {
		// 登录界面
		cout << "==================================================\n";
		cout << setfill(' ') << setw(29) << "WELCOME\n";
		cout << "--------------------------------------------------\n\n";
		cout << setfill(' ') << setw(29) << "（1）登录\n";
		cout << setfill(' ') << setw(29) << "（2）注册\n";
		cout << setfill(' ') << setw(38) << "（3）展示拓扑结构\n\n";
		cout << "输入您的选择：";
		int choose1;
		cin >> choose1;
		cout << "==================================================\n";

		// 用户界面
		if (choose1 == 1) {
			bool flag = tree->login();
			if (flag) {
				system("pause");
				system("cls");
				while (1) {
					cout << "==================================================\n";
					cout << setfill(' ') << setw(29) << "用户界面\n";
					cout << "--------------------------------------------------\n\n";
					cout << setfill(' ') << setw(32) << "（1）修改密码\n";
					cout << setfill(' ') << setw(32) << "（2）删除用户\n";
					cout << setfill(' ') << setw(33) << "（3）退出界面\n\n";
					cout << "输入您的选择：";
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
						cout << "输入错误，请重新输入！\n";

					// 清屏
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
			cout << "输入错误，请重新输入！\n";

		// 清屏
		Sleep(1000);
		system("cls");
	}
}