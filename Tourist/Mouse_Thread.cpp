#include"main.h"
#include<windows.h>
#include<process.h>

extern bool Quit;


void Create_New_Passenger(PASSENGER *tailPtr);
Status User_sign_in(void);

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
			Quit = true;
			//�浵���ر��ļ���
			//�ر�ʱ�����
		}
		case 1:
		{
			//�û�ע��
		}
		case 2:
		{
			//�û���¼
			User_sign_in();
		}
		case 3:
		{
			//��ѯ�û�״̬
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