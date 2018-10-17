#include "moduleb.h"
#include "../main.h"

/*学生管理系统菜单*/
int Menu_student()
{
    int choice;
    printf("\n\t########################################################\n");
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##           欢 迎 进 入 学 生 管 理 系 统            ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##                 1:新增学生信息                     ##\n");
    printf("\t##                 2:删除学生信息                     ##\n");
    printf("\t##                 3:查找学生信息                     ##\n");
    printf("\t##                 4:修改学生信息                     ##\n");
    printf("\t##                 5:输出学生信息                     ##\n");
    printf("\t##                 6:退出                             ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t########################################################\n");
    printf("\n请输入你的选择:");
    scanf("%d",&choice);
    return choice;
}

/*修改学生信息的菜单*/
int stu_mode_Menu()
{
    int choice;
    printf("\n\t########################################################\n");
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##       欢 迎 进 入 修 改 学 生 信 息 系 统           ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##                 1:修改学生学号                     ##\n");
    printf("\t##                 2:修改学生姓名                     ##\n");
    printf("\t##                 3:修改学生课程                     ##\n");
    printf("\t##                 4:退出                             ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t########################################################\n");
    printf("\n请输入你的选择:");
    scanf("%d",&choice);
    return choice;
}

/*从键盘输入学生信息*/
int creat_stu(int stu_number,int class_number) 
{
    int i,n,j,p,q,tmp,f;
    FILE *fp;

    if((fp=fopen("log.log","a+")) == NULL)
    {
        printf("error\n");
        exit(1);
    }

    printf("please enter the number of students:\n");
    scanf("%d",&n);
    printf("please enter student information(学号 姓名 已选课程列表,输入内容以tab键作为分隔符):\n");
    for(i=stu_number; i<n+stu_number; i++)
    {
        scanf("%s %s %s",stu[i].num,stu[i].name,stu[i].class);
        stu[i].sum = 0;
        for(j=0; stu[i].class[j]; j++)
        {
            for(p=0; p<class_number; p++)
            {
                tmp = j;
                for(q=0; cla[p].class_num[q]; q++,tmp++)
                {
                    if(stu[i].class[tmp] != cla[p].class_num[q])
                    {
                        break;
                    }
                }
                if(cla[p].class_num[q] == '\0' && cla[p].class_peo_num < cla[p].class_peo_max)
                {
                    stu[i].sum = stu[i].sum+cla[p].credit_hour;
                    cla[p].class_peo_num++;
                }
                else if(cla[p].class_num[q] == '\0' && cla[p].class_peo_num >= cla[p].class_peo_max)
                {
                    for(tmp=j; tmp<j+q+1; tmp++)
                    {
                        if(j == 0)
                        {                        
                            f = j;
                        }
                        else
                        {
                            f = j-1;
                        }
                        for(; stu[i].class[f]; f++)   
                        {
                        stu[i].class[f] = stu[i].class[f+1];
                        }
                        if(stu[i].class[0] == ',')
                        {
                            for(f=0; stu[i].class[f]; f++)   
                            {
                                stu[i].class[f] = stu[i].class[f+1];
                            }
                        }
                    }
                    j--;
                }
            }
        }
	system("date >> log.log");
        fprintf(fp,"%s	%s %8s %11s %8.2f\n","student input ",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);
    }
    fclose(fp);
    return i;
}

/*从文件读取学生信息*/
int creat_stu_file(int stu_number,FILE *fp2)
{
    int i=stu_number;
    if((fp2=fopen("student.txt","r+")) == NULL)
    {
        printf("student.txt error!\n");
        exit(1);
    }
    while(!feof(fp2))
    {
        fscanf(fp2,"%s %s %s %f",stu[i].num,stu[i].name,stu[i].class,&stu[i].sum);
        i++;
    }

    fclose(fp2);
    return i-1;
}

/*删除学生的信息*/
int stu_del(int n,int class_number)
{
    char stu_name[20];
    int i,j,k,num,p,tmp,q;
    FILE *fp;

    if((fp=fopen("log.log","a+")) == NULL)
    {
        printf("error\n");
        exit(1);
    }

    printf("请输入要删除的学生的个数:\n");
    scanf("%d",&num);
    for(k=0; k<num; k++)
    {
        printf("请输入要删除的学生的姓名(一次输入一个学生姓名):\n");
        scanf("%s",stu_name);
        for(i=0; i<n; i++)
        {
            if(strcmp(stu[i].name,stu_name) == 0)
            {
		system("date >> log.log");
                fprintf(fp,"%s	%s %8s %11s %8.2f\n","student del ",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);
                for(j=0; stu[i].class[j]; j++)
                {
                    for(p=0; p<class_number; p++)
                    {
                        tmp = j;
                        for(q=0; cla[p].class_num[q]; q++,tmp++)
                        {
                            if(stu[i].class[tmp] != cla[p].class_num[q])
                            {
                                break;
                            }
                        }
                        if(cla[p].class_num[q] == '\0')
                        {
                            cla[p].class_peo_num--;
		            system("date >> log.log");
                            fprintf(fp,"%s	%4s %12s %10s %7d %8.2f %8d %8d\n","class change ",cla[p].class_num,cla[p].class_name,cla[p].class_pro,cla[p].teach_hour,cla[p].credit_hour,cla[p].class_peo_num,cla[p].class_peo_max);
                        }
                    }
                }
                for(j=i; j<n-1; j++)
                {
                    stu[j] = stu[j+1];
                }
                n--;
                break;
            }
        }
    }
    fclose(fp);
    return n;
}

/*查找学生的信息*/
void stu_find(int n)
{
    char stu_name[20];
    int i;
    printf("请输入要查找的学生姓名:\n");
    scanf("%s",stu_name);
    for(i=0; i<n; i++)
    {
        if(strcmp(stu[i].name,stu_name) == 0)
        {
            printf("学号    姓名  已选课程列表  已选课程总计学分\n");
            printf("%s %8s %11s %8.2f\n",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);
            break;
        }
    }
    if(i == n)
    {
        printf("没有找到该学生的信息\n");
    }
} 

/*修改学生的信息*/
void stu_mode(int n,int class_number)
{
    char stu_name[20],stu_class[20],stu_num[10];
    int i,choice,j,p,q,tmp,f;
    float stu_sum;
    FILE *fp;

    if((fp=fopen("log.log","a+")) == NULL)
    {
        printf("error\n");
        exit(1);
    }

    printf("请输入要修改的学生姓名:\n");
    scanf("%s",stu_name);
    for(i=0; i<n; i++)
    {
        if(strcmp(stu[i].name,stu_name) == 0)
        {
            break;
        }
    }
    while((choice = stu_mode_Menu()) != 4)
    {
        switch(choice)
        {
            case 1: printf("请输入改正后的学号：\n");
                    scanf("%s",stu_num);
                    strcpy(stu[i].num,stu_num); break;
            case 2: printf("请输入改正后的姓名:\n");
                    scanf("%s",stu_name);
                    strcpy(stu[i].name,stu_name); break;
            case 3: printf("请输入改正后的课程列表:\n");
                    scanf("%s",stu_class);
                    stu[i].sum = 0;
                    for(j=0; stu[i].class[j]; j++)  //在更改课程列表的时候，把之前相应的选课人数减1
                    {
                        for(p=0; p<class_number; p++)
                        {
                            tmp = j;
                            for(q=0; cla[p].class_num[q]; q++,tmp++)
                            {
                                if(stu[i].class[tmp] != cla[p].class_num[q])
                                {
                                    break;
                                }
                            }
                            if(cla[p].class_num[q] == '\0')
                            {
                                cla[p].class_peo_num--;
                            }
                        }
                    }

                    strcpy(stu[i].class,stu_class);

                    for(j=0; stu[i].class[j]; j++)  //如果输入的课程已达上限，则不选该课程
                    {
                        for(p=0; p<class_number; p++)
                        {
                            tmp = j;
                            for(q=0; cla[p].class_num[q]; q++,tmp++)
                            {
                                if(stu[i].class[tmp] != cla[p].class_num[q])
                                {
                                    break;
                                }
                            }
                            if(cla[p].class_num[q] == '\0' && cla[p].class_peo_num < cla[p].class_peo_max)
                            {
                                stu[i].sum = stu[i].sum+cla[p].credit_hour;
                                cla[p].class_peo_num++;
                            }
                            else if(cla[p].class_num[q] == '\0' && cla[p].class_peo_num >= cla[p].class_peo_max)
                            {
                                for(tmp=j; tmp<j+q+1; tmp++)
                                {
                                    if(j == 0)
                                    {                        
                                        f = j;
                                    }
                                    else
                                    {
                                        f = j-1;
                                    }
                                    for(; stu[i].class[f]; f++)   
                                    {
                                        stu[i].class[f] = stu[i].class[f+1];
                                    }
                                    if(stu[i].class[0] == ',')
                                    {
                                        for(f=0; stu[i].class[f]; f++)   
                                        {
                                            stu[i].class[f] = stu[i].class[f+1];
                                        }
                                    }
                                }
                                j--;
                            }
                        };
                    }break;
            default:
                    printf("输入错误，请重新输入\n");
        }
    }
    printf("修改之后的学生信息为：\n");
    printf("学号    姓名  已选课程列表  已选课程总计学分\n");
    printf("%s %8s %11s %8.2f\n",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);    
    system("date >> log.log");
    fprintf(fp,"%s	%s %8s %11s %8.2f\n","student change ",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);
    fclose(fp);      
}

/*输出学生信息*/
void print_stu(int n)
{
    int i;
    printf("\n学生管理系统的内容为(stu_infor):\n\n");
    printf("学号    姓名  已选课程列表  已选课程总计学分\n");
    for(i=0; i<n; i++)
    {
        printf("%s %8s %11s %8.2f\n",stu[i].num,stu[i].name,stu[i].class,stu[i].sum);
    }
}


