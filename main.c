#include "main.h"

int main()
{
    FILE *fp1,*fp2;
    int tmp,class_number = 0,stu_number = 0;
    int i,choice;
    
    printf("从键盘输入学生信息和课程信息请输入1，从文件读取学生信息和课程信息请输入任意数：\n");
    scanf("%d",&tmp);
    if(tmp == 1)
    {
        class_number=creat_class(class_number);
        stu_number=creat_stu(stu_number,class_number);
    }
    else
    {
        class_number=creat_class_file(class_number,fp1);
        stu_number=creat_stu_file(stu_number,fp2);
    }
                
    while((choice=Menu_class()) != 6)
    {
        switch(choice)
        {
            case 1:class_number=creat_class(class_number);break;
            case 2:class_number=class_del(class_number,stu_number);break;
            case 3:class_find(class_number);break;
            case 4:class_mode(class_number,stu_number);break;
            case 5:print_class(class_number);break;
            default:printf("输入错误，请重新输入");
	}
    }
    system("clear");

    while((choice=Menu_student()) != 6)
    {
        switch(choice)
        {
            case 1:stu_number=creat_stu(stu_number,class_number);break;
            case 2:stu_number=stu_del(stu_number,class_number);break;
            case 3:stu_find(stu_number);break;
            case 4:stu_mode(stu_number,class_number);break;
            case 5:print_stu(stu_number);break;
            default:printf("输入错误，请重新输入");
	}
    }
    system("clear");

    /*以写的方式打开class.txt*/
    if((fp1=fopen("class.txt","w")) == NULL)
    {
        printf("class.txt error!\n");
        exit(1);
    }

    /*以写的方式打开student.txt*/
    if((fp2=fopen("student.txt","w")) == NULL)
    {
        printf("student.txt error!\n");
        exit(1);
    }
    
    /*将课程信息写入到class.txt中*/
    for(i=0; i<class_number; i++)
    {
        fprintf(fp1,"%4s %12s %10s %7d %8.2f %8d %8d\n",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
    }
 
    /*将学生信息写入到student.tx中*/
    for(i=0; i<stu_number; i++)
    {
        fprintf(fp2,"%s %8s %11s %8.2f\n",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
