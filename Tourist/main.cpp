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
	Prepare();//准备函数

	//创建mouse_thread线程和time_thread线程
	HANDLE mouse_thread = (HANDLE)_beginthreadex(NULL, 0, mouse, NULL, 0, NULL);
	HANDLE time_thread = (HANDLE)_beginthreadex(NULL, 0, time, NULL, 0, NULL);

	//等待线程关闭信号，退出线程
	WaitForSingleObject(mouse_thread, INFINITE);
	CloseHandle(mouse_thread);
	//等待线程关闭信号，退出线程
	WaitForSingleObject(time_thread, INFINITE);
	CloseHandle(time_thread);

	system("pause");
	return 0;
}