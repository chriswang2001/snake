#pragma once

#include <stdbool.h>
#include <time.h>

//�����ͼ��Ⱥ͸߶�
#define Width 48
#define Height 27

//�ߵ�״̬(ö��)
typedef enum
{
    up, down, left, right
} Status;

//����ڵ�(�ṹ��)
typedef struct SNAKE
{
    int x;
    int y;
    struct SNAKE *next;
} Snake, *SnakePtr;

//ʳ������(�ṹ��)
typedef struct FOOD
{
    int x;
    int y;
} Food, *FoodPtr;

//����ȫ������//

//��ʼ����
void InitGame();
//������Ϸ
void GameEntry();
//������Ϸ
void RunGame();
//��ʼ����ͼ
void InitMap();
//��ʼ����
void InitSnake();
//����ʳ��
void CreateFood();
//�����ߵ��ƶ�
void SnakeMove();
//��������
void EndGame(int status);

//����
void SpeedUp();
//����
void SpeedDown();
//��ͣ
void Pause();
//�ж��Ƿ�ײǽ
bool HitWall();
//�ж��Ƿ�ҧ���Լ�
bool BiteSelf();
//�ж��Ƿ�Ե�ʳ��
bool EatFood();
//���ƹ���������е�λ��
void Position(int x, int y); 

//����ȫ�ֱ���//

//����ʱ�䣨���ٶȷ���أ� ��óɼ���ʵʱ���£�
extern int sleepTime, bestScore;
//ÿ��ʳ��÷� ��ǰ�÷� �ж��Ƿ�����û���־
extern int add, score, flag;
//��¼��ͣʱ��
extern clock_t t0;
//�����û���
extern char name[100];
//��ͷָ��
extern SnakePtr head;
//ʳ��ָ��
extern FoodPtr food;
//����״̬
extern Status status;
