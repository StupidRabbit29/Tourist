#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>
#include<vector>
#include<bitset>
#include<algorithm>
#include<iterator>
#include<fstream>
using namespace std;


/*常量定义*/
#define MY_INFINITE 999999 //最大int//？？？？宏重定义？？可能出问题？
#define NOT_EXIST -1
#define MAX_NODE_NUM 200 //最大城市数量
#define MIN_NODE_NUM 10 //最小城市数量

const bool DEBUG = true;//debug标志

/*枚举类型*/
enum Vehicle { CAR, TRAIN, AIRPLANE };
enum Status { ERROR, OK, STACK_FULL, STACK_EMPTY, UNABLE };
enum Travel_Strategy { STRA_minCOST, STRA_minTIME, STRA_limTIME_minCOST };
enum Location { IN_CAR, IN_TRAIN, IN_AIRPLANE, STAY_IN_CITY, ARRIVE };


/*全局变量*/


/*结构体*/
/*航班表结构*/
typedef struct trans_t {
	int src, dest;//起点和终点
	Vehicle transport;//车型//枚举类型
	char name[10];//交通工具名称
	int number;//车次 不同车型车次的编号不允许重复！！！//或许类型需要改为字符串？
	int time_departure;//发车时间 //系统时间精确到小时
	int time_consumed;//耗时
	int cost;//钱
	struct trans_t *nextPtr;
}trans_t_Node;

typedef trans_t_Node* Ptr_trans_t_Node;

/*边 结构*/
typedef struct Edge {
//	trans_t_Node *p_TransTable;
	struct trans_t *p_TransTable;
	int weight;//边的权重//是可以唯一确定的
	int num_OfTheEgde;//权重最小的边的编号
	int distance;//城市之间的距离，0代表本市到本市，-1代表不连通
}EDGE, *P_EDGE;

/*图（城市）-邻接矩阵 结构*/
typedef struct graph {
	EDGE **pp_G;//指向邻接矩阵(二维动态数组）的指针//大小为Graph_size*Graph_size
	int Graph_size;//城市数量
	char **City_Name;//数组名字是二维数组还是指针数组？？？？
}GRAPH;//定义了结构体方便后期扩展

	   /*栈 结构*/
typedef struct {
	int *base, *top, stack_size;
}SqStack;

/*系统时间 结构*/
typedef struct SYSTEM_TIME {
	int year, month, date, hour;
}SYSTEM_TIME;

/*旅客旅行状态 结构*/
typedef struct User_Status
{
	SYSTEM_TIME time;//当前时刻
	Location loca;//乘客旅行状态
	int src, dest;//起点，终点；若乘客在途中，代表交通工具的起始点；若乘客停留在某城市，src=dest；
				  //int number;//搭乘交通工具的车次
				  //Vehicle transport;//车型//枚举类型
	char name[10];//交通工具名称
}User_Status;

/*乘客 结构 链表形式存储*/
typedef struct passenger {
	char ID[20];//旅客名称
	int src, dest;//起点终点
	int strategy;//旅行策略//时间or费用最少or限制时间最少费用//STRA_minCOST, STRA_minTIME, STRA_limTIME_minCOST
	int num_passby;//途经节点数量
	int pass_by[2][MAX_NODE_NUM];//row0要求途经的城市;row1在该地停留时间 //已经访问过的城市需要标记？？？
	int Time_Limited;//若限制时间最少费用，还有一项限制的时间
	SYSTEM_TIME start_time;//旅行者开始旅行的时间
	User_Status status;//旅客旅行状态


	//FILE *fptr_route;	//路线——由旅行线路生成算法计算得到，若用户中途修改策略，路线会被全部覆盖重写，
						//面向程序设计者
						//.ini

	struct passenger *next_passenger;//指向下一个旅客
}PASSENGER;
//FILE *fptr_user;	//日志文档//用户文档——用户登录登出记录，查询操作记录
//FILE *fptr_status;	//用户状态文档——通过时间线程实时更新用户状态
//面向用户
//日志文档2：用户输入信息
//每小时读旅客状态 写入文件



/*旅客旅行路线的结点 结构*/
typedef struct pathnode
{
	int src;//一段路径的起点
	int dest;//一段路径的终点
	int number;//旅行者搭乘的车次
	SYSTEM_TIME start_time;//开始时间
	int time;//耗费时间
	struct pathnode *next;
}PathNode, *PATH;


/*函数声明*/
unsigned __stdcall mouse(void* pArguments);
unsigned __stdcall time(void* pArguments);

Status Prepare(void);
Status Read_Map(FILE *fptr);
void Read_trans_t();

void Create_New_Passenger(PASSENGER *tailPtr);
Status User_sign_in(void);
void Min_Cost();
Status Min_Time();
Status Min_Time_Limited_Time();
Status Output_route(PATH tour);
Status Finish_Path(PATH tour);
Status Output_Status(PASSENGER *psg);
void Change_User_Info(PASSENGER &psg);
Status Refresh(PASSENGER *tourist, int touristnum);

void Write_status_file(PASSENGER &psg);
void Write_user_file(int choice);
void Write_route_file(PATH tour);
Status Write_system_file();
Status Read_system_file();

SYSTEM_TIME operator+(const SYSTEM_TIME& A, int hour);
int operator-(const SYSTEM_TIME& A, const SYSTEM_TIME& B);
int pass_by_time(int V);
void Permutation(int k, int n, int a[], int **A);
void Freememory(void);
int Calculate_Time(PATH tour);





