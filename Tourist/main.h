#include<stdio.h>
#include<stdlib.h>

/*常量定义*/
#define INFINITE 2147483647 //最大int
#define NOT_EXIST -1
#define MAX_NODE_NUM 200 //最大城市数量
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
}TransTable_NODE, *Ptr_TransTable_NODE;

/*边 结构*/
typedef struct Edge {
	Ptr_TransTable_NODE p_TransTable;
	int weight;//边的权重//是可以唯一确定的
	int num_OfTheEgde;//权重最小的边的编号
}EDGE, *P_EDGE;

/*图（城市）-邻接矩阵 结构*/
typedef struct graph{
	EDGE **pp_G;//指向邻接矩阵(二维动态数组）的指针//大小为Graph_size*Graph_size
	int Graph_size;//城市数量
}GRAPH;//定义了结构体方便后期扩展

/*栈 结构*/
typedef struct {
	int *base, *top, stack_size;
}SqStack;



//函数放在.h里怪怪的？？因为有extern
//可以写函数声明
