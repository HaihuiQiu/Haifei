#include<stdio.h>
#include <stdlib.h>
int iCount;
int shuzi,j;
char ch;
struct subject
{
    char kemu[20];   //科目
    double score;      //绩点
    double xuefen;     //学分
};
struct Student
{
    double xuehao;     //学号
    char name[20];  //姓名
    double sum;    //总学分
    double SUM;     //总学分乘于绩点
    int keshu;   //科目数
    struct subject SUBJECT[100];
    struct Student* pNext;
};
void souye()  //首页界面
{
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
    scanf("%d",&shuzi);
    printf("\n\n");

}
struct Student* Create()
{
    struct Student* pHead=NULL;//初始化链表头指针为空
    struct Student* pEnd,*pNew;
    pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
    iCount=0;//初始化链表长度
    int n,j;
    void show1()
    {

        printf("请输入学生学号：");
        scanf("%lf",&pNew->xuehao);


        printf("请输入学生姓名：");
        scanf("%s",&pNew->name);
        printf("请问你要输入多少个科目：");
        scanf("%d",&n);
        for(j=0;j<n;j++)
        {
            printf("第%d个科目是：",j+1);
            scanf("%s",&pNew->SUBJECT[j].kemu);
            printf("该科目学分是：");
            scanf("%lf",&pNew->SUBJECT[j].xuefen);
            printf("该科目绩点是：");
            scanf("%lf",&pNew->SUBJECT[j].score);
            printf("\n");
            pNew->sum=pNew->sum+pNew->SUBJECT[j].xuefen;//总学分
            pNew->SUM=pNew->SUM+pNew->SUBJECT[j].xuefen*pNew->SUBJECT[j].score;
            pNew->keshu++;  //储存科目数
        }
        printf("%s的平均绩点是%.2lf\n",pNew->name,pNew->SUM/pNew->sum);   //计算平均绩点
    }
    char ch;
    pNew->keshu=0;
    pNew->sum=0,pNew->SUM=0;
    int i,m;
    show1();

    while(pNew->xuehao!=0)
    {
        iCount++;
        if(iCount==1)
        {
            pNew->pNext=pHead;//使得指向为空
            pEnd=pNew;        //跟踪新加入的节点
            pHead=pNew;       //头指针指向首节点
        }
        else
        {
            pNew->pNext=NULL;//新节点指针为空
            pEnd->pNext=pNew;//原来的尾节点指向新节点
            pEnd=pNew;       //*pEnd指向新节点

        }

        pNew=(struct Student*)malloc(sizeof(struct Student));//再次分配节点内存空间

      abc:  printf("是否继续录入成绩？（y/n）");
        scanf("%s",&ch);
        printf("\n");
        if(ch=='y'||ch=='Y')
            show1();
        else if(ch=='n'||ch=='N')
            break;
        else
        {
            printf("请正确输入\n");
            goto abc;
        }

    }
    free(pNew);//释放没有用到的空间
    return pHead;
}

void Print(struct Student* pHead)
{
    struct Student*pTemp;
    pTemp=pHead;
    int ilndex=1;
    int j;
    void show2()
    {
        printf("姓名：%s\n",pTemp->name);
        printf("学号：%.0lf\n",pTemp->xuehao);
        printf("共有%d科成绩\n",pTemp->keshu);
        for(j=0;j<pTemp->keshu;j++)
        {
            printf("%s有%.1lf个学分 绩点为%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);

        }
        printf("%s的平均绩点是%.2lf\n",pTemp->name,pTemp->SUM/pTemp->sum);
    }

    printf("通过学号查找请输入数字1\n通过姓名查找请输入数字2\n请输入数字");
    scanf("%d",&j);
    if(j==1)
    {
        double XH;//粗存临时学号
        printf("请输入学号");
        scanf("%lf",&XH);
        while(XH!=pTemp->xuehao)
        {
            printf("到这里\n\n\n\n\n\n\n\n\n\n");
            pTemp=pTemp->pNext;
            if(pTemp==NULL)
            {
                printf("纪录中不存在%.0lf",XH);
                return;
            }
        }

    }
    else if(j==2)
    {
        char XM[20];
        printf("请输入姓名");
        scanf("%s",&XM);
        while(XM!=pTemp->name)
        {
            pTemp=pTemp->pNext;
            if(pTemp==NULL)
            {
                printf("纪录中不存在%s",XM);
                return;
            }
        }

    }
    else
    {
        printf("输入错误！\n");
        Print(pHead);
    }
    show2();
    printf("是否继续查询成绩？（y/n）");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
    {
            Print(pHead);
    }
}
void Delete(struct Student* pHead)//删除信息
{
    double ilndex;
    struct Student* pTemp;//临时指针
    struct Student* pPre;//表示要删除节点前的节点
    pTemp=pHead;
    pPre=pTemp;
    printf("请输入要删除的学号");
    scanf("%lf",&ilndex);
    while(ilndex!=pTemp->xuehao)
    {

        if(pTemp==NULL)
        {
            printf("纪录中不存在%.0lf",ilndex);
            return;
        }
        pPre=pTemp;
        pTemp=pTemp->pNext;
    }
    printf("姓名：%s\n",pTemp->name);
    printf("学号：%.0lf\n",pTemp->xuehao);
    printf("共有%d科成绩\n",pTemp->keshu);
    for(j=0;j<pTemp->keshu;j++)
    {
        printf("%s有%.1lf个学分 绩点为%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);
    }
    printf("%s的平均绩点是%.2lf\n",pTemp->name,pTemp->SUM/pTemp->sum);

    printf("是否删除该学生信息（Y/N）");
    scanf("%s",&ch);
    if(ch=='y'||ch=='Y')
    {
        pPre->pNext=pTemp->pNext;//连接删除节点两边的节点
        free(pTemp);
        iCount--;
        printf("信息删除成功！");
    }
    else
        return;

}

void Inset(struct Student*pHead)
{
    double XH;
    int n;
    struct Student*pTemp;
    pTemp=pHead;
    printf("请输入学号");
    scanf("%lf",&XH);
    while(XH!=pTemp->xuehao)
    {
        if(pTemp==NULL)
        {
            printf("纪录中不存在%lf",XH);
            return;
        }
        pTemp=pTemp->pNext;
    }
    printf("请输入要增加的科目数");
    scanf("%d",&n);
    j=pTemp->keshu;
    while((n+j)!=pTemp->keshu)
    {
        pTemp->keshu++;
        printf("科目名称:");
        scanf("%s",&pTemp->SUBJECT[pTemp->keshu].kemu);
        printf("科目学分:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].xuefen);
        printf("科目绩点:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].score);
    }
    printf("修改成功！\n\n");
    printf("姓名：%s\n",pTemp->name);
    printf("学号：%.0lf\n",pTemp->xuehao);
    printf("共有%d科成绩\n",pTemp->keshu);
    for(j=0;j<pTemp->keshu;j++)
    {
        printf("%s有%.1lf个学分 绩点为%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);
    }
    printf("%s的平均绩点是%.2lf\n",pTemp->name,pTemp->SUM/pTemp->sum);

}
int writeInfo(struct Student *pHead)   //保存信息
{
    FILE *fp;
    struct Student *p;
    p=pHead;
    if((fp=fopen("chengji.txt","ab+"))==NULL)
    {
        printf("打开文件失败!");
        return;
    }
    while(p!=NULL)
    {

        fwrite(p,sizeof(struct Student),1,fp);;
        p=p->pNext;
    }
    printf("信息保存成功!\n");
    fclose(fp);
}

struct Student *readInfo()
{
    FILE *fp;
   // struct Student *pHead=NULL;
    struct Student *pEnd,*pNew;

    iCount=0;
    pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
    if((fp=fopen("chengji.txt","ab+"))==NULL)
    {
        printf("打开文件失败!\n");
        return;
    }
    while(fread(pNew,sizeof(struct Student),1,fp)!=NULL)
    {
        printf("pNew->name=%s\n",pNew->name);
        printf("pNew->xuehao=%.0lf\n",pNew->xuehao);
        printf("pNew->SUBJECT[0].kemu=%s\n",pNew->SUBJECT[0].kemu);
        printf("pNew->pNew->SUBJECT[0].xuefen=%.1lf\n",pNew->SUBJECT[0].xuefen);
        printf("pNew->SUBJECT[0].score=%.2lf\n",pNew->SUBJECT[0].score);
        iCount++;
        pNew->pNext=NULL;//新节点指针为空
        pEnd->pNext=pNew;//原来的尾节点指向新节点
        pEnd=pNew;//*pEnd指向新节点

//
//                    printf("第%d个科目是：",j+1);
//            scanf("%s",&pNew->SUBJECT[j].kemu);
//            printf("该科目学分是：");
//            scanf("%lf",&pNew->SUBJECT[j].xuefen);
//            printf("该科目绩点是：");
//            scanf("%lf",&pNew->SUBJECT[j].score);
    }

    fclose(fp);
    if(iCount==0)
    {
        printf("没有信息记录！\n");
        return;
    }

    printf("信息读入成功!\n");
    return 0;                /*返回链表的头指针*/
}
int main()
{

    struct Student* pHead;
    readInfo();
    souye();
    while(shuzi)
    {
        switch(shuzi)
        {
            case 1:pHead=Create();writeInfo(pHead);break;//录入信息
            case 2:Print(pHead);break;//查询信息
            case 3:Delete(pHead);break;//删除信息
            case 4:Inset(pHead);break;//增加科目
            case 5:break;
            case 6:break;
            default:break;
        }
        printf("\n\n");
        souye();
    }
    return 0;
}



