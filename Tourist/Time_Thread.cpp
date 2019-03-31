#include"main.h"
#include<windows.h>
#include<process.h>




SYSTEM_TIME System_Time;
extern bool Quit;

unsigned __stdcall time(void* pArguments)
{
	System_Time.year = 2019;
	System_Time.month = 3;
	System_Time.date = 23;
	System_Time.hour = 0;
	while (Quit == false)
	{
		Sleep(10000);
		System_Time.hour++;
		if (System_Time.hour == 24)
		{
			System_Time.date++;
			System_Time.hour = 0;
		}
		if (System_Time.date == 31)//让我们假设每个月都30天
		{
			System_Time.month++;
			System_Time.date = 1;
		}
		if (System_Time.month == 13)
		{
			System_Time.year++;
			System_Time.month = 1;
		}
	}
	/*写需要保存的系统状态*/

	_endthreadex(0);
	return 0;
}