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
    score = 0;   //���õ÷�
    t0 = 0; //������ͣʱ��
    fflush(stdin); //������뻺��
    system("color F3"); //����������������ɫ����ɫ ������
    Position(Width / 2 + 24, Height / 4);
    printf("̰���ߴ���ս");

    if(flag == 0) //�ж��Ƿ�����û�
    {
        Position(Width / 2 + 12, Height / 3);
        printf("�������û�����");
        gets(name);
    }

    Position(Width / 2 + 12, Height / 3 + 5);
    printf("��ѡ���Ѷ�ģʽ 1:�� 2:��ͨ 3:����");

    int difficultyLevel = _getch(); //��getch�������Բ����ԣ��������
    
    switch(difficultyLevel)
    {
        case 49://���ּ�ascii��
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
    system("cls"); //����
    InitMap();
    InitSnake();
    CreateFood();
    RunGame();
}

void InitMap()
{
    system("color F3");
    
    for (int i = 0; i <= Width; i += 2) //��ӡ���±߿�
    {
        Position(i, 0);
        printf("��");
        Position(i, Height);
        printf("��");
    }

    for (int i = 1; i < Height; i ++) //��ӡ���ұ߿�
    {
        Position(0, i);
        printf("��");
        Position(Width, i);
        printf("��");
    }

    //��Ϸ����Ui���
    Position(Width + 5, 3);
    printf("��ң�%s", name);

    Position(Width + 5, Height / 4 - 1);
    printf("��ߵ÷֣�%5d ", bestScore);
    Position(Width + 5, Height / 4 );
    printf("��ǰ�÷֣�%5d ", score);
    Position(Width + 5, Height / 4 + 1);
    printf("ÿ��ʳ��÷֣�%d", add);

    Position(Width + 5 , Height / 2 + 1);
    printf("����˵����");
    Position(Width + 5 , Height / 2 + 2);
    printf("�� �� �� �� �� �����ߵ��ƶ�   ");
    printf("F1 Ϊ���٣�F2 Ϊ����");
    Position(Width + 5 , Height / 2 + 3);
    printf("�ո�� Ϊ��ͣ/ȡ����ͣ        ");
    printf("ESC Ϊ�˳���Ϸ");

    Position(Width + 5,  Height / 2 + 5);
    printf("С��ʾ��");
    Position(Width + 5,  Height / 2 + 6);
    printf("��ͬ�Ѷ�ģʽ�ĳ�ʼ�ٶȲ�ͬ�����ߵ��ٶȽ��ܵõ����ߵķ�����");

    Position(Width + 5,  Height / 2 + 9);
    printf("��Ϸʱ�䣺0 s");

    Position(Width + 5, Height - 2);
    printf("Copyright 2020 by Chris Wang. All Rights Reserved.\n");
}

void InitSnake()
{
    head = (SnakePtr)malloc(sizeof(Snake));
    if(head == NULL)
        EndGame(-1);
    
    head->x = Width / 2;
    //��֤��ͷ������Ϊż����һ����ռ��������ȣ�һ���߶�-ԭ�����ڿ���̨��λ�߶��ǵ�λ��ȵ������������жϳ�ʳ���ײǽ��
    if(head->x % 2 != 0)
        head->x += 1;
    head->y = Height / 2;
    head->next = NULL;

    //��ʼ������Ϊ3
    SnakePtr tail ,temp = head;
    for (int i = 1; i < 3; i++) 
    {
        tail = (SnakePtr)malloc(sizeof(Snake));
        if(tail == NULL)
            EndGame(-1);
        else
            temp->next = tail;
        tail->x = head->x - 2 * i; //�����������
        tail->y = head->y;
        tail->next = NULL; //һ��Ҫ����βָ��NULL�����������������
        temp = tail;
    }

    temp = head;

    while (temp != NULL) 
    {
        Position(temp->x, temp->y);
        printf("��");
        
        temp = temp->next;
    }
    
}

void CreateFood()
{
    food = (FoodPtr)malloc(sizeof(Food));
    
    if(food == NULL)
        EndGame(-1);

    //������ǽ�����ʳ��Һ��������Ϊż������Ϊ��ͷ������ż����
    while(1)
    {
        food->x = (rand() % (Width - 3)) + 2;
        if(food->x % 2 == 0)
            break;
    }
    
    food->y = (rand() % (Height - 1)) + 1;

    //���������ʳ����������
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
    //��ʼ״̬Ϊ������
    status = right;
    //��ȡ����ʼ����ʱ��ʱ��
    clock_t t1 = clock();

    while (1)
    {
        fflush(stdin);
        if(_kbhit())//khbit�ж��Ƿ��а���������������ȡ
        {
            int ch1 = _getch();
            if (ch1 == 32)
                Pause();
            else if (ch1 == 27)
                EndGame(3);
            //��ȡ���ܼ�ʱ����������getch����һ�η���0/224���ڶ��η��ض�Ӧ��ֵ
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

        //�����ߵ��ƶ��ٶ�
        Sleep(sleepTime);
        SnakeMove();
        
        //������߷���
        if(score > bestScore)
            bestScore = score;
        
        clock_t t2 = clock();             
        int t = (t2 - t1 - t0) / CLOCKS_PER_SEC;
        Position(Width + 15,  Height / 2 + 9);
        printf("%d s", t); //��ʱ��

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

    //ע���ߵ�һ���ṹ�������ռ����
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
        printf("��"); 
        score = score + add;
        CreateFood();
    }
    else
    {
        SnakePtr temp = head;
        while (temp->next->next != NULL) 
            temp = temp->next;
        Position(head->x, head->y); 
        printf("��");    
        Position(temp->next->x, temp->next->y);
        //ע���������ո�
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
            printf("��ѡ����ȷ���Ѷ�ģʽ��"); break;
        case 1:
            printf("�Բ�����ײ��ǽ�ˡ���Ϸ������"); break;
        case 2:
            printf("�Բ�����ҧ���Լ��ˡ���Ϸ������"); break;
        case 3:
            printf("��������������Ϸ��"); break;
        default:
            printf("����δ֪����"); break;
    }
    
    Position(Width / 4, Height / 3 + 3);
    printf("��ң�%s", name);
    Position(Width / 4, Height / 3 + 4);
    printf("��ߵ÷֣�%d\n", bestScore);
    Position(Width / 4, Height / 3 + 5);
    printf("���ε÷֣�%d\n", score);
    Position(Width / 4, Height / 3 + 7);
    printf("q: �˳���Ϸ r:���¿�ʼ e:�������");
    
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
