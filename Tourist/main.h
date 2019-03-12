#include<stdio.h>
#include<stdlib.h>

/*常量定义*/
#define INFINITE 2147483647 //最大int
#define NOT_EXIST -1
#define MAX_NODE_NUM 200 //最大城市数量
#define MIN_NODE_NUM 10 //最小城市数量

/*枚举类型*/
enum Vehicle { CAR, TRAIN, AIRPLANE };
enum Status { ERROR, OK, STACK_FULL, STACK_EMPTY };
enum Travel_Strategy { STRA_minCOST, STRA_minTIME, STRA_limTIME_minCOST };

/*全局变量*/


/*结构体*/
/*航班表结构*/
typedef struct transport_table{
	int src, dest;//起点和终点//之后使用数组存储地点具体名字，使用数组下标访问
	Vehicle transport;//车型//枚举类型
	int number;//车次 不同车型车次的编号不允许重复！！！//或许类型需要改为字符串？
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
	int distance;//城市之间的距离，0代表本市到本市，-1代表不连通
}EDGE, *P_EDGE;

/*图（城市）-邻接矩阵 结构*/
typedef struct graph{
	EDGE **pp_G;//指向邻接矩阵(二维动态数组）的指针//大小为Graph_size*Graph_size
	int Graph_size;//城市数量
	char **City_Name;//数组名字是二维数组还是指针数组？？？？
}GRAPH;//定义了结构体方便后期扩展

/*栈 结构*/
typedef struct {
	int *base, *top, stack_size;
}SqStack;

/*乘客 结构 链表形式存储*/
typedef struct passenger{
	char ID[20];//旅客名称
	int src, dest;//起点终点
	int strategy;//旅行策略//时间or费用最少or限制时间最少费用
	int pass_by[MAX_NODE_NUM];//要求途经的城市 //虽然很浪费空间但是我不想malloc了
	int Time_Limited;//若限制时间最少费用，还有一项限制的时间
	int status;//状态//可以使用枚举类型？或者类型要改？

	FILE *fptr_user;//用户文档//什么鬼 存用户id的吗
	FILE *fptr_route;//路线 若用户中途修改策略，路线会被全部覆盖重写
	//或许还应该有一个记录用户状态的文档？

	struct passenger *next_passenger;//指向下一个旅客
}PASSENGER;



//函数放在.h里怪怪的？？因为有extern
//可以写函数声明
