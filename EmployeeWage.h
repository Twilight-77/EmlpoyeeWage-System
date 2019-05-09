#pragma once
#ifndef EMPLOYEEWAGE_H_
#define EMPLOYEEWAGE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)
#define max 100  //最大的人数
int i = 0;       //当前人数

struct Employee
{
	int workNumber;     //工号
	double baseWage;    //基本工资
	double allo;        //津贴
	double bonus;       //奖金
	double total;       //总工资
	char name[20];      //名字
}emp[max];


//菜单
void  Menu()
{
	printf("输入员工数量: %d\n", i);
	printf("#######################################################\n");
	printf("##             欢迎进入职工工资管理系统:             ##\n");
	printf("##                 1:录入员工信息                    ##\n");
	printf("##                 2:职工总工资进行排序              ##\n");
	printf("##                 3:文件保存到硬盘上                ##\n");
	printf("##                 4:查询员工信息                    ##\n");
	printf("##                 5:修改员工信息                    ##\n");
	printf("##                 6:查看所有员工信息                ##\n");
	printf("##                 7:添加员工信息                    ##\n");
	printf("##                 8:删除员工信息                    ##\n");
	printf("##                 9:退出程序                        ##\n");
	printf("##                                                   ##\n");
	printf("##                 请输入对应的编号(1-7)             ##\n");
	printf("#######################################################\n");
}

// 1，录入信息
void InputMessage()
{
	while (1)
	{
		printf("请输入员工的基本信息: \n");
		printf("工号: ");
		scanf("%d", &emp[i].workNumber);
		printf("姓名: ");
		scanf("%s", emp[i].name);
		printf("基本工资: ");
		scanf("%lf", &emp[i].baseWage);
		printf("津贴: ");
		scanf("%lf", &emp[i].allo);
		printf("奖金: ");
		scanf("%lf", &emp[i].bonus);
		emp[i].total = emp[i].baseWage + emp[i].allo + emp[i].bonus;    //计算总工资
		printf("继续输入吗？(Y/N): ");
		getchar();
		char ch;
		scanf("%c", &ch);
		i++;
		if (ch == 'N' || ch == 'n')
			break;
		fflush(stdin);  //清空缓存，防止空格
	}

}

//2
void Sort()
{
	//采用冒泡排序
	for (int k = 0; k < i - 1; ++k)
	{
		for (int p = 0; p < i - k - 1; ++p)
		{
			if (emp[p].total < emp[p + 1].total)
			{
				Employee temp = emp[p];
				emp[p] = emp[p + 1];
				emp[p + 1] = temp;
			}
		}
	}

	puts("排序结果如下: ");
	printf("名字\t总工资\n");
	for (int k = 0; k < i; ++k)
		printf("%s\t%.2lf\n", emp[k].name, emp[k].total);
}
//3
void SaveToDisk()
{
	FILE *fp;
	fp = fopen("test.txt", "w+");  //把信息写进磁盘
	for(int k = 0; k < i; ++k)
		fprintf(fp, "%d %s %.2lf  %.2lf  %.2lf\n", emp[k].workNumber, emp[k].name, emp[k].baseWage, emp[k].bonus, emp[k].allo);
	puts("写入完毕！");
	fclose(fp);					   //关闭
}

//4

//按照工号查找
int FindID(int id)
{
	for(int k = 0; k < i; ++k)
		if (emp[k].workNumber == id)
		{
			printf("工号： %d 姓名：%s 基本工资：%.2lf 津贴：%.2lf 奖金：%.2lf\n", emp[k].workNumber, emp[k].name, emp[k].baseWage, emp[k].bonus, emp[k].allo);
			return k;        //  若是找到了，则把当前位置的员工返回给调用函数
		}
	puts("没有找到!");
	return -1;
}
//按照名字查找
int FindName(char *name)
{
	for (int k = 0; k < i; ++k)
		if (strcmp(name, emp[k].name) == 0)
		{
			printf("工号： %d 姓名：%s 基本工资：%.2lf 津贴：%.2lf 奖金：%.2lf\n", emp[k].workNumber, emp[k].name, emp[k].baseWage, emp[k].bonus, emp[k].allo);
			return k;
		}
	puts("没有找到!");
	return -1;
}

//查询函数
void Find()
{
	printf("工号查找按1\t姓名查找按2\t\n");
	int ch;
	scanf("%d", &ch);
	if (ch == 1)
	{
		printf("输入工号:");
		int id;
		scanf("%d", &id);
		FindID(id);
	}
	else
	{
		printf("输入姓名:");
		char name[30];
		scanf("%s", name);
		FindName(name);
	}
}

//5
//修改信息
void Modify(int k)
{
	puts("请重新输入新的信息");
	printf("工号: ");
	scanf("%d", &emp[k].workNumber);
	printf("姓名: ");
	scanf("%s", emp[k].name);
	printf("基本工资: ");
	scanf("%lf", &emp[k].baseWage);
	printf("津贴: ");
	scanf("%lf", &emp[k].allo);
	printf("奖金: ");
	scanf("%lf", &emp[k].bonus);
	emp[k].total = emp[k].baseWage + emp[k].allo + emp[k].bonus;  //计算总工资
}

void ModifyMessage()
{
	printf("请先查找员工是否存在\n工号查找按1\t姓名查找按2\n");
	int ch;
	scanf("%d", &ch);
	if (ch == 1)       //学号查找
	{
		int id;
		printf("输入工号:");
		scanf("%d", &id);
		int k = FindID(id);
		if (k == -1)
		{
			printf("请重新选择\n");
		}
		else
		{
			Modify(k);
			puts("修改完毕!");
		}
	}
	else                //姓名查找
	{
		char name[20];
		scanf("%s", name);
		int k = FindName(name);
		if (k == -1)
		{
			printf("请重新选择\n");
		}
		else
		{
			Modify(k);
			puts("修改完毕!");
		}
	}
}

//6查看所有员工信息
void WatchMessage()
{
	system("cls");
	puts("员工全部信息如下");
	puts("-----------------------------------");
	printf("工号\t姓名\t基本工资\t津贴\t员工奖金\n");
	for(int k = 0; k < i; ++k)
		printf("%d\t%s\t%.2lf\t\t%.2lf\t%.2lf\n", emp[k].workNumber, emp[k].name, emp[k].baseWage, emp[k].bonus, emp[k].allo);
	puts("-----------------------------------");
}

//7添加员工信息
void AddNewOne()
{
	printf("请输入新添加的员工信息");
	printf("工号: ");
	scanf("%d", &emp[i].workNumber);
	printf("姓名: ");
	scanf("%s", emp[i].name);
	printf("基本工资: ");
	scanf("%lf", &emp[i].baseWage);
	printf("津贴: ");
	scanf("%lf", &emp[i].allo);
	printf("奖金: ");
	scanf("%lf", &emp[i].bonus);
	emp[i].total = emp[i].baseWage + emp[i].allo + emp[i].bonus;  //计算总工资
	i++;        //员工总数+1
}

//8 删除员工信息
void Delete()
{
	int flag = 0;
	printf("请输入离职的员工工号");
	int id;
	scanf("%d", &id);
	for (int k = 0; k < i; ++k)
	{
		if (emp[k].workNumber == id)  //如果找到了离职的工号
		{
			flag = 1;                 //标记已找到
			printf("员工%d删除完毕!\n", emp[k].workNumber);
			for (int p = k; p < i - 1; ++p)
				emp[p] = emp[p + 1];  //移动删除
			i--;  //员工总数减去一
			break;
		}
	}
	if(flag == 0)
		puts("未找到!");
}

void Choise()
{
	Menu();
	int ch;
	scanf("%d", &ch);
	switch (ch)
	{
	case 1:
		InputMessage();
		break;
	case 2:
		Sort();
		break;
	case 3:
		SaveToDisk();
		break;
	case 4:
		Find();
		break;
	case 5:
		ModifyMessage();
		break;
	case 6:
		WatchMessage();
		break;
	case 7:
		AddNewOne();
		break;
	case 8:
		Delete();
		break;
	case 9:
		exit(0);  //退出
	}
	system("pause");
	system("cls");
}

void FromDisk()
{
	FILE *fp = fopen("test.txt", "r");
	if (fp == NULL)
	{
		puts("打开失败!");
		exit(0);
	}
	else
	{
		while (fscanf(fp, "%d %s %lf %lf %lf", &emp[i].workNumber, emp[i].name, &emp[i].baseWage, &emp[i].bonus, &emp[i].allo) != EOF)  //没读到文件结尾就一直读取
		{
			emp[i].total = emp[i].baseWage + emp[i].allo + emp[i].bonus;
			i++;
		}
	}
	fclose(fp);
}

#endif
