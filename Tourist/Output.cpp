////ʹ������ ����path���飿��
//#include"main.h"
//char *Vehicle_Name[3] = { "����", "��", "�ɻ�" };
//
//SqStack *s;
//Status Init_Stack(SqStack *s)
//{
//	s->base = (int*)malloc(sizeof(int)*MAX_NODE_NUM);
//	if (s->base == NULL) exit(1);
//	s->stack_size = MAX_NODE_NUM;
//	s->top = s->base;
//	return OK;
//}
//Status Push(SqStack *s, int data)
//{
//	if (s->top - s->base >= s->stack_size) return STACK_FULL;//����
//	*s->top = data;
//	s->top++;
//	return OK;
//}
//Status Pop(SqStack *s, int &data)
//{
//	if (s->base == s->top) return STACK_EMPTY;
//	s->top--;
//	data = *s->top;
//	return OK;
//}
//
//
///*												���棡
//���֮ǰͼ�ıߵ�Ψһȷ����Ȩ�ز��ܱ��ı�
//��city_graph.pp_G[v1][v2].num_OfTheEgde�����иĶ�
//��������ͬһ���߳����ٴε���min cost��min time�ļ�*/
//
//extern GRAPH city_graph;
//Status Output(int path[], int dist[], int src, int dest,int travel_strategy/*����ö�����͡�*/)//���Σ���������
//{
//	if(travel_strategy==STRA_minCOST)
//		printf("�� %s�� %s�����ٻ���Ϊ��%dԪ\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
//	else if (travel_strategy == STRA_minTIME)
//		printf("�� %s�� %s��̺�ʱΪ��%dСʱ\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
//	else if (travel_strategy == STRA_limTIME_minCOST)
//		printf("�� %s�� %s������ʱ�����ٷ���Ϊ��\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
//	/*�������else�������⣬�Ժ��*/
//	
//	
//	/*��ӡ·����ջ��*/
//	int V = dest;
//	SqStack stack;
//	Init_Stack(&stack);
//	Push(&stack, V);
//	while (path[V] != -1)
//	{
//		Push(&stack, path[V]);
//		V = path[V];
//	}
//	printf("·���ǣ�\n");
//
//	int v1, v2;
//	Pop(&stack, v1);
//	while (stack.base != stack.top)//ջ�ǿ�
//	{
//		Pop(&stack, v2);//?????
//
//		//����һ���������ҵ����ͣ���㣬�յ�
//		TransTable_NODE *currentPtr = NULL;
//		int vehicle_num = city_graph.pp_G[v1][v2].num_OfTheEgde;
//		for (currentPtr = city_graph.pp_G[v1][v2].p_TransTable;
//			currentPtr != NULL || currentPtr->number != vehicle_num;//??????
//			currentPtr = city_graph.pp_G[v1][v2].p_TransTable->nextPtr);
//		/*ѭ���˳���currentPtrӦָ��ú��ࡣ*/
//
//		/*��������ʱ�仹û����*/
//		if (currentPtr->number == vehicle_num)
//			printf("����%d��%s\t��%s����\t����%s\n", vehicle_num, Vehicle_Name[currentPtr->transport], currentPtr->src, currentPtr->dest);
//		else return ERROR;
//		v1 = v2;
//	}
//
//	return OK;
//}