#define _CRT_SECURE_NO_WARNINGS
#include"main.h"
#include<windows.h>

extern PASSENGER *User;
extern PASSENGER *Passengers, *Passengers_tailPtr;
extern SYSTEM_TIME System_Time;
extern GRAPH city_graph;
extern int Travelstate[10];

//写入状态函数
void Write_status_file(PASSENGER &psg)
{
	//将User的状态结构体写入fptr指向的文件
	char str2[100] = { '\0' };
	char *loca[4] = { "CAR", "TRAIN", "AIRPLANE", "STAY_IN_CITY" };

	//旅客旅行时刻
	memset(str2, 0, sizeof(str2));
	sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
	WritePrivateProfileStringA(psg.ID, "System Time", str2, ".\\Status_File.ini");
	//旅客所处状态（某种交通工具或停留在某个城市）
	WritePrivateProfileStringA(psg.ID, "旅行状态", loca[(int)(psg.status.loca)], ".\\Status_File.ini");
	//旅客所在城市
	memset(str2, 0, sizeof(str2));
	sprintf(str2, "%s  ==》 %s", city_graph.City_Name[psg.status.src], city_graph.City_Name[psg.status.dest]);
	WritePrivateProfileStringA(psg.ID, "地理位置", str2, ".\\Status_File.ini");

}

void Write_user_file(int choice)
{	
	char str1[100] = { '\0' };
	char str2[100] = { '\0' };
	int number1 = 0;
	int number2 = 0;

	switch (choice)
	{
	case 1://sign_up
		//添加Sign_in_number和Sign_out_number键，记录用户登录登出次数
		WritePrivateProfileStringA(User->ID, "Sign_in_number", "0", ".\\User_File.ini");
		WritePrivateProfileStringA(User->ID, "Sign_out_number", "0", ".\\User_File.ini");
		//记录用户注册信息
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, "Sign_up", str2, ".\\User_File.ini");

		break;
	case 2://sign_in
		number1=GetPrivateProfileIntA(User->ID, "Sign_in_number", 0, ".\\User_File.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "Sign In No.%d", ++number1);
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, str1, str2, ".\\User_File.ini");
		break;
	case 3://sign_out
		number2 = GetPrivateProfileIntA(User->ID, "Sign_out_number", 0, ".\\User_File.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "Sign Out No.%d", ++number2);
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, str1, str2, ".\\User_File.ini");
		break;
	default:
		break;
	}

}

void Write_route_file(PATH tour)
{
	char filename[20] = { ".\\User_Route.ini" };
	char str1[100];

	int number = 0;
	PATH temp = tour;
	while (temp != NULL)
	{
		number++;
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "No.%d", number);

		WritePrivateProfileStructA(User->ID, str1, temp, sizeof(PathNode), filename);

		temp = temp->next;
	}

	int touristnum = 0;
	PASSENGER *tempp = Passengers;
	while (tempp != User)
		touristnum++;

	Travelstate[touristnum] = 1;
}

Status Write_system_file()
{
	WritePrivateProfileStringA("able_or_unable", "able", "1", ".\\System_File.ini");
	WritePrivateProfileStructA("System_Time", "time", &System_Time, sizeof(SYSTEM_TIME), ".\\System_File.ini");

	int number = 0;
	PASSENGER *temp = Passengers;
	while (temp != NULL)
	{
		temp = temp->next_passenger;
		number++;
	}
	char str1[100];
	memset(str1, 0, sizeof(str1));
	sprintf(str1, "%d", number);
	WritePrivateProfileStringA("Passenger", "number", str1, ".\\System_File.ini");

	int i = 0;
	temp = Passengers;
	for (i=1;i<=number;i++)
	{
		if (temp == User)
		{
			memset(str1, 0, sizeof(str1));
			sprintf(str1, "%d", i);
			WritePrivateProfileStringA("Passenger", "User", str1, ".\\System_File.ini");
		}
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "旅客No.%d", i);
		
		WritePrivateProfileStructA("Passenger", str1, &temp, sizeof(PASSENGER), ".\\System_File.ini");
		temp = temp->next_passenger;
	}

	WritePrivateProfileStructA("GRAPH", "graph", &city_graph, sizeof(GRAPH), ".\\System_File.ini");

	return OK;
}

Status Read_system_file()
{
	if (DEBUG)
		cout << "Called Read_system_file()" << endl;

	//判断system_file中是否有可读内容
	int able = GetPrivateProfileIntA("able_or_unable", "able", 0, ".\\System_File.ini");
	if (able == 0)
	{
		printf("没有系统使用记录，无法恢复系统！\n");
		return UNABLE;
	}

	//读取系统时间
	GetPrivateProfileStructA("System_Time", "time", &System_Time, sizeof(SYSTEM_TIME), ".\\System_File.ini");

	int number=GetPrivateProfileIntA("Passenger", "number", 0, ".\\System_File.ini");

	//逐个读取旅客信息
	if (number > 0)
	{
		PASSENGER *temp = Passengers;
		Passengers = (PASSENGER*)malloc(sizeof(PASSENGER));
		GetPrivateProfileStructA("Passenger", "旅客No.1", &Passengers, sizeof(PASSENGER), ".\\System_File.ini");
		int i = 2;
		char str1[100];
		for (; i <= number; i++)
		{
			memset(str1, 0, sizeof(str1));
			sprintf(str1, "旅客No.%d", i);
			temp->next_passenger = (PASSENGER*)malloc(sizeof(PASSENGER));
			GetPrivateProfileStructA("Passenger", str1, temp->next_passenger, sizeof(PASSENGER), ".\\System_File.ini");
			temp = temp->next_passenger;
		}

		Passengers_tailPtr = temp;
		User = NULL;
	}
	else
	{
		Passengers = NULL;
		Passengers_tailPtr = NULL;
		User = NULL;
	}
	
	//读取地图信息
	GetPrivateProfileStructA("GRAPH", "graph", &city_graph, sizeof(GRAPH), ".\\System_File.ini");

	cout << "Read system_file successfully" << endl;
	return OK;
}