#include"main.h"
PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL, *User;//User当前系统使用者
#define Passengers_headPtr Passengers


extern FILE *fptr_input;

void Write_user_file(int choice);

void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*读输入&初始化*/
	/*需要修改！！！！！文件输入*/
	PASSENGER psg_temp;
	printf("请输入ID：");
	scanf_s("%s", &psg_temp.ID);//&有没有问题？
	fprintf(fptr_input, "ID：%d\n", psg_temp.ID);//用户输入写入input.txt文件

	printf("请输入起点编号：");
	scanf_s("%d", &psg_temp.src);
	fprintf(fptr_input, "起点编号：%d\n", psg_temp.src);//用户输入写入input.txt文件

	printf("请输入终点编号：");
	scanf_s("%d", &psg_temp.dest);
	fprintf(fptr_input, "终点编号：%d\n", psg_temp.dest);//用户输入写入input.txt文件

	printf("请输入途经城市数量：");
	int cnt=0,i;
	scanf_s("%d", &cnt);
	fprintf(fptr_input, "途经城市数量：%d\n途经城市编号：",cnt);//用户输入写入input.txt文件
	printf("请输入途经城市编号：");
	bool stay = false;
	for (i = 0; i < cnt; i++)
	{
		scanf_s("%d", &psg_temp.pass_by[0][i]);
		fprintf(fptr_input, "%d ", psg_temp.pass_by[0][i]);//用户输入写入input.txt文件
		printf("是否需要在该地停留（Y=1/N=0）：");
		scanf_s("%d", &stay);
		if (stay == true)
		{
			printf("请输入停留时间（单位：小时）：");
			scanf_s("%d", &psg_temp.pass_by[1][i]);
		}
		else
			psg_temp.pass_by[1][i] = 0;
	}

	psg_temp.next_passenger = NULL;
	printf("请输入旅行策略编号：");
	scanf_s("%d", &psg_temp.strategy);
	fprintf(fptr_input, "\n旅行策略编号：%d\n", psg_temp.strategy);//用户输入写入input.txt文件
	if (psg_temp.strategy == STRA_limTIME_minCOST)
	{
		printf("请输入限制时间：");
		scanf_s("%d", &psg_temp.Time_Limited);
		fprintf(fptr_input, "限制时间：%d\n\n", psg_temp.Time_Limited);//用户输入写入input.txt文件
	}
	else
		psg_temp.Time_Limited = NULL;

	/*打开route.ini文件*/
	char string_filename[500];//随便取的500
	strcpy(string_filename, psg_temp.ID);
	strcat(string_filename, "_route");
	psg_temp.fptr_route=fopen(string_filename, "w+");

	

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

	/*计算路径*/
}