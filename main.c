#include "citylinklist.h"
#include <stdio.h>
int main(void) {
  CityInfo *head = NULL; //定义城市链表头指针
  CityInfo *end = NULL;  //定义城市链表尾指针
  MainMenu(&head, &end);
  return 0;
}
