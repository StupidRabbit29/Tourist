#include"main.h"

extern GRAPH city_graph;

Status Dijkstra(int src, int dest ,int path[],int path_size)/*����path�������ڱ���·�������ս��Ϊ����*/
{
	/*��ʼ��*/
	bool collected[MAX_NODE_NUM] = { false };
	int dist[MAX_NODE_NUM];

	//��¼���src
	dist_c[src] = 0;
	collected[src] = true;

	//��ʼ��dist_c��path_c����
	for (int i = 0; i < city_graph.Graph_size; i++)
	{
		if (city_graph.pp_G[src][i].weight < INFINITE) //�� ��src���ı߸�ֵ
		{
			dist_c[i] = city_graph.pp_G[src][i].weight;
			path_c[i] = src;
		}
		else //????
		{
			dist_c[i] = INFINITE;//��dist_c����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist_c[v]Ϊ��㵽Դ�����̾���
			path_c[i] = -1;//��path_c����Ԫ�س�ʼ��Ϊ-1��path_c����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
	{
		/*��¼δ��¼������dist_c��С��*/
		mindist = INFINITE;
		minV = -1;
		for (int V = 0; V < city_graph.Graph_size; V++)//����dist_c���飬�ҵ�dist��С�Ľڵ�
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

		if (minV == -1) break;//�������Ķ��㲻���ڣ�break������¼���ж����ͼ����ͨ��

		V = minV;//��¼����Сdist����
		collected[V] = true;

		/*����dist_c��path_c*/
		for (int W = 0; W < city_graph.Graph_size; W++)
		{
			if (collected[W] == false)
			{
				if (dist_c[V] + city_graph.pp_G[V][W].weight < dist_c[W])//���V��W��һ���� ����W�ڵ�δ����¼��path_c��
				{
					dist_c[W] = dist_c[V] + city_graph.pp_G[V][W].weight;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path_c[W] = V;//·����W����һ���ڵ���V
				}
			}
		}
	}

	/*��·����Ϊ�����*/



	return OK;
}

//ʹ������ ����path���飿��
char *Vehicle_Name[3] = { "����", "��", "�ɻ�" };

SqStack *s;
Status Init_Stack(SqStack *s)
{
	s->base = (int*)malloc(sizeof(int)*MAX_NODE_NUM);
	if (s->base == NULL) exit(1);
	s->stack_size = MAX_NODE_NUM;
	s->top = s->base;
	return OK;
}
Status Push(SqStack *s, int data)
{
	if (s->top - s->base >= s->stack_size) return STACK_FULL;//����
	*s->top = data;
	s->top++;
	return OK;
}
Status Pop(SqStack *s, int &data)
{
	if (s->base == s->top) return STACK_EMPTY;
	s->top--;
	data = *s->top;
	return OK;
}


/*												���棡
���֮ǰͼ�ıߵ�Ψһȷ����Ȩ�ز��ܱ��ı�
��city_graph.pp_G[v1][v2].num_OfTheEgde�����иĶ�
��������ͬһ���߳����ٴε���min cost��min time�ļ�*/

extern GRAPH city_graph;
Status Output(int path[], int dist[], int src, int dest, int travel_strategy/*����ö�����͡�*/)//���Σ���������
{
	if (travel_strategy == STRA_minCOST)
		printf("�� %s�� %s�����ٻ���Ϊ��%dԪ\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
	else if (travel_strategy == STRA_minTIME)
		printf("�� %s�� %s��̺�ʱΪ��%dСʱ\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
	else if (travel_strategy == STRA_limTIME_minCOST)
		printf("�� %s�� %s������ʱ�����ٷ���Ϊ��\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
	/*�������else�������⣬�Ժ��*/


	/*��ӡ·����ջ��*/
	int V = dest;
	SqStack stack;
	Init_Stack(&stack);
	Push(&stack, V);
	while (path[V] != -1)
	{
		Push(&stack, path[V]);
		V = path[V];
	}
	printf("·���ǣ�\n");

	int v1, v2;
	Pop(&stack, v1);
	while (stack.base != stack.top)//ջ�ǿ�
	{
		Pop(&stack, v2);//?????

		//����һ���������ҵ����ͣ���㣬�յ�
		TransTable_NODE *currentPtr = NULL;
		int vehicle_num = city_graph.pp_G[v1][v2].num_OfTheEgde;
		for (currentPtr = city_graph.pp_G[v1][v2].p_TransTable;
			currentPtr != NULL || currentPtr->number != vehicle_num;//??????
			currentPtr = city_graph.pp_G[v1][v2].p_TransTable->nextPtr);
		/*ѭ���˳���currentPtrӦָ��ú��ࡣ*/

		/*��������ʱ�仹û����*/
		if (currentPtr->number == vehicle_num)
			printf("����%d��%s\t��%s����\t����%s\n", vehicle_num, Vehicle_Name[currentPtr->transport], currentPtr->src, currentPtr->dest);
		else return ERROR;
		v1 = v2;
	}

	return OK;
}