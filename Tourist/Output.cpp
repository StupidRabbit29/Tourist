//ʹ������ ����path���飿��
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

Status Output(MAZE maze, int path[], int dist[], int src, int dest)
{
	printf("�� %s�� %s�����·������Ϊ��%d��\n\n", maze.landmark[src], maze.landmark[dest], dist[dest]);
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
	printf("���·���ǣ�\n");

	int v1, v2;
	char *direction;
	direction = (char*)malloc(sizeof(char)*MAXSIZE);
	Pop(&stack, v1);
	while (stack.base != stack.top)//ջ�ǿ�
	{
		Pop(&stack, v2);
		switch (maze.G[v1][v2].direction)
		{
		case 'N':
			direction = "��";
			break;
		case 'S':
			direction = "��";
			break;
		case 'W':
			direction = "��";
			break;
		case 'E':
			direction = "��";
			break;
		}
		printf("�� %s��%s��%d��\n���� %s\n", maze.landmark[v1], direction, maze.G[v1][v2].edge_len, maze.landmark[v2]);
		v1 = v2;
	}

	return OK;
}