#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define LET_CODE 26	//���Ҫ�������ĸ��Ŀ������չ��һ�����ģ�


typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;       //���������ṹ

typedef char **HuffmanCode;	//����������洢�ṹ

//char Let[LET_CODE]={'a','b','c','d','e','f','g'};//���Ҫ�������ĸ������չ��
char Let[LET_CODE]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int Num[LET_CODE]={0};
int letternum=0;
char a[1000];

void SaveFile(){
	FILE *fp;
	char ch[100];
	fp=fopen("article.txt","w");
	scanf("%s",ch);
	fprintf(fp,"%s",ch);			
	fclose(fp);
}

void ReadFile(){
	int m=0,ch,k;
	FILE *fp;
	fp=fopen("article.txt","r");
	if(fp){                                                                                                                                                                                                         
		while(!feof(fp)){
			ch=fgetc(fp);
			if(ch==EOF){
				break;
			}
			a[m]=ch;
			k=ch-'a';
			if(Let[k]==a[m]){
				Num[k]++;
			}
			m++;    //���ڿ��ƶ������ַ�����
		}
		letternum=m;
		a[m]=0;
		fclose(fp);
	}	
}

void PrintfArticle(){
	int i;
	for(i=0;i<letternum;i++){
  		printf("%c",a[i]);
	}
	printf("\n");
}

void LetterCount(){
	int i;
	for(i=0;i<LET_CODE;i++){
		printf("%c:%d\n",Let[i],Num[i]);	
	}	
}

//��������
void CreateHuffmanTree(HuffmanTree &HT,int *w,int n){
	//*wΪÿ����ĸ��Ȩֵ����Num[LET_CODE]��nΪͳ�Ƴ���������ĸ������Ҷ�ӽ�������
	int m,i,j,min1,min2,s1,s2;
	if(n<1){
		printf("....\n");
		return;
	}
	m=2*n-1;    //���н����
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for(i=1;i<=n;i++){      //��ʼ������HT[1]��HT[n]
		HT[i].weight=*w++;	
		HT[i].parent=HT[i].lchild=HT[i].rchild=0;
	}
	for(;i<=m;i++){         //��ʼ������HT[n+1]��HT[m]
		HT[i].weight=0;
		HT[i].parent=HT[i].lchild=HT[i].rchild=0;
	}
	for(i=n+1;i<=m;i++){	//��HT[1]��HT[i-1]��ѡȡparentֵΪ0����weightֵ��С��������� 
		min1=min2=32767;    //����ֵ,32767�������
		s1=s2=0;
		for(j=1;j<i;j++){    //����˫��ֵΪ0��Ȩֵ��С���������
			if(HT[j].parent==0){
				if(HT[j].weight<min1){
					min2=min1;      //min2��סmin1
					s2=s1;          //s2��סs1
					min1=HT[j].weight;
					s1=j;           //�޸���Сֵ��λ��
				}
				else if(HT[j].weight<min2){
					min2=HT[j].weight;
					s2=j;           //�޸Ĵ�Сֵ��λ��
				}
			}
		}
		HT[s1].parent=i;
		HT[s2].parent=i;            //�޸���Сֵ�ʹ�Сֵ˫��ֵ
		HT[i].weight=HT[s1].weight+HT[s2].weight;   //�޸�˫�׽��������Ϣ
		HT[i].lchild=s1;
		HT[i].rchild=s2;
	}
	printf("�������������ɹ�\n");
} 

void HuffmanCoding(HuffmanTree HT,HuffmanCode &HC,int n){
	char *cd;
	int i,c,f,start;
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));    //��������ͷָ��
	cd=(char*)malloc(n*sizeof(char));   //������������ʱ�洢�ռ�
	cd[n-1]='\0';                       //���������
	for(i=1;i<=n;i++){
		start=n-1;                      //�������λ��
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent){
			//��Ҷ�ӵ������������
			if(HT[f].lchild==c){
				cd[--start]='0';        //cΪ��˫�׽�������
   			}else{
			 	cd[--start]='1';        //cΪ��˫�׽����Һ���
			}    
		}
		HC[i]=(char*)malloc((n-start)*sizeof(char));
		strcpy(HC[i],cd+start);
	}
	free(cd);
}

void PrintfHuffmanCode(HuffmanTree HT,HuffmanCode HC){
	int i,j=1;
	for(i=0;i<LET_CODE;i++){
		if(Num[i]!=0){
			printf("%c:%s\n",Let[i],HC[j++]);
		}
	}
}

int main(){
	int switchnum=-1;
	int switchcase=0;	
	while(switchnum!=0){
		for(int i=0;i<LET_CODE;i++){
			Num[i]=0;
		}
		printf("��1��д������\n��2����ȡ����\n��3�������ַ����ִ���\n��4����ƹ���������\n��0���˳�\n");
		printf("������ѡ�����ţ�");
		scanf("%d",&switchnum);
		switch(switchnum){
			case 1:
				printf("�Ƿ�д�����ݣ���������1������������0��ע�⣺��ѡ��д������ʱ�������ļ�������\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					SaveFile();
				}
				switchcase=0; 
				break;
			case 2:
				ReadFile();
				PrintfArticle();
				break;
			case 3:
				printf("�Ƿ����ַ����ִ�������������1������������0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					ReadFile();
					LetterCount();
				}
				switchcase=0; 	
				break;
			case 4:
				printf("�Ƿ���ƹ��������룬��������1������������0\n");
				scanf("%d",&switchcase);
				if(switchcase==1){
					HuffmanTree HT;
					HuffmanCode HC;
					ReadFile();
					LetterCount();
					int i,n=0;
					int Let[LET_CODE];
					printf("���ڴ�����������....\n");
					for(i=0;i<LET_CODE;i++){
						 Let[n]=Num[i];
						 n++;
					}
					CreateHuffmanTree(HT,Let,n);
					HuffmanCoding(HT,HC,n);
					PrintfHuffmanCode(HT,HC);
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
