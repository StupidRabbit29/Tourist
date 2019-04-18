#include"main.h"

extern GRAPH city_graph;

void Read_Trans_Table()
{
	fstream f_trans;
	f_trans.open("Transtable.txt", fstream::in);
	if (!f_trans)
		cerr << "Transtable.txt��ʧ��\n";
	f_trans.seekg(0, fstream::beg);//�ƶ����ļ�ͷ
	int src, dest;
	Ptr_TransTable_NODE currentptr,preptr;
	int count_vehicle = 1;
	while (!f_trans.eof())//???���ܳ���
	{

		f_trans >> src >> dest;

		/*��������*/
		preptr= city_graph.pp_G[src][dest].p_TransTable;//ָ������ͷ
		currentptr = city_graph.pp_G[src][dest].p_TransTable;//ָ������ͷ

		while (currentptr != NULL/*ͷ��Ϊ��*/ /*|| currentptr->nextPtr != NULL/*ָ��β*/)
		{
			preptr = currentptr;
			currentptr = currentptr->nextPtr;
		}/*�˳���perָ������β��currentָ��*/
		currentptr = (Ptr_TransTable_NODE)malloc(sizeof(TransTable_NODE));

		if (city_graph.pp_G[src][dest].p_TransTable == NULL)//��ͷָ��Ϊ��//����Ϊ��
		{
			city_graph.pp_G[src][dest].p_TransTable = currentptr;
		}
		else
			preptr->nextPtr = currentptr;//����

		/*����ṹ������*/

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