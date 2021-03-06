﻿#include"main.h"

PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL, *User;//User当前系统使用者
#define Passengers_headPtr Passengers


extern FILE *fptr_input;
extern SYSTEM_TIME System_Time;
extern int Travelstate[10];

void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*读输入&初始化*/
	/*需要修改！！！！！文件输入*/
	if(DEBUG)
		cout << "Create_New_Passenger() called" << endl;
	
	PASSENGER *psg_temp;
	psg_temp = (PASSENGER*)malloc(sizeof(PASSENGER));
	printf("请输入ID：");

	//scanf_s("%s", psg_temp->ID);//&有没有问题？
	cin >> psg_temp->ID;
	fprintf(fptr_input, "ID：%s\n", psg_temp->ID);//用户输入写入input.txt文件

	printf("请输入起点编号：");
	scanf_s("%d", &psg_temp->src);
	fprintf(fptr_input, "起点编号：%d\n", psg_temp->src);//用户输入写入input.txt文件

	printf("请输入终点编号：");
	scanf_s("%d", &psg_temp->dest);
	fprintf(fptr_input, "终点编号：%d\n", psg_temp->dest);//用户输入写入input.txt文件

	printf("请输入途经城市数量：");
	int cnt=0,i;
	scanf_s("%d", &cnt);
	psg_temp->num_passby = cnt;
	fprintf(fptr_input, "途经城市数量：%d\n途经城市编号：",cnt);//用户输入写入input.txt文件
	int stay = 0;
	for (i = 0; i < cnt; i++)
	{
		printf("请输入途经城市编号：");
		scanf_s("%d", &psg_temp->pass_by[0][i]);
		fprintf(fptr_input, "%d ", psg_temp->pass_by[0][i]);//用户输入写入input.txt文件
		printf("是否需要在该地停留（Y=1/N=0）：");
		scanf_s("%d", &stay);
		if (stay == 1)
		{
			printf("请输入停留时间（单位：小时）：");
			scanf_s("%d", &psg_temp->pass_by[1][i]);
		}
		else
			psg_temp->pass_by[1][i] = 0;
	}

	psg_temp->next_passenger = NULL;
	printf("请输入旅行策略编号：");
	scanf_s("%d", &psg_temp->strategy);
	fprintf(fptr_input, "\n旅行策略编号：%d\n", psg_temp->strategy);//用户输入写入input.txt文件// STRA_minCOST, STRA_minTIME, STRA_limTIME_minCOST
	if (psg_temp->strategy == STRA_limTIME_minCOST)
	{
		printf("请输入限制时间：");
		scanf_s("%d", &psg_temp->Time_Limited);
		fprintf(fptr_input, "限制时间：%d\n\n", psg_temp->Time_Limited);//用户输入写入input.txt文件
	}
	else
		psg_temp->Time_Limited = NULL;

	/*旅客开始旅行时间*/
	psg_temp->start_time = System_Time;

	///*打开route.ini文件*/
	//char string_filename[500];//随便取的500
	//strcpy(string_filename, psg_temp->ID);
	//strcat(string_filename, "_route");
	//psg_temp->fptr_route=fopen(string_filename, "w+");
	//if(!(psg_temp->fptr_route))
	//	cout<<"route.ini"

	

	/*加入passengers链表*/
	if (Passengers_headPtr == NULL)
	{
		Passengers_headPtr = psg_temp;
		Passengers_tailPtr = psg_temp;
	}
	else
	{
		Passengers_tailPtr->next_passenger = psg_temp;
		Passengers_tailPtr = Passengers_tailPtr->next_passenger;
	}

	Write_user_file(1);//将用户注册信息写入User_File.ini

	User = psg_temp;//？？？？？？？？？？？？？？？？？？

	/*计算路径*/
	cout << "**********计算路径************" << endl;
	switch (psg_temp->strategy)
	{
	case 0:
		Min_Cost();
		break;
	case 1:
		Min_Time();
		break;
	case 2:
		Min_Time_Limited_Time();
		break;
	default:
		break;
	}

	PASSENGER *temp = Passengers;
	int touristnum = 0;
	while (temp != NULL)
	{
		if (temp == User)
			break;
		else
			touristnum ++;

		temp = temp->next_passenger;
	}
	Travelstate[touristnum] = 1;

	if(DEBUG)
		cout << "Create_New_Passenger() done " << endl;
}