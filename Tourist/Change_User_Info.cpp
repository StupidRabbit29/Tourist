#include"main.h"

extern FILE *fptr_input;

void Change_User_Info(PASSENGER &psg)
{
	/*在修改前是否需要输出旅客当前状态？？*/

	fprintf(fptr_input, "ID：%d  更改旅行计划\n", psg.ID);//用户输入写入input.txt文件

	/*修改旅客信息及策略*/
	int choice;
	printf("是否更改终点（Y=1/N=0）：");
	scanf_s("%d",&choice);
	if (choice == 1)
	{
		printf("请输入终点编号：");
		scanf_s("%d", &psg.dest);
		fprintf(fptr_input, "终点编号：%d\n", psg.dest);//用户输入写入input.txt文件
	}
	printf("是否更改途经城市（Y=1/N=0）：");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		printf("请输入途经城市数量：");
		int cnt = 0, i;
		scanf_s("%d", &cnt);
		fprintf(fptr_input, "途经城市数量：%d\n途经城市编号：", cnt);//用户输入写入input.txt文件
		printf("请输入途经城市编号：");
		bool stay = false;
		for (i = 0; i < cnt; i++)
		{
			scanf_s("%d", &psg.pass_by[0][i]);
			fprintf(fptr_input, "%d ", psg.pass_by[0][i]);//用户输入写入input.txt文件
			printf("是否需要在该地停留（Y=1/N=0）：");
			scanf_s("%d", &stay);
			if (stay == true)
			{
				printf("请输入停留时间（单位：小时）：");
				scanf_s("%d", &psg.pass_by[1][i]);
			}
			else
				psg.pass_by[1][i] = 0;
		}
	}
	printf("是否更改旅行策略（Y=1/N=0）：");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		printf("请输入旅行策略编号：");
		scanf_s("%d", &psg.strategy);
		fprintf(fptr_input, "\n旅行策略编号：%d\n", psg.strategy);//用户输入写入input.txt文件
	}
	if (choice == 1 && psg.strategy == STRA_limTIME_minCOST)
	{
		printf("请输入限制时间：");
		scanf_s("%d", &psg.Time_Limited);
		fprintf(fptr_input, "限制时间：%d\n\n", psg.Time_Limited);//用户输入写入input.txt文件
	}

	/*根据策略，旅客当前位置，终点，途经城市重算路径并覆盖。*/
	//
	//还没写！
	/*将新的路径写入文件*/
}