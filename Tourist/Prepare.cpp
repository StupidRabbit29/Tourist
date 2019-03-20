#include"main.h"
//׼����������ȡ��ͼ��������ȡ���������ʱ���̺߳���

/*ȫ�ֱ���*/
GRAPH city_graph = { NULL, 0, NULL };

/*����*/
Status Prepare(void)
{
	//�ָ��ϴιرյ�ϵͳ
	//���ļ�
	//��ȡ��ͼ������
	return OK;
}

//��ȡ��ͼ��Ϣ���������ƣ���ͨ�ԣ����룩
Status Read_Map(FILE *fptr)
{
	//��ȡ������Ŀ
	fscanf(fptr, "%d", &city_graph.Graph_size);
	fgetc(fptr);
	if (city_graph.Graph_size == 0 || city_graph.Graph_size < MIN_NODE_NUM)
		return ERROR;

	//��̬���������������
	city_graph.City_Name = (char**)malloc(sizeof(char*)*city_graph.Graph_size);
	if (city_graph.City_Name == NULL)
		return ERROR;

	//��ȡ��������
	int i = 0, j = 0;
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		fscanf(fptr, "%s", &city_graph.City_Name[i]);
		fgetc(fptr);
	}

	//������е�ͼ���ڽӾ���
	city_graph.pp_G = (EDGE**)malloc(sizeof(EDGE*)*city_graph.Graph_size);
	if (city_graph.pp_G == NULL)
		return ERROR;
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		city_graph.pp_G[i] = (EDGE*)malloc(sizeof(EDGE)*city_graph.Graph_size);
		if (city_graph.pp_G[i] == NULL)
			return ERROR;
	}

	//��ȡ�����������м�ľ���
	for (i = 0; i < city_graph.Graph_size; i++)
	{
		for (j = 0; j < city_graph.Graph_size; j++)
		{
			fscanf(fptr, "%d", &city_graph.pp_G[i][j].distance);
		}
	}

	//�رճ����ļ�
	fclose(fptr);
	return OK;
}