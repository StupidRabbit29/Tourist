#include"main.h"
//׼����������ȡ��ͼ��������ȡ���������ʱ���̺߳���

/*ȫ�ֱ���*/
GRAPH city_graph = { NULL, 0, NULL };

/*����*/
//��ȡ��ͼ��Ϣ���������ƣ���ͨ�ԣ����룩
Status Read_Map(GRAPH &map, FILE *fptr)
{
	//��ȡ������Ŀ
	fscanf(fptr, "%d", &map.Graph_size);
	if (map.Graph_size == 0 || map.Graph_size < MIN_NODE_NUM)
		return ERROR;

	//��̬���������������
	map.City_Name = (char**)malloc(sizeof(char*)*map.Graph_size);
	if (map.City_Name == NULL)
		return ERROR;

	//��ȡ��������
	int i = 0, j = 0;
	for (i = 0; i < map.Graph_size; i++)
	{
		fscanf(fptr, "%s", &map.City_Name[i]);
	}

	//������е�ͼ���ڽӾ���
	map.pp_G = (EDGE**)malloc(sizeof(EDGE*)*map.Graph_size);
	if (map.pp_G == NULL)
		return ERROR;
	for (i = 0; i < map.Graph_size; i++)
	{
		map.pp_G[i] = (EDGE*)malloc(sizeof(EDGE)*map.Graph_size);
		if (map.pp_G[i] == NULL)
			return ERROR;
	}

	//��ȡ�����������м�ľ���
	for (i = 0; i < map.Graph_size; i++)
	{
		for (j = 0; j < map.Graph_size; j++)
		{
			fscanf(fptr, "%d", &map.pp_G[i][j].distance);
		}
	}

	//�رճ����ļ�
	fclose(fptr);
	return OK;
}