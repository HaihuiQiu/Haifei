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
        printf("��ѡ����(��������0-6)��");
        scanf("%d",&shuzi);
    }


    return 0;
}

void souye()  //��ҳ����
{
    int shuzi;
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


}

void luru()      //�ɼ�¼��
{
    struct subject
    {
        char kemu[20];   //��Ŀ
        int score;      //����
        int xuefen;     //ѧ��
    };
    struct Student
    {
        int xuehao;     //ѧ��
        char name[20];  //����
        struct subject SUBJECT[100];

    }student[100];
    int n,j;

    printf("������ѧ��ѧ�ţ�");
    scanf("%d",&student[i].xuehao);
    printf("������ѧ��������");
    scanf("%10s",&student[i].name);
    printf("������Ҫ������ٸ���Ŀ��");
    scanf("%d",&n);
    for(j=0;j<n;j++)
    {
        printf("��%d����Ŀ�ǣ�",j+1);
        scanf("%s",&student[i].SUBJECT[i].kemu);
        printf("�ÿ�Ŀѧ���ǣ�");
        scanf("%d",&student[i].SUBJECT[i].xuefen);
        printf("�ÿ�Ŀ�����ǣ�");
        scanf("%d",&student[i].SUBJECT[i].score);
    }
    i++;
    printf("��һ����Ŀ��%s\n",student[0].SUBJECT[0].kemu);
    printf("��һ����Ŀ������%d\n",student[0].SUBJECT[0].score);

}
