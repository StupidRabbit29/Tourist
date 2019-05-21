#include"main.h"
#include<windows.h>
#include<process.h>

extern bool Quit;
extern PASSENGER *Passengers, *Passengers_tailPtr, *User;//User当前系统使用者
extern bool inputing;
extern SYSTEM_TIME System_Time;
extern int Travelstate[10];

unsigned __stdcall mouse(void* pArguments)
{

	int choice;//用户选择

	while (Quit == false)//在退出程序前循环读取用户输入，实现各种功能
	{
		//打印输入提示
		printf("***********系统时间：*******%d-%d-%d*****%d:00:00*************************\n", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		printf("                      请输入各项操作对应标号以进行操作\n");
		printf("                      标号\t操作内容\n");
		printf("                      0:\t退出系统！\n");
		printf("                      1:\t用户注册！\n");
		printf("                      2:\t用户登录！\n");
		printf("                      3:\t查询用户状态！\n");	
		printf("**************************************************************************\n");
		printf("请输入您的操作：\n");

		cin >> choice;
		getchar();
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			choice = 99999;
		}

		switch (choice)
		{
		case 0://退出系统
		{
			//通过设置Quit关闭时间进程
			Quit = true;
			break;
		}
		case 1://用户注册
		{
			inputing = true;
			Create_New_Passenger(Passengers_tailPtr);
			inputing = false;
			break;
		}
		case 2:
		{
			//用户登录
			inputing = true;
			User_sign_in();
			inputing = false;
			break;
		}
		case 3:
		{
			//查询用户状态
			PASSENGER *temp = Passengers;

			if (temp == NULL)
				printf("当前系统中无用户！\n");
			int touristnum = 0;
			while (temp != NULL)
			{
				if(Travelstate[touristnum] == 1)
					Refresh(temp, touristnum);
				
				Output_Status(temp);
				temp = temp->next_passenger;
				touristnum++;
			}

			break;
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