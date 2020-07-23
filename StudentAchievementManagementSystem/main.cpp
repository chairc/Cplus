#include <iostream>
#include <string>

#include "student.h"
#include "grade.h"
#include "people.h"

using namespace std;

/*
1.��¼���棨whileѭ����
    ��1�����Ƚ�����ĵ�¼��Ա�����жϣ�if��ʹ�ù���Ա�໹�ǹ�����Ա�ࡾ1Ϊ����Ա   2Ϊ������Ա��
    ��2����ѡ��ı�txt�ļ��������ڴ�
    ��3�����û�����������бȶ�
    ��4���ɹ�����в���
    
*/

int main(int argc, char** argv) {
	//�򵥵�¼����
	string username,password,id,name,sex,subject,id1,id2,name1,name2,str;
	int login_type,select_type,age,subject_grade,case7select_type,subject_grade1,subject_grade2;
	int flag = 1;//ѭ����־λ�������˳���ѭ����
	const int NUM = 100;
	while(flag == 1){
		Manager manager;//���ɹ���Ա�࣬���ù���Ա���ж�ȡ�ļ����ڴ�ķ���
		Student student;
		Grade grade;
		ManageStudent ms;
		ManageGrade mg;
		Worker worker;
		//��ʼ����������
		Manager *man = new Manager[NUM];
		Worker *wo = new Worker[NUM];
		Student *stu = new Student[NUM];
		Grade *gra = new Grade[NUM];
		manager.readFile("manager",man);
		worker.readFile("worker",wo);
		student.readFile(stu);
		grade.readFile(gra);
		cout<<"��ӭ������ѧ������ϵͳ"<<endl;
		cout<<"��1����¼"<<endl;
		cout<<"��0���˳�"<<endl;
		cout<<"��ѡ�������";
		cin>>select_type;
		system("cls");
		switch(select_type){
			case 1:
				cout<<"�������˺ţ�";
				cin>>username;
				cout<<"���������룺";
				cin>>password;
				cout<<"�������¼��ʽΪ��1������Ա/��2��������Ա��";
				cin>>login_type;
				if(login_type == 1){//�˴�Ϊ����Ա��¼
					system("cls");
					flag = 2;
					if(manager.login(username,password,man)){
						cout<<"Manager��¼�ɹ�"<<endl;
						while(flag == 2){
							cout<<"��ӭ����Ա"<<username<<endl;
							cout<<"��1�� ѧ����Ϣ��ʾ "<<"��8�� ѧ���ɼ�¼��"<<endl;
							cout<<"��2�� ѧ����Ϣ¼�� "<<"��9�� ѧ���ɼ�����"<<endl;
							cout<<"��3�� ѧ����Ϣ���� "<<"��10��ѧ���ɼ�ɾ��"<<endl;
							cout<<"��4�� ѧ����Ϣɾ�� "<<"��11������Ա��Ϣ��ʾ"<<endl;
							cout<<"��5�� ѧ���ɼ���ʾ "<<"��12��������Ա��Ϣ��ʾ"<<endl;
							cout<<"��6�� ѧ���ɼ����� "<<"��0�� ע���˻�"<<endl;
							cout<<"��7�� ѧ���ɼ��Ƚ� "<<endl;
							cout<<"��Ҫ���еĲ���Ϊ��";
							cin>>select_type;
							system("cls");
							switch(select_type){
								case 1:
									student.showAll(stu);
									break;
								case 2:
									cout<<"����������ѧ��ѧ�ţ��������Ա�����"<<endl;
									cin>>id>>name>>sex>>age;
									ms.insertStudent(id,name,sex,age,stu);
									break;
								case 3:
									cout<<"��������Ҫ�޸ĵ�ѧ��ѧ�ţ�";
									cin>>id;
									cout<<"��ǰ��ϢΪ��"<<endl;
									student.showOneStudent(id,stu);
									cout<<"��Ϣ�޸�Ϊ����������ѧ��ѧ�ţ��������Ա����䣩��";
									cin>>id>>name>>sex>>age;
									ms.updateStudent(id,name,sex,age,stu);
									break;
								case 4:
									cout<<"��������Ҫɾ����Ϣ��ѧ��ѧ�ţ�";
									cin>>id;
									ms.deleteStudent(id,stu);
									break;
								case 5:
									grade.showAll(gra);
									break;
								case 6:
									cout<<"�����������Ŀ��";
									cin>>subject;
									mg.sortStudentByGrade(subject,gra,NUM);
									break;
								case 7:
									grade.showAll(gra);
									cout<<"��1����ѧ�Ų�ѯ�Ƚ� ��2�����ɼ���ѯ�Ƚ�"<<endl;
									cout<<"��ѡ��ȽϷ�ʽ��";
									cin>>case7select_type;
									if(case7select_type == 1){
										cout<<"����������Ƚϵ�ѧ��1��ѧ��2������1������2���ȽϿ�Ŀ��";
										cin>>id1>>id2>>name1>>name2>>subject;
										str = mg.compareGrade(id1,id2,name1,name2,subject,gra);
									}else if(case7select_type == 2){
										cout<<"����������Ƚϵ�ѧ��1��ѧ��2���ɼ�1���ɼ�2���ȽϿ�Ŀ��";
										cin>>id1>>id2>>subject_grade1>>subject_grade2>>subject;
										str = mg.compareGrade(id1,id2,subject_grade1,subject_grade2,subject,gra);
									}else{
										cout<<"����ֵ�Ƿ���";
									}
									cout<<"�ȽϽ��Ϊ��"<<str<<endl;
									break;
								case 8:
									cout<<"����������ѧ��ѧ�ţ�������ѧ�ƣ��ɼ�"<<endl;
									cin>>id>>name>>subject>>subject_grade;
									mg.insertGrade(id,name,subject,subject_grade,gra);
									break;
								case 9:
									cout<<"��������Ҫ�޸ĵ�ѧ��ѧ�ţ�";
									cin>>id;
									cout<<"��ǰ��ϢΪ��"<<endl;
									grade.showOneStudentGrade(id,gra);
									cout<<"��Ϣ�޸�Ϊ����������ѧ��ѧ�ţ�������ѧ�ƣ��ɼ�����";
									cin>>id>>name>>subject>>subject_grade;
									mg.updateGrade(id,name,subject,subject_grade,gra);
									break;
								case 10:
									cout<<"������������Ҫɾ����Ϣ��ѧ��ѧ�ź�ѧ�ƣ�";
									cin>>id>>subject;
									mg.deleteGrade(id,subject,gra);
									break;
								case 11:
									manager.showAll(man);
									break;
								case 12:
									worker.showAll(wo);
									break;
								case 0:
									flag = 1;
									break;
							}
							if(select_type != 0){
								system("pause");
							}
							system("cls");
						}
					}else{
						cout<<"Manager��¼ʧ��"<<endl;
						flag = 1;
					}
				}else if(login_type == 2){//�˴�Ϊ������Ա��¼
					system("cls");
					flag = 2;
					if(worker.login(username,password,wo)){
						cout<<"Worker��¼�ɹ�"<<endl;
						while(flag ==2){
							cout<<"��ӭ������Ա"<<username<<endl;
							cout<<"��1�� ѧ����Ϣ��ʾ "<<"��5�� ѧ���ɼ�¼��"<<endl;
							cout<<"��2�� ѧ���ɼ���ʾ "<<"��6�� ѧ���ɼ�����"<<endl;
							cout<<"��3�� ѧ���ɼ����� "<<"��7�� ѧ���ɼ�ɾ��"<<endl;
							cout<<"��4�� ѧ���ɼ��Ƚ� "<<"��0�� ע���˻�"<<endl;
							cout<<"��Ҫ���еĲ���Ϊ��";
							cin>>select_type;
							system("cls");
							switch(select_type){
								case 1:
									student.showAll(stu);
									break;
								case 2:
									grade.showAll(gra);
									break;
								case 3:
									cout<<"�����������Ŀ��";
									cin>>subject;
									mg.sortStudentByGrade(subject,gra,NUM);
									break;
								case 4:
									grade.showAll(gra);
									cout<<"��1����ѧ�Ų�ѯ�Ƚ� ��2�����ɼ���ѯ�Ƚ�"<<endl;
									cout<<"��ѡ��ȽϷ�ʽ��";
									cin>>case7select_type;
									if(case7select_type == 1){
										cout<<"����������Ƚϵ�ѧ��1��ѧ��2������1������2���ȽϿ�Ŀ��";
										cin>>id1>>id2>>name1>>name2>>subject;
										str = mg.compareGrade(id1,id2,name1,name2,subject,gra);
									}else if(case7select_type == 2){
										cout<<"����������Ƚϵ�ѧ��1��ѧ��2���ɼ�1���ɼ�2���ȽϿ�Ŀ��";
										cin>>id1>>id2>>subject_grade1>>subject_grade2>>subject;
										str = mg.compareGrade(id1,id2,subject_grade1,subject_grade2,subject,gra);
									}else{
										cout<<"����ֵ�Ƿ���";
									}
									cout<<"�ȽϽ��Ϊ��"<<str<<endl;
									break;
								case 5:
									cout<<"����������ѧ��ѧ�ţ�������ѧ�ƣ��ɼ�"<<endl;
									cin>>id>>name>>subject>>subject_grade;
									mg.insertGrade(id,name,subject,subject_grade,gra);
									break;
								case 6:
									cout<<"��������Ҫ�޸ĵ�ѧ��ѧ�ţ�";
									cin>>id;
									cout<<"��ǰ��ϢΪ��"<<endl;
									grade.showOneStudentGrade(id,gra);
									cout<<"��Ϣ�޸�Ϊ����������ѧ��ѧ�ţ�������ѧ�ƣ��ɼ�����";
									cin>>id>>name>>subject>>subject_grade;
									mg.updateGrade(id,name,subject,subject_grade,gra);
									break;
								case 7:
									cout<<"������������Ҫɾ����Ϣ��ѧ��ѧ�ź�ѧ�ƣ�";
									cin>>id>>subject;
									mg.deleteGrade(id,subject,gra);
									break;
								case 0:
									flag = 1;
									break;
							}
							if(select_type != 0){
								system("pause");
							}
							system("cls");
						}
					}else{
						cout<<"Worker��¼ʧ��"<<endl;
						flag = 1;
					}
				}else{//�˴�Ϊ�Ƿ��ַ�
					cout<<"�Ƿ��ַ�����¼ʧ��"<<endl;
					flag = 1;
				}
				system("pause");
				system("cls");
				break;
			case 0:
				exit(0);
			default:
				cout<<"�Ƿ��ַ���"<<endl;
				system("pause");
				system("cls");
				break;
		}
	}
	return 0;
}
