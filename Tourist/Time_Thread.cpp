#include"main.h"
#include<windows.h>
#include<process.h>




SYSTEM_TIME System_Time;
extern bool Quit;

unsigned __stdcall time(void* pArguments)
{
	System_Time.year = 2019;
	System_Time.mouth = 3;
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
		if (System_Time.date == 31)//�����Ǽ���ÿ���¶�30��
		{
			System_Time.mouth++;
			System_Time.date = 1;
		}
		if (System_Time.mouth == 13)
		{
			System_Time.year++;
			System_Time.mouth = 1;
		}
	}
	_endthreadex(0);
	return 0;
}