#include"main.h"

extern int countP;
extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

//计算给定两个城市间的最短路径
Status Dijkstra_For_Min_Cost_Limited_Time(int src, int dest, int& cost)
{
	/*初始化*/
	bool collected[MAX_NODE_NUM] = { false };//点是否被确认最短距离
	int dist[MAX_NODE_NUM];//各城市到起点的距离

	//收录起点src
	dist[src] = 0;
	collected[src] = true;

	//初始化dist数组
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (i == src)
			continue;

		int min = MY_INFINITE;
		//遍历两个城市间的航班表，找到最快的通行方式
		Ptr_trans_t_Node temp = city_graph.pp_G[src][i].p_TransTable;
		while (temp)
		{
			if (temp->cost < min)
				min = temp->cost;
			
			temp = temp->nextPtr;
		}

		if (min < MY_INFINITE) //将 从src出的边赋值
			dist[i] = min;
		else
			dist[i] = MY_INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离

	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (!collected[dest])
	{
		/*收录未收录顶点中dist最小者*/
		mindist = MY_INFINITE;
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
				int min = MY_INFINITE;
				Ptr_trans_t_Node temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)//遍历V到W的所有交通方式，寻找时间最短的一种
				{
					if (temp->cost < min)
						min = temp->cost;

					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//如果V到W有一条更短的边 并且W节点未被收录到path中
					dist[W] = dist[V] + min;//起点到W的距离等于起点到W的距离+VW边的距离
			}
		}
	}
	cost = dist[dest];

	return OK;
}

//计算给定两个城市间的最短路径，重载，记录路径
Status Dijkstra_For_Min_Cost_Limited_Time(int src, int dest, PATH& tourend, int& cost)
{
	/*初始化*/
	bool collected[MAX_NODE_NUM] = { false };//点是否被确认最短距离
	int dist[MAX_NODE_NUM];//各城市到起点的距离
	int path[MAX_NODE_NUM][2];//path[0]存城市，记录路径, path[1]存不同城市间的旅行车次

	//收录起点src
	dist[src] = 0;
	collected[src] = true;

	//初始化dist和path数组
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (i == src)
			continue;

		int min = MY_INFINITE;
		int number = 0;
		//遍历两个城市间的航班表，找到最快的通行方式
		Ptr_trans_t_Node temp = city_graph.pp_G[src][i].p_TransTable;
		int Passtime = pass_by_time(src);
		while (temp)
		{
			if (temp->cost < min)
			{
				min = temp->cost;
				number = temp->number;
			}

			temp = temp->nextPtr;
		}

		if (min < MY_INFINITE) //将 从src出的边赋值
		{
			dist[i] = min;
			path[i][0] = src;
			path[i][1] = number;
		}
		else
		{
			dist[i] = MY_INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
			path[i][0] = -1;//将path数组元素初始化为-1，path数组元素为起点到节点i的路径的上一个节点
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (!collected[dest])
	{
		/*收录未收录顶点中dist最小者*/
		mindist = MY_INFINITE;
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
				int min = MY_INFINITE;
				int number = 0;
				Ptr_trans_t_Node temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)//遍历V到W的所有交通方式，寻找时间最短的一种
				{
					if (temp->cost < min)
					{
						min = temp->cost;
						number = temp->number;
					}

					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//如果V到W有一条更短的边 并且W节点未被收录到path中
				{
					dist[W] = dist[V] + min;//起点到W的距离等于起点到W的距离+VW边的距离
					path[W][0] = V;//路径中W的上一个节点是V
					path[W][1] = number;
				}
			}
		}
	}
	cost = dist[dest];

	V = dest;

	PATH next = NULL;
	//将各段边添加到旅客的旅行线路中
	while (V != src)
	{
		PATH temp = new PathNode;

		temp->dest = V;
		temp->src = path[V][0];
		temp->number = path[V][1];

		if (tourend != NULL)
		{
			temp->next = tourend->next;
			tourend->next = temp;
		}
		else
		{
			temp->next = next;
			next = temp;
		}

		V = path[V][0];
	}

	if (tourend == NULL)
		tourend = next;

	return OK;
}

int Calculate_Time(PATH tour)
{
	PATH temp = tour;
	while (temp->next != NULL)
		temp = temp->next;
	
	//返回旅程花费的总时间
	return (temp->start_time - User->start_time) + temp->time;
}
int Calculate_Cost(PATH tour)
{
	int cost = 0;
	PATH temp = tour;
	while (temp != NULL)
	{
		cost += temp->cost;
		temp = temp->next;
	}

	return cost;
}

Status Limited_Time(PATH tour)
{
	//初始化变量
	int pcity_num = User->num_passby;
	Ptr_trans_t_Node *citynode = new Ptr_trans_t_Node[pcity_num + 1];
	bool *Fastest = new bool[pcity_num + 1]{ false };
	//int start_time = User->start_time.hour;

	PATH temp = tour;
	for (int i = 0; i < pcity_num + 1; i++)
	{
		citynode[i] = city_graph.pp_G[temp->src][temp->dest].p_TransTable;
		temp = temp->next;
	}

	//将旅程中的旅行结点逐渐替换为更快的旅行方式
	int time = Calculate_Time(tour);

	if (time <= User->Time_Limited)
		return ERROR;

	while (true)
	{
		int salve = MY_INFINITE;//本次替换可节省的时间
		PATH changenode = NULL;//本次替换的结点
		PATH pre = NULL;//前一结点
		Ptr_trans_t_Node before = NULL;//替换前的交通工具
		Ptr_trans_t_Node now = NULL;//替换后的交通工具
		int start_time;

		//寻找替换结点
		temp = tour;
		int i = 0;
		
		//遍历所有路段
		while (temp != NULL)
		{
			if (Fastest[i] == false)
			{
				int cost = 0;//本路段原花费
				int mincost = MY_INFINITE;//比原花费大的最小花费
				start_time = (pre == NULL ? User->start_time.hour : (pre->start_time.hour + pre->time)%24);
				int time;
				if(pre==NULL)//本路段耗时
					time = (temp->start_time - User->start_time) + temp->time;
				else
					time = (temp->start_time - pre->start_time) + temp->time - pre->time;
				Ptr_trans_t_Node ttemp = citynode[i];//遍历交通工具用
				Ptr_trans_t_Node beforenode;//替换前的交通工具
				Ptr_trans_t_Node changeto = NULL;//将要替换为的交通工具
				//找到原交通工具
				while (true)
				{
					if (ttemp->number != temp->number)
						ttemp = ttemp->nextPtr;
					else
					{
						beforenode = ttemp;
						ttemp = citynode[i];
						break;
					}
				}
				cost = beforenode->cost;

				//逐个查看可选交通工具，是否更快，且价格增长较小
				int passtime = pass_by_time(temp->src);
				while (ttemp != NULL)
				{
					if (ttemp->number != temp->number && ttemp->cost <= mincost && ttemp->cost >= cost)
					{
						if (ttemp->time_departure >= (start_time+passtime)%24)
							//当日出发
						{
							if (ttemp->time_departure - (start_time + passtime) % 24 + ttemp->time_consumed + passtime< time)
							{
								changeto = ttemp;
								mincost = ttemp->cost;
								//time = ttemp->time_departure - (pre == NULL ? start_time : (pre->start_time.hour + pre->time)) + ttemp->time_consumed + passtime;
							}
						}
						else
							//次日出发
						{
							if (ttemp->time_departure + 24 - (start_time + passtime) % 24 + ttemp->time_consumed + passtime< time)
							{
								changeto = ttemp;
								mincost = ttemp->cost;
								//time = ttemp->time_departure + 24 - (pre == NULL ? start_time : (pre->start_time.hour + pre->time)) + ttemp->time_consumed + passtime;
							}
						}
					}

					ttemp = ttemp->nextPtr;
				}
				//暂存可能替换的结点的信息
				if (changeto != NULL && changeto != beforenode)
				{
					if (salve > changeto->cost - beforenode->cost)
					{
						salve = changeto->cost - beforenode->cost;
						changenode = temp;
						before = beforenode;
						now = changeto;
					}
				}

				if (changeto == NULL)
					Fastest[i] = true;
			}

			pre = temp;
			temp = temp->next;
			i++;
		}

		//替换
		if (now != NULL)
		{
			changenode->number = now->number;
			Finish_Path(tour);
		}
		
		//计算时间是否合格
		int time = Calculate_Time(tour);

		if (time <= User->Time_Limited)
			break;

		//处理Fastest
		bool finish = true;
		for (int i = 0; i < pcity_num + 1; i++)
			if (Fastest[i] == false)
				finish = false;

		if (finish == true)
		{
			cout << "未找到路线！" << endl;
			break;
		}
	}

	return OK;
}

//旅客限制时间最小花费旅行策略
Status Min_Time_Limited_Time()
{
	//确定路线数量
	int path_number = 1;
	int pcity_num = User->num_passby;
	for (int i = 2; i <= pcity_num; i++)
		path_number *= i;

	//初始化路线
	int **Path = NULL;
	Path = new int*[path_number];
	for (int i = 0; i < path_number; i++)
	{
		Path[i] = new int[User->num_passby + 2]{ 0 };
		Path[i][0] = User->src;
		Path[i][User->num_passby + 1] = User->dest;
	}

	countP = 0;
	//通过全排列，生成所有路线
	Permutation(0, pcity_num, User->pass_by[0], Path);

	//求出花费最少的路线
	int mincostpath = 0;
	int mincost = MY_INFINITE;
	//遍历所有的旅行路线求解
	for (int i = 0; i < path_number; i++)
	{
		int allcost = 0;
		for (int j = 0; j < pcity_num + 1; j++)
		{
			int tempcost = 0;
			//对每条路线逐段求解时间
			Dijkstra_For_Min_Cost_Limited_Time(Path[i][j], Path[i][j + 1], tempcost);
			allcost += tempcost;
		}

		if (allcost < mincost)
		{
			mincost = allcost;
			mincostpath = i;
		}
	}

	//找到最快的路线后，重用Dijkstra记录路线，使用链表存储路线
	PATH tour = NULL;
	PATH tourend = tour;

	int allcost = 0;

	for (int i = 0; i < pcity_num + 1; i++)
	{
		int tempcost = 0;
		//分段确定路线
		Dijkstra_For_Min_Cost_Limited_Time(Path[mincostpath][i], Path[mincostpath][i + 1], tour == NULL ? tour : tourend, tempcost);
		allcost += tempcost;

		if (tourend == NULL)
			tourend = tour;
		while (tourend->next != NULL)
			tourend = tourend->next;
	}

	//补全路线链表中的内容
	Finish_Path(tour);

	if (Calculate_Time(tour) > User->Time_Limited)
		Limited_Time(tour);

	cout << "旅途总时长：" << Calculate_Time(tour) << endl
		<< "旅途总花费：" << Calculate_Cost(tour) << endl;

	Output_route(tour);
	Write_route_file(tour);

	for (int i = 0; i < path_number; i++)
		delete[]Path[i];
	delete[]Path;

	while (tour != NULL)
	{
		PATH cur = tour;
		tour = tour->next;
		delete cur;
	}
	return OK;
}