#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*课程管理系统菜单*/
int Menu_class();

/*修改课程信息的菜单*/
int class_mode_menu();

/*从键盘输入课程信息*/
int creat_class(int class_number);

/*从文件读取课程信息*/
int creat_class_file(int class_number,FILE *fp1);

/*删除课程*/
int class_del(int n,int stu_number);

/*查找课程*/
void class_find(int n);

/*修改课程的信息*/
void class_mode(int n,int stu_number);

/*输出课程信息*/
void print_class(int n);

