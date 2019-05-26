#include"main.h"
//准备函数，读取地图函数，读取航班表函数，时间线程函数

/*全局变量*/
GRAPH city_graph = { NULL, 0, NULL };//地图
FILE *fptr_input;//日志文件，记录用户输入信息
extern PASSENGER *Passengers;
extern SYSTEM_TIME System_Time;

Status Prepare(void)
{
	if (DEBUG)
		cout << "Called Prepare()" << endl;

	//恢复上次关闭的系统
	char ch;
	printf("是否恢复上次打开的系统？Y（打开旧系统）/N（打开新系统）\n");
	scanf("%c", &ch);
	while (ch != 'Y' && ch != 'N')
	{
		printf("输入错误，请输入Y或N。\n");
		scanf("%c", &ch);
	}

	//判断是否正确读取到了内存
	if (ch == 'Y')
	{
		if (Read_system_file() == UNABLE)
			printf("读取存档失败！创建新系统\n");
	}
	else
	{
		System_Time.year = 2019;
		System_Time.month = 3;
		System_Time.date = 23;
		System_Time.hour = 0;
	}

	//读取地图
	FILE *fmap;
	fopen_s(&fmap, "map.txt", "r");
	if (fmap == NULL)
		cout << "Open file map.txt ERROR!" << endl;
	else
	{
		if (Read_Map(fmap) == ERROR)
		{
			printf("读取地图错误\n");
			return ERROR;
		}
	}

	fopen_s(&fptr_input, "User_input.txt", "w");

	//读取航班表
	Read_trans_t();

	/*打开：日志文档2-用户输入信息*/
	//fptr_input = fopen("log_file_input", "w");//只能写 

	return OK;
}

//读取地图信息（城市名称，连通性，距离）
Status Read_Map(FILE *fptr)
{
	if (DEBUG)
		cout << "Called Read_Map(FILE *fptr)" << endl;

	//读取城市数目
	fscanf(fptr, "%d", &city_graph.Graph_size);
	if (DEBUG)
		cout << "Get Graph_size" << endl;
	fgetc(fptr);
	if (city_graph.Graph_size == 0 || city_graph.Graph_size < MIN_NODE_NUM)
		return ERROR;

	//动态申请城市名称数组
	city_graph.City_Name = (char**)malloc(sizeof(char*)*city_graph.Graph_size);
	if (city_graph.City_Name == NULL)
		return ERROR;

	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		city_graph.City_Name[i] = new char[20];
		if (city_graph.City_Name[i] != NULL)
			memset(city_graph.City_Name[i], 0, 20);
		else
			return ERROR;
	}
	
	//读取城市名称
	int i = 0, j = 0;
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		fscanf(fptr, "%s", city_graph.City_Name[i]);
		fgetc(fptr);
	}
	if (DEBUG)
		cout << "Get city names" << endl;

	//申请城市地图的邻接矩阵
	city_graph.pp_G = (EDGE**)malloc(sizeof(EDGE*)*city_graph.Graph_size);
	if (city_graph.pp_G == NULL)
		return ERROR;
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		city_graph.pp_G[i] = (EDGE*)malloc(sizeof(EDGE)*city_graph.Graph_size);
		if (city_graph.pp_G[i] == NULL)
			return ERROR;
	}
	if (DEBUG)
		cout << "Initialize edges" << endl;

	//读取任意两个城市间的距离
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		for (j = 0; j < city_graph.Graph_size; j++)
		{
			city_graph.pp_G[i][j].p_TransTable = NULL;
			fscanf(fptr, "%d", &city_graph.pp_G[i][j].distance);
		}
	}
	if (DEBUG)
		cout << "Get city distance" << endl;

	//关闭城市文件
	fclose(fptr);
	return OK;
}

//释放内存
void Freememory(void)
{
	if (DEBUG)
		cout << "Called Freememory" << endl;

	Ptr_trans_t_Node temp = NULL;

	//释放所有城市的航班表
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		for (int j = 0; j < city_graph.Graph_size; j++)
		{
			temp = city_graph.pp_G[i][j].p_TransTable;
			while (temp != NULL)
			{
				Ptr_trans_t_Node pre = temp;
				temp = temp->nextPtr;
				free(pre);
			}
		}
	}

	//释放地图的边结点
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		free(city_graph.pp_G[i]);
	}
	free(city_graph.pp_G);

	//释放城市名称
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		free(city_graph.City_Name[i]);
	}
	free(city_graph.City_Name);

	//释放所有旅客的信息
	PASSENGER *tempp=Passengers;
	while (tempp != NULL)
	{
		PASSENGER *pre = tempp;
		tempp = tempp->next_passenger;
		free(pre);
	}

	cout << "Free memory successfully" << endl;
}