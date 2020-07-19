#include "snake.h"
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

void Position(int x, int y)
{
    //调整光标位置
    COORD position  = {x ,y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, position);
    
    //隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo = {1, false};
	SetConsoleCursorInfo(output, &cursorInfo);
}

void SpeedUp()
{
    if (sleepTime > 50)
    {
        sleepTime = sleepTime - 50;
        add += 1;
        //消除“已达到最小速度”
        Position(Width + 5, Height / 3);
        printf("                         ");
    }
    else
    {
        Position(Width + 5, Height / 3);
        printf("已达到最大速度。");
    }
}

void SpeedDown()
{
    if (sleepTime < 500)
    {
        sleepTime = sleepTime + 50;
        add -= 1;
        //消除“已达到最大速度”
        Position(Width + 5, Height / 3 + 1);
        printf("                         ");
    }
    else
    {
        Position(Width + 5, Height / 3 + 1);
        printf("已达到最小速度。");
    }
}

void Pause()
{
    clock_t t1 = clock();
    
    Position(Width + 5, Height / 3 + 2);
    printf("正在暂停中。");

    while(1)
    {
        if(_getch() == 32)
            break;
    }
    
    //记录总暂停时间
    clock_t t2 = clock();             
    t0 += t2 - t1;

    //消除“正在暂停中”
    Position(Width + 5, Height / 3 + 2);
    printf("                       ");
}

bool HitWall()
{
    if (head->x < 2 || head->x >= Width || head->y < 1 || head->y >= Height)
        return true;
    else
        return false;

}

bool BiteSelf()
{
    SnakePtr temp = head->next;
    while (temp != NULL)
    {
        if (temp->x == head->x && temp->y == head->y)
            return true;
        else
            temp = temp->next;
    }
        return false;
}

bool EatFood()
{
    if (head->x == food->x && head->y == food->y)
        return true;
    else
        return false;
}