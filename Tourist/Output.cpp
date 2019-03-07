//使用引用 访问path数组？？
#include"main.h"

Status Init_Stack(SqStack *s)
{
	s->base = (int*)malloc(sizeof(int)*MAXSIZE);
	if (s->base == NULL) exit(1);
	s->stack_size = MAXSIZE;
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

Status Output(MAZE maze, int path[], int dist[], int src, int dest)
{
	printf("从 %s到 %s的最短路径长度为：%d米\n\n", maze.landmark[src], maze.landmark[dest], dist[dest]);
	/*打印路径（栈）*/
	int V = dest;
	SqStack stack;
	Init_Stack(&stack);
	Push(&stack, V);
	while (path[V] != -1)
	{
		Push(&stack, path[V]);
		V = path[V];
	}
	printf("最短路径是：\n");

	int v1, v2;
	char *direction;
	direction = (char*)malloc(sizeof(char)*MAXSIZE);
	Pop(&stack, v1);
	while (stack.base != stack.top)//栈非空
	{
		Pop(&stack, v2);
		switch (maze.G[v1][v2].direction)
		{
		case 'N':
			direction = "北";
			break;
		case 'S':
			direction = "南";
			break;
		case 'W':
			direction = "西";
			break;
		case 'E':
			direction = "东";
			break;
		}
		printf("从 %s向%s走%d米\n到达 %s\n", maze.landmark[v1], direction, maze.G[v1][v2].edge_len, maze.landmark[v2]);
		v1 = v2;
	}

	return OK;
}