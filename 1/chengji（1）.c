#include<stdio.h>
#include <stdlib.h>
static int i=0;

void souye();
void luru();

int main()
{
    souye();
    int shuzi;
    scanf("%d",&shuzi);
    while(shuzi)
    {
        switch(shuzi)
        {
            case 1:luru();break;
            case 2:break;
            case 3:break;
            case 4:break;
            case 5:break;
            case 6:break;
            default:break;
        }
        printf("\n\n");
        souye();
        printf("请选择功能(输入数字0-6)：");
        scanf("%d",&shuzi);
    }


    return 0;
}

void souye()  //首页界面
{
    int shuzi;
    system ("color 0a");
    printf(" 学生成绩管理系统\n\n");
    printf("1:成绩录入\n");
    printf("2:成绩查询\n");
    printf("3:信息删除\n");
    printf("4:信息修改\n");
    printf("5:成绩排名\n");
    printf("6:人数统计\n");
    printf("0:退出系统\n");
    printf("请选择功能(输入数字0-6)：");


}

void luru()      //成绩录入
{
    struct subject
    {
        char kemu[20];   //科目
        int score;      //分数
        int xuefen;     //学分
    };
    struct Student
    {
        int xuehao;     //学号
        char name[20];  //姓名
        struct subject SUBJECT[100];

    }student[100];
    int n,j;

    printf("请输入学生学号：");
    scanf("%d",&student[i].xuehao);
    printf("请输入学生姓名：");
    scanf("%10s",&student[i].name);
    printf("请问你要输入多少个科目：");
    scanf("%d",&n);
    for(j=0;j<n;j++)
    {
        printf("第%d个科目是：",j+1);
        scanf("%s",&student[i].SUBJECT[i].kemu);
        printf("该科目学分是：");
        scanf("%d",&student[i].SUBJECT[i].xuefen);
        printf("该科目分数是：");
        scanf("%d",&student[i].SUBJECT[i].score);
    }
    i++;
    printf("第一个科目是%s\n",student[0].SUBJECT[0].kemu);
    printf("第一个科目分数是%d\n",student[0].SUBJECT[0].score);

}
