#include"main.h"

extern int countP;
extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

//��������������м�����·��
Status Dijkstra_For_Min_Cost_Limited_Time(int src, int dest, int& cost)
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };//���Ƿ�ȷ����̾���
	int dist[MAX_NODE_NUM];//�����е����ľ���

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist����
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (i == src)
			continue;

		int min = MY_INFINITE;
		//�����������м�ĺ�����ҵ�����ͨ�з�ʽ
		Ptr_trans_t_Node temp = city_graph.pp_G[src][i].p_TransTable;
		while (temp)
		{
			if (temp->cost < min)
				min = temp->cost;
			
			temp = temp->nextPtr;
		}

		if (min < MY_INFINITE) //�� ��src���ı߸�ֵ
			dist[i] = min;
		else
			dist[i] = MY_INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���

	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (!collected[dest])
	{
		/*��¼δ��¼������dist��С��*/
		mindist = MY_INFINITE;
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
				int min = MY_INFINITE;
				Ptr_trans_t_Node temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)//����V��W�����н�ͨ��ʽ��Ѱ��ʱ����̵�һ��
				{
					if (temp->cost < min)
						min = temp->cost;

					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//���V��W��һ�����̵ı� ����W�ڵ�δ����¼��path��
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
			}
		}
	}
	cost = dist[dest];

	return OK;
}

//��������������м�����·�������أ���¼·��
Status Dijkstra_For_Min_Cost_Limited_Time(int src, int dest, PATH& tourend, int& cost)
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };//���Ƿ�ȷ����̾���
	int dist[MAX_NODE_NUM];//�����е����ľ���
	int path[MAX_NODE_NUM][2];//path[0]����У���¼·��, path[1]�治ͬ���м�����г���

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist��path����
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (i == src)
			continue;

		int min = MY_INFINITE;
		int number = 0;
		//�����������м�ĺ�����ҵ�����ͨ�з�ʽ
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

		if (min < MY_INFINITE) //�� ��src���ı߸�ֵ
		{
			dist[i] = min;
			path[i][0] = src;
			path[i][1] = number;
		}
		else
		{
			dist[i] = MY_INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���
			path[i][0] = -1;//��path����Ԫ�س�ʼ��Ϊ-1��path����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (!collected[dest])
	{
		/*��¼δ��¼������dist��С��*/
		mindist = MY_INFINITE;
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
				int min = MY_INFINITE;
				int number = 0;
				Ptr_trans_t_Node temp = city_graph.pp_G[V][W].p_TransTable;
				while (temp)//����V��W�����н�ͨ��ʽ��Ѱ��ʱ����̵�һ��
				{
					if (temp->cost < min)
					{
						min = temp->cost;
						number = temp->number;
					}

					temp = temp->nextPtr;
				}

				if (dist[V] + min < dist[W])//���V��W��һ�����̵ı� ����W�ڵ�δ����¼��path��
				{
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path[W][0] = V;//·����W����һ���ڵ���V
					path[W][1] = number;
				}
			}
		}
	}
	cost = dist[dest];

	V = dest;

	PATH next = NULL;
	//�����α���ӵ��ÿ͵�������·��
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

//�ÿ�����ʱ����С�������в���
Status Min_Time_Limited_Time()
{
	//ȷ��·������
	int path_number = 1;
	int pcity_num = User->num_passby;
	for (int i = 2; i <= pcity_num; i++)
		path_number *= i;

	//��ʼ��·��
	int **Path = NULL;
	Path = new int*[path_number];
	for (int i = 0; i < path_number; i++)
	{
		Path[i] = new int[User->num_passby + 2]{ 0 };
		Path[i][0] = User->src;
		Path[i][User->num_passby + 1] = User->dest;
	}

	countP = 0;
	//ͨ��ȫ���У���������·��
	Permutation(0, pcity_num, User->pass_by[0], Path);

	//����������ٵ�·��
	int mincostpath = 0;
	int mincost = MY_INFINITE;
	//�������е�����·�����
	for (int i = 0; i < path_number; i++)
	{
		int allcost = 0;
		for (int j = 0; j < pcity_num + 1; j++)
		{
			int tempcost = 0;
			//��ÿ��·��������ʱ��
			Dijkstra_For_Min_Cost_Limited_Time(Path[i][j], Path[i][j + 1], tempcost);
			allcost += tempcost;
		}

		if (allcost < mincost)
		{
			mincost = allcost;
			mincostpath = i;
		}
	}

	//�ҵ�����·�ߺ�����Dijkstra��¼·�ߣ�ʹ������洢·��
	PATH tour = NULL;
	PATH tourend = tour;

	int allcost = 0;

	for (int i = 0; i < pcity_num + 1; i++)
	{
		int tempcost = 0;
		//�ֶ�ȷ��·��
		Dijkstra_For_Min_Cost_Limited_Time(Path[mincostpath][i], Path[mincostpath][i + 1], tour == NULL ? tour : tourend, tempcost);
		allcost += tempcost;

		if (tourend == NULL)
			tourend = tour;
		while (tourend->next != NULL)
			tourend = tourend->next;
	}

	//��ȫ·�������е�����
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