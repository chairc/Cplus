#include <iostream>
#include <string>
#include<fstream>
#include "student.h"
using namespace std;

int student_num;
const char student_url[100] = "../test/student.txt";//studentѧ�������·��

Student::Student(){
	//cout<<"Student�ѹ��죡"<<endl;
}

Student::~Student(){
	//cout<<"Student��������"<<endl;
}

void Student::readFile(Student *stu){
	fstream in;
	int i = 0,flag = 0;
	in.open(student_url,ios::in);
	if(!in){
		ofstream fout(student_url);//û���ļ�ʱ�����ļ�
		if(fout){
			fout.close();
			flag = 1;
		}
	}
	if(flag != 1){
		while(!in.eof() && flag != 1){
	        in>>stu[i].id>>stu[i].name>>stu[i].sex>>stu[i].age;//���ζ�ȡtxt�ļ���ÿ�е�����
	        i++;
	    }
	    student_num = i - 1;//��¼����Աtxt�ļ������������ո�Ҳ��һ������Ҫ-1��
	}
    in.close();
}

void Student::showAll(Student *stu){
	cout<<"ѧ��  "<<"����  "<<"�Ա�  "<<"����  "<<endl;
	for(int i = 0;i < student_num;i++){
		cout<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<endl;
	}
	cout<<"ѧ��Ϊ��"<<student_num<<"��"<<endl;
}

void Student::showOneStudent(string id,Student *stu){
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			cout<<"ѧ�ţ�"<<stu[i].id<<"\n������"<<stu[i].name<<"\n�Ա�"<<stu[i].sex<<"\n���䣺"<<stu[i].age<<endl;
		}
	}
}


/***************************ѧ������***************************/

ManageStudent::ManageStudent(){
	//cout<<"ManageStudent�ѹ��죡"<<endl;
}

ManageStudent::~ManageStudent(){
	//cout<<"ManageStudent��������"<<endl;
}
void ManageStudent::insertStudent(string id,string name,string sex,int age,Student *stu){
	//��ѧ����Ϣ����stu��
	int flag = 0;//ѧ���Ƿ���ڱ��λ
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			flag = 1;
		}
	}
	if(flag == 0){
		stu[student_num].id = id;
		stu[student_num].name = name;
		stu[student_num].sex = sex;
		stu[student_num].age = age;
		fstream out;
		out.open(student_url,ios_base::out);
		for(int i = 0;i < student_num + 1;i++){
			out<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<"\n";
		}
		out.close();
		cout<<"ѧ�����ӳɹ���"<<endl;
		student_num = student_num + 1;
		cout<<"ѧ��Ϊ��"<<student_num<<"��"<<endl;
	}else{
		cout<<"ѧ�����ڣ�����ʧ�ܣ�"<<endl;
	}
	
}

void ManageStudent::deleteStudent(string id,Student *stu){
	int flag = 0;//ɾ���ɹ�ʧ�ܱ��λ
	cout<<"ѧ��Ϊ��"<<student_num<<"��"<<endl;
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			for(int j = i;j<student_num;j++){
				stu[j] = stu[j+1];
			}
			flag = 1;
		}
	}
	if(flag == 1){
		fstream out;
		out.open(student_url,ios_base::out);
		student_num = student_num - 1;
		for(int i = 0;i < student_num;i++){
			out<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<"\n";
		}
		out.close();
		cout<<"ѧ��ɾ���ɹ���"<<endl;
		cout<<"ѧ��Ϊ��"<<student_num<<"��"<<endl;
	}else{
		cout<<"ѧ��ɾ��ʧ�ܣ�"<<endl;
	}
}

void ManageStudent::updateStudent(string id,string name,string sex,int age,Student *stu){
	int flag = 0;//���³ɹ�ʧ�ܱ��λ
	for(int i = 0;i < student_num;i++){
		if(id == stu[i].id){
			stu[i].id = id;
			stu[i].name = name;
			stu[i].sex = sex;
			stu[i].age = age;
			flag = 1;
		}
	}
	if(flag == 1){
		fstream out;
		out.open(student_url,ios_base::out);
		for(int i = 0;i<student_num;i++){
			out<<stu[i].id<<" "<<stu[i].name<<" "<<stu[i].sex<<" "<<stu[i].age<<"\n";
		}
		out.close();
		cout<<"ѧ�����³ɹ���"<<endl;
	}else{
		cout<<"ѧ������ʧ�ܣ�"<<endl;
	}
}

