#include"main.h"

extern FILE *fptr_input;

void Change_User_Info(PASSENGER &psg)
{
	/*���޸�ǰ�Ƿ���Ҫ����ÿ͵�ǰ״̬����*/

	fprintf(fptr_input, "ID��%d  �������мƻ�\n", psg.ID);//�û�����д��input.txt�ļ�

	/*�޸��ÿ���Ϣ������*/
	int choice;
	printf("�Ƿ�����յ㣨Y=1/N=0����");
	scanf_s("%d",&choice);
	if (choice == 1)
	{
		printf("�������յ��ţ�");
		scanf_s("%d", &psg.dest);
		fprintf(fptr_input, "�յ��ţ�%d\n", psg.dest);//�û�����д��input.txt�ļ�
	}
	printf("�Ƿ����;�����У�Y=1/N=0����");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		printf("������;������������");
		int cnt = 0, i;
		scanf_s("%d", &cnt);
		fprintf(fptr_input, ";������������%d\n;�����б�ţ�", cnt);//�û�����д��input.txt�ļ�
		printf("������;�����б�ţ�");
		bool stay = false;
		for (i = 0; i < cnt; i++)
		{
			scanf_s("%d", &psg.pass_by[0][i]);
			fprintf(fptr_input, "%d ", psg.pass_by[0][i]);//�û�����д��input.txt�ļ�
			printf("�Ƿ���Ҫ�ڸõ�ͣ����Y=1/N=0����");
			scanf_s("%d", &stay);
			if (stay == true)
			{
				printf("������ͣ��ʱ�䣨��λ��Сʱ����");
				scanf_s("%d", &psg.pass_by[1][i]);
			}
			else
				psg.pass_by[1][i] = 0;
		}
	}
	printf("�Ƿ�������в��ԣ�Y=1/N=0����");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		printf("���������в��Ա�ţ�");
		scanf_s("%d", &psg.strategy);
		fprintf(fptr_input, "\n���в��Ա�ţ�%d\n", psg.strategy);//�û�����д��input.txt�ļ�
	}
	if (choice == 1 && psg.strategy == STRA_limTIME_minCOST)
	{
		printf("����������ʱ�䣺");
		scanf_s("%d", &psg.Time_Limited);
		fprintf(fptr_input, "����ʱ�䣺%d\n\n", psg.Time_Limited);//�û�����д��input.txt�ļ�
	}

	/*���ݲ��ԣ��ÿ͵�ǰλ�ã��յ㣬;����������·�������ǡ�*/
	//
	//��ûд��
	/*���µ�·��д���ļ�*/
}