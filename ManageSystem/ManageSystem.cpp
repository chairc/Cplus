#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ListInitSize 20

typedef struct{
	int id;
	char name[20];
	short int age;
	char phone[20];
	char native[20];
}Student;

typedef struct{
	Student Stu[20];
	//int length;
}SqList;

int stdnum=0;   //���ڶ�ȡ����ʱ��¼�����ļ�ʱ��

void ReadStuInfo(SqList &L){
	int i,n=0;
	FILE *fp;
	fp=fopen("student.txt","r");
	printf("ѧ��ѧ�� ���� ���� �绰 ����Ϊ��\n");
	while(!feof(fp)){
		fscanf(fp,"%d %s %d %s %s\n",&L.Stu[n].id,L.Stu[n].name,&L.Stu[n].age,L.Stu[n].phone,L.Stu[n].native);
		n++;
	}
	stdnum=n;
	fclose(fp);
}

void SaveStuInfo(SqList &L){
	int i;
	FILE *fp;
	fp=fopen("student.txt","w");
	printf("������ѧ��������");
	scanf("%d",&stdnum);
	printf("����������ѧ��ѧ�� ���� ���� �绰 ���᣺\n");
	for(i=0;i<stdnum;i++){
		scanf("%d %s %d %s %s",&L.Stu[i].id,L.Stu[i].name,&L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
		fprintf(fp,"%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
	fclose(fp);
}

void InsertStuInfo(SqList &L){
	int addstdnum,i;
	FILE *fp;
	fp=fopen("student.txt","a");
	printf("����������ѧ��������");
	scanf("%d",&addstdnum);
	for(i=0;i<addstdnum;i++){
		scanf("%d %s %d %s %s",&L.Stu[i].id,L.Stu[i].name,&L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
		fprintf(fp,"%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
	fclose(fp);
}

void DeleteStuInfo(SqList &L){
	int searchid,i,j;
	printf("������ɾ��ѧ����Ϣ��ѧ�ţ�\n");
	scanf("%d",&searchid);
	for(i=0;i<stdnum;i++){
		if(L.Stu[i].id==searchid){
			for(j=i;j<stdnum;j++){
//				L.Stu[j].id=L.Stu[j+1].id;
//				strcpy(L.Stu[j].name,L.Stu[j+1].name);
//				L.Stu[j].age=L.Stu[j+1].age;
//				strcpy(L.Stu[j].phone,L.Stu[j+1].phone);
//				strcpy(L.Stu[j].native,L.Stu[j+1].native);
				L.Stu[j]=L.Stu[j+1];
			}
		}
	}
	FILE *fp;
	fp=fopen("student.txt","w");
	for(i=0;i<stdnum-1;i++){
		fprintf(fp,"%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
	stdnum=stdnum-1;
	fclose(fp);
}

void PrintfStuInfo(SqList L){
	int i;
	for(i=0;i<stdnum;i++){
		printf("%d %s %d %s %s\n",L.Stu[i].id,L.Stu[i].name,L.Stu[i].age,L.Stu[i].phone,L.Stu[i].native);
	}
}

int main() {
	SqList L;
	int switchnum=-1;
	int switchcase=0;	
	while(switchnum!=0){
		printf("��ӭ�����༶����ϵͳ��\n��1��д��ѧ����Ϣ\n��2����ȡѧ����Ϣ\n��3������ͬѧ��Ϣ\n��4��ɾ��ͬѧ��Ϣ\n��0���˳�\n");
		printf("������ѡ�����ţ�");
		scanf("%d",&switchnum);
		switch(switchnum){
			case 1:
				printf("�Ƿ�д�����ݣ���������1������������0��ע�⣺��ѡ��д������ʱ�������ļ�������\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					SaveStuInfo(L);
					PrintfStuInfo(L);
				}
				switchcase=0; 
				break;
			case 2:
				ReadStuInfo(L);
				PrintfStuInfo(L);
				break;
			case 3:
				printf("�Ƿ�������ݣ���������1������������0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					ReadStuInfo(L);
					InsertStuInfo(L);
				}
				switchcase=0; 	
				break;
			case 4:
				printf("�Ƿ�ɾ�����ݣ���������1������������0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					ReadStuInfo(L);
					DeleteStuInfo(L);
				}
				switchcase=0; 
				break;
			case 0:
				exit(0);
			default:
				printf("��������������������룡"); 
		}
	}
	return 0;
}
