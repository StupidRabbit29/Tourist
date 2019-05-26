#include"main.h"
#include<windows.h>
#include<process.h>

bool Quit = false;//退出系统
extern SYSTEM_TIME System_Time;

int main()
{
	//准备函数
	if (Prepare() != OK)
		cout << "Function Prepare ERROR" << endl;

	//创建mouse_thread线程和time_thread线程
	HANDLE time_thread = (HANDLE)_beginthreadex(NULL, 0, time, NULL, 0, NULL);
	HANDLE mouse_thread = (HANDLE)_beginthreadex(NULL, 0, mouse, NULL, 0, NULL);

	//等待线程关闭信号，退出线程
	WaitForSingleObject(mouse_thread, MY_INFINITE);
	CloseHandle(mouse_thread);
	//等待线程关闭信号，退出线程
	WaitForSingleObject(time_thread, MY_INFINITE);
	CloseHandle(time_thread);

	cout << "Program End" << endl;
	system("pause");

	return 0;
}