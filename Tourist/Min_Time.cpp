#include"main.h"

extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

void Write_route_file(PATH tour);
Status Output_route(PATH tour);

//��������������м�����·��
Status Dijkstra_For_Min_Time(int src, int dest, int start_time, int& time)
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };//���Ƿ�ȷ����̾���
	int dist[MAX_NODE_NUM];//�����е����ľ���

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist����
	for (int i = 0; i < city_graph.Graph_size&&i != src; i++)
	{
		int min = INFINITE;
		int number = 0;
		//�����������м�ĺ�����ҵ�����ͨ�з�ʽ
		Ptr_TransTable_NODE temp = city_graph.pp_G[src][i].p_TransTable;
		while (temp)
		{
			if (temp->time_departure >= start_time)
			//���ճ���
				if (temp->time_departure - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure - start_time + temp->time_consumed;
					number = temp->number;
				}
			
			if(temp->time_departure < start_time)
			//�ڶ������
				if (temp->time_departure + 24 - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure +24 - start_time + temp->time_consumed;
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

				if (dist[V] + min < dist[W])//���V��W��һ�����̵ı� ����W�ڵ�δ����¼��path��
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
			}
		}
	}
	time = dist[dest];

	return OK;
}

//��������������м�����·�������أ���¼·��
Status Dijkstra_For_Min_Time(int src, int dest, int start_time, PATH tourend, int& time)
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };//���Ƿ�ȷ����̾���
	int dist[MAX_NODE_NUM];//�����е����ľ���
	int path[MAX_NODE_NUM][2];//path[0]����У���¼·��, path[1]�治ͬ���м�����г���

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist��path����
	for (int i = 0; i < city_graph.Graph_size&&i!=src; i++)
	{
		int min = INFINITE;
		int number = 0;
		//�����������м�ĺ�����ҵ�����ͨ�з�ʽ
		Ptr_TransTable_NODE temp = city_graph.pp_G[src][i].p_TransTable;
		while (temp)
		{
			if (temp->time_departure >= start_time)
			//���ճ���
				if (temp->time_departure - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure - start_time + temp->time_consumed;
					number = temp->number;
				}

			if (temp->time_departure < start_time)
			//�ڶ������
				if (temp->time_departure + 24 - start_time + temp->time_consumed < min)
				{
					min = temp->time_departure + 24 - start_time + temp->time_consumed;
					number = temp->number;
				}

			temp = temp->nextPtr;
		}

		if (min < INFINITE) //�� ��src���ı߸�ֵ
		{
			dist[i] = min;
			path[i][0] = src;
			path[i][1] = number;
		}
		else
		{
			dist[i] = INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���
			path[i][0] = -1;//��path����Ԫ�س�ʼ��Ϊ-1��path����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
		}
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

				if (dist[V] + min < dist[W])//���V��W��һ�����̵ı� ����W�ڵ�δ����¼��path��
				{
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path[W][0] = V;//·����W����һ���ڵ���V
					path[W][1] = number;
				}
			}
		}
	}
	time = dist[dest];

	int V = dest;

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
			temp->next = NULL;
			tourend = temp;
		}

		V = path[V][0];
	}

	return OK;
}

//ȫ���У������ÿ�Ҫ;���Ľ�����ȫ���У��Ա��������
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

//��ȫ�ÿ�����·���еĿ�ȱ�������е�ǰ�����㣬�յ㣬��������֮�󣬼��ɵ��øú���
Status Finish_Path(PATH tour)
{
	PATH temp = tour;
	PATH pre = NULL;
	int arrive_pre = User->start_time.hour;
	while (temp != NULL)
	{
		//����������ҵ���Ӧ����
		Ptr_TransTable_NODE trans = city_graph.pp_G[temp->src][temp->dest].p_TransTable;
		while (trans != NULL)
		{
			if (trans->number == temp->number)
				break;
		}

		//����ڳ������еĵȴ�ʱ��
		int wait = 0;
		for (int i = 0; i < User->num_passby; i++)
			if (User->pass_by[0][i] == temp->src)
			{
				//arrive_pre += User->pass_by[1][i];
				wait = User->pass_by[1][i];
				break;
			}

		temp->start_time.hour = trans->time_departure;//�ÿͳ���ʱ��Ϊ��Ӧ��ͨ���߳���ʱ��
		temp->time = trans->time_consumed;//�ó̺ķ�ʱ����ڽ�ͨ���ߺ�ʱ
		//ȷ����������
		//int inter = pre->start_time.hour + pre->time + wait;
		if ((arrive_pre+wait)%24 > trans->time_departure)
		{
			//����������к�ڶ������
			if (temp == tour)
				temp->start_time.date = User->start_time.date + 1;
			else
			{
				temp->start_time.date = pre->start_time.date + 1;
				if (pre->time + wait > 24 - pre->start_time.hour)
					temp->start_time.date += (pre->start_time.hour + pre->time + wait) / 24;
			}
		}
		else
		{
			//����������к������
			if (temp == tour)
				temp->start_time.date = User->start_time.date;
			else
			{
				temp->start_time.date = pre->start_time.date;
				if (pre->time + wait > 24 - pre->start_time.hour)
					temp->start_time.date += (pre->start_time.hour + pre->time + wait) / 24;
			}
		}

		if (temp->start_time.date > 30)
		{
			temp->start_time.month = pre->start_time.month + 1;
			temp->start_time.date -= 30;
		}
		else
			temp->start_time.month = pre->start_time.month;

		if (temp->start_time.month > 12)
		{
			temp->start_time.year = pre->start_time.year + 1;
			temp->start_time.month -= 12;
		}
		else
			temp->start_time.year = pre->start_time.year;

		arrive_pre = (temp->start_time.hour + temp->time) % 24;

		pre = temp;
		temp = temp->next;
	}

	return OK;
}

//�ÿ����ʱ�����в���
Status Min_Time()
{
	//ȷ��·������
	int path_number = 1;
	int pcity_num = User->num_passby;
	for (int i = 2; i <= User->num_passby; i++)
		path_number *= i;

	//��ʼ��·��
	int **Path = new int*[path_number];
	for (int i = 0; i < path_number; i++)
	{
		Path[i] = new int[User->num_passby + 2]{ 0 };
		Path[i][0] = User->src;
		Path[i][User->num_passby + 1] = User->dest;
	}

	//ͨ��ȫ���У���������·��
	Permutation(0, pcity_num, User->pass_by[0], Path);

	//�����ʱ��̵�·��
	int mintimepath = 0;
	int mintime = INFINITE;
	//�������е�����·�����
	for (int i = 0; i < path_number; i++)
	{
		int alltime = 0;
		int tempstarttime = User->start_time.hour;
		for (int j = 0; j < pcity_num + 1; j++)
		{
			int temptime = 0;
			//��ÿ��·��������ʱ��
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

	//�ҵ�����·�ߺ�����Dijkstra��¼·�ߣ�ʹ������洢·��
	PATH tour = NULL;
	PATH tourend = tour;

	int alltime = 0;
	int tempstarttime = User->start_time.hour;

	for (int i = 0; i < pcity_num + 1; i++)
	{
		int temptime = 0;
		//�ֶ�ȷ��·��
		Dijkstra_For_Min_Time(Path[mintimepath][i], Path[mintimepath][i + 1], tempstarttime, tour==NULL?tour:tourend,  temptime);
		alltime += temptime;
		tempstarttime = (User->start_time.hour + alltime) % 24;
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
		delete tour;
	}
	return OK;
}

//����Ļ�ϴ�ӡ�ÿ͵�����·��
Status Output_route(PATH tour)
{
	int number = 0;
	PATH temp = tour;

	while (temp != NULL)
	{
		number++;
		Ptr_TransTable_NODE trans = city_graph.pp_G[temp->src][temp->dest].p_TransTable;
		while (trans != NULL)
		{
			if (trans->number == temp->number)
				break;

			trans = trans->nextPtr;
		}

		cout << "No." << number << " " << city_graph.City_Name[temp->src]
			<< "----->" << city_graph.City_Name[temp->dest] << " "
			<< trans->name << "  ����ʱ�䣺" << temp->start_time.year << "-" << temp->start_time.month
			<< "-" << temp->start_time.date << " " << temp->start_time.hour << ":00:00" << endl;

		temp = temp->next;
	}
}