#include"main.h"

extern GRAPH city_graph;
int path_t[MAX_NODE_NUM], dist_t[MAX_NODE_NUM];//dist即为weight，即time_consumed

void Init_Graph_Min_Time()//遍历整个图，将其边初的权重始化
{
	int min_time, num_of_the_MinTimeEdge;
	TransTable_NODE *currentPtr;
	for (int row = 0; row < city_graph.Graph_size; row++)//有向图！不可只遍历半个二维数组
	{
		for (int col = 0; col < city_graph.Graph_size; col++)
		{
			min_time = INFINITE;
			num_of_the_MinTimeEdge = NOT_EXIST;
			/*遍历链表里的每一个节点*/
			for (currentPtr = city_graph.pp_G[row][col].p_TransTable;
				currentPtr != NULL; //此处可判定边是否存在？？
				currentPtr = city_graph.pp_G[row][col].p_TransTable->nextPtr)
			{
				if (city_graph.pp_G[row][col].p_TransTable->time_consumed < min_time)
				{
					min_time = city_graph.pp_G[row][col].p_TransTable->time_consumed;
					num_of_the_MinTimeEdge = city_graph.pp_G[row][col].p_TransTable->number;
				}
			}
			/*更新边的信息*/
			city_graph.pp_G[row][col].weight = min_time;
			city_graph.pp_G[row][col].num_OfTheEgde = num_of_the_MinTimeEdge;
		}
	}
}


Status Dijkstra_Mintime_consumed(int src, int dest)//参数由旅客信息获得。
{
	/*初始化*/
	bool collected[MAX_NODE_NUM] = { false };

	//收录起点src
	dist_t[src] = 0;
	collected[src] = true;

	//初始化dist_t和path_t数组
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (city_graph.pp_G[src][i].weight < INFINITE) //将 从src出的边赋值
		{
			dist_t[i] = city_graph.pp_G[src][i].weight;
			path_t[i] = src;
		}
		else //????
		{
			dist_t[i] = INFINITE;//将dist_t数组元素初始化为无穷;对未被收录的，dist_t[v]为起点到源点的最短距离
			path_t[i] = -1;//将path_t数组元素初始化为-1，path_t数组元素为起点到节点i的路径的上一个节点
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
	{
		/*收录未收录顶点中dist_t最小者*/
		mindist = INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//遍历dist_t数组，找到dist最小的节点
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

		if (minV == -1) break;//若这样的顶点不存在，break（已收录所有顶点或图不连通）

		V = minV;//收录该最小dist顶点
		collected[V] = true;

		/*更新dist_t和path_t*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false)
			{
				if (dist_t[V] + city_graph.pp_G[V][W].weight < dist_t[W])//如果V到W有一条边 并且W节点未被收录到path_t中
				{
					dist_t[W] = dist_t[V] + city_graph.pp_G[V][W].weight;//起点到W的距离等于起点到W的距离+VW边的距离
					path_t[W] = V;//路径中W的上一个节点是V
				}
			}
		}
	}
	return OK;
}