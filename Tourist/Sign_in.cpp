#include"main.h"
#include<string.h>

/*�ⲿ����*/
extern PASSENGER *Passengers;
extern PASSENGER *User;

/*����*/

//�û���¼
Status User_sign_in(void)
{
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
				}
				else if (choice == 2)
				{
					//���ô�ӡ�ÿ���Ϣ�ĺ���
				}
				else
				{
					//�ÿ��˳�
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

Status Output_Status(void)
{

}