#include"main.h"
#include<windows.h>

extern PASSENGER *User;
extern FILE *fptr_user;

//写入状态函数
void Write_status_file(FILE *fptr)
{
	//将User的状态结构体写入fptr指向的文件
	
}

void Write_user_file(int choice)
{	
	char str[100] = { '\0' };

	switch (choice)
	{
	case 1://sign_up
		//添加Sign_in_number和Sign_out_number键，记录用户登录登出次数
		WritePrivateProfileStringA(User->ID, "Sign_in_number", "0", ".\\User_File.ini");
		WritePrivateProfileStringA(User->ID, "Sign_out_number", "0", ".\\User_File.ini");
		//记录用户注册信息
		WritePrivateProfileStringA(User->ID, "Sign_up", "", ".\\User_File.ini");

		break;
	case 2://sign_in
		int number=GetPrivateProfileIntA(User->ID, "Sign_in_number", 0, ".\\User_File.ini");
		memset(str, 0, sizeof(str));
		sprintf(str, "Sign In No.%d", ++number);
		WritePrivateProfileStringA(User->ID, str, "", ".\\User_File.ini");
		break;
	case 3://sign_out
		int number = GetPrivateProfileIntA(User->ID, "Sign_out_number", 0, ".\\User_File.ini");
		memset(str, 0, sizeof(str));
		sprintf(str, "Sign Out No.%d", ++number);
		WritePrivateProfileStringA(User->ID, str, "", ".\\User_File.ini");
		break;
	default:
		break;
	}


}

void Write_route_file()
{

}