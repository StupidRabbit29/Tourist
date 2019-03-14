#include"main.h"
#include<string.h>

/*外部变量*/
extern PASSENGER *Passengers;
extern PASSENGER *User;

void Write_status_file(FILE *fptr);
void Change_User_Info(PASSENGER &psg);
void Write_user_file(FILE *fptr, int choice);


/*函数*/

//用户登录
Status User_sign_in(void)
{
	Write_user_file(User->fptr_user, 1);
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
					Write_user_file(User->fptr_user, 3);
					Output_Status();
				}
				else
				{
					//旅客退出
					Write_user_file(User->fptr_user, 2);
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

Status Output_Status(void)
{
	Write_status_file(stdout);

	return OK;
}