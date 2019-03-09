#include"main.h"

extern GRAPH city_graph;
int path_t[MAX_NODE_NUM], dist_t[MAX_NODE_NUM];//dist��Ϊweight����time_consumed

void Init_Graph_Min_Time()//��������ͼ������߳���Ȩ��ʼ��
{
	int min_time, num_of_the_MinTimeEdge;
	TransTable_NODE *currentPtr;
	for (int row = 0; row < city_graph.Graph_size; row++)//����ͼ������ֻ���������ά����
	{
		for (int col = 0; col < city_graph.Graph_size; col++)
		{
			min_time = INFINITE;
			num_of_the_MinTimeEdge = NOT_EXIST;
			/*�����������ÿһ���ڵ�*/
			for (currentPtr = city_graph.pp_G[row][col].p_TransTable;
				currentPtr != NULL; //�˴����ж����Ƿ���ڣ���
				currentPtr = city_graph.pp_G[row][col].p_TransTable->nextPtr)
			{
				if (city_graph.pp_G[row][col].p_TransTable->time_consumed < min_time)
				{
					min_time = city_graph.pp_G[row][col].p_TransTable->time_consumed;
					num_of_the_MinTimeEdge = city_graph.pp_G[row][col].p_TransTable->number;
				}
			}
			/*���±ߵ���Ϣ*/
			city_graph.pp_G[row][col].weight = min_time;
			city_graph.pp_G[row][col].num_OfTheEgde = num_of_the_MinTimeEdge;
		}
	}
}


Status Dijkstra_Mintime_consumed(int src, int dest)//�������ÿ���Ϣ��á�
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };

	//��¼���src
	dist_t[src] = 0;
	collected[src] = true;

	//��ʼ��dist_t��path_t����
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (city_graph.pp_G[src][i].weight < INFINITE) //�� ��src���ı߸�ֵ
		{
			dist_t[i] = city_graph.pp_G[src][i].weight;
			path_t[i] = src;
		}
		else //????
		{
			dist_t[i] = INFINITE;//��dist_t����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist_t[v]Ϊ��㵽Դ�����̾���
			path_t[i] = -1;//��path_t����Ԫ�س�ʼ��Ϊ-1��path_t����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
	{
		/*��¼δ��¼������dist_t��С��*/
		mindist = INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//����dist_t���飬�ҵ�dist��С�Ľڵ�
		{
			if (collected[V] == false)
			{
				if (dist_t[V] < mindist)
				{
					mindist = dist_t[V];
					minV = V;
				}
			}
		}

		if (minV == -1) break;//�������Ķ��㲻���ڣ�break������¼���ж����ͼ����ͨ��

		V = minV;//��¼����Сdist����
		collected[V] = true;

		/*����dist_t��path_t*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false)
			{
				if (dist_t[V] + city_graph.pp_G[V][W].weight < dist_t[W])//���V��W��һ���� ����W�ڵ�δ����¼��path_t��
				{
					dist_t[W] = dist_t[V] + city_graph.pp_G[V][W].weight;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path_t[W] = V;//·����W����һ���ڵ���V
				}
			}
		}
	}
	return OK;
}