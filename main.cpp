#include "snake.h""

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    Snake s;
    s.start();
    return 0;
}
