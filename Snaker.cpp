// Snaker.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Snaker.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <deque>
#define zone_size 25

// w,a,s,d,k对应的键值分别为119,97,115,100,107
using namespace std;

char body[zone_size][zone_size];//游戏过程界面
enum direction {up, down, left, right};//分别用于当前前进方向的判断
deque<pair<int, int>> snack;//存放组成蛇身体的每个结点的位置
size_t level;//设置难度
int x, y;//食物的二维坐标


int a = 10;

void srand_food() {//生成新食物的位置
	bool flag_srand = true;
	x = rand() % (zone_size - 1) + 0;
	y = rand() % (zone_size - 1) + 0;
	while (flag_srand) {//保证生成随机数的二维坐标不会与蛇身坐标重合
		flag_srand = false;
		for (size_t i = 0; i < snack.size(); i++) {
			if (snack[i].first == x && snack[i].second == y) {
				x = rand() % (zone_size - 1) + 0;
				y = rand() % (zone_size - 1) + 0;
				flag_srand = true;
			}
		}
	}
	flag_srand = true;
	body[x][y] = '*';
}

void climb(int s_direction) {
	int x_offset, y_offset;
	switch (s_direction) {
	case direction::up:
		x_offset = snack[snack.size() - 1].first - 1;
		y_offset = snack[snack.size() - 1].second; 
		break;
	case direction::down:
		x_offset = snack[snack.size() - 1].first + 1;
		y_offset = snack[snack.size() - 1].second;
		break;
	case direction::left:
		x_offset = snack[snack.size() - 1].first;
		y_offset = snack[snack.size() - 1].second - 1;
		break;
	case direction::right:
		x_offset = snack[snack.size() - 1].first;
		y_offset = snack[snack.size() - 1].second + 1;
	}
	if (body[x_offset][y_offset] == '*') {//向上走恰好吃到食物
		body[x_offset][y_offset] = '@';
		snack.push_back(make_pair(x_offset, y_offset));
		body[snack[0].first][snack[0].second] = ' ';
		snack.pop_front();
		snack.push_back(make_pair(x_offset, y_offset));
		body[snack[snack.size() - 1].first][snack[snack.size() - 1].second] = '@';
		srand_food();
	}
	else {//向上走
		snack.push_back(make_pair(x_offset, y_offset));
		body[snack[0].first][snack[0].second] = ' ';
		snack.pop_front();
		body[snack[snack.size() - 1].first][snack[snack.size() - 1].second] = '@';
	}
}

int main()
{
	bool flag = true;//主程序循环标志
	int ch,ch1 = 0;//ch获取按键信息,ch1用于难度判断
	/************************************程序主界面************************************/
	while (flag) {
		cout << "****************************************Snaker********************************************" << endl;
		cout << endl;
		cout << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		cout << "                             w 和 s 选择难度，k 开始游戏" << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		cout << endl;
		if (ch1 == 0) {
			cout << "                   >> 1.简单                           简单的难度:" << endl;
			cout << endl;
			cout << "                      2.困难                              蛇的移动速度较慢。" << endl;
			cout << endl;
			cout << "                      3.冷酷" << endl;
		}
		else if (ch1 == 1) {
			cout << "                      1.简单                           困难的难度:" << endl;
			cout << endl;
			cout << "                   >> 2.困难                              蛇的移动速度较快。" << endl;
			cout << endl;
			cout << "                      3.冷酷" << endl;
		}
		else {
			cout << "                      1.简单                           冷酷的难度:" << endl;
			cout << endl;
			cout << "                      2.困难                              你的眼镜可能会感到不适" << endl;
			cout << endl;
			cout << "                   >> 3.冷酷" << endl;
		}
		cout << endl;
		cout << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		cout << "                                    制作人: 相博文        " << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		if (_kbhit()) {
			ch = _getch();
			if (ch == 115)
				if (ch1 != 2)
					ch1++;
				else
					ch1 = 0;
			else if (ch == 119)
				if (ch1 != 0)
					ch1--;
				else
					ch1 = 2;
			else if (ch == 107) {
				flag = false;
				if (ch1 == 0)
					level = 100;
				else if (ch1 == 1)
					level = 50;
				else if (ch1 == 2)
					level = 1;
			}
		}
		system("cls");
	}
	flag = true;//重置标志器
	//程序初始状态
	for (size_t i = 0; i < zone_size; ++i)
		for (size_t j = 0; j < zone_size; ++j)
			body[i][j] = ' ';
	for (size_t i = 0; i < 4; ++i)
		body[0][i] = '@';
	for (size_t i = 0; i < zone_size; ++i) {
		for (size_t j = 0; j < zone_size; ++j)
			cout << body[i][j] << ' ';
		cout << endl;
	}
	/**********************************************************************************/
	/************************************游戏主过程************************************/
	for (size_t i = 0; i < 4; i++)//初始化蛇身长度为4
		snack.push_back(make_pair(0, i));
	int curr_dirct = direction::right;//蛇的初始化方向
	srand((unsigned)time(NULL));
	x = rand() % (zone_size-1) + 0,
	y = rand() % (zone_size-1) + 0;//随机初始化食物位置
	body[x][y] = '*';
	while (flag) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 119) {//'w'键
				if (snack[snack.size() - 1].first == 0)//上方已到边界
					flag = false;
				else if (curr_dirct == direction::down)//蛇无法向当前方向的相反方向走，按键无效
					continue;
				else if (body[snack[snack.size() - 1].first - 1][snack[snack.size() - 1].second] == '@')//向上行走会咬到自己
					flag = false;
				else {//向上走
					curr_dirct = direction::up;
					climb(direction::up);
				}
			}
			else if (ch == 97) {//'a'键
				if (snack[snack.size() - 1].second == 0)
					flag = false;
				else if (curr_dirct == direction::right)//蛇无法向当前方向的相反方向走，按键无效
					continue; 
				else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second - 1] == '@')
					flag = false;
				else {
					curr_dirct = direction::left;
					climb(direction::left);
				}
			}
			else if (ch == 115) {//'s'键
				if (snack[snack.size() - 1].first == zone_size - 1)
					flag = false;
				else if (curr_dirct == direction::up)//蛇无法向当前方向的相反方向走，按键无效
					continue; 
				else if (body[snack[snack.size() - 1].first + 1][snack[snack.size() - 1].second] == '@')
					flag = false;
				else {
					curr_dirct = direction::down;
					climb(direction::down);
				}
			}
			else if (ch == 100) {//'d'键
				if (snack[snack.size() - 1].first == zone_size - 1)
					flag = false;
				else if (curr_dirct == direction::left)//蛇无法向当前方向的相反方向走，按键无效
					continue; 
				else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second + 1] == '@')
					flag = false;
				else {
					curr_dirct = direction::right;
					climb(direction::right);
				}
			}
		}
		else if (curr_dirct == direction::right) {//未按下按键，继续向当前方向爬行
			if (snack[snack.size() - 1].second == zone_size - 1 )//到边界
				flag = false;
			else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second + 1] == '@')//未到但咬到自己
				flag = false;
			else //向该方向继续前进
				climb(direction::right);
		}
		else if (curr_dirct == direction::up) {//继续向上行走
			if (snack[snack.size() - 1].first == 0 )
				flag = false;
			else if (body[snack[snack.size() - 1].first - 1][snack[snack.size() - 1].second] == '@')
				flag = false;
			else 
				climb(direction::up);
		}
		else if (curr_dirct == direction::down) {//继续向下行走
			if (snack[snack.size() - 1].first == zone_size - 1)
				flag = false;
			else if (body[snack[snack.size() - 1].first + 1][snack[snack.size() - 1].second] == '@')
				flag = false;
			else 
				climb(direction::down);
		}
		else if (curr_dirct == direction::left) {//继续向左行走
			if (snack[snack.size() - 1].second == 0)
				flag = false;
			else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second - 1] == '@')
				flag = false;
			else 
				climb(direction::left);
		}
		system("cls");
		for (size_t i = 0; i < zone_size; ++i) {
			for (size_t j = 0; j < zone_size; ++j)
				cout << body[i][j] << ' ';
			cout << endl;
		}
		Sleep(level);
	}
	system("pause");
}
