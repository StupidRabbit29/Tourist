#include"main.h"
#include<string.h>

/*外部变量*/
extern PASSENGER *Passengers;
extern PASSENGER *User;
extern SYSTEM_TIME System_Time;
extern GRAPH city_graph;

void Change_User_Info(PASSENGER &psg);
void Write_user_file(int choice);


/*函数*/

//用户登录
Status User_sign_in(void)
{
	Write_user_file(2);
	//读取用户输入的ID
	char userID[20];
	gets_s(userID);
	getchar();
	bool find_passenger = false;

	//使用temp遍历旅客链表
	PASSENGER *temp = Passengers;

	//寻找与用户输入ID匹配的旅客
	while (temp != NULL && !find_passenger)
	{
		if (strcmp(userID, temp->ID) != 0)
		{
			temp = temp->next_passenger;
		}
		else
		{
			User = temp;
			find_passenger = true;
		}
	}

	//用户不存在，需要重新输入ID
	if (find_passenger == false)
	{
		printf("用户不存在！请重新输入ID！\n");
		User_sign_in();
	}
	else//用户进行下一步操作
	{
		//输出提示信息
		printf("请选择您要进行的操作:\n");
		printf("修改旅行方案（输入1）\n");
		printf("查询旅程状态（输入2）\n");
		printf("退出登录    （输入3）\n");

		int choice = 0;
		bool choice_correct = false;

		//读取正确输入，决定下一步操作
		while (choice_correct == false)
		{
			scanf("%d", &choice);
			getchar();
			if (choice == 1 || choice == 2 || choice == 3)
			{
				if (choice == 1)
				{
					//调用调整旅行方案的函数
					Change_User_Info(*User);
				}
				else if (choice == 2)
				{
					//调用打印旅客信息的函数

					Output_Status(User);
				}
				else
				{
					//旅客退出
					Write_user_file(3);
					User = NULL;
				}

				choice_correct = true;
			}
			else
			{
				printf("输入不符合要求，请重新输入：\n");
				choice = 0;
			}
		}
	}
		
	return OK;
}

Status Output_Status(PASSENGER *psg)
{
	char *loca[4] = { "CAR", "TRAIN", "AIRPLANE", "STAY_IN_CITY" };
	char str2[100] = { '\0' };

	printf("旅客：【%s】", psg->ID);
	printf("时间：%d - %d - %d  %d : 00 : 00\n", System_Time.year, System_Time.month, System_Time.date, System_Time.hour);
	printf("旅行状态：%s\n", loca[(int)(psg->status.loca)]);
	memset(str2, 0, sizeof(str2));
	sprintf(str2, "%s  ==》 %s", city_graph.City_Name[psg->status.src], city_graph.City_Name[psg->status.dest]);
	printf("地理位置：%s\n", str2);

	return OK;
}