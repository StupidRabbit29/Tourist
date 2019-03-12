#include"main.h"
//准备函数，读取地图函数，读取航班表函数，时间线程函数

/*全局变量*/
GRAPH city_graph = { NULL, 0, NULL };

/*函数*/
//读取地图信息（城市名称，连通性，距离）
Status Read_Map(GRAPH &map, FILE *fptr)
{
	fscanf(fptr, "%d", &map.Graph_size);
	if (map.Graph_size == 0 || map.Graph_size < MIN_NODE_NUM)
		return ERROR;

	map.City_Name = (char**)malloc(sizeof(char*)*map.Graph_size);
	if (map.City_Name == NULL)
		return ERROR;

	int i = 0;
	for (i = 0; i < map.Graph_size; i++)
	{
		fscanf(fptr, "%s", &map.City_Name[i]);
	}


}