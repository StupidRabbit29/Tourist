#include"main.h"

/*全局变量定义  暂时放在这个文件里*/
extern GRAPH city_graph;
int path_c[MAX_NODE_NUM], dist_c[MAX_NODE_NUM];//dist即为weight，或者说是cost

void Init_Graph_MinCost()//遍历整个图，将其边初的权重始化
{
	int min_cost,num_of_the_MinCostEdge;
	TransTable_NODE *currentPtr;
	for (int row = 0; row < city_graph.Graph_size; row++)//有向图！不可只遍历半个二维数组
	{
		for (int col = 0; col < city_graph.Graph_size; col++)
		{
			min_cost = INFINITE;
			num_of_the_MinCostEdge = NOT_EXIST;
			/*遍历链表里的每一个节点*/
			for (currentPtr = city_graph.pp_G[row][col].p_TransTable;
				currentPtr != NULL; //此处可判定边是否存在？？
				currentPtr= city_graph.pp_G[row][col].p_TransTable->nextPtr)
			{
				if (city_graph.pp_G[row][col].p_TransTable->cost < min_cost)
				{
					min_cost = city_graph.pp_G[row][col].p_TransTable->cost;
					num_of_the_MinCostEdge = city_graph.pp_G[row][col].p_TransTable->number;
				}
			}
			/*更新边的信息*/
			city_graph.pp_G[row][col].weight = min_cost;
			city_graph.pp_G[row][col].num_OfTheEgde = num_of_the_MinCostEdge;
		}
	}
}


Status Dijkstra_MinCost(int src, int dest)
{
	/*初始化*/
	bool collected[MAX_NODE_NUM] = { false };

	//收录起点src
	dist_c[src] = 0;
	collected[src] = true;
	
	//初始化dist_c和path_c数组
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (city_graph.pp_G[src][i].weight < INFINITE ) //将 从src出的边赋值
		{
			dist_c[i] = city_graph.pp_G[src][i].weight;
			path_c[i] = src;
		}
		else //????
		{
			dist_c[i] = INFINITE;//将dist_c数组元素初始化为无穷;对未被收录的，dist_c[v]为起点到源点的最短距离
			path_c[i] = -1;//将path_c数组元素初始化为-1，path_c数组元素为起点到节点i的路径的上一个节点
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
	{
		/*收录未收录顶点中dist_c最小者*/
		mindist = INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//遍历dist_c数组，找到dist最小的节点
		{
			if (collected[V] == false)
			{
				if (dist_c[V] < mindist)
				{
					mindist = dist_c[V];
					minV = V;
				}
			}
		}

		if (minV == -1) break;//若这样的顶点不存在，break（已收录所有顶点或图不连通）

		V = minV;//收录该最小dist顶点
		collected[V] = true;

		/*更新dist_c和path_c*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false)
			{
				if (dist_c[V] + city_graph.pp_G[V][W].weight < dist_c[W])//如果V到W有一条边 并且W节点未被收录到path_c中
				{
					dist_c[W] = dist_c[V] + city_graph.pp_G[V][W].weight;//起点到W的距离等于起点到W的距离+VW边的距离
					path_c[W] = V;//路径中W的上一个节点是V
				}
			}
		}
	}
	return OK;
}