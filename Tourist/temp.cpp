#include"main.h"

extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

Status Init_Stack(SqStack *s);
Status Push(SqStack *s, int data);
Status Pop(SqStack *s, int &data);


Status Dijkstra_For_Min_Time(int src, int dest, int start_time, int& time)
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };
	int dist[MAX_NODE_NUM];

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist��path����
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		int min = INFINITE;
		int number = 0;
		Ptr_TransTable_NODE temp = city_graph.pp_G[src][i].p_TransTable;
		while (i != src&&temp)
		{
			if (temp->time_departure >= start_time)
				if (temp->time_departure - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure - start_time + temp->time_consumed;
					number = temp->number;
				}

			if (temp->time_departure < start_time)
				if (temp->time_departure + 24 - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure + 24 - start_time + temp->time_consumed;
					number = temp->number;
				}

			temp = temp->nextPtr;
		}

		if (min < INFINITE) //�� ��src���ı߸�ֵ
			dist[i] = min;
		else 
			dist[i] = INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���					   
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (!collected[dest])
	{
		/*��¼δ��¼������dist��С��*/
		mindist = INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//����dist���飬�ҵ�dist��С�Ľڵ�
		{
			if (collected[V] == false)
			{
				if (dist[V] < mindist)
				{
					mindist = dist[V];
					minV = V;
				}
			}
		}

		if (minV == -1) break;//�������Ķ��㲻���ڣ�break������¼���ж����ͼ����ͨ��

		V = minV;//��¼����Сdist����
		collected[V] = true;

		/*����dist��path*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false && city_graph.pp_G[V][W].p_TransTable)
			{
				int min = INFINITE;
				int number = 0;
				Ptr_TransTable_NODE temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)//����V��W�����н�ͨ��ʽ��Ѱ��ʱ����̵�һ��
				{
					if (temp->time_departure >= (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24)
					//�ÿͿ��Ե���V�ĵ��ճ���
						if (temp->time_departure - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed < min)
						{
							//����ʱ����̣�ˢ��
							min = temp->time_departure - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}

					if (temp->time_departure < (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24)
					//�ÿ���Ҫ�ڶ������
						if (temp->time_departure + 24 - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed < min)
						{
							//����ʱ����̣�ˢ��
							min = temp->time_departure + 24 - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}
					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//���V��W��һ���� ����W�ڵ�δ����¼��path��
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
			}
		}
	}
	time = dist[dest];

	return OK;
}