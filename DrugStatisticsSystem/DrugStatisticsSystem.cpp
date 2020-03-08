#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ListInitSize 20

typedef struct{
	//int Med_rank;
	int Med_id;
	char Med_name[30];
	float Med_price;
	float Med_sell_num;
	float Med_sell_price;
}Medicine;

typedef struct{
	Medicine Med[20];
	//int length;
}SqList;

int mednum=0;

void ReadMedInfo(SqList &L){
	int i,n=1;
	FILE *fp;
	fp=fopen("medicine.txt","r");
	printf("ҩƷ��� ҩƷ���� ҩƷ���� ҩƷ�������� ҩƷ���۶�Ϊ��\n");
	while(!feof(fp)){
		fscanf(fp,"%d %s %f %f %f\n",&L.Med[n].Med_id,L.Med[n].Med_name,&L.Med[n].Med_price,&L.Med[n].Med_sell_num,&L.Med[n].Med_sell_price);
		n++;
	}
	mednum=n-1;
	printf("�Ѷ�ȡ%d������\n",n-1);
	fclose(fp);
}

void SaveMedInfo(SqList &L){
	int i;
	FILE *fp;
	fp=fopen("medicine.txt","w");
	printf("������ҩƷ������");
	scanf("%d",&mednum);
	printf("����������ҩƷ��� ҩƷ���� ҩƷ���� ҩƷ����������\n");
	for(i=1;i<=mednum;i++){
		scanf("%d %s %f %f",&L.Med[i].Med_id,L.Med[i].Med_name,&L.Med[i].Med_price,&L.Med[i].Med_sell_num);
		L.Med[i].Med_sell_price=L.Med[i].Med_price*L.Med[i].Med_sell_num;
		//printf("%f",L.Med[i].Med_sell_price);
		fprintf(fp,"%d %s %f %f %f\n",L.Med[i].Med_id,L.Med[i].Med_name,L.Med[i].Med_price,L.Med[i].Med_sell_num,L.Med[i].Med_sell_price);
	}
	fclose(fp);
}

void SearchMedOneOfInfo(SqList &L,int switchcase){
	int i,j;
	FILE *fp;
	int updateid;
	
	printf("��ѡ����Ҫ���µ�ҩƷ��ţ�");
	scanf("%d",&updateid);
	for(i=1;i<=mednum;i++){
		if(L.Med[i].Med_id==updateid){
			fp=fopen("medicine.txt","w");
			if(switchcase==1){
				printf("������Ҫ���µĵ��ۣ�");
				scanf("%f",&L.Med[i].Med_price);
				L.Med[i].Med_sell_price=L.Med[i].Med_price*L.Med[i].Med_sell_num;
			}else if(switchcase==2){
				float addnum;
				printf("������Ҫ���Ӷ�������������");
				scanf("%f",&addnum);
				L.Med[i].Med_sell_num+=addnum;
				L.Med[i].Med_sell_price=L.Med[i].Med_price*L.Med[i].Med_sell_num;
			}else{
				printf("ѡ����������ѡ��");
				return;
			}
			for(j=1;j<=mednum;j++){
				fprintf(fp,"%d %s %f %f %f\n",L.Med[j].Med_id,L.Med[j].Med_name,L.Med[j].Med_price,L.Med[j].Med_sell_num,L.Med[j].Med_sell_price);
			}
			fclose(fp);
			return;
		}
	}
	return;
}

void PrintfMedInfo(SqList L){
	int i,rank=1;
	for(i=1;i<=mednum;i++){
		printf("%d:%d %s %.2f %.2f %.2f\n",rank,L.Med[i].Med_id,L.Med[i].Med_name,L.Med[i].Med_price,L.Med[i].Med_sell_num,L.Med[i].Med_sell_price);
		rank++;
	}
}

void PriceSort(SqList &L){
	int flag=1,i,j;
	for(i=1;i<mednum;i++){
		flag=0;
		for(j=1;j<=mednum-i;j++){
			if(L.Med[j].Med_price<L.Med[j+1].Med_price){
				L.Med[0]=L.Med[j];
				L.Med[j]=L.Med[j+1];
				L.Med[j+1]=L.Med[0];
				flag=1;
			}
		}
	}
} 

void SellNumAjust(SqList &L,int s,int m){
	int j;
	L.Med[0]=L.Med[s];
	for(j=2*s;j<=m;j*=2){
		if(j<m&&L.Med[j].Med_sell_num>L.Med[j+1].Med_sell_num){
			j++;
		}
		if(L.Med[0].Med_sell_num<=L.Med[j].Med_sell_num){
			break;
		}
		L.Med[s]=L.Med[j];
		s=j;
	}
	L.Med[s]=L.Med[0];		//������� 
}

void SellNumSort(SqList &L){
	int i;
	Medicine temp;
	for(i=mednum/2;i>0;i--){	//������ʼ�� 
		SellNumAjust(L,i,mednum);
	}
	for(i=mednum;i>1;i--){	//�ѵ�����͵��� 
		temp=L.Med[1];		//�Ѷ������һ����¼���� 
		L.Med[1]=L.Med[i];
		L.Med[i]=temp;
		SellNumAjust(L,1,i-1);	//��L.Med[1]��L.Med[i-1]���µ���Ϊ�� 
	}
}

void SellPriceSort(SqList &L){
	int i,j;
	for(i=2;i<=mednum;i++){
		if(L.Med[i].Med_sell_price>L.Med[i-1].Med_sell_price){
			L.Med[0]=L.Med[i];  //��iλ����Ϊ�ڱ�����0λ����
			L.Med[i]=L.Med[i-1];
			for(j=i-2;L.Med[0].Med_sell_price>L.Med[j].Med_sell_price;j--){
				L.Med[j+1]=L.Med[j];
			}
			L.Med[j+1]=L.Med[0];	//�����¼
		}
	}
}

int main(){
	SqList L;
	int switchnum=-1;
	int switchcase=0;	
	while(switchnum!=0){
		printf("��ӭ����ҩƷ����ͳ��ϵͳ��\n��1������������Ϣ\n��2����ȡ������Ϣ\n��3������������Ϣ\n��4������������Ϣ\n��0���˳�\n");
		printf("������ѡ�����ţ�");
		scanf("%d",&switchnum);
		switch(switchnum){
			case 1:
				printf("�Ƿ񴴽����ݣ���������1������������0��ע�⣺��ѡ��д������ʱ�������ļ�������\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
				SaveMedInfo(L);
				PrintfMedInfo(L);
				}
				switchcase=0; 
				break;
			case 2:
				ReadMedInfo(L);
				PrintfMedInfo(L);
				break;
			case 3:
				ReadMedInfo(L);
				printf("��ѡ������ʽ����1������������2����������������3�������۶�����0��������һ��\n");
				scanf("%d",&switchcase);
				if(switchcase!=0){
					if(switchcase==1){
						PriceSort(L);
						PrintfMedInfo(L);
					}else if(switchcase==2){
						SellNumSort(L);
						PrintfMedInfo(L);
					}else if(switchcase==3){
						SellPriceSort(L);
						PrintfMedInfo(L);
					}
				}			
				switchcase=0; 	
				break;
			case 4:
				ReadMedInfo(L);
				printf("ѡ����µ����ͣ���1�����۸��£�2�������������£�0��������һ��\n");
				scanf("%d",&switchcase);
				if(switchcase!=0){
					SearchMedOneOfInfo(L,switchcase);
				}
				break;
			case 0:
				exit(0);
			default:
				printf("��������������������룡"); 
		}
	}

	return 0;
}
