#include<cstdio>
#include<cstdlib>
//Ϊʲô����дstdio.h???


/*�ṹ��*/

/*�����ṹ*/
typedef struct transport_table{
	int src, dest;//�����յ�//֮��ʹ������洢�ص�������֣�ʹ�������±����
	int transport;//����//ö������
	int number;//���� //����������Ҫ��Ϊ�ַ�����
	int time_departure;//����ʱ�� //ϵͳʱ�侫ȷ��Сʱ
	int time_consumed;//��ʱ
	int cost;//Ǯ
	struct transport_table *nextPtr;
}Transport_Table;

/*ͼ-�ڽӾ��� �ṹ*/
typedef struct {
	Transport_Table **pp_G;//ָ���ڽӾ����ָ�룬(��ά��̬���飩
}GRAPH;//�����˽ṹ�巽�������չ


/*��������*/

//��������.h��ֵֹģ�����Ϊ��extern