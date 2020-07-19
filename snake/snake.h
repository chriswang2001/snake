#pragma once

#include <stdbool.h>
#include <time.h>

//定义地图宽度和高度
#define Width 48
#define Height 27

//蛇的状态(枚举)
typedef enum
{
    up, down, left, right
} Status;

//蛇身节点(结构体)
typedef struct SNAKE
{
    int x;
    int y;
    struct SNAKE *next;
} Snake, *SnakePtr;

//食物类型(结构体)
typedef struct FOOD
{
    int x;
    int y;
} Food, *FoodPtr;

//声明全部函数//

//开始界面
void InitGame();
//进入游戏
void GameEntry();
//运行游戏
void RunGame();
//初始化地图
void InitMap();
//初始化蛇
void InitSnake();
//创造食物
void CreateFood();
//控制蛇的移动
void SnakeMove();
//结束界面
void EndGame(int status);

//加速
void SpeedUp();
//减速
void SpeedDown();
//暂停
void Pause();
//判断是否撞墙
bool HitWall();
//判断是否咬到自己
bool BiteSelf();
//判断是否吃到食物
bool EatFood();
//控制光标在命令行的位置
void Position(int x, int y); 

//声明全局变量//

//休眠时间（与速度反相关） 最好成绩（实时更新）
extern int sleepTime, bestScore;
//每个食物得分 当前得分 判断是否更改用户标志
extern int add, score, flag;
//记录暂停时间
extern clock_t t0;
//储存用户名
extern char name[100];
//蛇头指针
extern SnakePtr head;
//食物指针
extern FoodPtr food;
//运行状态
extern Status status;
