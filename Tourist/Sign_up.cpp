#include"main.h"
PASSENGER *Passengers = NULL, *Passengers_tailPtr = NULL, *User;//User��ǰϵͳʹ����
#define Passengers_headPtr Passengers


extern FILE *fptr_input;

void Write_user_file(int choice);

void Create_New_Passenger(PASSENGER *tailPtr)
{
	/*������&��ʼ��*/
	/*��Ҫ�޸ģ����������ļ�����*/
	PASSENGER psg_temp;
	printf("������ID��");
	scanf_s("%s", &psg_temp.ID);//&��û�����⣿
	fprintf(fptr_input, "ID��%d\n", psg_temp.ID);//�û�����д��input.txt�ļ�

	printf("����������ţ�");
	scanf_s("%d", &psg_temp.src);
	fprintf(fptr_input, "����ţ�%d\n", psg_temp.src);//�û�����д��input.txt�ļ�

	printf("�������յ��ţ�");
	scanf_s("%d", &psg_temp.dest);
	fprintf(fptr_input, "�յ��ţ�%d\n", psg_temp.dest);//�û�����д��input.txt�ļ�

	printf("������;������������");
	int cnt=0,i;
	scanf_s("%d", &cnt);
	fprintf(fptr_input, ";������������%d\n;�����б�ţ�",cnt);//�û�����д��input.txt�ļ�
	printf("������;�����б�ţ�");
	bool stay = false;
	for (i = 0; i < cnt; i++)
	{
		scanf_s("%d", &psg_temp.pass_by[0][i]);
		fprintf(fptr_input, "%d ", psg_temp.pass_by[0][i]);//�û�����д��input.txt�ļ�
		printf("�Ƿ���Ҫ�ڸõ�ͣ����Y=1/N=0����");
		scanf_s("%d", &stay);
		if (stay == true)
		{
			printf("������ͣ��ʱ�䣨��λ��Сʱ����");
			scanf_s("%d", &psg_temp.pass_by[1][i]);
		}
		else
			psg_temp.pass_by[1][i] = 0;
	}

	psg_temp.next_passenger = NULL;
	printf("���������в��Ա�ţ�");
	scanf_s("%d", &psg_temp.strategy);
	fprintf(fptr_input, "\n���в��Ա�ţ�%d\n", psg_temp.strategy);//�û�����д��input.txt�ļ�
	if (psg_temp.strategy == STRA_limTIME_minCOST)
	{
		printf("����������ʱ�䣺");
		scanf_s("%d", &psg_temp.Time_Limited);
		fprintf(fptr_input, "����ʱ�䣺%d\n\n", psg_temp.Time_Limited);//�û�����д��input.txt�ļ�
	}
	else
		psg_temp.Time_Limited = NULL;

	/*��route.ini�ļ�*/
	char string_filename[500];//���ȡ��500
	strcpy(string_filename, psg_temp.ID);
	strcat(string_filename, "_route");
	psg_temp.fptr_route=fopen(string_filename, "w+");

	

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

	/*����·��*/
}