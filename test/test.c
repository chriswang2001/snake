#include <conio.h>
#include <stdio.h>

//测试键盘按键对应的键值
int main()
{
    while (1)
    {
           int ch1 = _getch();
           printf("%d  ",ch1);
           int ch2 = _getch();

           printf("%d\n",ch2);
    }

    return 0;
}