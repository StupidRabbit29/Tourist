#include"main.h"
void Change_User_Info(PASSENGER &psg)
{
	/*在修改前是否需要输出旅客当前状态？？*/

	/*修改旅客信息及策略*/
	int choice;
	printf("是否更改终点（Y=1/N=0）：");
	scanf_s("%d",choice);
	if (choice == 1)
	{
		printf("请输入终点编号：");
		scanf_s("%d", psg.dest);
	}
	printf("是否更改途经城市（Y=1/N=0）：");
	scanf_s("%d", choice);
	if (choice == 1)
	{
		printf("请输入途经城市数量：");
		int cnt = 0, i;
		scanf_s("%d", cnt);
		printf("请输入途经城市编号：");
		for (i = 0; i < cnt; i++)
		{
			scanf_s("%d", psg.pass_by[i]);
		}
	}
	printf("是否更改旅行策略（Y=1/N=0）：");
	scanf_s("%d", choice);
	if (choice == 1)
	{
		printf("请输入旅行策略编号：");
		scanf_s("%d", psg.strategy);
	}
	if (choice == 1 && psg.strategy == STRA_limTIME_minCOST)
	{
		printf("请输入限制时间：");
		scanf_s("%d", psg.Time_Limited);
	}

	/*根据策略，旅客当前位置，终点，途经城市重算路径并覆盖。*/
	//
	//还没写！
}