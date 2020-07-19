#include "snake.h"
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

void Position(int x, int y)
{
    //�������λ��
    COORD position  = {x ,y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, position);
    
    //���ع��
    CONSOLE_CURSOR_INFO cursorInfo = {1, false};
	SetConsoleCursorInfo(output, &cursorInfo);
}

void SpeedUp()
{
    if (sleepTime > 50)
    {
        sleepTime = sleepTime - 50;
        add += 1;
        //�������Ѵﵽ��С�ٶȡ�
        Position(Width + 5, Height / 3);
        printf("                         ");
    }
    else
    {
        Position(Width + 5, Height / 3);
        printf("�Ѵﵽ����ٶȡ�");
    }
}

void SpeedDown()
{
    if (sleepTime < 500)
    {
        sleepTime = sleepTime + 50;
        add -= 1;
        //�������Ѵﵽ����ٶȡ�
        Position(Width + 5, Height / 3 + 1);
        printf("                         ");
    }
    else
    {
        Position(Width + 5, Height / 3 + 1);
        printf("�Ѵﵽ��С�ٶȡ�");
    }
}

void Pause()
{
    clock_t t1 = clock();
    
    Position(Width + 5, Height / 3 + 2);
    printf("������ͣ�С�");

    while(1)
    {
        if(_getch() == 32)
            break;
    }
    
    //��¼����ͣʱ��
    clock_t t2 = clock();             
    t0 += t2 - t1;

    //������������ͣ�С�
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