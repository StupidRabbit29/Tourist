#include"main.h"
#include<windows.h>
#include<process.h>

SYSTEM_TIME System_Time;
extern bool Quit;
extern GRAPH city_graph;
extern PASSENGER *Passengers;

//�ٶ����10���ÿͣ�����ÿ���ÿ͵ĵ�ǰ���е��ĵڼ�������
int Travelstate[10] = { 0 };

Status Write_system_file();

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
		if (System_Time.date == 31)//�����Ǽ���ÿ���¶�30��
		{
			System_Time.month++;
			System_Time.date = 1;
		}
		if (System_Time.month == 13)
		{
			System_Time.year++;
			System_Time.month = 1;
		}

		//�������ÿ�ˢ��������״̬
		PASSENGER *temp = Passengers;
		int touristnum = 0;
		while (temp != NULL)
		{
			if (Travelstate[touristnum] != 0)
				Refresh(temp, touristnum);

			touristnum++;
			temp = temp->next_passenger;
		}

	}

	/*д��Ҫ�����ϵͳ״̬*/
	Write_system_file();

	_endthreadex(0);
	return 0;
}

bool operator<(const SYSTEM_TIME& A, const SYSTEM_TIME& B)
{
	if (A.year < B.year ||
		A.year == B.year&&A.month < B.month ||
		A.year == B.year&&A.month == B.month&&A.date < B.date ||
		A.year == B.year&&A.month == B.month&&A.date == B.date&&A.hour < B.hour)
		return true;
	else
		return false;
}

//ˢ���ÿ�״̬
Status Refresh(PASSENGER *tourist, int touristnum)
{
	PathNode cur;
	char filename[20] = { ".\\User_Route.ini" };
	char str1[100];
	bool RefreshOK = false;

	memset(str1, 0, sizeof(str1));
	sprintf(str1, "No.%d", Travelstate[touristnum]);
	GetPrivateProfileStructA(tourist->ID, str1, &cur, sizeof(PathNode), filename);

	while (!RefreshOK)
	{
		if (System_Time < cur.start_time)
			//�ÿ�ͣ���ڵ�ǰ����
		{
			tourist->status = { System_Time , STAY_IN_CITY , cur.src, cur.dest };
			RefreshOK = true;
		}
		else if ((System_Time.year - cur.start_time.year) * 360 * 24 + (System_Time.month - cur.start_time.month) * 30 * 24 +
			(System_Time.date - cur.start_time.date) * 24 + (System_Time.hour - cur.start_time.hour) <= cur.time)
			//�ÿͳ���ǰ����һ������
		{
			Ptr_TransTable_NODE trans = city_graph.pp_G[cur.src][cur.dest].p_TransTable;
			while (trans != NULL)
			{
				if (trans->number == cur.number)
					break;

				trans = trans->nextPtr;
			}

			tourist->status = { System_Time , (Location)trans->transport , cur.src, cur.dest};
			strcpy(tourist->status.name, trans->name);
			RefreshOK = true;
		}
		else
		{
			//�ж��Ƿ�ﵽ�յ�
			if (cur.dest == tourist->dest)
			{
				tourist->status= { System_Time , ARRIVE , cur.dest, cur.dest, 0 };
				Travelstate[touristnum] = 0;
				break;
			}

			//�ÿ��Ѿ����е�����һ������
			Travelstate[touristnum]++;
			memset(str1, 0, sizeof(str1));
			sprintf(str1, "No.%d", Travelstate[touristnum]);
			GetPrivateProfileStructA(tourist->ID, str1, &cur, sizeof(PathNode), filename);
		}
	}

	return OK;
}

