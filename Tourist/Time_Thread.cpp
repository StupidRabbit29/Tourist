#include"main.h"
#include<windows.h>
#include<process.h>






unsigned __stdcall time(void* pArguments)
{



	_endthreadex(0);
	return 0;
}