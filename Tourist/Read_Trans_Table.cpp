#include"main.h"

extern GRAPH city_graph;

void Read_trans_t()
{
	if (DEBUG)
		cout << "Called Read_trans_t()" << endl;

	fstream f_trans;
	f_trans.open("Transtable.txt", fstream::in);
	if (!f_trans)
		cerr << "Transtable.txt打开失败\n";
	f_trans.seekg(0, fstream::beg);//移动到文件头
	int src, dest;
	//Ptr_trans_t_Node currentptr,preptr;
	struct trans_t *currentptr, *preptr;
	int count_vehicle = 1;
	while (!f_trans.eof())//???可能出错
	{

		f_trans >> src >> dest;

		/*处理链表*/
		preptr= city_graph.pp_G[src][dest].p_TransTable;//指向链表头
		currentptr = city_graph.pp_G[src][dest].p_TransTable;//指向链表头

		while (currentptr != NULL/*头不为空*/ /*|| currentptr->nextPtr != NULL/*指到尾*/)
		{
			preptr = currentptr;
			currentptr = currentptr->nextPtr;
		}/*退出后per指到链表尾，current指空*/
		//currentptr = (Ptr_trans_t_Node)malloc(sizeof(trans_t_Node));
		currentptr = (struct trans_t*)malloc(sizeof(struct trans_t));
		

		if (city_graph.pp_G[src][dest].p_TransTable == NULL)//若头指针为空//链表为空
		{
			city_graph.pp_G[src][dest].p_TransTable = currentptr;
		}
		else
			preptr->nextPtr = currentptr;//连接

		/*处理结构体内容*/

		currentptr->src = src;
		currentptr->dest = dest;

		int temp_transport;
		f_trans >> temp_transport;
		currentptr->transport = (Vehicle)temp_transport;

		currentptr->number = count_vehicle;
		count_vehicle++;

		string temp_string;
		f_trans >> temp_string;
		for (int i; i < temp_string.size(); i++)
		{
			currentptr->name[i] = temp_string[i];
		}

		f_trans >> currentptr->time_departure >> currentptr->time_consumed >> currentptr->cost;

		currentptr->nextPtr = NULL;
	}

}