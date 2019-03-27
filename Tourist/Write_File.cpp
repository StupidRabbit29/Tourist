#include"main.h"
#include<windows.h>

extern PASSENGER *User;
extern SYSTEM_TIME System_Time;
extern GRAPH city_graph;

//д��״̬����
void Write_status_file(PASSENGER &psg)
{
	//��User��״̬�ṹ��д��fptrָ����ļ�
	char str2[100] = { '\0' };
	char *loca[4] = { "CAR", "TRAIN", "AIRPLANE", "STAY_IN_CITY" };

	//�ÿ�����ʱ��
	memset(str2, 0, sizeof(str2));
	sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
	WritePrivateProfileStringA(psg.ID, "System Time", str2, ".\\Status_File.ini");
	//�ÿ�����״̬��ĳ�ֽ�ͨ���߻�ͣ����ĳ�����У�
	WritePrivateProfileStringA(psg.ID, "����״̬", loca[(int)(psg.status.loca)], ".\\Status_File.ini");
	//�ÿ����ڳ���
	memset(str2, 0, sizeof(str2));
	sprintf(str2, "%s  ==�� %s", city_graph.City_Name[psg.status.src], city_graph.City_Name[psg.status.dest]);
	WritePrivateProfileStringA(psg.ID, "����λ��", str2, ".\\Status_File.ini");

}

void Write_user_file(int choice)
{	
	char str1[100] = { '\0' };
	char str2[100] = { '\0' };

	switch (choice)
	{
	case 1://sign_up
		//���Sign_in_number��Sign_out_number������¼�û���¼�ǳ�����
		WritePrivateProfileStringA(User->ID, "Sign_in_number", "0", ".\\User_File.ini");
		WritePrivateProfileStringA(User->ID, "Sign_out_number", "0", ".\\User_File.ini");
		//��¼�û�ע����Ϣ
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, "Sign_up", str2, ".\\User_File.ini");

		break;
	case 2://sign_in
		int number=GetPrivateProfileIntA(User->ID, "Sign_in_number", 0, ".\\User_File.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "Sign In No.%d", ++number);
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, str1, str2, ".\\User_File.ini");
		break;
	case 3://sign_out
		int number = GetPrivateProfileIntA(User->ID, "Sign_out_number", 0, ".\\User_File.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "Sign Out No.%d", ++number);
		memset(str2, 0, sizeof(str2));
		sprintf(str2, "%d - %d - %d  %d : 00 : 00", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
		WritePrivateProfileStringA(User->ID, str1, str2, ".\\User_File.ini");
		break;
	default:
		break;
	}

}

void Write_route_file()
{

}

void Write_system_file()
{

}