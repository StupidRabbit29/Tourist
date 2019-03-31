#include"main.h"
#include<windows.h>
#include<process.h>

extern bool Quit;
extern PASSENGER *Passengers, *Passengers_tailPtr, *User;//User��ǰϵͳʹ����

void Create_New_Passenger(PASSENGER *tailPtr);
Status User_sign_in(void);
Status Output_Status(PASSENGER *psg);

unsigned __stdcall mouse(void* pArguments)
{

	int choice;//�û�ѡ��

	while (Quit == false)//���˳�����ǰѭ����ȡ�û����룬ʵ�ָ��ֹ���
	{
		//��ӡ������ʾ
		printf("/**************************************************************************/\n");
		printf("\t��������������Ӧ����Խ��в���\n");
		printf("\t���\t��������\n");
		printf("\t0:\t�˳�ϵͳ��\n");
		printf("\t1:\t�û�ע�ᣡ\n");
		printf("\t2:\t�û���¼��\n");
		printf("\t3:\t��ѯ�û�״̬��\n");	
		printf("/**************************************************************************/\n");
		printf("���������Ĳ�����\n");

		scanf("%d", &choice);

		switch (choice)
		{
		case 0://�˳�ϵͳ
		{
			//ͨ������Quit�ر�ʱ�����
			Quit = true;
		}
		case 1://�û�ע��
		{
			Create_New_Passenger(Passengers_tailPtr);
		}
		case 2:
		{
			//�û���¼
			User_sign_in();
		}
		case 3:
		{
			//��ѯ�û�״̬
			PASSENGER *temp = Passengers;

			if (temp == NULL)
				printf("��ǰϵͳ�����û���\n");
			while (temp != NULL)
			{
				Output_Status(temp);
				temp = temp->next_passenger;
			}
		}
		default:
		{
			printf("��ѡ��Ĳ��������ڣ�\n");
			break;
		}
		}

	}

	_endthreadex(0);
	return 0;
}