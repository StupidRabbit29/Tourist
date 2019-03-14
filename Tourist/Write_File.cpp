#include"main.h"

extern PASSENGER *User;

//写入状态函数
void Write_status_file(FILE *fptr)
{
	//将User的状态结构体写入fptr指向的文件
	fwrite(&(User->status), sizeof(User_Status), 1, fptr);
}

void Write_user_file(FILE *fptr, int choice)
{
	printf("%s\n", User->ID);
	
	switch (choice)
	{
	case 1:
		fprintf(fptr, "状态：登录\n");
		break;
	case 2:
		fprintf(fptr, "状态：登出\n");
		break;
	case 3:
		fprintf(fptr, "状态：旅行状态查询\n");
		break;
	default:
		break;
	}

	//打印时间
}

void Write_route_file()
{

}