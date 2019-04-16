#include"main.h"

extern GRAPH city_graph;
extern PASSENGER *User;
extern char *Vehicle_Name[3];

Status Init_Stack(SqStack *s);
Status Push(SqStack *s, int data);
Status Pop(SqStack *s, int &data);

Status Dijkstra_For_Min_Time(int src, int dest, int start_time, int& time)
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };
	int dist[MAX_NODE_NUM];

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist��path����
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

		if (min < INFINITE) //�� ��src���ı߸�ֵ
		{
			dist[i] = min;
			//path[i][0] = src;
			//path[i][1] = number;
		}
		else //????
		{
			dist[i] = INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���
			//path[i][0] = -1;//��path����Ԫ�س�ʼ��Ϊ-1��path����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
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

				if (dist[V] + min < dist[W])//���V��W��һ���� ����W�ڵ�δ����¼��path��
				{
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					//path[W][0] = V;//·����W����һ���ڵ���V
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
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };
	int dist[MAX_NODE_NUM];

	//��¼���src
	dist[src] = 0;
	collected[src] = true;

	//��ʼ��dist��path����
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

		if (min < INFINITE) //�� ��src���ı߸�ֵ
		{
			dist[i] = min;
			path[i][0] = src;
			path[i][1] = number;
		}
		else //????
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

				if (dist[V] + min < dist[W])//���V��W��һ���� ����W�ڵ�δ����¼��path��
				{
					dist[W] = dist[V] + min;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path[W][0] = V;//·����W����һ���ڵ���V
					path[W][1] = number;
				}
			}
		}
	}
	time = dist[dest];

	/*��·����Ϊ����ģ�ջ��*/

	/*���յ㿪ʼ������·��ѹ��ջ*/
	int V = dest;
	SqStack stack;
	Init_Stack(&stack);
	Push(&stack, V);
	while (path[V][0] != -1)
	{
		Push(&stack, path[V][0]);
		V = path[V][0];
	}

	/*��ջ���õ�����*/
	int i = 0;
	while (stack.base != stack.top)//ջ�ǿ�
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