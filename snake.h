#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<windows.h>
using namespace std;


bool IsEque(COORD a, COORD b);

/*The wall is the boundary of the game, and random stones appear in the middle of the game boundary*/
class wall
{
public:
	wall();
	~wall();
	/*stone will random created in the edge*/
	/*
	public:
	COORD    Random_Stone();*/													//return stone's pos ande stone's length and width
	/*wall's properties*/
public:
	vector<COORD> pos;
};

/*Snake is the dominant body of a player*/
class Snake
{
public:
	Snake();
	Snake(int speed = 5);
	~Snake();
/*Snake's action*/
public:
	void Move(char *direction, bool *eating);													 //return the snake's pos and snake's speed 
	bool Eating(COORD Food_Pos);									 //return snake's option to be changed
	bool IsDead(wall &e);
/*Snake's properties*/
public:
	int length;
	int speed;
	deque<COORD> pos;
};



/*Food can make snakes grow or acquire other abilities */
class Food
{
public:
	Food();
	Food& operator =(Food &f);
	void Re_Rand();
	//Food& operator()();//我才知道好像自带这个重载
	~Food();
/*Food's properties*/
public:
	COORD pos;
};
/*Food_Speed will lets the snake speed up*/
//class Food_Speed : public Food
//{
//public:
//	Food_Speed();
//	~Food_Speed();
//private:
//	int Add_Speed;
//};

/*Game Initialization*/
int Game_Init();

/*Game Menu*/
int Game_Menu(int option);

/*Game Runing*/

int Game_Runing(int Hard_Level = 0);


#endif
