#include "modulea.h"
#include "../main.h"

/*课程管理系统菜单*/
int Menu_class()
{
    int choice;
    printf("\n\t########################################################\n");
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##           欢 迎 进 入 课 程 管 理 系 统            ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##                 1:新增课程信息                     ##\n");
    printf("\t##                 2:删除课程信息                     ##\n");
    printf("\t##                 3:查找课程信息                     ##\n");
    printf("\t##                 4:修改课程信息                     ##\n");
    printf("\t##                 5:输出课程信息                     ##\n");
    printf("\t##                 6:退出                             ##\n");     
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t########################################################\n");
    printf("\n请输入你的选择:");
    scanf("%d",&choice);
    return choice;
}

/*修改课程信息的菜单*/
int class_mode_menu()
{
    int choice;
    printf("\n\t########################################################\n");
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##       欢 迎 进 入 修 改 课 程 信 息 系 统           ##\n");
    printf("\t##                                                    ##\n");
    printf("\t##                 1:修改课程编号                     ##\n");
    printf("\t##                 2:修改课程名称                     ##\n");
    printf("\t##                 3:修改课程性质                     ##\n");
    printf("\t##                 4:修改授课学时                     ##\n");
    printf("\t##                 5:修改课程学分                     ##\n");
    printf("\t##                 6:修改课程已选人数                 ##\n");
    printf("\t##                 7:修改课程人数上限                 ##\n");
    printf("\t##                 8:退出                             ##\n");     
    printf("\t##                                                    ##\n");
    printf("\t##                                                    ##\n");
    printf("\t########################################################\n");
    printf("\n请输入你的选择:");
    scanf("%d",&choice);
    return choice;
}

/*从键盘输入课程信息*/
int creat_class(int class_number)
{
    int i,n;
    FILE *fp;

    if((fp=fopen("log.log","a+")) == NULL)
    {
        printf("error\n");
        exit(1);
    }

    printf("please enter the number of courses:\n");
    scanf("%d",&n);
    printf("please enter class information(课程编号 课程名称 课程性质 授课学时 学分 课程已选人数 课程人数上限,输入内容以tab作为分隔符):\n");
    for(i=class_number; i<n+class_number; i++)
    {
        scanf("%s %s %s %d %f %d %d",cla[i].class_num,cla[i].class_name,cla[i].class_pro,&cla[i].teach_hour,&cla[i].credit_hour,&cla[i].class_peo_num,&cla[i].class_peo_max);
	system("date >> log.log");
        fprintf(fp,"%s	%4s %12s %10s %7d %8.2f %8d %8d\n","class input ",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
    }
    fclose(fp);
    return i;
}

/*从文件读取课程信息*/
int creat_class_file(int class_number,FILE *fp1)
{
    int i=class_number;
    if((fp1=fopen("class.txt","r+")) == NULL)
    {
        printf("class.txt error!\n");
        exit(1);
    }
    while(!feof(fp1))
    {
        fscanf(fp1,"%s %s %s %d %f %d    %d",cla[i].class_num,cla[i].class_name,cla[i].class_pro,&cla[i].teach_hour,&cla[i].credit_hour,&cla[i].class_peo_num,&cla[i].class_peo_max);
        i++;
    }

    fclose(fp1);
    return i-1;
}

/*删除课程的信息*/
int class_del(int n,int stu_number)
{
    char name[20];
    int i,j,k,num,p,q,t,tmp;
    FILE *fp;

    if((fp=fopen("log.log","a+")) == NULL)
    {
        printf("error\n");
        exit(1);
    }
    fprintf(fp,"test");
    printf("请输入要删除的课程的个数:\n");
    scanf("%d",&num);
    for(k=0; k<num; k++)
    {
        printf("请输入要删除的课程名称(一次输入一个课程名称):\n");
        scanf("%s",name);
        for(i=0; i<n; i++)
        {
            if(strcmp(cla[i].class_name,name) == 0)
            {
		system("date >> log.log");
                fprintf(fp,"%s	%4s %12s %10s %7d %8.2f %8d %8d\n","class del ",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
                for(p=0; p<stu_number; p++)   //删除课程的时候，把学生系统里相应的这个课程删除，并减掉相应的学分
                {
                    for(q=0; stu[p].class[q]; q++)
                    {
                        if(cla[i].class_num[0] == stu[p].class[q])                      
                        {
                            tmp = q;                            
                            for(t=0; cla[i].class_num[t]; t++,tmp++)
                            {
                                if(cla[i].class_num[t] != stu[p].class[tmp])
                                {
                                    break;
                                }
                            }
                            if(cla[i].class_num[t] == '\0')
                            {
                                for(tmp=q; tmp<q+t+1; tmp++)
                                {
                                    if(q == 0)
                                    {
                                        j = q;
                                    }
                                    else
                                    {
                                        j = q-1;
                                    }
                                    for(; stu[p].class[j]; j++)   
                                    {
                                        stu[p].class[j] = stu[p].class[j+1];
                                    }
                                }
                                if(stu[p].class[0] == ',')
                                {
                                    for(j=0; stu[p].class[j]; j++)   
                                    {
                                        stu[p].class[j] = stu[p].class[j+1];
                                    }
                                }
                                q = q+t;
                                stu[p].sum = stu[p].sum-cla[i].credit_hour;
                                fprintf(fp,"%s	%s %8s %11s %8.2f\n","student change ",stu[p].num,stu[p].name,stu[p].class,stu[p].sum);
                                break;
                            }
                        }
                    }
                }   
                for(j=i; j<n-1; j++)
                {
                    cla[j] = cla[j+1];
                }
                n--;
                break;
            }
        } 
    }
    fclose(fp);
    return n;
}

/*查找课程的信息*/
void class_find(int n)
{
    char name[20];
    int i;
    printf("请输入要查找的课程名称:\n");
    scanf("%s",name);
    for(i=0; i<n; i++)
    {
        if(strcmp(cla[i].class_name,name) == 0)
        {
            printf("课程编号 课程名称 课程性质 授课学时  学分  课程已选人数 课程人数上限\n");
            printf("%4s %12s %10s %7d %8.2f %8d %8d\n",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
            break;
        }
    }
    if(i == n)
    {
        printf("没有找到该课程的信息\n");
    }
} 

/*修改课程的信息*/
void class_mode(int n,int stu_number)
{
    char name[20];
    int i,choice,p,q,tmp,f;
    class_infor t;
    FILE *fp;

    if((fp=fopen("log.log","a+")) == NULL)
    {
        printf("error\n");
        exit(1);
    }

    printf("请输入要查找的课程名称:\n");
    scanf("%s",name);
    for(i=0; i<n; i++)
    {
        if(strcmp(cla[i].class_name,name) == 0)
        {
            break;
        }
    }
    while((choice = class_mode_menu()) != 8 )
    {
        switch(choice)
        {
            case 1: printf("请输入改正后的课程编号:\n");
                    scanf("%s",t.class_num);
                    for(p=0; p<stu_number; p++) //更改课程编号的时候，把学生系统里相应的编号改掉
                    {
                        for(q=0; stu[p].class[q]; q++)
                        {
                            if(cla[i].class_num[0] == stu[p].class[q])                      
                            {
                                tmp = q;                            
                                for(f=0; cla[i].class_num[f]; f++,tmp++)
                                {
                                    if(cla[i].class_num[f] != stu[p].class[tmp])
                                    {
                                        break;
                                    }
                                }
                                if(cla[i].class_num[f] == '\0')
                                {
                                    for(f=0; t.class_num[f]; f++,q++)
                                    {
                                        stu[p].class[q] = t.class_num[f];
					system("date >> log.log");
                                        fprintf(fp,"%s	%s %8s %11s %8.2f\n","student change ",stu[p].num,stu[p].name,stu[p].class,stu[p].sum);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    strcpy(cla[i].class_num,t.class_num); break;
            case 2: printf("请输入改正后的课程名称:\n");
                    scanf("%s",t.class_name);
                    strcpy(cla[i].class_name,t.class_name); break;
            case 3: printf("请输入改正后的课程性质:\n");
                    scanf("%s",t.class_pro);
                    strcpy(cla[i].class_pro,t.class_pro); break;
            case 4: printf("请输入改正后的授课学时:\n");
                    scanf("%d",&t.teach_hour);
                    cla[i].teach_hour = t.teach_hour; break;
            case 5: printf("请输入改正后的学分:\n");
                    scanf("%f",&t.credit_hour);
                    for(p=0; p<stu_number; p++)  //更改学分的时候，把学生系统里相应的学分更改
                    {
                        for(q=0; stu[p].class[q]; q++)
                        {
                            if(cla[i].class_num[0] == stu[p].class[q])                      
                            {
                                tmp = q;                            
                                for(f=0; cla[i].class_num[f]; f++,tmp++)
                                {
                                    if(cla[i].class_num[f] != stu[p].class[tmp])
                                    {
                                        break;
                                    }
                                }
                                if(cla[i].class_num[f] == '\0')
                                {
                                    stu[p].sum = stu[p].sum+(t.credit_hour-cla[i].credit_hour); 
				    system("date >> log.log");
                                    fprintf(fp,"%s	%s %8s %11s %8.2f\n","student change ",stu[p].num,stu[p].name,stu[p].class,stu[p].sum);                
                                    break;
                                }
                            }
                        }
                    }
                    cla[i].credit_hour = t.credit_hour; break;
            case 6: printf("请输入改正后的课程已选人数:\n");
                    scanf("%d",&t.class_peo_num);
                    cla[i].class_peo_num = t.class_peo_num; break;
            case 7: printf("请输入改正后的课程人数上限:\n");
                    scanf("%d",&t.class_peo_max);
                    cla[i].class_peo_max = t.class_peo_max; break;
            default:
                    printf("输入错误，请重新输入\n");
        }
    }
    printf("修改之后的课程信息为：\n");
    printf("课程编号 课程名称 课程性质 授课学时  学分  课程已选人数 课程人数上限\n");
    printf("%4s %12s %10s %7d %8.2f %8d %8d\n",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
    system("date >> log.log");
    fprintf(fp,"%s	%4s %12s %10s %7d %8.2f %8d %8d\n","class change ",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
    fclose(fp);
}

/*输出课程信息*/
void print_class(int n)
{
    int i;
    printf("\n课程管理系统的内容为(class_infor):\n\n");
    printf("课程编号 课程名称 课程性质 授课学时  学分  课程已选人数 课程人数上限\n");
    for(i=0; i<n; i++)
    {
        printf("%4s %12s %10s %7d %8.2f %8d %8d\n",cla[i].class_num,cla[i].class_name,cla[i].class_pro,cla[i].teach_hour,cla[i].credit_hour,cla[i].class_peo_num,cla[i].class_peo_max);
    }
}

