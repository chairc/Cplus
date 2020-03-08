#include <stdio.h>
#include <stdlib.h>

#define StackInitSize 100
#define StackIncrement 10

typedef struct{
	int *base;
	int top;
	int stacksize;
}SqStack;

typedef struct BitNode{
	char data;
	BitNode* lchild;
    BitNode* rchild;
}BitNode,*Bitree;

/*��ջADT*/
typedef struct{
    Bitree *base;
    int top;
    int stacksize;
}TreeStack;

//���������ȹ�ϵ
char Con[7][7]={{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},{'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},{'<','<','<','<','<','=',' '},{'>','>','>','>',' ','>','>'},{'<','<','<','<','<',' ','='}};


void InitStack(SqStack &S){
	S.base=(int*)malloc(StackInitSize*sizeof(int));
	if(!S.base){
		return;
	}
	S.top=0;
	S.stacksize=StackInitSize;
}

int StackEmpty(SqStack &S){
	if(S.top==0){
		return 1;
	}
	return 0;
}

int StackLength(SqStack S){
	return S.top;
}

void Push(SqStack &S,int e){
	if(S.top>=S.stacksize){
		S.base=(int*)realloc(S.base,(S.stacksize+StackIncrement)*sizeof(int));
		if(!S.base){
			return;
		}
		S.stacksize+=StackIncrement;
	}
	S.base[S.top++]=e;
}

void Pop(SqStack &S,int &e){
	if(S.top==0){
		return;
	}
	e=S.base[--S.top];
}

int GetTop(SqStack S){
	int e;
	if(S.top==0){
		return 0;
	}
	e=S.base[S.top-1];
	return e;
}

/*������ջ*/
void TreeInitStack(TreeStack &S){
	S.base=(Bitree*)malloc(StackInitSize*sizeof(Bitree));
    S.top=0;
    S.stacksize=StackInitSize;
}

Bitree TreeGetTop(TreeStack S){
	if(S.top==0) return 0;
	return S.base[S.top-1];
}

Bitree Pop_t(TreeStack &S,Bitree &e){
	if(S.top==0){
		return 0;
	}
	e=S.base[--S.top];
	return e;
}

void Push_t(TreeStack &S,Bitree e)
{
    if(S.top+1>S.stacksize)
    {
        S.base=(Bitree*)realloc(S.base,(S.stacksize+StackIncrement)*sizeof(Bitree));
        S.stacksize+=StackIncrement;
    }
    S.base[S.top++]=e;
}


//��׺���ʽ
int Compare(char theta1,char theta2){
	char op[7]={'+','-','*','/','(',')','#'};
	int i,j;
	int t1,t2;
	for(i=0;i<7;i++){
		if(theta1==op[i]){
			t1=i;
			break;
		}
	}
	for(j=0;j<7;j++){
		if(theta2==op[j]){
			t2=j;
			break;
		}
	}
	return Con[t1][t2];
} 

int Operate(int a,char theta,int b){
	switch(theta){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			if(b!=0){
				return a/b;
			}else{
				printf("0����Ϊ������");
				return 0;
			}
	}
}

//������׺���ʽ
int EvaluateExpression(char *str){
	//OPTRΪ��������ջ��OPNDΪ������ջ 
	SqStack OPTR,OPND;
	char *p;
	int num=0,ch,a,b,theta;
	p=str;
	InitStack(OPTR);
	InitStack(OPND);
	Push(OPTR,*p);      //'#'��ջ
	p++;
	while(*p!='#'||GetTop(OPTR)!='#'){
		if(*p>='0'&&*p<='9'){
			num=0;      //pָ��Ϊ������
			while(*p!='#'&&*p>='0'&&*p<='9'){
				num=num*10+*p-'0';
				p++;
			}
			Push(OPND,num);
		}else{
			switch(Compare(GetTop(OPTR),(int)*p)){
				case '<':
					Push(OPTR,*p);
					p++;
					break;
				case '=':
					Pop(OPTR,ch);
					p++;
					break;
				case '>':
					Pop(OPND,b);
					Pop(OPND,a);
					Pop(OPTR,theta);
					Push(OPND,Operate(a,theta,b));
					break;
			}
		}
	}
	return GetTop(OPND);
}

//������
void CreateTree(char *str,Bitree &bt){
	char *p;
	Bitree m,n;
	int num,a,b,ch,theta;
	p=str;
	SqStack OPTR;//�����
	TreeStack OPND;
	InitStack(OPTR);
	TreeInitStack(OPND);
	Push(OPTR,*p);      //'#'��ջ
	p++;
	while(*p!='#'||GetTop(OPTR)!='#'){
		if(*p>='0'&&*p<='9'){
			num=0;      //pָ��Ϊ������
			while(*p!='#'&&*p>='0'&&*p<='9'){
				num=num*10+(*p-'0');                //����һ��ֻ�ܴ���һ�����֣������ǽ�����һλ����ֵ������
				p++;
			}
			bt=(Bitree)malloc(sizeof(BitNode));     //������
			bt->data=num;                           //����������data��
			bt->lchild=NULL;
			bt->rchild=NULL;
			Push_t(OPND,bt);                        //�����ѹ��ջ��
		}
		switch(Compare(GetTop(OPTR),*p)){           //���ȼ��Ƚϣ�����ջջ��Ԫ�غ�����������Ƚ�
			case '<':
				Push(OPTR,*p);
				p++;
				break;
			case '=':
				Pop(OPTR,ch);
				p++;
				break;
			case '>':
				    Pop_t(OPND,m);                  //�������ȼ���ķ���ʱ��ȡ��������ջ���������
					Pop_t(OPND,n);
					Pop(OPTR,theta);
					bt=(Bitree)malloc(sizeof(BitNode));
					bt->data=theta;
					bt->lchild=n;                   //��ȡ���ķ�����������ȡ���ķ�������
					bt->rchild=m;
					Push_t(OPND,bt);
					break;
		}
	}
	bt=TreeGetTop(OPND);
	printf("������������ɹ���\n");
}

//��������ݹ�
void PreOrderTraverse(Bitree bt){
	if(bt){
		if(bt->lchild||bt->rchild)
			printf("%c ",bt->data);
		else
			printf("%d ",bt->data);
		PreOrderTraverse(bt->lchild);
		PreOrderTraverse(bt->rchild);
	}
}
//��������ݹ�
void PostOrderTraverse(Bitree bt){
	if(bt){
		PostOrderTraverse(bt->lchild);
		PostOrderTraverse(bt->rchild);
		if(bt->lchild||bt->rchild)
			printf("%c ",bt->data);
		else
			printf("%d ",bt->data);
	}
}

int main(){
	char ch[100];
	int result;
	Bitree bt;
	
	printf("����һ����׺���ʽ��");
	gets(ch);
	result=EvaluateExpression(ch);
	printf("%d\n",result);
	CreateTree(ch,bt);
	printf("ǰ׺���ʽΪ��");
	PreOrderTraverse(bt);
	printf("\n");
	printf("��׺���ʽΪ��");
	PostOrderTraverse(bt);
	
	return 0;
}
