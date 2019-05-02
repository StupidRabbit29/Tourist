#include"main.h"

extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

void Write_route_file(PATH tour);
Status Output_route(PATH tour);
int pass_by_time(int V);

//计算给定两个城市间的最短路径
Status Dijkstra_For_Min_Time(int src, int dest, int start_time, int& time)
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
		int number = 0;
		//遍历两个城市间的航班表，找到最快的通行方式
		Ptr_trans_t_Node temp = city_graph.pp_G[src][i].p_TransTable;
		int Passtime = pass_by_time(src);
		while (temp)
		{
			if (temp->time_departure >= (start_time + Passtime) % 24)
			//当日出发
				if (temp->time_departure - (start_time + Passtime) % 24 + temp->time_consumed < min)
				{
					min = temp->time_departure - (start_time + Passtime) % 24 + temp->time_consumed;
					number = temp->number;
				}
			
			if(temp->time_departure < (start_time + Passtime) % 24)
			//第二天出发
				if (temp->time_departure + 24 - (start_time + Passtime) % 24 + temp->time_consumed < min)
				{
					min = temp->time_departure +24 - (start_time + Passtime) % 24 + temp->time_consumed;
					number = temp->number;
				}

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
		int  Passtime = pass_by_time(V);

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
					if (temp->time_departure >= (dist[V] % 24 + Passtime + start_time) % 24)
						//旅客可以到达V的当日出发
						if (temp->time_departure - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed < min)
						{
							//旅行时间更短，刷新
							min = temp->time_departure - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}

					if (temp->time_departure < (dist[V] % 24 + Passtime + start_time) % 24)
						//旅客需要第二天出发
						if (temp->time_departure + 24 - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed < min)
						{
							//旅行时间更短，刷新
							min = temp->time_departure + 24 - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}
					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//如果V到W有一条更短的边 并且W节点未被收录到path中
					dist[W] = dist[V] + min;//起点到W的距离等于起点到W的距离+VW边的距离
			}
		}
	}
	time = dist[dest];

	return OK;
}

//计算给定两个城市间的最短路径，重载，记录路径
Status Dijkstra_For_Min_Time(int src, int dest, int start_time, PATH& tourend, int& time)
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
			if (temp->time_departure >= (start_time + Passtime) % 24)
				//当日出发
				if (temp->time_departure - (start_time + Passtime) % 24 + temp->time_consumed < min)
				{
					min = temp->time_departure - (start_time + Passtime) % 24 + temp->time_consumed;
					number = temp->number;
				}

			if (temp->time_departure < (start_time + Passtime) % 24)
				//第二天出发
				if (temp->time_departure + 24 - (start_time + Passtime) % 24 + temp->time_consumed < min)
				{
					min = temp->time_departure + 24 - (start_time + Passtime) % 24 + temp->time_consumed;
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
		int  Passtime = pass_by_time(V);

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
					if (temp->time_departure >= (dist[V] % 24 + Passtime + start_time) % 24)
						//旅客可以到达V的当日出发
						if (temp->time_departure - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed < min)
						{
							//旅行时间更短，刷新
							min = temp->time_departure - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed;
							number = temp->number;
						}

					if (temp->time_departure < (dist[V] % 24 + Passtime + start_time) % 24)
						//旅客需要第二天出发
						if (temp->time_departure + 24 - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed < min)
						{
							//旅行时间更短，刷新
							min = temp->time_departure + 24 - (dist[V] % 24 + Passtime + start_time) % 24 + temp->time_consumed;
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
	time = dist[dest];

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

//全排列，对于旅客要途径的结点进行全排列，以便逐个遍历
void Permutation(int k, int n, int a[], int **A)
{
	static int count = 0;
	if (k == n - 1)
	{
		for (int i = 0; i < n; i++)
			A[count][i+1] = a[i];

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

//补全旅客旅行路线中的空缺，链表中的前三项，起点，终点，车次填完之后，即可调用该函数
Status Finish_Path(PATH tour)
{
	PATH temp = tour;
	PATH pre = NULL;
	int arrive_pre = User->start_time.hour;
	while (temp != NULL)
	{
		if (temp == tour)
			temp->start_time = User->start_time;
		else
			temp->start_time = pre->start_time;

		//遍历航班表，找到对应车次
		Ptr_trans_t_Node trans = city_graph.pp_G[temp->src][temp->dest].p_TransTable;
		while (trans != NULL)
		{
			if (trans->number == temp->number)
				break;
			else
				trans = trans->nextPtr;
		}

		//添加在出发城市的等待时间
		int wait = 0;
		for (int i = 0; i < User->num_passby; i++)
			if (User->pass_by[0][i] == temp->src)
			{
				//arrive_pre += User->pass_by[1][i];
				wait = User->pass_by[1][i];
				break;
			}

		temp->start_time.hour = trans->time_departure;//旅客出发时间为对应交通工具出发时间
		temp->time = trans->time_consumed;//旅程耗费时间等于交通工具耗时
		//确定出发日期
		//int inter = pre->start_time.hour + pre->time + wait;
		if ((arrive_pre+wait)%24 > trans->time_departure)
		{
			//到达出发城市后第二天出发
			if (temp == tour)
				temp->start_time.date += 1;
			else
			{
				temp->start_time.date += 1;
				if (pre->time + wait > 24 - pre->start_time.hour)
					temp->start_time.date += (pre->start_time.hour + pre->time + wait) / 24;
			}
		}
		else
		{
			//到达出发城市后当天出发
			if (temp != tour)
			{
				if (pre->time + wait > 24 - pre->start_time.hour)
					temp->start_time.date += (pre->start_time.hour + pre->time + wait) / 24;
			}
		}

		if (temp->start_time.date > 30)
		{
				temp->start_time.month += 1;
				temp->start_time.date -= 30;
		}

		if (temp->start_time.month > 12)
		{
				temp->start_time.year += 1;
				temp->start_time.month -= 12;	
		}

		arrive_pre = (temp->start_time.hour + temp->time) % 24;

		pre = temp;
		temp = temp->next;
	}

	return OK;
}

//旅客最短时间旅行策略
Status Min_Time()
{
	//确定路线数量
	int path_number = 1;
	int pcity_num = User->num_passby;
	for (int i = 2; i <= User->num_passby; i++)
		path_number *= i;

	//初始化路线
	int **Path= NULL;
	Path = new int*[path_number];
	for (int i = 0; i < path_number; i++)
	{
		Path[i] = new int[User->num_passby + 2]{ 0 };
		Path[i][0] = User->src;
		Path[i][User->num_passby + 1] = User->dest;
	}

	//通过全排列，生成所有路线
	Permutation(0, pcity_num, User->pass_by[0], Path);

	//求出耗时最短的路线
	int mintimepath = 0;
	int mintime = MY_INFINITE;
	//遍历所有的旅行路线求解
	for (int i = 0; i < path_number; i++)
	{
		int alltime = 0;
		int tempstarttime = User->start_time.hour;
		for (int j = 0; j < pcity_num + 1; j++)
		{
			int temptime = 0;
			//对每条路线逐段求解时间
			Dijkstra_For_Min_Time(Path[i][j], Path[i][j + 1], tempstarttime, temptime);
			alltime += temptime;
			tempstarttime = (User->start_time.hour + alltime) % 24;
		}

		if (alltime < mintime)
		{
			mintime = alltime;
			mintimepath = i;
		}
	}

	//找到最快的路线后，重用Dijkstra记录路线，使用链表存储路线
	PATH tour = NULL;
	PATH tourend = tour;

	int alltime = 0;
	int tempstarttime = User->start_time.hour;

	for (int i = 0; i < pcity_num + 1; i++)
	{
		int temptime = 0;
		//分段确定路线
		Dijkstra_For_Min_Time(Path[mintimepath][i], Path[mintimepath][i + 1], tempstarttime, tour==NULL?tour:tourend, temptime);
		alltime += temptime;
		tempstarttime = (User->start_time.hour + alltime) % 24;

		if (tourend == NULL)
			tourend = tour;
		while (tourend->next != NULL)
			tourend = tourend->next;
	}

	//补全路线链表中的内容
	Finish_Path(tour);
	
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

//在屏幕上打印旅客的旅行路线
Status Output_route(PATH tour)
{
	int number = 0;
	PATH temp = tour;

	while (temp != NULL)
	{
		number++;
		Ptr_trans_t_Node trans = city_graph.pp_G[temp->src][temp->dest].p_TransTable;
		while (trans != NULL)
		{
			if (trans->number == temp->number)
				break;

			trans = trans->nextPtr;
		}

		cout << "No." << number << " " << city_graph.City_Name[temp->src]
			<< "----->" << city_graph.City_Name[temp->dest] << " "
			<< trans->name << "  发车时间：" << temp->start_time.year << "-" << temp->start_time.month
			<< "-" << temp->start_time.date << " " << temp->start_time.hour << ":00:00" << endl;

		temp = temp->next;
	}

	return OK;
}


int pass_by_time(int V)
{
	for (int i = 0; i < User->num_passby; i++)
	{
		if (User->pass_by[0][i] == V)
		{
			return User->pass_by[1][i];
			break;
		}
	}

	return 0;
}