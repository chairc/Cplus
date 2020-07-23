#include <iostream>
#include <string>
#include<fstream>
#include "grade.h"
using namespace std;

int grade_num;
const char grade_url[100] = "../test/grade.txt";//grade�ɼ������·��

Grade::Grade(){
	//cout<<"Grade�ѹ��죡"<<endl;
}

Grade::~Grade(){
	//cout<<"Grade��������"<<endl;
}

void Grade::readFile(Grade *gra){
	fstream in;
	int i = 0,flag = 0;
	in.open(grade_url,ios::in);
	if(!in){
		ofstream fout(grade_url);//û���ļ�ʱ�����ļ�
		if(fout){
			fout.close();
			flag = 1;
		}
	}
	if(flag != 1){
		while(!in.eof() && flag != 1){
	        in>>gra[i].id>>gra[i].name>>gra[i].subject>>gra[i].grade;//���ζ�ȡtxt�ļ���ÿ�е�����
	        i++;
	    }
		grade_num = i - 1;//��¼����Աtxt�ļ���������
	}
    in.close();
}

void Grade::showAll(Grade *gra){
	cout<<"ѧ��  "<<"����  "<<"��Ŀ  "<<"�ɼ�  "<<endl;
	for(int i = 0;i<grade_num;i++){
		cout<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<endl;
	}
}

void Grade::showOneStudentGrade(string id,Grade *gra){
	for(int i = 0;i<grade_num;i++){
		if(id == gra[i].id){
			cout<<"ѧ�ţ�"<<gra[i].id<<"\n������"<<gra[i].name<<"\n��Ŀ��"<<gra[i].subject<<"\n�ɼ���"<<gra[i].grade<<endl;
		}
	}
}

/***************************�ɼ�����***************************/

ManageGrade::ManageGrade(){
	//cout<<"ManageStudent�ѹ��죡"<<endl;
}

ManageGrade::~ManageGrade(){
	//cout<<"ManageStudent��������"<<endl;
}
void ManageGrade::insertGrade(string id,string name,string subject,int grade,Grade *gra){
	int flag = 0;//�ɼ��Ƿ���ڱ��λ
	for(int i = 0;i < grade_num;i++){
		if(id == gra[i].id && subject == gra[i].subject){
			flag = 1;
		}
	}
	if(flag == 0){
		//��id name sbject grade����stu��
	 	gra[grade_num].id = id;
		gra[grade_num].name = name;
		gra[grade_num].subject = subject;
		gra[grade_num].grade = grade;
		fstream out;
		out.open(grade_url,ios_base::out);
		for(int i = 0;i < grade_num + 1;i++){
			out<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<"\n";
		}
		out.close();
		cout<<"ѧ���ɼ����ӳɹ���"<<endl;
		grade_num = grade_num + 1;
		cout<<"ѧ���ɼ�Ϊ��"<<grade_num<<"��"<<endl;
	}else{
		cout<<"ѧ��Ϊ"<<id<<"��ѧ����"<<name<<"�ɼ����ڣ��ɼ�Ϊ��"<<grade<<endl;
	}
}

void ManageGrade::deleteGrade(string id,string subject,Grade *gra){
	int flag = 0;//1Ϊ�ɹ� 0Ϊʧ��
	cout<<"ѧ���ɼ�Ϊ��"<<grade_num<<"��"<<endl;
	for(int i = 0;i<grade_num;i++){
		if(id == gra[i].id && subject == gra[i].subject){
			flag = 1;//���ҳɹ�
			for(int j = i;j<grade_num;j++){
				gra[j] = gra[j+1];//�󷽵�һ����ǰ�ƶ�һ��
			}
		}
	}
	if(flag == 1){
		fstream out;
		out.open(grade_url,ios_base::out);
		grade_num = grade_num - 1;
		for(int i = 0;i<grade_num;i++){
			out<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<"\n";
		}
		cout<<"ѧ���ɼ�ɾ���ɹ���"<<endl;
		cout<<"ѧ���ɼ�Ϊ��"<<grade_num<<"��"<<endl;
		out.close();
	}else{
		cout<<"ѧ���ɼ�ɾ��ʧ�ܣ�"<<endl;
	}
}

void ManageGrade::updateGrade(string id,string name,string subject,int grade,Grade *gra){
	int flag = 0;//���³ɹ�ʧ�ܱ��λ
	for(int i = 0;i < grade_num;i++){
		if(id == gra[i].id && subject == gra[i].subject){//�˴��Զ�Ѱ�ҿ�Ŀ
			gra[i].id = id;
			gra[i].name = name;
			gra[i].subject = subject;
			gra[i].grade = grade;
			flag = 1;
		}
	}
	if(flag == 1){
		fstream out;
		out.open(grade_url,ios_base::out);
		for(int i = 0;i < grade_num;i++){
			out<<gra[i].id<<" "<<gra[i].name<<" "<<gra[i].subject<<" "<<gra[i].grade<<"\n";
		}
		out.close();
		cout<<"ѧ���ɼ����³ɹ���"<<endl;
	}else{
		cout<<"ѧ���ɼ�����ʧ�ܣ�"<<endl;
	}
}

void ManageGrade::sortStudentByGrade(string subject,Grade *gra,const int NUM){
	int flag = 0;//ѧ���Ƿ���ڱ��λ
	Grade gra_new[NUM];//��ʼ��һ���µĶ������飬�Ա�֤����ʱ���Ḳ��ԭ��������
	int gra_new_num = 0;
	for(int n = 0;n < grade_num;n++){
		if(subject == gra[n].subject){
			gra_new[gra_new_num] = gra[n];//��gra���������е�subject����ѭ������gra_new��,�������øı�gra������������λ�ú����¶�ȡԭtxt�ļ�
			gra_new_num++;
			flag = 1;
		}
	}
	if(flag == 1){
		//gra_new_num - 1�ֱȽ�
		for(int i = 0;i < gra_new_num - 1;i++){
			int max = i;
			for(int j = i + 1;j < gra_new_num;j++){
				if(gra_new[j].grade > gra_new[max].grade){
					max = j;
				}
			}
			//���ҵ�����Сֵ��iλ�����ڵ�ֵ���н���
			if(i != max){
				Grade gra_temp = gra_new[i];
				gra_new[i] = gra_new[max];
				gra_new[max] = gra_temp;
			}
		}
		//ѭ������gra_new��������
		cout<<subject<<"ѧ�ƴӴ�С����Ϊ��"<<endl;
		for(int i = 0;i < gra_new_num;i++){
			cout<<gra_new[i].id<<" "<<gra_new[i].name<<" "<<gra_new[i].subject<<" "<<gra_new[i].grade<<endl;
		}
	}else{
		cout<<subject<<"ѧ�Ʋ����ڣ�"<<endl;
	}
}

string ManageGrade::compareGrade(string id1,string id2,string name1,string name2,string subject,Grade *gra){
	string str;//���ڷ��رȽϺ�ɼ�����
	int comp1 = -1, comp2 = -1;//ʹ������int���ͼ�ס��Աλ��
	for(int i = 0;i < grade_num;i++){
		if(id1 == gra[i].id && subject == gra[i].subject){
			comp1 = i;
		}else if(id2 == gra[i].id && subject == gra[i].subject){
			comp2 = i;
		}
	}
	if(comp1 == -1 && comp2 != -1){
		str = "�����ѧ��" + id1 + "�ɼ������ڣ�";
	}else if(comp1 != -1 && comp2 == -1){
		str = "�����ѧ��" + id2 + "�ɼ������ڣ�";
	}else if(comp1 == comp2 == -1){
		str = "�������ѧ��" + id1 + "," + id2 + "�ɼ��������ڣ�";
	}else{
		if(gra[comp1].grade > gra[comp2].grade){
			str = "�ɼ���������Ϊ��" + name1;
		}else if(gra[comp1].grade < gra[comp2].grade){
			str = "�ɼ���������Ϊ��" + name2;
		}else{
			str = "�ɼ���ͬ";
		}
	}
	return str;
}

string ManageGrade::compareGrade(string id1,string id2,int grade1,int grade2,string subject,Grade *gra){
	string name1,name2,str;
	int flag1 = 0,flag2 = 0;//���λ
	if(grade1 > grade2){
		flag1 = 1;
	}else if(grade1 < grade2){
		flag2 = 1;
	}else{
		flag1 = flag2 = 1;
	}
	for(int i = 0;i < grade_num;i++){
		if(id1 == gra[i].id && subject == gra[i].subject && flag1 == 1){
			name1 = gra[i].name;
			str = "�ɼ���������Ϊ��" + name1;
		}else if(id2 == gra[i].id && subject == gra[i].subject && flag2 == 1){
			name2 = gra[i].name;
			str = "�ɼ���������Ϊ��" + name2;
		}
	}
	if(flag1 == flag2 == 1){
		str = name1 + "��" + name2 + "�ɼ���ͬ";
	}
	return str;
}
	
