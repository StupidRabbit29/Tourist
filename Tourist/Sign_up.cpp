#include"main.h"
PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL;
#define Passengers_headPtr Passengers
void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*������*/
	PASSENGER psg_temp;
	printf("������ID��");
	scanf_s("%s", psg_temp.ID);
	printf("����������ţ�");
	scanf_s("%d", psg_temp.src);
	printf("�������յ��ţ�");
	scanf_s("%d", psg_temp.dest);
	printf("������;������������");
	int cnt=0,i;
	scanf_s("%d", cnt);
	printf("������;�����б�ţ�");
	for (i = 0; i < cnt; i++)
	{
		scanf_s("%d", psg_temp.pass_by[i]);
	}
	psg_temp.next_passenger = NULL;
	printf("���������в��Ա�ţ�");
	scanf_s("%d", psg_temp.strategy);
	if (psg_temp.strategy == STRA_limTIME_minCOST)
	{
		printf("����������ʱ�䣺");
		scanf_s("%d", psg_temp.Time_Limited);
	}
	else
		psg_temp.Time_Limited = NULL;

	/*����passengers����*/
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