#include "snake.h"

void Snake::start()//старт игры
{
	std::thread p_t_b(press_the_button);//в отдельном потоке фиксируется нажатие кнопок
	int delay = 1000;
	print_map();
	while (!drive_snake.pos_x && !drive_snake.pos_y);//ждем начала движения
	while (!stop_snake)
	{
		print_map();
		std::this_thread::sleep_for(std::chrono::milliseconds(delay--));
		if (apple.size() < 3)add_apple();
		if (snake_length > 20)
		{
			stop_snake = true;
			std::cout << "\nПОЗДРАВЛЯЮ!!!\nВы выиграли, змея отелась!!!\n";
			system("pause");
			return;
		}
		snake_to_drive();

	}

	stop_snake = true;
	if (p_t_b.joinable()) p_t_b.join();
}




void Snake::press_the_button()//отработка нажатия клавиши
{
	char button;
	while (!stop_snake)
	{
		if (std::cin)
		{
			button = _getch();
			if (button == 72)
			{
				if ((snake_head->pos_y - snake_head->child->pos_y) == 1) continue;
				set_drive_snake(0, -1);
			}
			if (button == 80) 
			{
				if ((snake_head->pos_y - snake_head->child->pos_y) == -1) continue;
				set_drive_snake(0, 1);
			}
			if (button == 75) 
			{
				if ((snake_head->pos_x - snake_head->child->pos_x) == 1) continue;
				set_drive_snake(-1, 0);
			}
			if (button == 77)
			{
				if ((snake_head->pos_x - snake_head->child->pos_x) == -1) continue;
				set_drive_snake(1, 0);
			}

			if (button == '0') stop_snake = true;;
		}
	}
}

void Snake::set_drive_snake(int x, int y)//изменение направления движения змеи
{
	mutex.lock();
	drive_snake.pos_x = x;
	drive_snake.pos_y = y;
	mutex.unlock();
}

void Snake::add_apple()//добавление яблока
{
	int x, y;
	while (true)
	{
		x = rand() % 50;
		y = rand() % 50;
		if (!snake_map[x][y])
		{
			snake_map[x][y] = 9;
			pos add(x, y);
			apple.push_back(add);
			return;
		}
	}
}

void Snake::del_apple(int x, int y)//удаление яблока по позиции
{
	for (auto it = apple.begin(); it != apple.end(); it++)
	{
		if (it->pos_x == x && it->pos_y == y)
		{
			apple.erase(it);
			return;
		}
	}
}

void Snake::print_map()//печать карты
{
	system("cls");
	std::cout << "O++++++++++++++++++++++++++++++++++++++++++++++++++O" << std::endl;
	for (int i = 0; i < 50; ++i)
	{
		std::cout << "+";
		for (int j = 0; j < 50; ++j)
		{
			if (snake_map[i][j] == 0) std::cout << " ";
			if (snake_map[i][j] == 1) std::cout << "0";
			if (snake_map[i][j] == 2) std::cout << "*";
			if (snake_map[i][j] == 9) std::cout << "@";
		}
		std::cout << "+\n";
	}
}

void Snake::snake_to_drive()
{
	int p_x = snake_head->pos_x + drive_snake.pos_x;
	int p_y = snake_head->pos_y + drive_snake.pos_y;
	if (snake_head->pos_x + drive_snake.pos_x < 0 || snake_head->pos_x + drive_snake.pos_x >= 50 || snake_head->pos_y + drive_snake.pos_y < 0 || snake_head->pos_y + drive_snake.pos_y >= 50)
	{
		stop_snake = true;
		std::cout << "\nВы проиграли, змея уткнулась в колючку!!!\n";
		system("pause");
		return;
	}
	if (snake_map[p_x][p_y] == 2)
	{
		stop_snake = true;
		std::cout << "\nВы проиграли, змея съела себя!!!\n";
		system("pause");
		return;
	}
	if (snake_map[p_x][p_y] == 9)
	{
		snake_map[snake_head->pos_x][snake_head->pos_y] = 2;
		snake_map[p_x][p_y] = 1;
		pos* newHead = new pos(p_x, p_y);
		newHead->child = snake_head;
		snake_head->parent = newHead;
		snake_head = newHead;
		snake_length++;
		del_apple(p_x, p_y);
		return;
	}
	if (snake_map[p_x][p_y] == 0)
	{
		snake_map[snake_head->pos_x][snake_head->pos_y] = 2;
		snake_map[p_x][p_y] = 1;
		pos* newHead = new pos(p_x, p_y);
		newHead->child = snake_head;
		snake_head->parent = newHead;
		snake_head = newHead;
		pos* del_head = snake_tail;
		snake_tail = del_head->parent;
		delete del_


		return;
	}

}

