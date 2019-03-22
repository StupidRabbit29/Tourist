#include"main.h"
PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL, *User;//User当前系统使用者
#define Passengers_headPtr Passengers

void Write_user_file(int choice);

void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*读输入&初始化*/
	/*需要修改！！！！！文件输入*/
	PASSENGER psg_temp;
	printf("请输入ID：");
	scanf_s("%s", psg_temp.ID);
	printf("请输入起点编号：");
	scanf_s("%d", psg_temp.src);
	printf("请输入终点编号：");
	scanf_s("%d", psg_temp.dest);
	printf("请输入途经城市数量：");
	int cnt=0,i;
	scanf_s("%d", cnt);
	printf("请输入途经城市编号：");
	for (i = 0; i < cnt; i++)
	{
		scanf_s("%d", psg_temp.pass_by[i]);
	}
	psg_temp.next_passenger = NULL;
	printf("请输入旅行策略编号：");
	scanf_s("%d", psg_temp.strategy);
	if (psg_temp.strategy == STRA_limTIME_minCOST)
	{
		printf("请输入限制时间：");
		scanf_s("%d", psg_temp.Time_Limited);
	}
	else
		psg_temp.Time_Limited = NULL;

	char string[500];//随便取的500
	//sprintf(string, "%s_user.ini", psg_temp.ID);//???????会不会把\0写进去
	//fopen("string", "w+");
	sprintf(string, "%s_route.ini", psg_temp.ID);
	fopen("string", "w+");
	/*sprintf(string, "%s_status.ini", psg_temp.ID);
	fopen("string", "w+");*/

	///*格式化输出到user文档*/
	//fprintf(psg_temp.ID,"%s ");



	/*加入passengers链表*/
	if (Passengers_headPtr == NULL)
	{
		Passengers_headPtr = &psg_temp;
		Passengers_tailPtr = &psg_temp;
	}
	else
	{
		Passengers_tailPtr->next_passenger = &psg_temp;
		Passengers_tailPtr = Passengers_tailPtr->next_passenger;
	}

	Write_user_file(1);//将用户注册信息写入User_File.ini

	User = &psg_temp;//？？？？？？？？？？？？？？？？？？
}