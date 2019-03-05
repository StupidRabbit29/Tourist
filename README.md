# Tourist
A huge program!

旅行模拟查询系统

作者：竹倩叶、付彬
项目创建时间：2019/3/2
版本描述：

问题描述：
1、城市（总数不少于10个）之间有三种交通工具（汽车、火车和飞机）相连；
2、某旅客于某一时刻向系统提出旅行要求（包括：起点、终点、途经某些城市和旅行策略），系统根据该旅客的要求为其设计一条旅行线路并输出；
3、系统能查询当前时刻旅客所处的地点和状态（停留城市/所在交通工具）；
4、旅行策略有：
（1）最少费用策略：无时间限制，费用最少即可，
（2）最少时间策略：无费用限制，时间最少即可，
（3）限时最少费用策略：在规定的时间内所需费用最省；
5、建立汽车、火车和飞机的时刻表（航班表），有沿途到站及票价信息；
6、旅行模拟查询系统以时间为轴向前推移，每10秒左右向前推进1个小时(非查询状态的请求不计时)；
7、不考虑城市内换乘交通工具所需时间；
8、系统时间精确到小时；
9、建立日志文件，对旅客状态变化和键入等信息进行记录；
10、选做一：某旅客在旅行途中可更改旅行计划，系统应做相应的操作；
11、选做二：用图形绘制地图，并在地图上反映出旅客的旅行过程；