#include"main.h"
//׼����������ȡ��ͼ��������ȡ���������ʱ���̺߳���

/*ȫ�ֱ���*/
GRAPH city_graph = { NULL, 0, NULL };

/*����*/
//��ȡ��ͼ��Ϣ���������ƣ���ͨ�ԣ����룩
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