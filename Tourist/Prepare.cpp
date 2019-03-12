#include"main.h"
//准备函数，读取地图函数，读取航班表函数，时间线程函数

/*全局变量*/
GRAPH city_graph = { NULL, 0, NULL };

/*函数*/
//读取地图信息（城市名称，连通性，距离）
Status Read_Map(GRAPH &map, FILE *fptr)
{
	//读取城市数目
	fscanf(fptr, "%d", &map.Graph_size);
	if (map.Graph_size == 0 || map.Graph_size < MIN_NODE_NUM)
		return ERROR;

	//动态申请城市名称数组
	map.City_Name = (char**)malloc(sizeof(char*)*map.Graph_size);
	if (map.City_Name == NULL)
		return ERROR;

	//读取城市名称
	int i = 0, j = 0;
	for (i = 0; i < map.Graph_size; i++)
	{
		fscanf(fptr, "%s", &map.City_Name[i]);
	}

	//申请城市地图的邻接矩阵
	map.pp_G = (EDGE**)malloc(sizeof(EDGE*)*map.Graph_size);
	if (map.pp_G == NULL)
		return ERROR;
	for (i = 0; i < map.Graph_size; i++)
	{
		map.pp_G[i] = (EDGE*)malloc(sizeof(EDGE)*map.Graph_size);
		if (map.pp_G[i] == NULL)
			return ERROR;
	}

	//读取任意两个城市间的距离
	for (i = 0; i < map.Graph_size; i++)
	{
		for (j = 0; j < map.Graph_size; j++)
		{
			fscanf(fptr, "%d", &map.pp_G[i][j].distance);
		}
	}

	//关闭城市文件
	fclose(fptr);
	return OK;
}