#ifndef __CITYLINKLIST_H_
#define __CITYLINKLIST_H_
#include <stdio.h>
typedef struct CityInfo {
  char name[20];         //定义城市名称
  double pos_x;          //定义城市x坐标
  double pos_y;          //定义城市y坐标
  double area;           //定义城市面积
  unsigned int Hu_popu;  //定义城市人口
  struct CityInfo *next; //定义指针指向下一个城市
} CityInfo;              //定义城市信息结构体
typedef struct CityPoin {
  CityInfo *addr;
  double extent;
  struct CityPoin *next;
} CityPoin; //定义城市信息指针结构体;
void SafeInputStr(FILE *fp, char *Dst, unsigned int count); //安全输入
void PrintCityInfo(CityInfo *node); //打印城市信息函数
void InputCityInfo(CityInfo *node); //输入城市信息将其存储到node指针里面
void SearchNode(CityInfo *head, char *name, CityInfo **result); //查找节点
void CreateCityLinkList(CityInfo **head, CityInfo **end); //创建城市链表
void GetCityPos(
    CityInfo
        *head); //给定一个城市名返回其x,y坐标,将其存储在pos_x,和pos_y地址里面
void InsertCity(CityInfo **head, CityInfo **end); //插入城市节点;
void DeleteCity(CityInfo **head,
                CityInfo **end); //按城市名称查找并删除节点;
void UpdateCity(CityInfo *head); //更新城市信息
void ChoiceCity(
    CityInfo *
        head); //给定一个坐标(pos_x,pos_y)和一个距离D,返回所有与P的距离小于D的城市;
void WriteOut(CityInfo *head); //将当前信息保存到文件内;
void ReadIn(CityInfo **head, CityInfo **end);   //从外部文件读入数据;
void MainMenu(CityInfo **head, CityInfo **end); //主界面菜单
void ExitMenu();                                //退出界面;

#endif
