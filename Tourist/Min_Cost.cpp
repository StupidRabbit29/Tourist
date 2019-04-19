#include"main.h"

/*全局变量定义  暂时放在这个文件里*/
extern GRAPH city_graph;
extern PASSENGER *User;//User当前系统使用者
//dist即为weight，或者说是cost

void Write_route_file(PATH tour);
Status Output_route(PATH tour);
Status Finish_Path(PATH tour);

void Init_Graph_MinCost()//遍历整个图，将其边初的权重始化
{
	int min_cost, num_of_the_MinCostEdge;
	//trans_t_Node *currentPtr;
	struct trans_t *currentPtr;
	for (int row = 0; row < city_graph.Graph_size; row++)//有向图！不可只遍历半个二维数组
	{
		for (int col = 0; col < city_graph.Graph_size; col++)
		{
			min_cost = MY_INFINITE;
			num_of_the_MinCostEdge = NOT_EXIST;
			/*遍历链表里的每一个节点*/
			for (currentPtr = city_graph.pp_G[row][col].p_TransTable;
				currentPtr != NULL; //此处可判定边是否存在？？
				currentPtr = city_graph.pp_G[row][col].p_TransTable->nextPtr)
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


/*Dijkstra，传入起点和终点即可获得最短路径。
传入path容器用于保存路径，最终结果为正序。
	注意，path内保存的是节点的编号。
图为全局变量，不用当作参数传入，调用dijkstra之前请初始化图使其每条边有唯一确定的权重。
能算出最少花费是多少，用返回值返回。
*/
int Dijkstra_MinCost(const int src, const int dest, vector<int> &path)
{
	/*初始化*/
	/*bool collected[MAX_NODE_NUM] = { false };
	int dist[MAX_NODE_NUM];*/
	bitset<MAX_NODE_NUM> collected;//无参构造，长度为MAX_NODE_NUM，默认每一位为０
	vector<int> dist(city_graph.Graph_size);//dist和path是定长数组
	vector<int> path_temp(city_graph.Graph_size);

	//收录起点src
	dist[src] = 0;
	collected.set(src, true);

	//初始化dist和path_temp数组
	for (int i = 0; i < city_graph.Graph_size; i++)//G[src].size应该是节点个数
	{
		/*假设是有权有向图*/
		if (city_graph.pp_G[src][i].weight < MY_INFINITE) //将 从src出的边赋值
		{
			dist[i] = city_graph.pp_G[src][i].weight;
			path_temp[i] = src;
		}
		else //????
		{
			dist[i] = MY_INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
			path_temp[i] = -1;//将path_temp数组元素初始化为-1，path_temp数组元素为起点到节点i的路径的上一个节点
			//dist.insert(dist.begin() + i, MY_INFINITE);
			//path_temp.insert(path_temp.begin() + i, -1);
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
	{
		/*收录未收录顶点中dist最小者*/
		mindist = MY_INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//遍历dist数组，找到dist最小的节点
		{
			if (collected[V] == false)//bitset支持[]运算符，返回bool
			{
				if (dist[V] < mindist)
				{
					mindist = dist[V];
					minV = V;
				}
			}
		}

		if (collected[dest] == true) break;//若终点被收录，break/*不用算完整个图*/
		

		V = minV;//收录该最小dist顶点
		collected[V] = true;

		/*更新dist和path_temp*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false)
			{
				if (dist[V] + city_graph.pp_G[V][W].weight < dist[W])//如果V到W有一条边 并且W节点未被收录到path_temp中
				{
					dist[W] = dist[V] + city_graph.pp_G[V][W].weight;//起点到W的距离等于起点到W的距离+VW边的距离
					path_temp[W] = V;//路径中W的上一个节点是V
				}
			}
		}
	}


	/*把路径变为正序的（栈）*/

	/*从终点开始把逆序路径压入栈*/
	V = dest;
	stack<int> s;
	s.push(V);//终点压入栈
	while (path_temp.at(V) != -1)
	{
		s.push(path_temp.at(V));//V的上一个点压入栈
		V = path_temp.at(V);
	}

	/*弹栈，得到正序*/
	int i = 0, cost_count = 0, W;//WV为一条弧，W为弧尾，V为弧头，由弧尾指向弧头
	W = s.top();
	s.pop();//删除栈顶元素但不返回其值  
	path.push_back(W);//返回栈顶的元素，但不删除该元素  
	while (!s.empty())//栈非空
	{
		V = s.top();
		path.push_back(V);//返回栈顶的元素，但不删除该元素  
		cost_count += city_graph.pp_G[W][V].weight;
		W = V;
		s.pop();//删除栈顶元素但不返回其值  
		++i;
	}

	return cost_count;
}

void Min_Cost()
{
	if (DEBUG)
		cout << "Min_Cost() Called" << endl;
	//判断需要经过的中间节点个数是否等于0
	if (User->num_passby == 0)//为0直接dijkstra
	{
		vector<int> path(1);//0占位
		path.at(0) = Dijkstra_MinCost(User->src, User->dest, path);

		/*待改：调用函数将结果写入文件？*/
		/*改为链表*/
		PATH headptr = NULL, currentptr=NULL, tailptr=NULL;
		for (int col = 0; col < path.size()/*?*/; col++)//遍历cost最小的一行
		{
			currentptr = (PATH)malloc(sizeof(PathNode));
			currentptr->src = path.at(col);
			currentptr->dest = path.at(col + 1);
			currentptr->number = city_graph.pp_G[currentptr->src][currentptr->dest].num_OfTheEgde;//???
			currentptr->next = NULL;

			if (headptr == NULL)
			{
				headptr = currentptr;
				tailptr = currentptr;
			}
			else
			{
				tailptr->next = currentptr;
				tailptr = tailptr->next;
			}
		}

		//补全路线链表中的内容
		Finish_Path(headptr);

		Output_route(headptr);
		Write_route_file(headptr);

		/*释放链表*/
		while (headptr != NULL)
		{
			currentptr = headptr;
			headptr = headptr->next;
			free(currentptr);
		}
	}

	else//要经过的中间节点个数不为0
	{
		//图完全连通，省略判断连通性

		/*计算总共有多少条路径*/
		int path_count=1;
		for (int i = 2; i <= User->num_passby; i++)
		{
			path_count *= i;//阶乘
		}

		vector<vector<int>> all_path(path_count);//存放所有可能的路径//[0]存放总花费
		vector<int> passby(User->pass_by[0], User->pass_by[0] + User->num_passby);  //用数组初始化vector  //??可能出问题//?????????????

		//sort(passby.begin(), passby.end());//为了全排列

		/*对每一个排列，计算最短路径*/
		int counter = 0;
		for (sort(passby.begin(), passby.end());//为了全排列
			counter< path_count;//???可能出错
			counter++)
		{
			all_path[counter].push_back(0);//0号位存总花费，同时初始化为0

			/*起点到第一个中间节点*/
			all_path.at(counter).at(0) = Dijkstra_MinCost(User->src,passby[0] , all_path.at(counter));//第counter行

			//计算中间节点集
			for (int i = 0; i < passby.size() - 1; i++)
			{
				int tempint;
				tempint = Dijkstra_MinCost(passby[i], passby[i + 1], all_path.at(counter));
				all_path.at(counter).at(0) += tempint;
			}

			/*最后一个中间节点到终点*/
			int tempint;
			tempint = Dijkstra_MinCost(passby[passby.size() - 1], User->dest, all_path.at(counter));
			all_path.at(counter).at(0) += tempint;

			/*每个中间节点既会当终点又会当起点，会被存两遍*/
			unique(all_path.at(counter).begin(), all_path.at(counter).end());
			//size需要手动改
			for (int k = 0; k < User->num_passby; k++)
			{
				all_path.at(counter).erase(all_path.at(counter).end() - 1);
			}

			/*准备计算下个路径*/
			next_permutation(passby.begin(), passby.end());

		}

		/*找到cost最小的路径*/
		int min_cost = MY_INFINITE, min_row;
		for (int i = 0; i < path_count/*行数*/; i++)
		{
			if (all_path[i][0] < min_cost)
			{
				min_cost = all_path[i][0];
				min_row = i;
			}
		}

		/*待改：调用函数将结果写入文件？*/
		/*改为链表*/
		PATH headptr = NULL, currentptr = NULL, tailptr = NULL;
		for (int col = 0; col < all_path.at(min_row).size()/*?*/; col++)//遍历cost最小的一行
		{
			currentptr = (PATH)malloc(sizeof(PathNode));
			currentptr->src = all_path.at(min_row).at(col);
			currentptr->dest = all_path.at(min_row).at(col + 1);
			currentptr->number = city_graph.pp_G[currentptr->src][currentptr->dest].num_OfTheEgde;//???
			currentptr->next = NULL;

			if (headptr == NULL)
			{
				headptr = currentptr;
				tailptr = currentptr;
			}
			else
			{
				tailptr->next = currentptr;
				tailptr = tailptr->next;
			}
		}

		//补全路线链表中的内容
		Finish_Path(headptr);

		Output_route(headptr);
		Write_route_file(headptr);

		/*释放链表*/
		while( headptr != NULL)
		{
			currentptr = headptr;
			headptr = headptr->next;
			free(currentptr);
		}
	}
}