#include<iostream>
#include<string>
#include<map>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<stdio.h>
#include"windows.h"
#include<WinUser.h>
#include"snake.h"
#include"tool.h"
#include"conio.h"
#include<time.h>
using namespace std;
/*Main interface design*/

/*
贪吃蛇小游戏

>开始游戏<
选择难度
退出游戏

*/

char *Title = "贪吃蛇小游戏";

char *Main_menu[] = { "开始游戏",
					  "选择难度",
					  "退出游戏" };

char *ChooseHard = "难度选择";


char *HardLevel[] = {"Easy",
					 "Normal",
				     "Hard"    };


bool IsEque(COORD a, COORD b)
{
	return (a.X == b.X) && (a.Y == b.Y);
}
int Game_Init()
{

	SHORT tmp_up;
	SHORT tmp_down;
	SHORT tmp_enter;
	int i = 0;
	int keycount = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息  
	CursorInfo.bVisible = false; //隐藏控制台光标  
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态  
	SetWindowSize(40, 40);
	SetColor(5);
	SetCursorPosition(15, 5);
	cout << Title << endl;
	SetCursorPosition(16, 17);
	cout << Main_menu[0] << endl;
	SetCursorPosition(16, 19);
	cout << Main_menu[1] << endl;
	SetCursorPosition(16, 21);
	cout << Main_menu[2] << endl;
	tmp_up = GetKeyState(VK_UP);
	tmp_down = GetKeyState(VK_DOWN);
	tmp_enter = GetKeyState(VK_RETURN);
	while (tmp_enter == GetKeyState(VK_RETURN))
	{
		if (tmp_up != GetKeyState(VK_UP))
		{
			keycount++;
			tmp_up = GetKeyState(VK_UP);
			if (keycount == 2)
			{
				keycount = 0;
				if (i == 0)
				{
					i = 2;
				}
				else
				{
					i--;
				}
			}

		}
		if (tmp_down != GetKeyState(VK_DOWN))
		{
			keycount++;
			tmp_down = GetKeyState(VK_DOWN);
			if (keycount == 2)
			{
				keycount = 0;
				if (i == 2)
				{
					i = 0;
				}
				else
				{
					i++;
				}
			}
		}
		switch (i)
		{
		case 0:
			SetCursorPosition(15, 21);
			cout << " ";
			SetCursorPosition(20, 21);
			cout << " ";
			SetCursorPosition(15, 19);
			cout << " ";
			SetCursorPosition(20, 19);
			cout << " ";
			SetCursorPosition(15, 17);
			cout << ">";
			SetCursorPosition(20, 17);
			cout << "<";
			break;
		case 1:
			SetCursorPosition(15, 21);
			cout << " ";
			SetCursorPosition(20, 21);
			cout << " ";
			SetCursorPosition(15, 19);
			cout << ">";
			SetCursorPosition(20, 19);
			cout << "<";
			SetCursorPosition(15, 17);
			cout << " ";
			SetCursorPosition(20, 17);
			cout << " ";
			break;
		case 2:
			SetCursorPosition(15, 21);
			cout << ">";
			SetCursorPosition(20, 21);
			cout << "<";
			SetCursorPosition(15, 19);
			cout << " ";
			SetCursorPosition(20, 19);
			cout << " ";
			SetCursorPosition(15, 17);
			cout << " ";
			SetCursorPosition(20, 17);
			cout << " ";
			break;
		default:
			break;
		}
	}
	
	return i;
}


Snake::Snake()
{
	COORD a = { 20,20 };
	this->pos.push_back(a);
	this->pos.push_back(a);
	this->pos.push_back(a);
	this->pos.push_back(a);
	this->pos.push_back(a);
	this->length = 5;
	this->speed = 5;
}
Snake::Snake(int speed)
{
	this->length = 5;
	this->speed = speed;
	COORD a = { 20,20 };
	for (int i = 0; i < length; i++)
	{
		this->pos.push_back(a);
	}
}

void Snake::Move(char *direction,bool *eating)
{
	COORD a;
	char buf;
	bool FLGE = 0;
	int tmp[4];
	SetColor(7);
	tmp[0] = GetAsyncKeyState(VK_UP);
	tmp[1] = GetAsyncKeyState(VK_LEFT);
	tmp[2] = GetAsyncKeyState(VK_DOWN);
	tmp[3] = GetAsyncKeyState(VK_RIGHT);
	if (GetAsyncKeyState(VK_UP) != tmp[0])
	{
		buf = 'U';
		tmp[0] = GetAsyncKeyState(VK_UP);
		FLGE = 1;
	}
	if (GetAsyncKeyState(VK_DOWN) != tmp[2])
	{
		buf = 'D';
		tmp[2] = GetAsyncKeyState(VK_DOWN);
		FLGE = 1;
	}
	if (GetAsyncKeyState(VK_LEFT) != tmp[1])
	{
		buf = 'L';
		tmp[1] = GetAsyncKeyState(VK_LEFT);
		FLGE = 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) != tmp[3])
	{
		buf = 'R';
		tmp[3] = GetAsyncKeyState(VK_RIGHT);
		FLGE = 1;
	}
	if (FLGE)
	{
		switch (*direction)
		{
		case 'U':
			if (buf != 'D')
			{
				*direction = buf;
				FLGE = 0;
			}
			break;
		case 'D':
			if (buf != 'U')
			{
				*direction = buf;
				FLGE = 0;
			}
			break;
		case 'L':
			if (buf != 'R')
			{
				*direction = buf;
				FLGE = 0;
			}
			break;
		case 'R':
			if (buf != 'L')
			{
				*direction = buf;
				FLGE = 0;
			}
			break;
		default:
			break;
		}
	}
	switch (*direction)
	{
	case 'U':
		a.X = pos[0].X;
		a.Y = pos[0].Y - 1;
		pos.push_front(a);
		SetCursorPosition(this->pos[0].X, this->pos[0].Y);
		cout << "■";
		SetCursorPosition(this->pos[pos.size() - 1].X, this->pos[pos.size() - 1].Y);
		if (!*eating)
		{
			cout << " ";
			pos.pop_back();
		}
		else
		{
			cout << "■";
			*eating = 0;
		}
		break;
	case 'L':
		a.X = pos[0].X - 1;
		a.Y = pos[0].Y;
		pos.push_front(a);
		SetCursorPosition(this->pos[0].X, this->pos[0].Y);
		cout << "■";
		SetCursorPosition(this->pos[pos.size()-1].X, this->pos[pos.size()-1].Y);
		if (!(*eating))
		{
			cout << " ";
			pos.pop_back();
		}
		else
		{
			cout << "■";
			*eating = 0;
		}
		
		break;
	case 'D':
		a.X = pos[0].X;
		a.Y = pos[0].Y + 1;
		pos.push_front(a);
		SetCursorPosition(this->pos[0].X, this->pos[0].Y);
		cout << "■";
		SetCursorPosition(this->pos[pos.size()-1].X, this->pos[pos.size()-1].Y);
		if (!*eating)
		{
			cout << " ";
			pos.pop_back();
		}
		else
		{
			cout << "■";
			*eating = 0;
		}
		
		break;
	case 'R':
		a.X = pos[0].X + 1;
		a.Y = pos[0].Y;
		pos.push_front(a);
		SetCursorPosition(this->pos[0].X, this->pos[0].Y);
		cout << "■";
		SetCursorPosition(this->pos[pos.size() - 1].X, this->pos[pos.size() - 1].Y);
		if (!*eating)
		{
			cout << " ";
			pos.pop_back();
		}
		else
		{
			cout << "■";
			*eating = 0;
		}
		
		break;
	}
}

bool Snake::Eating(COORD Food_Pos)
{
	COORD tmp;
	if (IsEque(this->pos[0], Food_Pos))
	{
		tmp.X = this->pos[pos.size() - 1].X; 
		tmp.Y = this->pos[pos.size()-1].Y;
		this->pos.push_back(tmp);
		this->length =this->length+ 1;
		return true;
	}
	else
	{
		return false;
	}
}



bool Snake::IsDead(wall &e)
{
	deque<COORD>::iterator it_d;
	vector<COORD>::iterator it_v;
	it_d = adjacent_find(this->pos.begin(), this->pos.end(),IsEque);
	if (it_d != this->pos.end())
	{
		return false;
	}
	else 
	{
		for (it_v = e.pos.begin(); it_v != e.pos.end(); it_v++)
		{
			if (IsEque(this->pos[0], *it_v))
			{
				return true;
			}
		}
		for (int i = 1; i < this->pos.size(); i++)
		{
			if (IsEque(this->pos[0], this->pos[i]))
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

Snake::~Snake()
{
	this->length = 0;
	this->pos.clear();
	this->speed = 0;
}

wall::wall()
{
	int x, y;
	COORD tmp;
	for (x = 0; x < 40; x++)
	{
		if (x == 0 || x == 39)
		{
			for ( y = 0; y < 40; y++)
			{
				tmp.X = x;
				tmp.Y = y;
				this->pos.push_back(tmp);
				SetCursorPosition(x, y);
				cout << "▲";
			}
		}
		else
		{
			tmp.X = x;
			tmp.Y = 0;
			this->pos.push_back(tmp);
			SetCursorPosition(x, 0);
			cout << "▲";
			tmp.X = x;
			tmp.Y = 39;
			this->pos.push_back(tmp);
			SetCursorPosition(x, 39);
			cout << "▲";
		}
		
	}
	
}

wall::~wall()
{
	this->pos.clear();
}

Food::Food()
{
	int x;
	int y;
	COORD tmp;
	rerand:
	x = rand() % 38;
	y = rand() % 38;
	if (x != 0 && y != 0)
	{
		tmp.X = x;
		tmp.Y = y;
		this->pos = tmp;
		SetCursorPosition(x, y);
		SetColor(3);
		cout << "●";
	}
	else
	{
		goto rerand;
	}
}
Food& Food::operator =(Food &f)
{
	this->pos.X = 0;
	this->pos.Y = 0;
	this->pos = { f.pos.X, f.pos.Y };
	return *this;
}
void Food::Re_Rand()
{
	Food tmp;
	this->pos.X = tmp.pos.X;
	this->pos.Y = tmp.pos.Y;
}
//Food& Food::operator()()
//{
//	Food tmp;
//	return tmp;
//}
Food::~Food()
{
	this->pos = { 0,0 };
}

int Game_Runing(int Hard_Level)
{
	int rate;
	bool flag_eat;
	wall edge;
	char directiion;
	Snake player = 5;
	Food f;
	switch (Hard_Level)
	{
	case 0:
		rate = 150;
		break;
	case 1:
		rate = 125;
		break;
	case 2:
		rate = 120;
		break;
	default:
		cout << "程序难度参数错误" << endl;
		return 0;
	}
	directiion = 'D';
	
	while (!(player.IsDead(edge)))
	{
		
		player.Move(&directiion, &flag_eat);
		flag_eat = player.Eating(f.pos);
		if (flag_eat)
		{
			f.Re_Rand();
		}
		Sleep(rate);
	}
	system("cls");
	cout << "十分遗憾，您输了！" << endl;
	return 0;
}

int Game_Menu(int option)
{
	SHORT tmp_up;
	SHORT tmp_down;
	SHORT tmp_enter;
	int keycount = 0;
	int i;
	system("cls");
	i = 0;
	switch (option)
	{
	case 0:
		break;
	case 1:
		SetCursorPosition(15, 5);
		cout << ChooseHard << endl;
		SetCursorPosition(16, 17);
		cout << HardLevel[0] << endl;
		SetCursorPosition(16, 19);
		cout << HardLevel[1] << endl;
		SetCursorPosition(16, 21);
		cout << HardLevel[2] << endl;
		tmp_up = GetKeyState(VK_UP);
		tmp_down = GetKeyState(VK_DOWN);
		tmp_enter = GetKeyState(VK_RETURN);
		while (tmp_enter == GetKeyState(VK_RETURN))
		{
			if (tmp_up != GetKeyState(VK_UP))
			{
				keycount++;
				tmp_up = GetKeyState(VK_UP);
				if (keycount == 2)
				{
					keycount = 0;
					if (i == 0)
					{
						i = 2;
					}
					else
					{
						i--;
					}
				}

			}
			if (tmp_down != GetKeyState(VK_DOWN))
			{
				keycount++;
				tmp_down = GetKeyState(VK_DOWN);
				if (keycount == 2)
				{
					keycount = 0;
					if (i == 2)
					{
						i = 0;
					}
					else
					{
						i++;
					}
				}
			}
			switch (i)
			{
			case 0:
				SetCursorPosition(15, 21);
				cout << " ";
				SetCursorPosition(20, 21);
				cout << " ";
				SetCursorPosition(15, 19);
				cout << " ";
				SetCursorPosition(20, 19);
				cout << " ";
				SetCursorPosition(15, 17);
				cout << ">";
				SetCursorPosition(20, 17);
				cout << "<";
				break;
			case 1:
				SetCursorPosition(15, 21);
				cout << " ";
				SetCursorPosition(20, 21);
				cout << " ";
				SetCursorPosition(15, 19);
				cout << ">";
				SetCursorPosition(20, 19);
				cout << "<";
				SetCursorPosition(15, 17);
				cout << " ";
				SetCursorPosition(20, 17);
				cout << " ";
				break;
			case 2:
				SetCursorPosition(15, 21);
				cout << ">";
				SetCursorPosition(20, 21);
				cout << "<";
				SetCursorPosition(15, 19);
				cout << " ";
				SetCursorPosition(20, 19);
				cout << " ";
				SetCursorPosition(15, 17);
				cout << " ";
				SetCursorPosition(20, 17);
				cout << " ";
				break;
			default:
				break;
			}
		}
		break;
	case 2:
		cout << "再见！" << endl;
		system("pause");
		exit(0);
		break;
	default:
		cout << "程序参数错误，请重试！" << endl;
		system("pause");
		break;
	}
	return i;
}

