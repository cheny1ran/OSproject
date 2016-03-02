#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"filenode.h"
using namespace std;
class user
{
public:
	user();
	~user();
	//�û�����
	bool login(string account, string password);
	bool adduser(string account, string password, string grp);
	bool deluser(string account);
	bool chgpwd(string pwd, string account);

	
	//�ļ�����
	bool mkdir(string filename);//ֻ��ǰ·��
	bool chmod(char mod[3],string path);	//���ֲ����� chmod +x(?)
	bool chown(string owner,string path);
	bool chgrp(string group, string path);
	bool cd(string path);
	bool rmdir(string path);//ֻɾ�����ļ���
	bool cat(string path);//ֻ�ܲ鿴��Ŀ¼�ļ�����
	bool touch(string filename);//ֻ��ǰ·��
	bool rm(string path);
	bool mv(string newname,string old);//ֻ���� ���ƶ�����
	//pwd=cout crtpath
	void ls(string arg);
	void ls();
	bool cp(string path1, string path2);	//���path2Ŀ¼�����޳����ļ�//ֻ�ܿ����ļ�����һ�ļ����ļ���
	void vi(string path, string txt);


	
	//getter & setter
	void setUsrname(string str);
	void setPwd(string str);
	void setGroup(string str);
	string getUsrname();
	string getPwd();
	string getGroup();

	void printinfo();
	string home;

public:
	void updateSize(string path,string updatefile);
	void updateSize(string path, int changesize,bool pls);
	int allocInode();
	int allocBlock();
	int findPath(string path, int &prenode);//ͨ��·�����Ҳ��������һ������inode����һ������inode
	//���ݸ��ڵ���ļ�������inode/����block ͨ��inode��block
	int findInode(const int inum, string filename);
	//׷�Ӵ洢���� mkdir append��ǵø���linknum
	void append2LastBlk(const int inum,string appendText);
	void freeblk(const int inum);
	string usrname;
	string pwd;
	string group;
	int posct=-1;	//ʹ��ʱ�ĳ�ʼ������
	int poslk=-1;
	
};

