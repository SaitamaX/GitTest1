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
deque<pair<int, int>> snack;//�������������ÿ������λ��
size_t level;//�����Ѷ�
int x, y;//ʳ��Ķ�ά����


int a = 10;

void srand_food() {//������ʳ���λ��
	bool flag_srand = true;
	x = rand() % (zone_size - 1) + 0;
	y = rand() % (zone_size - 1) + 0;
	while (flag_srand) {//��֤����������Ķ�ά���겻�������������غ�
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
	if (body[x_offset][y_offset] == '*') {//������ǡ�óԵ�ʳ��
		body[x_offset][y_offset] = '@';
		snack.push_back(make_pair(x_offset, y_offset));
		body[snack[0].first][snack[0].second] = ' ';
		snack.pop_front();
		snack.push_back(make_pair(x_offset, y_offset));
		body[snack[snack.size() - 1].first][snack[snack.size() - 1].second] = '@';
		srand_food();
	}
	else {//������
		snack.push_back(make_pair(x_offset, y_offset));
		body[snack[0].first][snack[0].second] = ' ';
		snack.pop_front();
		body[snack[snack.size() - 1].first][snack[snack.size() - 1].second] = '@';
	}
}

int main()
{
	bool flag = true;//������ѭ����־
	int ch,ch1 = 0;//ch��ȡ������Ϣ,ch1�����Ѷ��ж�
	/************************************����������************************************/
	while (flag) {
		cout << "****************************************Snaker********************************************" << endl;
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
	for (size_t i = 0; i < zone_size; ++i) {
		for (size_t j = 0; j < zone_size; ++j)
			cout << body[i][j] << ' ';
		cout << endl;
	}
	/**********************************************************************************/
	/************************************��Ϸ������************************************/
	for (size_t i = 0; i < 4; i++)//��ʼ��������Ϊ4
		snack.push_back(make_pair(0, i));
	int curr_dirct = direction::right;//�ߵĳ�ʼ������
	srand((unsigned)time(NULL));
	x = rand() % (zone_size-1) + 0,
	y = rand() % (zone_size-1) + 0;//�����ʼ��ʳ��λ��
	body[x][y] = '*';
	while (flag) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 119) {//'w'��
				if (snack[snack.size() - 1].first == 0)//�Ϸ��ѵ��߽�
					flag = false;
				else if (curr_dirct == direction::down)//���޷���ǰ������෴�����ߣ�������Ч
					continue;
				else if (body[snack[snack.size() - 1].first - 1][snack[snack.size() - 1].second] == '@')//�������߻�ҧ���Լ�
					flag = false;
				else {//������
					curr_dirct = direction::up;
					climb(direction::up);
				}
			}
			else if (ch == 97) {//'a'��
				if (snack[snack.size() - 1].second == 0)
					flag = false;
				else if (curr_dirct == direction::right)//���޷���ǰ������෴�����ߣ�������Ч
					continue; 
				else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second - 1] == '@')
					flag = false;
				else {
					curr_dirct = direction::left;
					climb(direction::left);
				}
			}
			else if (ch == 115) {//'s'��
				if (snack[snack.size() - 1].first == zone_size - 1)
					flag = false;
				else if (curr_dirct == direction::up)//���޷���ǰ������෴�����ߣ�������Ч
					continue; 
				else if (body[snack[snack.size() - 1].first + 1][snack[snack.size() - 1].second] == '@')
					flag = false;
				else {
					curr_dirct = direction::down;
					climb(direction::down);
				}
			}
			else if (ch == 100) {//'d'��
				if (snack[snack.size() - 1].first == zone_size - 1)
					flag = false;
				else if (curr_dirct == direction::left)//���޷���ǰ������෴�����ߣ�������Ч
					continue; 
				else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second + 1] == '@')
					flag = false;
				else {
					curr_dirct = direction::right;
					climb(direction::right);
				}
			}
		}
		else if (curr_dirct == direction::right) {//δ���°�����������ǰ��������
			if (snack[snack.size() - 1].second == zone_size - 1 )//���߽�
				flag = false;
			else if (body[snack[snack.size() - 1].first][snack[snack.size() - 1].second + 1] == '@')//δ����ҧ���Լ�
				flag = false;
			else //��÷������ǰ��
				climb(direction::right);
		}
		else if (curr_dirct == direction::up) {//������������
			if (snack[snack.size() - 1].first == 0 )
				flag = false;
			else if (body[snack[snack.size() - 1].first - 1][snack[snack.size() - 1].second] == '@')
				flag = false;
			else 
				climb(direction::up);
		}
		else if (curr_dirct == direction::down) {//������������
			if (snack[snack.size() - 1].first == zone_size - 1)
				flag = false;
			else if (body[snack[snack.size() - 1].first + 1][snack[snack.size() - 1].second] == '@')
				flag = false;
			else 
				climb(direction::down);
		}
		else if (curr_dirct == direction::left) {//������������
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
