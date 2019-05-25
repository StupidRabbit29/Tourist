#include"main.h"
#include<windows.h>
#include<process.h>

extern FILE *fptr_input;
extern SYSTEM_TIME System_Time;
extern int Travelstate[10];
extern PASSENGER *Passengers;
void Min_Cost();
Status Min_Time();

void Change_User_Info(PASSENGER &psg)
{
	/*在修改前是否需要输出旅客当前状态？？*/

	//判断旅客是否到达终点
	
	fprintf(fptr_input, "ID：%s  更改旅行计划\n", psg.ID);//用户输入写入input.txt文件
	
	//判断旅客位置
	if (psg.status.loca == STAY_IN_CITY)
	{
		psg.src = psg.status.src;/*修改起点为目前城市*/
		psg.start_time = System_Time;
		WritePrivateProfileSectionA(psg.ID, "", ".\\User_Route.ini");
	}
	else if(psg.status.loca != ARRIVE)
	{
		psg.src = psg.status.dest;

		PASSENGER *temp = Passengers;
		int touristnum = 0;
		while (temp != NULL)
		{
			if (temp == &psg)
				break;

			touristnum++;
			temp = temp->next_passenger;
		}

		char str1[10]={'\0'};
		sprintf(str1, "No.%d", Travelstate[touristnum]);
		PathNode cur;

		GetPrivateProfileStructA(psg.ID, str1, &cur, sizeof(PathNode), ".\\User_Route.ini");

		int hours = cur.time-(System_Time-cur.start_time);

		psg.start_time = System_Time + hours;

		WritePrivateProfileSectionA(psg.ID, "", ".\\User_Route.ini");
		memset(str1, 0, sizeof(str1));
		sprintf(str1, "No.1");
		WritePrivateProfileStructA(psg.ID, str1, &cur, sizeof(PathNode), ".\\User_Route.ini");

		Travelstate[touristnum] = 1;
	}
	else
		psg.src = psg.status.dest;

	/*修改旅客信息及策略*/
	int choice;
	cout << "是否更改终点（Y=1/N=0）：";
	scanf_s("%d",&choice);
	bool Get = false;
	while (!Get)
	{
		if (choice == 1)
		{
			cout << "请输入终点编号：";
			scanf_s("%d", &psg.dest);
			if (psg.src == psg.dest)
				cout << "终点不能与起点相同！\n";
			else
				Get = true;
			fprintf(fptr_input, "终点编号：%d\n", psg.dest);//用户输入写入input.txt文件
		}
		else
		{
			if (psg.src == psg.dest)
			{
				cout << "终点与起点相同，必须输入终点！\n";
				choice = 1;
			}
			else
				Get = true;
		}

	}

	cout << "是否更改途经城市（Y=1/N=0）：";
	scanf_s("%d", &choice);
	for (int i = 0; i < MAX_NODE_NUM; i++)
		psg.pass_by[0][i] = psg.pass_by[1][i] = -1;

	if (choice == 1)
	{
		printf("请输入途经城市数量：");
		//cout << "";
		int cnt = 0, i;
		scanf_s("%d", &cnt);
		psg.num_passby = cnt;
		fprintf(fptr_input, "途经城市数量：%d\n途经城市编号：", cnt);//用户输入写入input.txt文件
		printf("请输入途经城市编号：");
		//cout << "";
		int stay_in_city = -1;
		bool stay = false;
		for (i = 0; i < cnt; i++)
		{
			scanf_s("%d", &psg.pass_by[0][i]);
			fprintf(fptr_input, "%d ", psg.pass_by[0][i]);//用户输入写入input.txt文件
			printf("是否需要在该地停留（Y=1/N=0）：");
			//cout << "";
			scanf_s("%d", &stay_in_city);
			if (stay_in_city == 1)
			{
				printf("请输入停留时间（单位：小时）：");
				//cout << "";
				scanf_s("%d", &psg.pass_by[1][i]);
			}
			else
				psg.pass_by[1][i] = 0;
		}
	}
	else
		psg.num_passby = 0;

	//printf("是否更改旅行策略（Y=1/N=0）：");
	cout << "是否更改旅行策略（Y=1/N=0）：";
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		//printf("请输入旅行策略编号：");
		cout << "请输入旅行策略编号：";
		scanf_s("%d", &psg.strategy);
		fprintf(fptr_input, "\n旅行策略编号：%d\n", psg.strategy);//用户输入写入input.txt文件
	}

	if (choice == 1 && psg.strategy == STRA_limTIME_minCOST)
	{
		//printf("请输入限制时间：");
		cout << "请输入限制时间：";
		scanf_s("%d", &psg.Time_Limited);
		fprintf(fptr_input, "限制时间：%d\n\n", psg.Time_Limited);//用户输入写入input.txt文件
	}

	/*根据策略，旅客当前位置，终点，途经城市重算路径并覆盖。*/
		/*计算路径*/
	cout << "**********计算路径************" << endl;
	switch (psg.strategy)
	{
	case 0:
		Min_Cost();
		break;
	case 1:
		Min_Time();
		break;
	case 2:
		Min_Time_Limited_Time();
		break;
	default:
		break;
	}
	cout << " Change_User_Info() done " << endl;
}