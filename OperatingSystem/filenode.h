#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class block{
public:
	//��Ŀ¼�ļ���ʹ���ļ�����
	int bnum;
	bool status=false;
	string text;//length=512;
	//Ŀ¼�ļ�ά���ļ�����

};
class cls1{
public:
	block* bp[4];
	cls1(){
		for (int i = 0; i < 4; i++){
			bp[i] = NULL;
		}
	};
};
class cls2{
public:
	cls1* p1[4];
	cls2(){
		for (int i = 0; i < 4; i++){
			p1[i] = new cls1();
		}
	};
};
class inode{
public:
	bool status=false;
	string owner="";	//length=20
	string group="";	//length=20
	int linknum=0;	//��������ʹ�õ��ĸ��洢�ڵ� Ĭ��ÿ���ļ�����һ��block
	int size=0;
	block* bp[4];//ֱ�ӵ�ַ 
	cls1* p1;//һ�μ�ַ 
	cls2* p2;//���μ�ַ 
	string permission="";//-rw-r--r-- length=10
	//string time;

	inode(){
		for (int i = 0; i < 4; i++){
			bp[i] = NULL;
		}
		p1 = new cls1();
		p2 = new cls2();
	};
};
class filenode
{
	
};

