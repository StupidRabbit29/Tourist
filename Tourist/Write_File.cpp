#include"main.h"
#include<windows.h>

extern PASSENGER *User;
extern SYSTEM_TIME System_Time;
extern GRAPH city_graph;

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
		int number=GetPrivateProfileIntA(User->ID, "Sign_in_number", 0, ".\\User_File.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "Sign In No.%d", ++number);
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, str1, str2, ".\\User_File.ini");
		break;
	case 3://sign_out
		int number = GetPrivateProfileIntA(User->ID, "Sign_out_number", 0, ".\\User_File.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "Sign Out No.%d", ++number);
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, str1, str2, ".\\User_File.ini");
		break;
	default:
		break;
	}

}

void Write_route_file()
{

}

void Write_system_file()
{

}