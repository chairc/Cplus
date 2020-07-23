#include <iostream>
#include <string>
#include<fstream>
#include <string.h>
#include "people.h"
using namespace std;

int people_num;

People::People(){
	
}

People::~People(){
	
}

void People::showAll(People *peo){
	cout<<"���  "<<"����  "<<"����  "<<endl;
	for(int i = 0;i < people_num;i++){
		cout<<peo[i].id<<" "<<peo[i].username<<" "<<peo[i].password<<endl;
	}
}

void People::readFile(string url,People *peo){
	fstream in;
	int i = 0,flag = 0;//iΪ��ȡ�ļ�������¼
	string url_str = "../test/" + url + ".txt";//ƴ�����·��
    char url_char[100];
    strcpy(url_char,url_str.c_str());
	in.open(url_char,ios::in);
	if(!in){
		ofstream fout(url_char);//û���ļ�ʱ�����ļ�
		if(fout){
			fout.close();
			flag = 1;
		}
	}
	if(flag != 1){
		while(!in.eof() && flag != 1){
	        in>>peo[i].id>>peo[i].username>>peo[i].password;//���ζ�ȡtxt�ļ���ÿ�е�����
	        i++;
    }
		people_num = i;//��¼����Աtxt�ļ���������
	}
    in.close();
}

bool People::login(string username,string password,People *peo){
	for(int i = 0;i < people_num;i++){
		if(username == peo[i].username && password == peo[i].password){
			return true;
		}
	}
	return false;
}

/***************************����Ա����***************************/

Manager::Manager(){
	//cout<<"Manager�ѹ��죡"<<endl;
}

Manager::Manager(string username,string password){
	cout<<"Manager��¼�ȶ��С�����"<<endl;
}

Manager::~Manager(){
	//cout<<"Manager��������"<<endl;
}

void Manager::readFile(string url,Manager *man){
	People::readFile(url,man);
}

bool Manager::login(string username,string password,Manager *man){
	return People::login(username,password,man);
}

void Manager::showAll(Manager *man){
	People::showAll(man);
}

/***************************������Ա����***************************/

Worker::Worker(){
	//cout<<"Worker�ѹ��죡"<<endl;
}

Worker::Worker(string username,string password){
	cout<<"Worker��¼�ȶ��С�����"<<endl;
}

Worker::~Worker(){
	//cout<<"Worker��������"<<endl;
}

void Worker::readFile(string url,Worker *wo){
	People::readFile(url,wo);
}

bool Worker::login(string username,string password,Worker *wo){
	return People::login(username,password,wo);
}

void Worker::showAll(Worker *wo){
	People::showAll(wo);
}
