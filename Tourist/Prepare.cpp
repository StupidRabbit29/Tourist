#include"main.h"
//准备函数，读取地图函数，读取航班表函数，时间线程函数

/*全局变量*/
GRAPH city_graph = { NULL, 0, NULL };

FILE *fptr_input;//日志文件，记录用户输入信息


/*函数*/
Status Prepare(void)
{
	//恢复上次关闭的系统

	/*打开：日志文档2-用户输入信息*/
	fptr_input = fopen("log_file_input", "w");//只能写

	//读取地图、航班
	FILE *fmap;
	fopen_s(&fmap, "map.txt", "r");
	if (Read_Map(fmap) == ERROR)
	{
		printf("读取地图错误\n");
		return ERROR;
	}
		 
	return OK;
}

//读取地图信息（城市名称，连通性，距离）
Status Read_Map(FILE *fptr)
{
	//读取城市数目
	fscanf(fptr, "%d", &city_graph.Graph_size);
	fgetc(fptr);
	if (city_graph.Graph_size == 0 || city_graph.Graph_size < MIN_NODE_NUM)
		return ERROR;

	//动态申请城市名称数组
	city_graph.City_Name = (char**)malloc(sizeof(char*)*city_graph.Graph_size);
	if (city_graph.City_Name == NULL)
		return ERROR;

	//读取城市名称
	int i = 0, j = 0;
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		fscanf(fptr, "%s", &city_graph.City_Name[i]);
		fgetc(fptr);
	}

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

	//读取任意两个城市间的距离
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		for (j = 0; j < city_graph.Graph_size; j++)
		{
			fscanf(fptr, "%d", &city_graph.pp_G[i][j].distance);
		}
	}

	//关闭城市文件
	fclose(fptr);
	return OK;
}