#include"main.h"
PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL, *User;//User��ǰϵͳʹ����
#define Passengers_headPtr Passengers

void Write_user_file(int choice);

void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*������&��ʼ��*/
	/*��Ҫ�޸ģ����������ļ�����*/
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

	char string[500];//���ȡ��500
	//sprintf(string, "%s_user.ini", psg_temp.ID);//???????�᲻���\0д��ȥ
	//fopen("string", "w+");
	sprintf(string, "%s_route.ini", psg_temp.ID);
	fopen("string", "w+");
	/*sprintf(string, "%s_status.ini", psg_temp.ID);
	fopen("string", "w+");*/

	///*��ʽ�������user�ĵ�*/
	//fprintf(psg_temp.ID,"%s ");



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

	Write_user_file(1);//���û�ע����Ϣд��User_File.ini

	User = &psg_temp;//������������������������������������
}