#include"main.h"
void Change_User_Info(PASSENGER &psg)
{
	/*���޸�ǰ�Ƿ���Ҫ����ÿ͵�ǰ״̬����*/

	/*�޸��ÿ���Ϣ������*/
	int choice;
	printf("�Ƿ�����յ㣨Y=1/N=0����");
	scanf_s("%d",choice);
	if (choice == 1)
	{
		printf("�������յ��ţ�");
		scanf_s("%d", psg.dest);
	}
	printf("�Ƿ����;�����У�Y=1/N=0����");
	scanf_s("%d", choice);
	if (choice == 1)
	{
		printf("������;������������");
		int cnt = 0, i;
		scanf_s("%d", cnt);
		printf("������;�����б�ţ�");
		for (i = 0; i < cnt; i++)
		{
			scanf_s("%d", psg.pass_by[i]);
		}
	}
	printf("�Ƿ�������в��ԣ�Y=1/N=0����");
	scanf_s("%d", choice);
	if (choice == 1)
	{
		printf("���������в��Ա�ţ�");
		scanf_s("%d", psg.strategy);
	}
	if (choice == 1 && psg.strategy == STRA_limTIME_minCOST)
	{
		printf("����������ʱ�䣺");
		scanf_s("%d", psg.Time_Limited);
	}

	/*���ݲ��ԣ��ÿ͵�ǰλ�ã��յ㣬;����������·�������ǡ�*/
	//
	//��ûд��
}