#include"main.h"

extern PASSENGER *User;

//д��״̬����
void Write_status_file(FILE *fptr)
{
	//��User��״̬�ṹ��д��fptrָ����ļ�
	fwrite(&(User->status), sizeof(User_Status), 1, fptr);
}

void Write_user_file(FILE *fptr, int choice)
{
	printf("%s\n", User->ID);
	
	switch (choice)
	{
	case 1:
		fprintf(fptr, "״̬����¼\n");
		break;
	case 2:
		fprintf(fptr, "״̬���ǳ�\n");
		break;
	case 3:
		fprintf(fptr, "״̬������״̬��ѯ\n");
		break;
	default:
		break;
	}

	//��ӡʱ��
}

void Write_route_file()
{

}