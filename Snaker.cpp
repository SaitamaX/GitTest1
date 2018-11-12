// Snaker.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Snaker.h"
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <deque>
#define zone_size 25

// w,a,s,d,k��Ӧ�ļ�ֵ�ֱ�Ϊ119,97,115,100,107
using namespace std;

char body[zone_size][zone_size];//��Ϸ���̽���
enum direction {up, down, left, right};//�ֱ����ڵ�ǰǰ��������ж�
deque<pair<int, int>> snake;//�������������ÿ������λ��
size_t level;//�����Ѷ�
int x, y;//ʳ��Ķ�ά����

void srand_food() {//������ʳ���λ��
	bool flag_srand = true;
	x = rand() % (zone_size - 1) + 0;
	y = rand() % (zone_size - 1) + 0;
	while (flag_srand) {//��֤����������Ķ�ά���겻�������������غ�
		flag_srand = false;
		for (size_t i = 0; i < snake.size(); i++) {
			if (snake[i].first == x && snake[i].second == y) {
				x = rand() % (zone_size - 1) + 0;
				y = rand() % (zone_size - 1) + 0;
				flag_srand = true;
			}
		}
	}
	body[x][y] = '*';
}

void show_result() {
	for (size_t i = 0; i < zone_size; ++i) {
		for (size_t j = 0; j < zone_size; ++j)
			if (j != zone_size - 1)
				cout << body[i][j] << ' ';
			else
				cout << body[i][j];
		cout << '#';
		cout << endl;
	}
	cout << " # # # # # # # # # # # # # # # # # # # # # # # # #";
}

void climb(int s_direction) {
	int x_offset, y_offset;
	switch (s_direction) {
	case direction::up:
		x_offset = snake[snake.size() - 1].first - 1;
		y_offset = snake[snake.size() - 1].second; 
		break;
	case direction::down:
		x_offset = snake[snake.size() - 1].first + 1;
		y_offset = snake[snake.size() - 1].second;
		break;
	case direction::left:
		x_offset = snake[snake.size() - 1].first;
		y_offset = snake[snake.size() - 1].second - 1;
		break;
	case direction::right:
		x_offset = snake[snake.size() - 1].first;
		y_offset = snake[snake.size() - 1].second + 1;
	}
	if (body[x_offset][y_offset] == '*') {//��÷�����ǡ�óԵ�ʳ��
		body[x_offset][y_offset] = '@';
		snake.push_back(make_pair(x_offset, y_offset));
		body[snake[0].first][snake[0].second] = ' ';
		snake.pop_front();
		snake.push_back(make_pair(x_offset, y_offset));
		body[snake[snake.size() - 1].first][snake[snake.size() - 1].second] = '@';
		srand_food();
	}
	else {//������÷�����
		snake.push_back(make_pair(x_offset, y_offset));
		body[snake[0].first][snake[0].second] = ' ';
		snake.pop_front();
		body[snake[snake.size() - 1].first][snake[snake.size() - 1].second] = '@';
	}
}

int main()
{
	bool flag = true;//������ѭ����־
	int ch,ch1 = 0;//ch��ȡ������Ϣ,ch1�����Ѷ��ж�
	/************************************����������************************************/
	while (flag) {
		cout << "*****************************************Snaker*******************************************" << endl;
		cout << endl;
		cout << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		cout << "                             w �� s ѡ���Ѷȣ�k ��ʼ��Ϸ" << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		cout << endl;
		if (ch1 == 0) {
			cout << "                   >> 1.��                           �򵥵��Ѷ�:" << endl;
			cout << endl;
			cout << "                      2.����                              �ߵ��ƶ��ٶȽ�����" << endl;
			cout << endl;
			cout << "                      3.���" << endl;
		}
		else if (ch1 == 1) {
			cout << "                      1.��                           ���ѵ��Ѷ�:" << endl;
			cout << endl;
			cout << "                   >> 2.����                              �ߵ��ƶ��ٶȽϿ졣" << endl;
			cout << endl;
			cout << "                      3.���" << endl;
		}
		else {
			cout << "                      1.��                           �����Ѷ�:" << endl;
			cout << endl;
			cout << "                      2.����                              ����۾����ܻ�е�����" << endl;
			cout << endl;
			cout << "                   >> 3.���" << endl;
		}
		cout << endl;
		cout << endl;
		cout << "------------------------------------------------------------------------------------------" << endl;
		cout << "                                    ������: �಩��        " << endl;
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
	flag = true;//���ñ�־��
	//�����ʼ״̬
	for (size_t i = 0; i < zone_size; ++i)
		for (size_t j = 0; j < zone_size; ++j)
				body[i][j] = ' ';
	for (size_t i = 0; i < 4; ++i)
		body[0][i] = '@';
	show_result();
	/**********************************************************************************/
	/************************************��Ϸ������************************************/
	for (size_t i = 0; i < 4; i++)//��ʼ��������Ϊ4
		snake.push_back(make_pair(0, i));
	int curr_dirct = direction::right;//�ߵĳ�ʼ������
	srand((unsigned)time(NULL));
	srand_food();
	while (flag) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 119) {//'w'��
				if (snake[snake.size() - 1].first == 0)//�Ϸ��ѵ��߽�
					flag = false;
				else if (curr_dirct == direction::down)//���޷���ǰ������෴�����ߣ�������Ч
					climb(direction::down);
				else if (body[snake[snake.size() - 1].first - 1][snake[snake.size() - 1].second] == '@')//�������߻�ҧ���Լ�
					flag = false;
				else {//������
					curr_dirct = direction::up;
					climb(direction::up);
				}
			}
			else if (ch == 97) {//'a'��
				if (snake[snake.size() - 1].second == 0)
					flag = false;
				else if (curr_dirct == direction::right)//���޷���ǰ������෴�����ߣ�������Ч
					climb(direction::right); 
				else if (body[snake[snake.size() - 1].first][snake[snake.size() - 1].second - 1] == '@')
					flag = false;
				else {
					curr_dirct = direction::left;
					climb(direction::left);
				}
			}
			else if (ch == 115) {//'s'��
				if (snake[snake.size() - 1].first == zone_size - 1)
					flag = false;
				else if (curr_dirct == direction::up)//���޷���ǰ������෴�����ߣ�������Ч
					climb(direction::up); 
				else if (body[snake[snake.size() - 1].first + 1][snake[snake.size() - 1].second] == '@')
					flag = false;
				else {
					curr_dirct = direction::down;
					climb(direction::down);
				}
			}
			else if (ch == 100) {//'d'��
				if (snake[snake.size() - 1].second == zone_size - 1)
					flag = false;
				else if (curr_dirct == direction::left)//���޷���ǰ������෴�����ߣ�������Ч
					climb(direction::left); 
				else if (body[snake[snake.size() - 1].first][snake[snake.size() - 1].second + 1] == '@')
					flag = false;
				else {
					curr_dirct = direction::right;
					climb(direction::right);
				}
			}
		}
		else if (curr_dirct == direction::right) {//δ���°�����������ǰ��������
			if (snake[snake.size() - 1].second == zone_size - 1 )//���߽�
				flag = false;
			else if (body[snake[snake.size() - 1].first][snake[snake.size() - 1].second + 1] == '@')//δ����ҧ���Լ�
				flag = false;
			else //��÷������ǰ��
				climb(direction::right);
		}
		else if (curr_dirct == direction::up) {//������������
			if (snake[snake.size() - 1].first == 0 )
				flag = false;
			else if (body[snake[snake.size() - 1].first - 1][snake[snake.size() - 1].second] == '@')
				flag = false;
			else 
				climb(direction::up);
		}
		else if (curr_dirct == direction::down) {//������������
			if (snake[snake.size() - 1].first == zone_size - 1)
				flag = false;
			else if (body[snake[snake.size() - 1].first + 1][snake[snake.size() - 1].second] == '@')
				flag = false;
			else 
				climb(direction::down);
		}
		else if (curr_dirct == direction::left) {//������������
			if (snake[snake.size() - 1].second == 0)
				flag = false;
			else if (body[snake[snake.size() - 1].first][snake[snake.size() - 1].second - 1] == '@')
				flag = false;
			else 
				climb(direction::left);
		}
		system("cls");
		show_result();
		Sleep(level);
	}
	cout << endl;
	system("pause");
}
