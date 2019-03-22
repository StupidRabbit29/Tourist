#include"main.h"
#include<windows.h>
#include<process.h>




int System_Time = 0;
extern bool Quit;

unsigned __stdcall time(void* pArguments)
{
	while (Quit == false)
	{
		Sleep(10000);
		System_Time++;
	}
	_endthreadex(0);
	return 0;
}