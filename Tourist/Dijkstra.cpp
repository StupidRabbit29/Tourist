#include"main.h"

extern GRAPH city_graph;

char *Vehicle_Name[3] = { "汽车", "火车", "飞机" };

/*栈的一些操作*/
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
	if (s->top - s->base >= s->stack_size) return STACK_FULL;//判满
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


/*Dijkstra，传入起点和终点即可获得最短路径。
传入path数组用于保存路径（path大小为MAX_NODE_NUM（一个定义在main.h里的常量）），最终结果为正序。
	注意，path内保存的是节点（地点）的编号（如果需要打印车次需要做其他处理）。
图为全局变量，不用当作参数传入，调用dijkstra之前请初始化图使其每条边有唯一确定的权重。
*/
Status Dijkstra(int src, int dest ,int path[])
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
		if (city_graph.pp_G[src][i].weight < INFINITE) //将 从src出的边赋值
		{
			dist[i] = city_graph.pp_G[src][i].weight;
			path[i] = src;
		}
		else //????
		{
			dist[i] = INFINITE;//将dist数组元素初始化为无穷;对未被收录的，dist[v]为起点到源点的最短距离
			path[i] = -1;//将path数组元素初始化为-1，path数组元素为起点到节点i的路径的上一个节点
		}
	}

	/*Dijkstra*/
	int V = src;
	int minV, mindist;
	while (1)
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
			if (collected[W] == false)
			{
				if (dist[V] + city_graph.pp_G[V][W].weight < dist[W])//如果V到W有一条边 并且W节点未被收录到path中
				{
					dist[W] = dist[V] + city_graph.pp_G[V][W].weight;//起点到W的距离等于起点到W的距离+VW边的距离
					path[W] = V;//路径中W的上一个节点是V
				}
			}
		}
	}


	/*把路径变为正序的（栈）*/

	/*从终点开始把逆序路径压入栈*/
	V = dest;
	SqStack stack;
	Init_Stack(&stack);
	Push(&stack, V);
	while (path[V] != -1)
	{
		Push(&stack, path[V]);
		V = path[V];
	}

	/*弹栈，得到正序*/
	int i=0;
	while (stack.base != stack.top)//栈非空
	{
		Pop(&stack, path[i]);//?????
		++i;
	}

	return OK;
}