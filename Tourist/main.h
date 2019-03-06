#include<stdio.h>
#include<stdlib.h>

/*枚举类型*/
enum Vehicle{car, train, airplane};
enum Status{ERROR, OK};

/*结构体*/

/*航班表结构*/
typedef struct transport_table{
	int src, dest;//起点和终点//之后使用数组存储地点具体名字，使用数组下标访问
	Vehicle transport;//车型//枚举类型
	int number;//车次 //或许类型需要改为字符串？
	int time_departure;//发车时间 //系统时间精确到小时
	int time_consumed;//耗时
	int cost;//钱
	struct transport_table *nextPtr;
}TransTable, *PtrTransTable;

/*边 结构*/
typedef struct Edge {
	PtrTransTable p_TransTable;
	int weight;//边的权重//是可以唯一确定的
}EDGE, *P_EDGE;

/*图（城市）-邻接矩阵 结构*/
typedef struct graph{
	EDGE **pp_G;//指向邻接矩阵(二维动态数组）的指针
	int Graph_size;//城市数量
}GRAPH;//定义了结构体方便后期扩展


/*常量定义*/

//函数放在.h里怪怪的？？因为有extern
