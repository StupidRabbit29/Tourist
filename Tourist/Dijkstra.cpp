#include"main.h"

extern GRAPH city_graph;

char *Vehicle_Name[3] = { "����", "��", "�ɻ�" };

/*ջ��һЩ����*/
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


/*Dijkstra�����������յ㼴�ɻ�����·����
����path�������ڱ���·����path��СΪMAX_NODE_NUM��һ��������main.h��ĳ������������ս��Ϊ����
	ע�⣬path�ڱ�����ǽڵ㣨�ص㣩�ı�ţ������Ҫ��ӡ������Ҫ������������
ͼΪȫ�ֱ��������õ����������룬����dijkstra֮ǰ���ʼ��ͼʹ��ÿ������Ψһȷ����Ȩ�ء�
*/
Status Dijkstra(int src, int dest ,int path[])
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
		if (city_graph.pp_G[src][i].weight < INFINITE) //�� ��src���ı߸�ֵ
		{
			dist[i] = city_graph.pp_G[src][i].weight;
			path[i] = src;
		}
		else //????
		{
			dist[i] = INFINITE;//��dist����Ԫ�س�ʼ��Ϊ����;��δ����¼�ģ�dist[v]Ϊ��㵽Դ�����̾���
			path[i] = -1;//��path����Ԫ�س�ʼ��Ϊ-1��path����Ԫ��Ϊ��㵽�ڵ�i��·������һ���ڵ�
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
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
			if (collected[W] == false)
			{
				if (dist[V] + city_graph.pp_G[V][W].weight < dist[W])//���V��W��һ���� ����W�ڵ�δ����¼��path��
				{
					dist[W] = dist[V] + city_graph.pp_G[V][W].weight;//��㵽W�ľ��������㵽W�ľ���+VW�ߵľ���
					path[W] = V;//·����W����һ���ڵ���V
				}
			}
		}
	}


	/*��·����Ϊ����ģ�ջ��*/

	/*���յ㿪ʼ������·��ѹ��ջ*/
	V = dest;
	SqStack stack;
	Init_Stack(&stack);
	Push(&stack, V);
	while (path[V] != -1)
	{
		Push(&stack, path[V]);
		V = path[V];
	}

	/*��ջ���õ�����*/
	int i=0;
	while (stack.base != stack.top)//ջ�ǿ�
	{
		Pop(&stack, path[i]);//?????
		++i;
	}

	return OK;
}