#include"main.h"

/*ȫ�ֱ�������  ��ʱ��������ļ���*/
extern GRAPH city_graph;
extern PASSENGER *User;//User��ǰϵͳʹ����
//dist��Ϊweight������˵��cost

Status Dijkstra(int src, int dest, int path[]);

void Init_Graph_MinCost()//��������ͼ������߳���Ȩ��ʼ��
{
	int min_cost,num_of_the_MinCostEdge;
	TransTable_NODE *currentPtr;
	for (int row = 0; row < city_graph.Graph_size; row++)//����ͼ������ֻ���������ά����
	{
		for (int col = 0; col < city_graph.Graph_size; col++)
		{
			min_cost = INFINITE;
			num_of_the_MinCostEdge = NOT_EXIST;
			/*�����������ÿһ���ڵ�*/
			for (currentPtr = city_graph.pp_G[row][col].p_TransTable;
				currentPtr != NULL; //�˴����ж����Ƿ���ڣ���
				currentPtr= city_graph.pp_G[row][col].p_TransTable->nextPtr)
			{
				if (city_graph.pp_G[row][col].p_TransTable->cost < min_cost)
				{
					min_cost = city_graph.pp_G[row][col].p_TransTable->cost;
					num_of_the_MinCostEdge = city_graph.pp_G[row][col].p_TransTable->number;
				}
			}
			/*���±ߵ���Ϣ*/
			city_graph.pp_G[row][col].weight = min_cost;
			city_graph.pp_G[row][col].num_OfTheEgde = num_of_the_MinCostEdge;
		}
	}
}
Status Min_Cost()
{
	//�ж���Ҫ�������м�ڵ�����Ƿ����0
	if (User->num_passby == 0)//Ϊ0ֱ��dijkstra
	{
		int path[MAX_NODE_NUM];
		Dijkstra(User->src, User->dest, path);
	}
	else//Ҫ�������м�ڵ������Ϊ0
	{
		//ͼ��ȫ��ͨ��ʡ���ж���ͨ��

		/*��㵽ȫ���м�ڵ��dijkstra*/
		for (int i = 0; i < User->num_passby; i++)
		{

		}



		/*ȫ�����м�ڵ�*/
		/*ÿ������Ҫ��һ�������·������һ��ָ�������������Ҫ����·���ܳ�����������*/


		/*�м�ڵ�ᾭ����ε������鲻����*/
	}
}
void perm()


















//Status Dijkstra_MinCost(int src, int dest)
//{
//	/*��ʼ��*/
//	bool collected[MAX_NODE_NUM] = { false };
//
//	//��¼���src
//	dist_c[src] = 0;
//	collected[src] = true;
//	
//	//��ʼ��dist_c��path_c����
//	for (int i = 0; i < city_graph.Graph_size; i++)
//	{
//		if (city_graph.pp_G[src][i].weight < INFINITE ) //�� ��src���ı߸�ֵ
//		{
//			dist_c[i] = city_graph.pp_G[src][i].weight;
//			path_c[i] = src;
//		}
//		else //????
//		{
//			dist_c[i] = INFINITE;//��dist_c����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist_c[v]Ϊ��㵽Դ�����̾���
//			path_c[i] = -1;//��path_c����Ԫ�س�ʼ��Ϊ-1��path_c����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
//		}
//	}
//
//	/*Dijkstra*/
//	int V = src;
//	int minV, mindist;
//	while (1)
//	{
//		/*��¼δ��¼������dist_c��С��*/
//		mindist = INFINITE;
//		minV = -1;
//		for (int V = 0; V < city_graph.Graph_size; V++)//����dist_c���飬�ҵ�dist��С�Ľڵ�
//		{
//			if (collected[V] == false)
//			{
//				if (dist_c[V] < mindist)
//				{
//					mindist = dist_c[V];
//					minV = V;
//				}
//			}
//		}
//
//		if (minV == -1) break;//�������Ķ��㲻���ڣ�break������¼���ж����ͼ����ͨ��
//
//		V = minV;//��¼����Сdist����
//		collected[V] = true;
//
//		/*����dist_c��path_c*/
//		for (int W = 0; W < city_graph.Graph_size; W++)
//		{
//			if (collected[W] == false)
//			{
//				if (dist_c[V] + city_graph.pp_G[V][W].weight < dist_c[W])//���V��W��һ���� ����W�ڵ�δ����¼��path_c��
//				{
//					dist_c[W] = dist_c[V] + city_graph.pp_G[V][W].weight;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
//					path_c[W] = V;//·����W����һ���ڵ���V
//				}
//			}
//		}
//	}
//	return OK;
//}