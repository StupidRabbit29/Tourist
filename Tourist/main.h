#include<stdio.h>
#include<stdlib.h>

/*ö������*/
enum Vehicle{car, train, airplane};
enum Status{ERROR, OK};

/*�ṹ��*/

/*�����ṹ*/
typedef struct transport_table{
	int src, dest;//�����յ�//֮��ʹ������洢�ص�������֣�ʹ�������±����
	Vehicle transport;//����//ö������
	int number;//���� //����������Ҫ��Ϊ�ַ�����
	int time_departure;//����ʱ�� //ϵͳʱ�侫ȷ��Сʱ
	int time_consumed;//��ʱ
	int cost;//Ǯ
	struct transport_table *nextPtr;
}TransTable, *PtrTransTable;

/*ͼ�����У�-�ڽӾ��� �ṹ*/
typedef struct graph{
	PtrTransTable **pp_G;//ָ���ڽӾ���(��ά��̬���飩��ָ��
	int Graph_size;//��������
}GRAPH;//�����˽ṹ�巽�������չ


/*��������*/

//��������.h��ֵֹģ�����Ϊ��extern