////使用引用 访问path数组？？
//#include"main.h"
//char *Vehicle_Name[3] = { "汽车", "火车", "飞机" };
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
//	if (s->top - s->base >= s->stack_size) return STACK_FULL;//判满
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
///*												警告！
//输出之前图的边的唯一确定的权重不能被改变
//即city_graph.pp_G[v1][v2].num_OfTheEgde不能有改动
//即不能在同一个线程内再次调用min cost或min time文件*/
//
//extern GRAPH city_graph;
//Status Output(int path[], int dist[], int src, int dest,int travel_strategy/*传入枚举类型。*/)//传参？？？？？
//{
//	if(travel_strategy==STRA_minCOST)
//		printf("从 %s到 %s的最少花费为：%d元\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
//	else if (travel_strategy == STRA_minTIME)
//		printf("从 %s到 %s最短耗时为：%d小时\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
//	else if (travel_strategy == STRA_limTIME_minCOST)
//		printf("从 %s到 %s的限制时间最少费用为：\n\n", city_graph.City_Name[src], city_graph.City_Name[dest], dist[dest]);
//	/*最后这条else还有问题，稍后改*/
//	
//	
//	/*打印路径（栈）*/
//	int V = dest;
//	SqStack stack;
//	Init_Stack(&stack);
//	Push(&stack, V);
//	while (path[V] != -1)
//	{
//		Push(&stack, path[V]);
//		V = path[V];
//	}
//	printf("路径是：\n");
//
//	int v1, v2;
//	Pop(&stack, v1);
//	while (stack.base != stack.top)//栈非空
//	{
//		Pop(&stack, v2);//?????
//
//		//遍历一条链表以找到车型，起点，终点
//		TransTable_NODE *currentPtr = NULL;
//		int vehicle_num = city_graph.pp_G[v1][v2].num_OfTheEgde;
//		for (currentPtr = city_graph.pp_G[v1][v2].p_TransTable;
//			currentPtr != NULL || currentPtr->number != vehicle_num;//??????
//			currentPtr = city_graph.pp_G[v1][v2].p_TransTable->nextPtr);
//		/*循环退出后currentPtr应指向该航班。*/
//
//		/*出发到达时间还没加上*/
//		if (currentPtr->number == vehicle_num)
//			printf("乘坐%d号%s\t从%s出发\t到达%s\n", vehicle_num, Vehicle_Name[currentPtr->transport], currentPtr->src, currentPtr->dest);
//		else return ERROR;
//		v1 = v2;
//	}
//
//	return OK;
//}