#include"main.h"
PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL;
#define Passengers_headPtr Passengers
void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*读输入*/
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
	fprintf()
}