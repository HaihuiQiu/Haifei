#include<stdio.h>
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
    printf("4:��Ϣ�޸�\n");
    printf("5:�ɼ�����\n");
    printf("6:����ͳ��\n");
    printf("0:�˳�ϵͳ\n");
    printf("��ѡ����(��������0-6)��");
    scanf("%d",&shuzi);
    printf("\n\n");

}
struct Student* Create()
{
    struct Student* pHead=NULL;//��ʼ������ͷָ��Ϊ��
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
            pNew->keshu++;  //�����Ŀ��
        }
        printf("%s��ƽ��������%.2lf\n",pNew->name,pNew->SUM/pNew->sum);   //����ƽ������
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
    int ilndex=1;
    int j;
    void show2()
    {
        printf("������%s\n",pTemp->name);
        printf("ѧ�ţ�%.0lf\n",pTemp->xuehao);
        printf("����%d�Ƴɼ�\n",pTemp->keshu);
        for(j=0;j<pTemp->keshu;j++)
        {
            printf("%s��%.1lf��ѧ�� ����Ϊ%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);

        }
        printf("%s��ƽ��������%.2lf\n",pTemp->name,pTemp->SUM/pTemp->sum);
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
            printf("������\n\n\n\n\n\n\n\n\n\n");
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
        while(XM!=pTemp->name)
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
        Print(pHead);
    }
    show2();
    printf("�Ƿ������ѯ�ɼ�����y/n��");
    scanf("%c",&ch);
    if(ch=='y'||ch=='Y')
    {
            Print(pHead);
    }
}
void Delete(struct Student* pHead)//ɾ����Ϣ
{
    double ilndex;
    struct Student* pTemp;//��ʱָ��
    struct Student* pPre;//��ʾҪɾ���ڵ�ǰ�Ľڵ�
    pTemp=pHead;
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
    printf("%s��ƽ��������%.2lf\n",pTemp->name,pTemp->SUM/pTemp->sum);

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
    int n;
    struct Student*pTemp;
    pTemp=pHead;
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
    j=pTemp->keshu;
    while((n+j)!=pTemp->keshu)
    {
        pTemp->keshu++;
        printf("��Ŀ����:");
        scanf("%s",&pTemp->SUBJECT[pTemp->keshu].kemu);
        printf("��Ŀѧ��:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].xuefen);
        printf("��Ŀ����:");
        scanf("%lf",&pTemp->SUBJECT[pTemp->keshu].score);
    }
    printf("�޸ĳɹ���\n\n");
    printf("������%s\n",pTemp->name);
    printf("ѧ�ţ�%.0lf\n",pTemp->xuehao);
    printf("����%d�Ƴɼ�\n",pTemp->keshu);
    for(j=0;j<pTemp->keshu;j++)
    {
        printf("%s��%.1lf��ѧ�� ����Ϊ%.1lf\n",pTemp->SUBJECT[j].kemu,pTemp->SUBJECT[j].xuefen,pTemp->SUBJECT[j].score);
    }
    printf("%s��ƽ��������%.2lf\n",pTemp->name,pTemp->SUM/pTemp->sum);

}
int writeInfo(struct Student *pHead)   //������Ϣ
{
    FILE *fp;
    struct Student *p;
    p=pHead;
    if((fp=fopen("chengji.txt","ab+"))==NULL)
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

struct Student *readInfo()
{
    FILE *fp;
   // struct Student *pHead=NULL;
    struct Student *pEnd,*pNew;

    iCount=0;
    pEnd=pNew=(struct Student*)malloc(sizeof(struct Student));
    if((fp=fopen("chengji.txt","ab+"))==NULL)
    {
        printf("���ļ�ʧ��!\n");
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
        pNew->pNext=NULL;//�½ڵ�ָ��Ϊ��
        pEnd->pNext=pNew;//ԭ����β�ڵ�ָ���½ڵ�
        pEnd=pNew;//*pEndָ���½ڵ�

//
//                    printf("��%d����Ŀ�ǣ�",j+1);
//            scanf("%s",&pNew->SUBJECT[j].kemu);
//            printf("�ÿ�Ŀѧ���ǣ�");
//            scanf("%lf",&pNew->SUBJECT[j].xuefen);
//            printf("�ÿ�Ŀ�����ǣ�");
//            scanf("%lf",&pNew->SUBJECT[j].score);
    }

    fclose(fp);
    if(iCount==0)
    {
        printf("û����Ϣ��¼��\n");
        return;
    }

    printf("��Ϣ����ɹ�!\n");
    return 0;                /*���������ͷָ��*/
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
            case 1:pHead=Create();writeInfo(pHead);break;//¼����Ϣ
            case 2:Print(pHead);break;//��ѯ��Ϣ
            case 3:Delete(pHead);break;//ɾ����Ϣ
            case 4:Inset(pHead);break;//���ӿ�Ŀ
            case 5:break;
            case 6:break;
            default:break;
        }
        printf("\n\n");
        souye();
    }
    return 0;
}



