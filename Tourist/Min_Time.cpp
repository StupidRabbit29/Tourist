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
			
			if(temp->time_departure < start_time)
				if (temp->time_departure + 24 - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure +24 - start_time + temp->time_consumed;
					number = temp->number;
				}

			temp = temp->nextPtr;
		}

		if (min < INFINITE) //将 从src出的边赋值
		{
			dist[i] = min;
			//path[i][0] = src;
			//path[i][1] = number;
		}
		else //????
		{
			dist[i] = INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
			//path[i][0] = -1;//将path数组元素初始化为-1，path数组元素为起点到节点i的路径的上一个节点
		}
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
			if (collected[W] == false&&city_graph.pp_G[V][W].p_TransTable)
			{
				int min = INFINITE;
				int number = 0;
				Ptr_TransTable_NODE temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)
				{
					if (temp->time_departure >= (dist[V]%24+start_time)%24)
						if (temp->time_departure - (dist[V] % 24 + start_time) % 24 + temp->time_consumed < min)
						{
							min = temp->time_departure - (dist[V] % 24 + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}

					if(temp->time_departure < (dist[V] % 24 + start_time) % 24)
						if (temp->time_departure +24 - (dist[V] % 24 + start_time) % 24 + temp->time_consumed < min)
						{
							min = temp->time_departure+24 - (dist[V] % 24 + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}
					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//如果V到W有一条边 并且W节点未被收录到path中
				{
					dist[W] = dist[V] + min;//起点到W的距离等于起点到W的距离+VW边的距离
					//path[W][0] = V;//路径中W的上一个节点是V
					//path[W][1] = number;
				}
			}
		}
	}
	time = dist[dest];

	return OK;
}

Status Dijkstra_For_Min_Time(int src, int dest, int start_time, int path[][2], int& time)
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
		{
			dist[i] = min;
			path[i][0] = src;
			path[i][1] = number;
		}
		else //????
		{
			dist[i] = INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
			path[i][0] = -1;//将path数组元素初始化为-1，path数组元素为起点到节点i的路径的上一个节点
		}
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
				while (temp)
				{
					if (temp->time_departure >= (dist[V] % 24 + start_time) % 24)
						if (temp->time_departure - (dist[V] % 24 + start_time) % 24 + temp->time_consumed < min)
						{
							min = temp->time_departure - (dist[V] % 24 + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}

					if (temp->time_departure < (dist[V] % 24 + start_time) % 24)
						if (temp->time_departure + 24 - (dist[V] % 24 + start_time) % 24 + temp->time_consumed < min)
						{
							min = temp->time_departure + 24 - (dist[V] % 24 + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}
					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//如果V到W有一条边 并且W节点未被收录到path中
				{
					dist[W] = dist[V] + min;//起点到W的距离等于起点到W的距离+VW边的距离
					path[W][0] = V;//路径中W的上一个节点是V
					path[W][1] = number;
				}
			}
		}
	}
	time = dist[dest];

	/*把路径变为正序的（栈）*/

	/*从终点开始把逆序路径压入栈*/
	int V = dest;
	SqStack stack;
	Init_Stack(&stack);
	Push(&stack, V);
	while (path[V][0] != -1)
	{
		Push(&stack, path[V][0]);
		V = path[V][0];
	}

	/*弹栈，得到正序*/
	int i = 0;
	while (stack.base != stack.top)//栈非空
	{
		Pop(&stack, path[i][0]);//?????
		++i;
	}

	return OK;
}

void Permutation(int k, int n, int a[], int **A)
{
	static int count = 0;
	if (k == n - 1)
	{
		for (int i = 0; i < n; i++)
			A[count][i+1] = a[i];
		//cout << a[i] << " ";
		//cout << endl;

		count++;
	}
	else
	{
		for (int i = k; i < n; i++)
		{
			int temp = a[i];
			a[i] = a[k];
			a[k] = temp;

			Permutation(k + 1, n, a, A);

			temp = a[i];
			a[i] = a[k];
			a[k] = temp;
		}
	}
}

Status Min_Time()
{
	int path_number = 1;
	int pcity_num = User->num_passby;
	for (int i = 2; i <= User->num_passby; i++)
		path_number *= i;

	int **Path = new int*[path_number];
	for (int i = 0; i < path_number; i++)
	{
		Path[i] = new int[User->num_passby + 2]{ 0 };
		Path[i][0] = User->src;
		Path[i][User->num_passby + 1] = User->dest;
	}

	Permutation(0, pcity_num, User->pass_by[0], Path);

	int mintimepath = 0;
	int mintime = INFINITE;
	for (int i = 0; i < path_number; i++)
	{
		int alltime = 0;
		int tempstarttime = User->start_time;
		for (int j = 0; j < pcity_num + 1; j++)
		{
			int temptime = 0;
			Dijkstra_For_Min_Time(Path[i][j], Path[i][j + 1], tempstarttime, temptime);
			alltime += temptime;
			tempstarttime = (User->start_time + alltime) % 24;
		}

		if (alltime < mintime)
		{
			mintime = alltime;
			mintimepath = i;
		}
	}

	//int(*Finalpath)[2] = new int[2 * MAX_NODE_NUM][2];


	



}