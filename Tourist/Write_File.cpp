#include"main.h"
#include<windows.h>

extern PASSENGER *User;
extern FILE *fptr_user;

//д��״̬����
void Write_status_file(FILE *fptr)
{
	//��User��״̬�ṹ��д��fptrָ����ļ�
	
}

void Write_user_file(int choice)
{	
	char str[100] = { '\0' };

	switch (choice)
	{
	case 1://sign_up
		//���Sign_in_number��Sign_out_number������¼�û���¼�ǳ�����
		WritePrivateProfileStringA(User->ID, "Sign_in_number", "0", ".\\User_File.ini");
		WritePrivateProfileStringA(User->ID, "Sign_out_number", "0", ".\\User_File.ini");
		//��¼�û�ע����Ϣ
		WritePrivateProfileStringA(User->ID, "Sign_up", "", ".\\User_File.ini");

		break;
	case 2://sign_in
		int number=GetPrivateProfileIntA(User->ID, "Sign_in_number", 0, ".\\User_File.ini");
		memset(str, 0, sizeof(str));
		sprintf(str, "Sign In No.%d", ++number);
		WritePrivateProfileStringA(User->ID, str, "", ".\\User_File.ini");
		break;
	case 3://sign_out
		int number = GetPrivateProfileIntA(User->ID, "Sign_out_number", 0, ".\\User_File.ini");
		memset(str, 0, sizeof(str));
		sprintf(str, "Sign Out No.%d", ++number);
		WritePrivateProfileStringA(User->ID, str, "", ".\\User_File.ini");
		break;
	default:
		break;
	}


}

void Write_route_file()
{

}