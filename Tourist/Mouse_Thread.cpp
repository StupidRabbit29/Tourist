#include"main.h"
#include<windows.h>
#include<process.h>

extern bool Quit;


void Create_New_Passenger(PASSENGER *tailPtr);
Status User_sign_in(void);

unsigned __stdcall mouse(void* pArguments)
{

	int choice;//用户选择

	while (Quit == false)//在退出程序前循环读取用户输入，实现各种功能
	{
		//打印输入提示
		printf("/**************************************************************************/\n");
		printf("\t请输入各项操作对应标号以进行操作\n");
		printf("\t标号\t操作内容\n");
		printf("\t0:\t退出系统！\n");
		printf("\t1:\t用户注册！\n");
		printf("\t2:\t用户登录！\n");
		printf("\t3:\t查询用户状态！\n");	
		printf("/**************************************************************************/\n");
		printf("请输入您的操作：\n");

		scanf("%d", &choice);

		switch (choice)
		{
		case 0://退出系统
		{
			Quit = true;
			//存档，关闭文件等
			//关闭时间进程
		}
		case 1:
		{
			//用户注册
		}
		case 2:
		{
			//用户登录
			User_sign_in();
		}
		case 3:
		{
			//查询用户状态
		}
		default:
		{
			printf("您选择的操作不存在！\n");
			break;
		}
		}

	}

	_endthreadex(0);
	return 0;
}