#include"main.h"

extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

Status Init_Stack(SqStack *s);
Status Push(SqStack *s, int data);
Status Pop(SqStack *s, int &data);


Status Dijkstra_For_Min_Time(int src, int dest, int start_time, int& time)
{
	/*初始化*/
	bool collected[MAX_NODE_NUM] = { false };
	int dist[MAX_NODE_NUM];

	//收录起点src
	dist[src] = 0;
	collected[src] = true;

	//初始化dist和path数组
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

		if (min < INFINITE) //将 从src出的边赋值
			dist[i] = min;
		else 
			dist[i] = INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离					   
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (!collected[dest])
	{
		/*收录未收录顶点中dist最小者*/
		mindist = INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//遍历dist数组，找到dist最小的节点
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

		if (minV == -1) break;//若这样的顶点不存在，break（已收录所有顶点或图不连通）

		V = minV;//收录该最小dist顶点
		collected[V] = true;

		/*更新dist和path*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false && city_graph.pp_G[V][W].p_TransTable)
			{
				int min = INFINITE;
				int number = 0;
				Ptr_TransTable_NODE temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)//遍历V到W的所有交通方式，寻找时间最短的一种
				{
					if (temp->time_departure >= (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24)
					//旅客可以到达V的当日出发
						if (temp->time_departure - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed < min)
						{
							//旅行时间更短，刷新
							min = temp->time_departure - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}

					if (temp->time_departure < (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24)
					//旅客需要第二天出发
						if (temp->time_departure + 24 - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed < min)
						{
							//旅行时间更短，刷新
							min = temp->time_departure + 24 - (dist[V] % 24 + User->pass_by[1][V] + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}
					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//如果V到W有一条边 并且W节点未被收录到path中
					dist[W] = dist[V] + min;//起点到W的距离等于起点到W的距离+VW边的距离
			}
		}
	}
	time = dist[dest];

	return OK;
}