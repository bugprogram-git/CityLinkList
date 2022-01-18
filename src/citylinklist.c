#include "citylinklist.h"
#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
void SafeInputStr(FILE *fp, char *Dst, unsigned int count) {
  __fpurge(fp); //刷新文件缓冲区
  for (int i = 0; i < count - 1; i++) {
    Dst[i] = getchar();
    if (Dst[i] == '\0' || Dst[i] == '\n') {
      Dst[i] = '\0';
      break;
    }
  }
  Dst[count] = '\0';
  __fpurge(fp); //刷新文件缓冲区
  return;
}
void PrintCityInfo(CityInfo *node) {
  printf("\t\t\t\t\t城市名称:%s\n", node->name);
  printf("\t\t\t\t\t城市坐标:(%lf,%lf)\n", node->pos_x, node->pos_y);
  printf("\t\t\t\t\t城市面积:%lf(平方千米)\n", node->area);
  printf("\t\t\t\t\t城市人口:%d(万)\n", node->Hu_popu);
  printf("\t\t\t\t\t城市GDP:%lf(亿元)\n", node->GDP);
  printf("\t\t\t\t\t城市人均GDP:%lf(万元)\n", node->Per_GDP);
}
void InputCityInfo(CityInfo *node, char *name) {
  strcpy(node->name, name);
  printf("\t\t\t\t\t请输入该城市的x坐标(千米):");
  scanf("%lf", &node->pos_x);
  printf("\t\t\t\t\t请输入该城市的y坐标(千米):");
  scanf("%lf", &node->pos_y);
  printf("\t\t\t\t\t请输入该城市的人口(万):");
  scanf("%d", &node->Hu_popu);
  printf("\t\t\t\t\t请输入该城市的面积(平方千米):");
  scanf("%lf", &node->area);
  printf("\t\t\t\t\t请输入该城市的GDP(亿元):");
  scanf("%lf", &node->GDP);
  node->Per_GDP = (node->GDP / node->Hu_popu);
  return;
}
void SearchNode(CityInfo *head, char *name, CityInfo **result) {
  *result = NULL; //初始化查找节点空间
  while (head != NULL) {
    if (strcmp(name, head->name) == 0) {
      *result = head; //如果查找到,则将查找到的地址存放在result里面,函数返回
      break;
    } else {
      head = head->next; //指针指向下一个节点
    }
  }
}
void GetCityPos(CityInfo *head) {
  if (head == NULL) {
    printf("\t\t\t\t\t城市链表为空!\n");
    return;
  }
  char name[20];
  printf("\t\t\t\t\t请输入城市名称:");
  SafeInputStr(stdin, name, 20); //输入城市名称
  while (head != NULL) {
    if (strcmp(head->name, name) == 0) { //比较查找的城市名称是否相等
      printf("\t\t\t\t\t查到该城市坐标为:(%lf,%lf)(千米)\n", head->pos_x,
             head->pos_y);
      return;
    } else {
      head = head->next;
    }
  }
  printf("未查找到符合条件的城市!\n");
  return;
}
void AddCityToLinkList(CityInfo **head, CityInfo **end, unsigned int count) {
  CityInfo *result = NULL;
  CityInfo *node = NULL;
  char name[20];
  for (int i = 1; i <= count; i++) {
    printf("\t\t\t\t\t请输入第%d个城市的节点信息\n", i);
    node = malloc(sizeof(CityInfo));
    node->next = NULL;
    if (node == NULL) {
      perror("malloc:");
      return;
    }
    printf("\t\t\t\t\t请输入第%d个城市的名称:", i);
    SafeInputStr(stdin, name, 20);
    SearchNode(*head, name, &result); //查找城市链表里面是否存在该城市名称
    if (result == NULL) {
      InputCityInfo(node, name);
      if (*head == NULL) { //如果链表为空
        *head = node;      //改变头指针指向
        *end = node;       //改变尾指针指向
      } else {
        (*end)->next = node;
        *end = node; //改变尾指针指向
      }
      printf("\t\t\t\t\t操作成功!\n");
    } else {
      i--;
      printf("\t\t\t\t\t该城市已经存在!\n");
    }
  }
}
void CreateCityLinkList(CityInfo **head, CityInfo **end) {
  unsigned int count;
  printf("\t\t\t\t\t请输入您要创建的城市节点个数:");
  scanf("%d", &count);
  AddCityToLinkList(head, end, count); //插入城市节点
  printf("\t\t\t\t\t创建成功!\n");
  return;
}
void DeleteCity(CityInfo **head, CityInfo **end) {
  //删除城市节点有几种特殊情况
  // 1.整个链表为空;
  // 2.整个链表只有一个节点;
  // 3.删除第一个节点;
  // 4.删除最后一个节点;
  if (*head == NULL) {
    printf("\t\t\t\t\t城市链表为空!\n");
    return;
  }
  CityInfo *tmp = NULL;
  CityInfo *tmp2 = NULL;
  unsigned int count;
  printf("\t\t\t\t\t请输入您要删除的城市节点个数:");
  scanf("%d", &count);
  for (int i = 1; i <= count; i++) {
    char name[10];
    printf("\t\t\t\t\t请输入您要删除的第%d个城市名称:", count);
    SafeInputStr(stdin, name, 20);
    if (strcmp((*head)->name, name) == 0) {
      if ((*end) == (*head)) {
        free(*head);
        *head = NULL;
        *end = NULL;
      } else {
        CityInfo *next = (*head);
        (*head) = (*head)->next;
        free(next);
        next = NULL;
      }
      printf("\t\t\t\t\t删除成功!\n");
      continue;
    }
    tmp = *head;
    while (tmp->next != NULL) {
      if (strcmp(tmp->next->name, name) == 0) {
        tmp2 = tmp->next;
        tmp->next = tmp->next->next;
        free(tmp2);
        if (tmp->next == NULL) {
          *end = tmp;
        }
        printf("删除成功!\n");
        continue;
      }
      tmp = tmp->next;
    }
    printf("未查找到相关城市信息,删除失败!\n");
  }
}
void InputCityName(); //输入城市名称
void UpdateCity(CityInfo *head) {
  unsigned int choice;
  CityInfo **result;
  int flag = 0;
  char name[20];
  printf("\t\t\t\t\t请输入您要更新的城市名称:");
  SafeInputStr(stdin, name, 20);
  while (head != NULL) {
    if (strcmp(head->name, name) == 0) {
      flag = 1;
      break;
    }
    head = head->next;
  }
  bzero(name, 20); //初始化城市名称空间
  if (flag == 1) {
    printf("\t\t\t\t\t当前城市信息如下\n");
    PrintCityInfo(head); //打印城市信息
    while (1) {
      printf("\t\t\t\t\t-------------------------\n");
      printf("\t\t\t\t\t1.修改城市名称\n");
      printf("\t\t\t\t\t2.修改城市x坐标\n");
      printf("\t\t\t\t\t3.修改城市y坐标\n");
      printf("\t\t\t\t\t4.修改城市人口\n");
      printf("\t\t\t\t\t5.修改城市GDP\n");
      printf("\t\t\t\t\t6.修改该城市所有信息\n");
      printf("\t\t\t\t\t7.退回上一级菜单\n");
      printf("\t\t\t\t\t请输入您的选择:");
      scanf("%d", &choice);
      switch (choice) {
      case 1:
        while (1) {
          printf("\t\t\t\t\t该城市当前城市名称为:%s\n", head->name);
          printf("\t\t\t\t\t请输入新的城市名称:");
          SafeInputStr(stdin, name, 20);
          if (strcmp(name, head->name) == 0) {
            printf("\t\t\t\t\t城市名未更新!\n");
            break;
          } else {
            SearchNode(head, name, result);
            if (result == NULL) {
              strcpy(head->name, name);
              break;
            } else {
              printf("\t\t\t\t\t城市链表已有该城市\n");
            }
          }
        }
        break;
      case 2:
        printf("\t\t\t\t\t该城市当前的城市x坐标为:%lf(千米)\n", head->pos_x);
        printf("\t\t\t\t\t请输入新的城市x坐标(千米):");
        scanf("%lf", &head->pos_x);
        break;
      case 3:
        printf("\t\t\t\t\t该城市当前的城市y坐标为:%lf(千米)\n", head->pos_x);
        printf("\t\t\t\t\t请输入新的城市y坐标:(千米)");
        scanf("%lf", &head->pos_y);
        break;
      case 4:
        printf("\t\t\t\t\t该城市当前的人口为%d(万)", head->Hu_popu);
        printf("\t\t\t\t\t请输入新的城市人口:(万)");
        scanf("%d", &head->Hu_popu);
        break;
      case 5:
        printf("\t\t\t\t\t该城市当前的GDP为%lf(亿元)", head->GDP);
        printf("\t\t\t\t\t请输入新的城市GDP:(亿元)");
        scanf("%lf", &head->GDP);
        break;

      case 6:
        while (1) {
          printf("\t\t\t\t\t该城市当前城市名称为:%s\n", head->name);
          printf("\t\t\t\t\t请输入新的城市名称:");
          bzero(name, 20);
          SafeInputStr(stdin, name, 20);
          if (strcmp(name, head->name) == 0) {
            printf("\t\t\t\t\t城市名未更新!\n");
            break;
          } else {
            SearchNode(head, name, result);
            if (result == NULL) {
              strcpy(head->name, name);
              break;
            } else {
              printf("\t\t\t\t\t城市链表已有该城市\n");
            }
          }
        }
        printf("\t\t\t\t\t请输入新的城市x坐标(千米):");
        scanf("%lf", &head->pos_x);
        printf("\t\t\t\t\t请输入新的城市y坐标(千米):");
        scanf("%lf", &head->pos_y);
        printf("\t\t\t\t\t请输入新的城市人口(万):");
        scanf("%d", &head->Hu_popu);
        break;
      case 7:
        return;
      default:
        printf("\t\t\t\t\t输入错误!\n");
        break;
      }
    }
  }
}
void ChoiceCity(CityInfo *head) {
  if (head == NULL) {
    printf("城市链表为空!\n");
    return;
  }
  double extent, pos_x, pos_y, D;
  CityPoin *HEAD = NULL;
  CityPoin *END = NULL;
  CityPoin *NODE = NULL;
  CityPoin *TMP = NULL; //定义4个空指针
  //这里之所以使用CityPoin类型存放城市指针;主要是为了后续扩展(如对查找到的城市信息进行排序)
  unsigned int flag = 0;
  printf("\t\t\t\t\t请输入x坐标(千米):");
  scanf("%lf", &pos_x);
  printf("\t\t\t\t\t请输入y坐标(千米):");
  scanf("%lf", &pos_y);
  printf("\t\t\t\t\t请输入距离(千米):");
  scanf("%lf", &D);
  while (head != NULL) {
    extent = sqrt(pow((head->pos_x - pos_x), 2) +
                  pow((head->pos_y - pos_y), 2)); //计算距离
    if (extent < D) {
      NODE = malloc(sizeof(CityPoin)); //申请内存空间
      if (NODE == NULL) {
        perror("malloc:");
        return;
      }
      NODE->next = NULL;
      NODE->addr = head;
      NODE->extent = extent; //初始化节点数据
      if (HEAD == NULL) {
        HEAD = NODE;
        END = NODE;
      } else {
        END->next = NODE;
        END = NODE;
      }
      flag++;
    }
    head = head->next;
  }
  if (flag == 0) {
    printf("\t\t\t\t\t未查找到符合条件的城市\n");
  } else {
    printf("\t\t\t\t\t查到%d个城市符合条件\n\n", flag);
    TMP = HEAD;
    for (int i = 1; i <= flag; i++) {
      printf("\t\t\t\t\t%s---->距离--->%lf(千米)\n\n", TMP->addr->name,
             TMP->extent);
      TMP = HEAD->next;
    }
    TMP = HEAD;
    while (TMP != NULL) {
      END = TMP;
      TMP = TMP->next;
      free(END);
    }
  }
  return;
}
void ExitMenu() {
  char choice[10]; //初始化一块栈空间用于存放用户输入的字符串
  while (1) {
    printf("\t\t\t\t\t你确认要退出系统吗?(yes/no)\n");
    printf("\t\t\t\t\t请输入你的选择:");
    SafeInputStr(stdin, choice, 4);
    if (strcasecmp("yes", choice) == 0) {
      exit(0); //如果用户输入"yes"则推出进程
    } else {
      if (strcasecmp("no", choice) == 0) {
        break;
      } else {
        printf("输入错误!\n"); //输入错误则进入下一次循环
      }
    }
  }
}
void WriteOut(CityInfo *head) {
  char filename[20]; //初始化一块栈空间用于存放用户输入的文件名
  printf("\t\t\t\t\t请输入您想要保存数据的文件名:");
  SafeInputStr(stdin, filename, 20); //输入文件名称
  FILE *fp = fopen(filename, "w");   //写入方式打开文件
  if (fp == NULL) {
    perror("\t\t\t\t\tfopen");
    return;
  }
  while (head != NULL) {
    fwrite((void *)head, 72, 1, fp); //循环写入数据
    head = head->next;               //指向下一个节点
  }
  fclose(fp); //关闭文件流
}
void ReadIn(CityInfo **head, CityInfo **end) {
  char filename[20];
  char choice[4] = {0};
  CityInfo *result = NULL;
  CityInfo *tmp = *end;
  CityInfo *node = NULL;
  CityInfo *HEAD = NULL;
  CityInfo *END = NULL;
  printf("\t\t\t\t\t请输入您要导入的文件名称:");
  SafeInputStr(stdin, filename, 20); //输入文件名称
  FILE *fp = fopen(filename, "r+");
  if (fgetc(fp) == EOF) {
    printf("\t\t\t\t\t该文件为空文件!\n");
    return;
  } else {
    rewind(fp);
  } //判断该文件是否为空文件
  while (!feof(fp)) {
    node = malloc(sizeof(CityInfo)); //申请内存空间
    if (node == NULL) {
      perror("malloc");
      continue;
    }
    fread((void *)node, 72, 1, fp); //读入城市数据
    node->next = NULL;
    SearchNode(*head, node->name, &result); //查找该节点是否已经存在与城市链表
    if (result == NULL) {
      if (HEAD == NULL) {
        HEAD = node;
        END = node;
      }
      END->next = node;
    } else {
      printf("\t\t\t\t\t城市链表中已有该城市!是否覆盖?(yes/no):");
      while (1) {
        SafeInputStr(stdin, choice, 4); //输入yes/no
        if (strcmp("yes", choice) == 0) {
          strcpy(result->name, node->name);
          result->pos_x = node->pos_x;
          result->pos_y = node->pos_y;
          result->area = node->area;
          result->Hu_popu = node->Hu_popu;
          result->GDP = node->GDP;
          result->Per_GDP = node->Per_GDP;
          free(node);
          node = NULL;
          break;
        } else {
          if (strcmp("no", choice) == 0) {
            free(node); //释放节点空间
            node = NULL;
            break;
          } else {
            printf("\t\t\t\t\t输入错误!\n");
          }
        }
      }
    }
    if ((*head) == NULL) {
      *head = HEAD;
      *end = END;
    } else {
      (*end)->next = HEAD;
      *end = END;
    }
  }

  printf("\t\t\t\t\t导入成功!\n");
}
void LoadingBar() { //加载进度条
  char str[] = {'-', '\\', '|', '/'};
  for (int i = 1; i <= 50; i++) {
    printf("\t\t\t     [");
    for (int j = 1; j <= 50; j++) {
      if (j <= i) {
        printf("\033[32m#\033[0m");
      } else {
        putchar(' ');
      }
    }
    printf("]");
    printf(" %d", 2 * i);
    putchar('%');
    if (i == 50) {
      printf(" ");
      printf("[ \033[32m  done  \033[0m ]");
      printf("           ");
    } else {
      printf("[ %c Loading... ]", str[i % 4]);
    }
    printf("\r");
    fflush(stdout);
    usleep(40 * 1000);
  }
  putchar('\n');
}
void SearchCityInfo(CityInfo *head) {
  char cityname[20];
  CityInfo *result = NULL;
  printf("\t\t\t\t\t请输入您要查找的城市名称:");
  SafeInputStr(stdin, cityname, 20);
  SearchNode(head, cityname, &result);
  if (result == NULL) {
    printf("\t\t\t\t\t未查找到该城市!\n");
  } else {
    printf("\t\t\t\t\t查找到该城市信息如下:\n");
    PrintCityInfo(result);
    putchar('\n');
  }
}
void CalTwoCityDis(CityInfo *head) { //计算某两个城市之间的距离
  char Src_City[20];
  char Dst_City[20];
  CityInfo *Src_result = NULL;
  CityInfo *Dst_result = NULL;
  while (1) {
    printf("\t\t\t\t\t请输入起点城市:");
    SafeInputStr(stdin, Src_City, 20);
    SearchNode(head, Src_City, &Src_result);
    if (Src_result == NULL) {
      printf("\t\t\t\t\t为查找到相关城市信息!\n");
    } else {
      break;
    }
  }
  while (1) {
    printf("\t\t\t\t\t请输入终点城市:");
    SafeInputStr(stdin, Dst_City, 20);
    SearchNode(head, Dst_City, &Dst_result);
    if (Dst_result == NULL) {
      printf("\t\t\t\t\t未查找到相关城市信息!\n");
    } else {
      break;
    }
  }
  double distance;
  distance = sqrt(pow((Src_result->pos_x - Dst_result->pos_x), 2) +
                  pow((Src_result->pos_y - Dst_result->pos_y), 2));
  printf("\t\t\t\t\t计算该两个城市的距离为:%lf\n", distance);
  return;
}

void MainMenu(CityInfo **head, CityInfo **end) {
  printf("\t\t\t\t\t\t******欢迎******\n");
  LoadingBar();
  unsigned int answer;
  char choice[5] = {0};
  unsigned int count;
  while (1) {
    printf("\t\t\t\t\t********************************* \n");
    printf("\t\t\t\t\t*1.创建城市链表                   \n");
    printf("\t\t\t\t\t*2.向城市链表插入新的城市节点     \n");
    printf("\t\t\t\t\t*3.删除某个城市节点               \n");
    printf("\t\t\t\t\t*4.查找某城市坐标                 \n");
    printf("\t\t\t\t\t*5.查找某城市信息                 \n");
    printf("\t\t\t\t\t*6.更新某个城市信息               \n");
    printf("\t\t\t\t\t*7.返回距离某坐标范围内的所有城市 \n");
    printf("\t\t\t\t\t*8.返回两个城市之间的距离         \n");
    printf("\t\t\t\t\t*9.保存当前城市链表信息           \n");
    printf("\t\t\t\t\t*10.读取数据库文件                \n");
    printf("\t\t\t\t\t*11.退出系统                      \n");
    printf("\t\t\t\t\t**********************************\n");
    printf("\t\t\t\t 请输入:");
    scanf("%d", &answer);
    switch (answer) {
    case 1:
      CreateCityLinkList(head, end);
      break;
    case 2:
      printf("\t\t\t\t\t请输入你要插入的城市节点个数:");
      scanf("%d", &count);
      AddCityToLinkList(head, end, count);
      break;
    case 3:
      DeleteCity(head, end);
      break;
    case 4:
      GetCityPos(*head);
      break;
    case 5:
      SearchCityInfo(*head);
      break;
    case 6:
      UpdateCity(*head);
      break;
    case 7:
      ChoiceCity(*head);
      break;
    case 8:
      CalTwoCityDis(*head);
      break;
    case 9:
      WriteOut(*head);
      break;
    case 10:
      ReadIn(head, end);
      break;
    case 11:
      ExitMenu();
      continue;
    default:
      printf("输入错误!\n");
    }
  }
  return;
}
