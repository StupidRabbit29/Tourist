#include"main.h"
#include<string.h>

/*�ⲿ����*/
extern PASSENGER *Passengers;
extern PASSENGER *User;
extern SYSTEM_TIME System_Time;
extern GRAPH city_graph;

void Change_User_Info(PASSENGER &psg);
void Write_user_file(int choice);


/*����*/

//�û���¼
Status User_sign_in(void)
{
	Write_user_file(2);
	//��ȡ�û������ID
	char userID[20];
	gets_s(userID);
	getchar();
	bool find_passenger = false;

	//ʹ��temp�����ÿ�����
	PASSENGER *temp = Passengers;

	//Ѱ�����û�����IDƥ����ÿ�
	while (temp != NULL && !find_passenger)
	{
		if (strcmp(userID, temp->ID) != 0)
		{
			temp = temp->next_passenger;
		}
		else
		{
			User = temp;
			find_passenger = true;
		}
	}

	//�û������ڣ���Ҫ��������ID
	if (find_passenger == false)
	{
		printf("�û������ڣ�����������ID��\n");
		User_sign_in();
	}
	else//�û�������һ������
	{
		//�����ʾ��Ϣ
		printf("��ѡ����Ҫ���еĲ���:\n");
		printf("�޸����з���������1��\n");
		printf("��ѯ�ó�״̬������2��\n");
		printf("�˳���¼    ������3��\n");

		int choice = 0;
		bool choice_correct = false;

		//��ȡ��ȷ���룬������һ������
		while (choice_correct == false)
		{
			scanf("%d", &choice);
			getchar();
			if (choice == 1 || choice == 2 || choice == 3)
			{
				if (choice == 1)
				{
					//���õ������з����ĺ���
					Change_User_Info(*User);
				}
				else if (choice == 2)
				{
					//���ô�ӡ�ÿ���Ϣ�ĺ���

					Output_Status(User);
				}
				else
				{
					//�ÿ��˳�
					Write_user_file(3);
					User = NULL;
				}

				choice_correct = true;
			}
			else
			{
				printf("���벻����Ҫ�����������룺\n");
				choice = 0;
			}
		}
	}
		
	return OK;
}

Status Output_Status(PASSENGER *psg)
{
	char *loca[4] = { "CAR", "TRAIN", "AIRPLANE", "STAY_IN_CITY" };
	char str2[100] = { '\0' };

	printf("�ÿͣ���%s��", psg->ID);
	printf("ʱ�䣺%d - %d - %d  %d : 00 : 00\n", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
	printf("����״̬��%s\n", loca[(int)(psg->status.loca)]);
	memset(str2, 0, sizeof(str2));
	sprintf(str2, "%s  ==�� %s", city_graph.City_Name[psg->status.src], city_graph.City_Name[psg->status.dest]);
	printf("����λ�ã�%s\n", str2);

	return OK;
}