#include"main.h"
#include<windows.h>
#include<process.h>

bool Quit = false;
extern SYSTEM_TIME System_Time;

Status Prepare(void);
unsigned __stdcall mouse(void* pArguments);
unsigned __stdcall time(void* pArguments);

int main()
{
	Prepare();//׼������

	//����mouse_thread�̺߳�time_thread�߳�
	HANDLE mouse_thread = (HANDLE)_beginthreadex(NULL, 0, mouse, NULL, 0, NULL);
	HANDLE time_thread = (HANDLE)_beginthreadex(NULL, 0, time, NULL, 0, NULL);

	//�ȴ��̹߳ر��źţ��˳��߳�
	WaitForSingleObject(mouse_thread, INFINITE);
	CloseHandle(mouse_thread);
	//�ȴ��̹߳ر��źţ��˳��߳�
	WaitForSingleObject(time_thread, INFINITE);
	CloseHandle(time_thread);

	system("pause");
	return 0;
}