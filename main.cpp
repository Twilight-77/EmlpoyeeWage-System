#include "pch.h"
#include "EmployeeWage.h"
#include <Windows.h>

int main()
{
	FILE *fp;  
	fp = fopen("test.txt", "a+");
	char ch = fgetc(fp);
	if (ch == EOF)         //如果是第一次打开文件
	{
		while (1)
		{
			Choise();
		}
	}
	else                   //如果是系统再次登陆
	{
		printf("欢迎再次登陆该系统!\n");
		system("pause");
		system("cls");
		FromDisk();        //从磁盘获取文件
		while (1)
		{
			Choise();
		}
	}
	return 0;
}
