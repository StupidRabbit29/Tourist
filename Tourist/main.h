#include<cstdio>
#include<cstdlib>
//为什么不能写stdio.h???


/*结构体*/

/*航班表结构*/
typedef struct transport_table{
	int src, dest;//起点和终点//之后使用数组存储地点具体名字，使用数组下标访问
	int transport;//车型//枚举类型
	int number;//车次 //或许类型需要改为字符串？
	int time_departure;//发车时间 //系统时间精确到小时
	int time_consumed;//耗时
	int cost;//钱
	struct transport_table *nextPtr;
}Transport_Table;

/*图-邻接矩阵 结构*/
typedef struct {
	Transport_Table **pp_G;//指向邻接矩阵的指针，(二维动态数组）
}GRAPH;//定义了结构体方便后期扩展


/*常量定义*/

//函数放在.h里怪怪的？？因为有extern