#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include <conio.h>
#include <mutex>
#include <Windows.h>

struct pos
{
	int pos_x;
	int pos_y;
	pos* child{ nullptr };
	pos* parent{ nullptr };
	pos(int x, int y) :pos_x(x), pos_y(y) {};
};

class Snake
{
	pos* snake_head;
	pos* snake_tail;
	int snake_length = 3;
	std::vector <pos> apple;
	int snake_map[50][50]{ 0 };
	pos drive_snake{ 0, 0 };
	bool stop_snake{ false };
	std::mutex mutex;

	void press_the_button();
	void set_drive_snake(int, int);
	void add_apple();
	void del_apple(int, int);
	void print_map();
	void snake_to_drive();
	
public:
	Snake()
	{
		pos* p_one = new pos(25, 25);
		snake_head = p_one;
		pos* p_two = new pos(26, 25);
		p_two->parent = p_one;
		p_one->child = p_two;
		pos* p_three = new pos(27, 25);
		p_three->parent = p_two;
		p_two->child = snake_tail = p_three;
		snake_map[25][25] = 1;
		snake_map[26][25] = snake_map[27][25] = 2;
		add_apple();
		add_apple();
		add_apple();
	}
	~Snake()
	{
		pos* one = snake_head;
		pos* two = snake_head->child;
		do
		{
			delete one;
			one = two;
			two = one->child;
		} while (two);
		delete one;
	}
	void start();
};