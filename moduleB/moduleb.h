#include "stdio.h"
#include "stdlib.h"

/*学生管理系统菜单*/
int Menu_student();

/*修改学生信息的菜单*/
int stu_mode_Menu();

/*从键盘输入学生信息*/
int creat_stu(int stu_number,int class_number);

/*从文件读取学生信息*/
int creat_stu_file(int stu_number,FILE *fp2);

/*删除学生*/
int stu_del(int n,int class_number);

/*查找学生*/
void stu_find(int n);

/*修改学生的信息*/
void stu_mode(int n,int class_number);

/*输出学生信息*/
void print_stu(int n);




