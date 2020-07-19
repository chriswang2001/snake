#include "snake.h"
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int sleepTime = 0, bestScore = 0;
int add = 0, score = 0, flag = 0;
clock_t t0 = 0;
char name[100];
SnakePtr head;
FoodPtr food;
Status status;

void InitGame()
{
    score = 0;   //重置得分
    t0 = 0; //重置暂停时间
    fflush(stdin); //清空输入缓存
    system("color F3"); //调整背景和字体颜色（白色 湖蓝）
    Position(Width / 2 + 24, Height / 4);
    printf("贪吃蛇大作战");

    if(flag == 0) //判断是否更换用户
    {
        Position(Width / 2 + 12, Height / 3);
        printf("请输入用户名：");
        gets(name);
    }

    Position(Width / 2 + 12, Height / 3 + 5);
    printf("请选择难度模式 1:简单 2:普通 3:困难");

    int difficultyLevel = _getch(); //用getch函数可以不回显，体验更好
    
    switch(difficultyLevel)
    {
        case 49://数字键ascii码
            sleepTime = 450; add = 2; break;
        case 50: 
            sleepTime = 300; add = 5; break;
        case 51:
            sleepTime = 100; add = 9; break;
        default:
            EndGame(0);
    }

    GameEntry();
}

void GameEntry()
{
    fflush(stdin);
    system("cls"); //清屏
    InitMap();
    InitSnake();
    CreateFood();
    RunGame();
}

void InitMap()
{
    system("color F3");
    
    for (int i = 0; i <= Width; i += 2) //打印上下边框
    {
        Position(i, 0);
        printf("■");
        Position(i, Height);
        printf("■");
    }

    for (int i = 1; i < Height; i ++) //打印左右边框
    {
        Position(0, i);
        printf("■");
        Position(Width, i);
        printf("■");
    }

    //游戏界面Ui设计
    Position(Width + 5, 3);
    printf("玩家：%s", name);

    Position(Width + 5, Height / 4 - 1);
    printf("最高得分：%5d ", bestScore);
    Position(Width + 5, Height / 4 );
    printf("当前得分：%5d ", score);
    Position(Width + 5, Height / 4 + 1);
    printf("每个食物得分：%d", add);

    Position(Width + 5 , Height / 2 + 1);
    printf("操作说明：");
    Position(Width + 5 , Height / 2 + 2);
    printf("用 ↑ ↓ ← → 控制蛇的移动   ");
    printf("F1 为加速，F2 为减速");
    Position(Width + 5 , Height / 2 + 3);
    printf("空格键 为暂停/取消暂停        ");
    printf("ESC 为退出游戏");

    Position(Width + 5,  Height / 2 + 5);
    printf("小提示：");
    Position(Width + 5,  Height / 2 + 6);
    printf("不同难度模式的初始速度不同，更高的速度将能得到更高的分数。");

    Position(Width + 5,  Height / 2 + 9);
    printf("游戏时间：0 s");

    Position(Width + 5, Height - 2);
    printf("Copyright 2020 by Chris Wang. All Rights Reserved.\n");
}

void InitSnake()
{
    head = (SnakePtr)malloc(sizeof(Snake));
    if(head == NULL)
        EndGame(-1);
    
    head->x = Width / 2;
    //保证蛇头横坐标为偶数（一个□占据两个宽度，一个高度-原因在于控制台单位高度是单位宽度的两倍，便于判断吃食物和撞墙）
    if(head->x % 2 != 0)
        head->x += 1;
    head->y = Height / 2;
    head->next = NULL;

    //初始蛇身长度为3
    SnakePtr tail ,temp = head;
    for (int i = 1; i < 3; i++) 
    {
        tail = (SnakePtr)malloc(sizeof(Snake));
        if(tail == NULL)
            EndGame(-1);
        else
            temp->next = tail;
        tail->x = head->x - 2 * i; //蛇身两个宽度
        tail->y = head->y;
        tail->next = NULL; //一定要把蛇尾指向NULL，方便后续遍历操作
        temp = tail;
    }

    temp = head;

    while (temp != NULL) 
    {
        Position(temp->x, temp->y);
        printf("□");
        
        temp = temp->next;
    }
    
}

void CreateFood()
{
    food = (FoodPtr)malloc(sizeof(Food));
    
    if(food == NULL)
        EndGame(-1);

    //避免在墙外产生食物，且横坐标必须为偶数（因为蛇头坐标是偶数）
    while(1)
    {
        food->x = (rand() % (Width - 3)) + 2;
        if(food->x % 2 == 0)
            break;
    }
    
    food->y = (rand() % (Height - 1)) + 1;

    //避免产生的食物在蛇身上
    SnakePtr temp = head;
    while (temp)
    {
        if (temp->x == food->x && temp->y == food->y)
        {
            free(food);
            CreateFood();
            return ;
        }
        else
            temp = temp->next;
    }

    Position(food->x, food->y);
    printf("$");
}

void RunGame()
{
    //初始状态为向右走
    status = right;
    //获取程序开始运行时的时间
    clock_t t1 = clock();

    while (1)
    {
        fflush(stdin);
        if(_kbhit())//khbit判断是否有按键操作，但不读取
        {
            int ch1 = _getch();
            if (ch1 == 32)
                Pause();
            else if (ch1 == 27)
                EndGame(3);
            //读取功能键时，需用两次getch，第一次返回0/224，第二次返回对应键值
            else if(ch1 == 224 || ch1 == 0)
            {
            int ch2 = _getch();
            if (ch1 == 224 && ch2 == 72 && status != down)
                status = up;
            else if (ch1 == 224 && ch2 == 80 && status != up)
                status = down;
            else if (ch1 == 224 && ch2 == 75 && status != right)
                status = left;
            else if (ch1 == 224 && ch2 == 77 && status != left)
                status = right;
            else if (ch1 == 0 && ch2 == 59)
                SpeedUp();
            else if (ch1 == 0 && ch2 == 60)
                SpeedDown();
            }
        }

        //控制蛇的移动速度
        Sleep(sleepTime);
        SnakeMove();
        
        //更新最高分数
        if(score > bestScore)
            bestScore = score;
        
        clock_t t2 = clock();             
        int t = (t2 - t1 - t0) / CLOCKS_PER_SEC;
        Position(Width + 15,  Height / 2 + 9);
        printf("%d s", t); //计时器

        Position(Width + 15, Height / 4 - 1);
        printf("%5d", bestScore);
        Position(Width + 15, Height / 4 );
        printf("%5d", score);
        Position(Width + 19, Height / 4 + 1);
        printf("%d", add);
    }
}

void SnakeMove()
{
    SnakePtr nexthead = (SnakePtr)malloc(sizeof(Snake));

    //注意蛇的一个结构体横坐标占两格
    switch (status)
    {
    case up:
        nexthead->x = head->x;
        nexthead->y = head->y - 1;
        break;
    case down:
        nexthead->x = head->x;
        nexthead->y = head->y + 1;
        break;
    case left:
        nexthead->x = head->x - 2;
        nexthead->y = head->y;
        break;
    case right:
        nexthead->x = head->x + 2;
        nexthead->y = head->y;
        break;
    default:
        EndGame(-1);
    }
    
    nexthead->next = head;
    head = nexthead;
    
    if(HitWall())
        EndGame(1);
    else if(BiteSelf())
        EndGame(2);
    else if(EatFood())
    {
        Position(head->x, head->y); 
        printf("□"); 
        score = score + add;
        CreateFood();
    }
    else
    {
        SnakePtr temp = head;
        while (temp->next->next != NULL) 
            temp = temp->next;
        Position(head->x, head->y); 
        printf("□");    
        Position(temp->next->x, temp->next->y);
        //注意是两个空格
        printf("  ");
        free(temp->next);            
        temp->next = NULL;
    }
}

void EndGame(int status)
{
    system("cls");
    fflush(stdin);

    Position(Width / 4, Height / 3);
    switch(status)
    {
        case 0:
            printf("请选择正确的难度模式。"); break;
        case 1:
            printf("对不起，您撞到墙了。游戏结束。"); break;
        case 2:
            printf("对不起，您咬到自己了。游戏结束。"); break;
        case 3:
            printf("您主动结束了游戏。"); break;
        default:
            printf("发生未知错误"); break;
    }
    
    Position(Width / 4, Height / 3 + 3);
    printf("玩家：%s", name);
    Position(Width / 4, Height / 3 + 4);
    printf("最高得分：%d\n", bestScore);
    Position(Width / 4, Height / 3 + 5);
    printf("本次得分：%d\n", score);
    Position(Width / 4, Height / 3 + 7);
    printf("q: 退出游戏 r:重新开始 e:更换玩家");
    
    int ch;
    loop: ch = _getch();
    switch(ch)
    {
        case 'q': case 'Q':
            exit(0); break;
        case 'r': case 'R':
            flag = 1; system("cls"); InitGame(); break;
        case 'e': case 'E':
            flag = 0; bestScore = 0; system("cls"); InitGame(); break;
        default:
            goto loop;
    }
}
