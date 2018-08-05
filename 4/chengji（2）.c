#include<stdio.h>
#include<string.h>
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
    double point;  //绩点
    int rank;   //绩点排名
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
    printf("4:信息补录\n");
    printf("5:成绩排名\n");
    printf("6:人数统计\n");
    printf("7:保存退出\n");
    printf("请选择功能(输入数字0-6)：");
    scanf("%d",&shuzi);
    printf("\n\n");

}
struct Student* Create(struct Student* pHead)
{
   // struct Student* pHead=NULL;//初始化链表头指针为空
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
            pNew->point=pNew->SUM/pNew->sum;
            pNew->keshu++;  //储存科目数
        }
        printf("%s的平均绩点是%.2lf\n",pNew->name,pNew->point);   //计算平均绩点
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
    if(pTemp==NULL)
    {
        printf("没有数据！！！\n");
        return;
    }

    int ilndex=1;
    int j;
 /*   void abc(struct Student*pTemp)
    {
        struct Student*p=pTemp;
        struct Student*p0;
        struct Student*p1;
        struct Student*p2;
        for(p0=pTemp;p0->pNext!=NULL;p0=p0->pNext)
        {
            for(p1=pTemp,p2=p1->pNext;p1->pNext!=NULL;p1=p1->pNext,p2=p2->pNext)
            {
                if(p1->point<p2->point)
                {
                    int ab=p1->rank;
                    p1->rank=p2->rank;
                    p2->rank=ab;
                }
            }
        }
        int i=0;
        while(p!=NULL)
        {
            p->rank=++i;
            printf("%d ",p->rank);
            p=p->pNext;
        }
    }
	
	
    abc(pHead);*/
    void show2()
    {
        printf("\t姓名：%s\n",pTemp->name);
        printf("\t学号：%.0lf\n",pTemp->xuehao);
        printf("\t科目\t学分\t绩点\n");
        for(j=0;j<pTemp->keshu;j++)
        {
            printf("\t%s\t%.1lf\t%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);

        }
        printf("\t平均绩点：%.2lf\n\n",pTemp->point);
      //  printf("\t绩点排名：%d\n\n",pTemp->rank);
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
        while(strcmp(XM,pTemp->name)!=0)
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
        Print(pTemp);
    }
    show2();
    char ch;
    printf("是否继续查询成绩？（y/n）");
    scanf("%s",&ch);
    if(ch=='y'||ch=='Y')
    {
            Print(pTemp);
    }
    else
        return;
}
void Delete(struct Student* pHead)//删除信息
{
    double ilndex;
    struct Student* pTemp;//临时指针
    struct Student* pPre;//表示要删除节点前的节点
    pTemp=pHead;
    if(pTemp==NULL)//判断是否有数据
    {
        printf("没有数据！！！\n");
        return;
    }
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
    printf("%s的平均绩点是%.2lf\n",pTemp->name,pTemp->point);

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
    int n,j,i;
    struct Student*pTemp;
    pTemp=pHead;
    if(pTemp==NULL)
    {
        printf("没有数据！！！\n");
        return;
    }
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
    i=pTemp->keshu;
    while((n+i)!=pTemp->keshu)
    {

        printf("科目名称:");
        scanf("%s",&pTemp->SUBJECT[pTemp->keshu].kemu);
        printf("科目学分:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].xuefen);
        printf("科目绩点:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].score);
        pTemp->sum=pTemp->sum+pTemp->SUBJECT[pTemp->keshu].xuefen;//总学分
        pTemp->SUM=pTemp->SUM+pTemp->SUBJECT[pTemp->keshu].xuefen*pTemp->SUBJECT[pTemp->keshu].score;
        pTemp->point=pTemp->SUM/pTemp->sum;
        pTemp->keshu++;
    }
    printf("修改成功！\n\n");
    printf("姓名：%s\n",pTemp->name);
    printf("学号：%.0lf\n",pTemp->xuehao);
    printf("共有%d科成绩\n",pTemp->keshu);
    for(j=0;j<pTemp->keshu;j++)
    {
        printf("%s有%.1lf个学分 绩点为%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);
    }
    printf("%s的平均绩点是%.2lf\n",pTemp->name,pTemp->point);

}


int rinking(struct Student *pHead)
{
    struct Student*pTemp=pHead;
    struct Student*p0;
    struct Student*p1;
    struct Student*p2;
    if((pTemp==NULL)||(pTemp->pNext==NULL))
    {
        printf("没有数据！！！\n\n");
        return 0;
    }

    void swapNode(struct Student*p1,struct Student*p2 )
    {
        char Ch[20];
        int Temp;
        double Temp1;

        Temp1=p1->xuehao;
        p1->xuehao=p2->xuehao;
        p2->xuehao=Temp1;

        strcpy(Ch,p1->name);
        strcpy(p1->name,p2->name);
        strcpy(p2->name,Ch);

        Temp1=p1->point;
        p1->point=p2->point;
        p2->point=Temp1;

        return;
    }
    for(p0=pHead;p0->pNext!=NULL;p0=p0->pNext)
    {
        for(p1=pHead,p2=p1->pNext;p1->pNext!=NULL;p1=p1->pNext,p2=p2->pNext)
        {
            if(p1->point<p2->point)
            {

                swapNode(p1,p2);
            }
        }
    }
    pTemp=pHead;
    int rank1=0;//名次临时变量
    printf("\t名次\t学号\t\t姓名\t\t绩点\n");
    while(pTemp!=NULL)
    {
        printf("\t%d\t%.0lf\t\t%s\t\t%.2lf\n",pTemp->rank=++rank1,pTemp->xuehao,pTemp->name,pTemp->point);
        pTemp=pTemp->pNext;
    }


}


int writeInfo(struct Student *pHead)   //保存信息
{
    FILE *fp;
    struct Student *p;
    p=pHead;
    if((fp=fopen("data.data","wb"))==NULL)
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

//读入数据
struct Student *readInfo()
{
    FILE *fp;
    struct Student *pHead=NULL;
    struct Student *pEnd,*pNew;

    iCount=0;
    pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
    if((fp=fopen("data.data","ab+"))==NULL)
    {
        printf("打开文件失败!\n");
        return;
    }
    while(fread(pNew,sizeof(struct Student),1,fp)!=0)
    {
        printf("pNew->name=%s\n",pNew->name);
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

    }

    free(pNew);//释放没有用到的空间
    fclose(fp);
    if(iCount==0)
    {
        printf("没有信息记录！\n");
        return;
    }
    printf("信息读入成功!\n");
    return pHead;                /*返回链表的头指针*/
}
int main()
{

    struct Student* pHead;
    pHead=readInfo();
    souye();
    while(shuzi)
    {
        switch(shuzi)
        {
            case 1:pHead=Create(pHead);writeInfo(pHead);break;//录入信息
            case 2:Print(pHead);break;//查询信息
            case 3:Delete(pHead);writeInfo(pHead);break;//删除信息
            case 4:Inset(pHead);writeInfo(pHead);break;//增加科目
            case 5:rinking(pHead);pHead=readInfo();break;
            case 6:break;
            case 7:shuzi=0;break;
        }
        printf("\n\n");
        if(shuzi==0)
            break;
        souye();
    }
    return 0;
}



