#include<stdio.h>
#include<string.h>
#include <stdlib.h>
int iCount;
int shuzi,j;
char ch;
struct subject
{
    char kemu[20];   //��Ŀ
    double score;      //����
    double xuefen;     //ѧ��
};
struct Student
{
    double xuehao;     //ѧ��
    char name[20];  //����
    double sum;    //��ѧ��
    double SUM;     //��ѧ�ֳ��ڼ���
    int keshu;   //��Ŀ��
    double point;  //����
    int rank;   //��������
    struct subject SUBJECT[100];
    struct Student* pNext;
};


void souye()  //��ҳ����
{
    system ("color 0a");
    printf(" ѧ���ɼ�����ϵͳ\n\n");
    printf("1:�ɼ�¼��\n");
    printf("2:�ɼ���ѯ\n");
    printf("3:��Ϣɾ��\n");
    printf("4:��Ϣ��¼\n");
    printf("5:�ɼ�����\n");
    printf("6:����ͳ��\n");
    printf("7:�����˳�\n");
    printf("��ѡ����(��������0-6)��");
    scanf("%d",&shuzi);
    printf("\n\n");

}
struct Student* Create(struct Student* pHead)
{
   // struct Student* pHead=NULL;//��ʼ������ͷָ��Ϊ��
    struct Student* pEnd,*pNew;
    pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
    iCount=0;//��ʼ��������
    int n,j;
    void show1()
    {

        printf("������ѧ��ѧ�ţ�");
        scanf("%lf",&pNew->xuehao);


        printf("������ѧ��������");
        scanf("%s",&pNew->name);
        printf("������Ҫ������ٸ���Ŀ��");
        scanf("%d",&n);
        for(j=0;j<n;j++)
        {
            printf("��%d����Ŀ�ǣ�",j+1);
            scanf("%s",&pNew->SUBJECT[j].kemu);
            printf("�ÿ�Ŀѧ���ǣ�");
            scanf("%lf",&pNew->SUBJECT[j].xuefen);
            printf("�ÿ�Ŀ�����ǣ�");
            scanf("%lf",&pNew->SUBJECT[j].score);
            printf("\n");
            pNew->sum=pNew->sum+pNew->SUBJECT[j].xuefen;//��ѧ��
            pNew->SUM=pNew->SUM+pNew->SUBJECT[j].xuefen*pNew->SUBJECT[j].score;
            pNew->point=pNew->SUM/pNew->sum;
            pNew->keshu++;  //�����Ŀ��
        }
        printf("%s��ƽ��������%.2lf\n",pNew->name,pNew->point);   //����ƽ������
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
            pNew->pNext=pHead;//ʹ��ָ��Ϊ��
            pEnd=pNew;        //�����¼���Ľڵ�
            pHead=pNew;       //ͷָ��ָ���׽ڵ�
        }
        else
        {
            pNew->pNext=NULL;//�½ڵ�ָ��Ϊ��
            pEnd->pNext=pNew;//ԭ����β�ڵ�ָ���½ڵ�
            pEnd=pNew;       //*pEndָ���½ڵ�

        }

        pNew=(struct Student*)malloc(sizeof(struct Student));//�ٴη���ڵ��ڴ�ռ�

      abc:  printf("�Ƿ����¼��ɼ�����y/n��");
        scanf("%s",&ch);
        printf("\n");
        if(ch=='y'||ch=='Y')
            show1();
        else if(ch=='n'||ch=='N')
            break;
        else
        {
            printf("����ȷ����\n");
            goto abc;
        }

    }
    free(pNew);//�ͷ�û���õ��Ŀռ�
    return pHead;
}

void Print(struct Student* pHead)
{
    struct Student*pTemp;
    pTemp=pHead;
    if(pTemp==NULL)
    {
        printf("û�����ݣ�����\n");
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
        printf("\t������%s\n",pTemp->name);
        printf("\tѧ�ţ�%.0lf\n",pTemp->xuehao);
        printf("\t��Ŀ\tѧ��\t����\n");
        for(j=0;j<pTemp->keshu;j++)
        {
            printf("\t%s\t%.1lf\t%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);

        }
        printf("\tƽ�����㣺%.2lf\n\n",pTemp->point);
      //  printf("\t����������%d\n\n",pTemp->rank);
    }

    printf("ͨ��ѧ�Ų�������������1\nͨ��������������������2\n����������");
    scanf("%d",&j);
    if(j==1)
    {
        double XH;//�ִ���ʱѧ��
        printf("������ѧ��");
        scanf("%lf",&XH);
        while(XH!=pTemp->xuehao)
        {
            pTemp=pTemp->pNext;
            if(pTemp==NULL)
            {
                printf("��¼�в�����%.0lf",XH);
                return;
            }
        }

    }
    else if(j==2)
    {
        char XM[20];
        printf("����������");
        scanf("%s",&XM);
        while(strcmp(XM,pTemp->name)!=0)
        {
            pTemp=pTemp->pNext;
            if(pTemp==NULL)
            {
                printf("��¼�в�����%s",XM);
                return;
            }
        }

    }
    else
    {
        printf("�������\n");
        Print(pTemp);
    }
    show2();
    char ch;
    printf("�Ƿ������ѯ�ɼ�����y/n��");
    scanf("%s",&ch);
    if(ch=='y'||ch=='Y')
    {
            Print(pTemp);
    }
    else
        return;
}
void Delete(struct Student* pHead)//ɾ����Ϣ
{
    double ilndex;
    struct Student* pTemp;//��ʱָ��
    struct Student* pPre;//��ʾҪɾ���ڵ�ǰ�Ľڵ�
    pTemp=pHead;
    if(pTemp==NULL)//�ж��Ƿ�������
    {
        printf("û�����ݣ�����\n");
        return;
    }
    pPre=pTemp;
    printf("������Ҫɾ����ѧ��");
    scanf("%lf",&ilndex);
    while(ilndex!=pTemp->xuehao)
    {

        if(pTemp==NULL)
        {
            printf("��¼�в�����%.0lf",ilndex);
            return;
        }
        pPre=pTemp;
        pTemp=pTemp->pNext;
    }
    printf("������%s\n",pTemp->name);
    printf("ѧ�ţ�%.0lf\n",pTemp->xuehao);
    printf("����%d�Ƴɼ�\n",pTemp->keshu);
    for(j=0;j<pTemp->keshu;j++)
    {
        printf("%s��%.1lf��ѧ�� ����Ϊ%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);
    }
    printf("%s��ƽ��������%.2lf\n",pTemp->name,pTemp->point);

    printf("�Ƿ�ɾ����ѧ����Ϣ��Y/N��");
    scanf("%s",&ch);
    if(ch=='y'||ch=='Y')
    {
        pPre->pNext=pTemp->pNext;//����ɾ���ڵ����ߵĽڵ�
        free(pTemp);
        iCount--;
        printf("��Ϣɾ���ɹ���");
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
        printf("û�����ݣ�����\n");
        return;
    }
    printf("������ѧ��");
    scanf("%lf",&XH);
    while(XH!=pTemp->xuehao)
    {
        if(pTemp==NULL)
        {
            printf("��¼�в�����%lf",XH);
            return;
        }
        pTemp=pTemp->pNext;
    }
    printf("������Ҫ���ӵĿ�Ŀ��");
    scanf("%d",&n);
    i=pTemp->keshu;
    while((n+i)!=pTemp->keshu)
    {

        printf("��Ŀ����:");
        scanf("%s",&pTemp->SUBJECT[pTemp->keshu].kemu);
        printf("��Ŀѧ��:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].xuefen);
        printf("��Ŀ����:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].score);
        pTemp->sum=pTemp->sum+pTemp->SUBJECT[pTemp->keshu].xuefen;//��ѧ��
        pTemp->SUM=pTemp->SUM+pTemp->SUBJECT[pTemp->keshu].xuefen*pTemp->SUBJECT[pTemp->keshu].score;
        pTemp->point=pTemp->SUM/pTemp->sum;
        pTemp->keshu++;
    }
    printf("�޸ĳɹ���\n\n");
    printf("������%s\n",pTemp->name);
    printf("ѧ�ţ�%.0lf\n",pTemp->xuehao);
    printf("����%d�Ƴɼ�\n",pTemp->keshu);
    for(j=0;j<pTemp->keshu;j++)
    {
        printf("%s��%.1lf��ѧ�� ����Ϊ%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);
    }
    printf("%s��ƽ��������%.2lf\n",pTemp->name,pTemp->point);

}


int rinking(struct Student *pHead)
{
    struct Student*pTemp=pHead;
    struct Student*p0;
    struct Student*p1;
    struct Student*p2;
    if((pTemp==NULL)||(pTemp->pNext==NULL))
    {
        printf("û�����ݣ�����\n\n");
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
    int rank1=0;//������ʱ����
    printf("\t����\tѧ��\t\t����\t\t����\n");
    while(pTemp!=NULL)
    {
        printf("\t%d\t%.0lf\t\t%s\t\t%.2lf\n",pTemp->rank=++rank1,pTemp->xuehao,pTemp->name,pTemp->point);
        pTemp=pTemp->pNext;
    }


}


int writeInfo(struct Student *pHead)   //������Ϣ
{
    FILE *fp;
    struct Student *p;
    p=pHead;
    if((fp=fopen("data.data","wb"))==NULL)
    {
        printf("���ļ�ʧ��!");
        return;
    }

    while(p!=NULL)
    {
        fwrite(p,sizeof(struct Student),1,fp);;
        p=p->pNext;
    }
    printf("��Ϣ����ɹ�!\n");
    fclose(fp);
}

//��������
struct Student *readInfo()
{
    FILE *fp;
    struct Student *pHead=NULL;
    struct Student *pEnd,*pNew;

    iCount=0;
    pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
    if((fp=fopen("data.data","ab+"))==NULL)
    {
        printf("���ļ�ʧ��!\n");
        return;
    }
    while(fread(pNew,sizeof(struct Student),1,fp)!=0)
    {
        printf("pNew->name=%s\n",pNew->name);
        iCount++;
        if(iCount==1)
        {
            pNew->pNext=pHead;//ʹ��ָ��Ϊ��
            pEnd=pNew;        //�����¼���Ľڵ�
            pHead=pNew;       //ͷָ��ָ���׽ڵ�
        }
        else
        {
            pNew->pNext=NULL;//�½ڵ�ָ��Ϊ��
            pEnd->pNext=pNew;//ԭ����β�ڵ�ָ���½ڵ�
            pEnd=pNew;       //*pEndָ���½ڵ�

        }
         pNew=(struct Student*)malloc(sizeof(struct Student));//�ٴη���ڵ��ڴ�ռ�

    }

    free(pNew);//�ͷ�û���õ��Ŀռ�
    fclose(fp);
    if(iCount==0)
    {
        printf("û����Ϣ��¼��\n");
        return;
    }
    printf("��Ϣ����ɹ�!\n");
    return pHead;                /*���������ͷָ��*/
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
            case 1:pHead=Create(pHead);writeInfo(pHead);break;//¼����Ϣ
            case 2:Print(pHead);break;//��ѯ��Ϣ
            case 3:Delete(pHead);writeInfo(pHead);break;//ɾ����Ϣ
            case 4:Inset(pHead);writeInfo(pHead);break;//���ӿ�Ŀ
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



