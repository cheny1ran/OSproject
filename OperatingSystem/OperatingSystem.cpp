// OperatingSystem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
extern vector<user*> users;
extern inode* inod[20];
extern block* blk[100];
extern user* cyan;
extern string crtpath;
extern user* crtuser;
fstream fuser,fdisk,fblk;
using namespace std;

void init(){

	fuser.open("users.txt", ios::in | ios::out);	//��ȡ�û���Ϣ

	char bufi[144];
	char bufb[520];

	for (int i = 0; i < 20; i++){
		inod[i] = (inode*)malloc(144); //����144�ڴ��ÿ��inode��		
		new (inod[i]) inode;
	}
	for (int i = 0; i < 100; i++){
		blk[i] = (block*)malloc(520);	//����520�ڴ��ÿ��inode��
		blk[i]->bnum = i;
		new (blk[i]) block;
	}

	fdisk.open("inode.txt", ios::in | ios::out);
	//int i = 0;
	int k = 0;

	
	//��ʼ��inode��
	while (!fdisk.eof()){
		fdisk.getline(bufi, 144);
		string buf = bufi;
		string t;
		vector<string>s;
		for (int j = 0; j < buf.length(); j++){
			if (buf[j] == ' '){
				s.push_back(t);
				t = "";
			}
			else t += buf[j];
		}
		s.push_back(t);
		if (s.size() == 10){
			if (s[0] == "true") inod[k]->status = true;
			else inod[k]->status = false;

			inod[k]->owner = s[1];
			inod[k]->group = s[2];
			inod[k]->linknum = atoi(s[3].c_str());
			inod[k]->size = atoi(s[4].c_str());
			if (s[5] != "NULL") inod[k]->bp[0] = blk[atoi(s[5].c_str())];
			if (s[6] != "NULL") inod[k]->bp[1] = blk[atoi(s[6].c_str())];
			if (s[7] != "NULL") inod[k]->bp[2] = blk[atoi(s[7].c_str())];
			if (s[8] != "NULL") inod[k]->bp[3] = blk[atoi(s[8].c_str())];
			inod[k]->permission = s[9];
		}
		k++;
	}
	
	//��ʼ��block��
	for (int i = 0; i < 100; i++){
		string fname = "./block/" + to_string(i);
		fblk.open(fname, ios::in | ios::out);
		char buf[512];
		bool sf = true;
		while (!fblk.eof()){
			fblk.getline(buf, 512);
			string txt = buf;
			if (sf){			
				if (txt == "true") blk[i]->status = true;
				else blk[i]->status = false;
				blk[i]->bnum = i;
				sf = false;
			}
			else blk[i]->text += txt;
		}
		fblk.close();
	}
	
	
	while (!fuser.eof()){
		fuser.getline(bufi,144);
		string buf = bufi;
		vector<string> s;
		string t;
		for (int i = 0; i < buf.length(); i++){
			if (buf[i] == ' '){
				s.push_back(t);
				t = "";			
			}
			else t += buf[i];	
		}
		s.push_back(t);
		if (s.size() == 3){
			user* u = new user();
			u->setUsrname(s[0]);
			u->setPwd(s[1]);
			u->setGroup(s[2]);
			u->home = "/" + s[0] + "/";
			users.push_back(u);
		}
	}

	
	fuser.close();
	fdisk.close();

}

void beforeexit(){
	fuser.open("users.txt", ios::in | ios::out);
	fdisk.open("inode.txt", ios::in | ios::out);
	for (int i = 0; i < users.size(); i++){
		string txt;
		txt += users[i]->getUsrname() + " ";
		txt += users[i]->getPwd() + " ";
		txt += users[i]->getGroup();
		txt += "\n";
		fuser.write(txt.c_str(), txt.length());
	}
	for (int i = 0; i < 20; i++){
		string txt;
		if (inod[i]->status) txt += "true ";
		else txt += "false ";
		txt += inod[i]->owner + " ";
		txt += inod[i]->group + " ";
		txt += to_string(inod[i]->linknum) + " ";
		txt += to_string(inod[i]->size) + " ";
		for (int j = 0; j < 4; j++){
			if (inod[i]->bp[j] == NULL){
				txt += "NULL ";
			}
			else txt += to_string(inod[i]->bp[j]->bnum)+" ";
		}
		
		txt += inod[i]->permission;
		txt += "\n";
		fdisk.write(txt.c_str(), txt.length());
	}
	for (int i = 0; i < 100; i++){
		string fname = "./block/" + to_string(i);
		fblk.open(fname, ios::in | ios::out);
		string txt;
		if (blk[i]->status)
			txt += "true\n";
		else txt += "false\n";
		txt += blk[i]->text;
		fblk.write(txt.c_str(), txt.length());
		fblk.close();
	}
	fdisk.close();
	fuser.close();
}

void panel(){
	cout << "--------------------------------------------------------------------------------\n";
	cout << "                                   ��¼ϵͳ\n";
	cout << "--------------------------------------------------------------------------------\n";
	string user, pwd;
	cout << "�����û�����";
	cin >> user;
	cout << "�������룺";
	cin >> pwd;
	if (cyan->login(user, pwd)){
		cout << "------------------------------------------------------------------------------\n";
		cout << "                             Welcome " + user + "\n";
		cout << "------------------------------------------------------------------------------\n";
		string command = "";
		int bg = 1;

		char jdf;
		if (user == "root") jdf = '#';
		else jdf = '@';
		while (getline(cin, command)){
			if (command == "exit") return;
			vector<string>args;
			string arg = "";
			for (int i = 0; i < command.length(); i++){
				if (command[i] != ' '){
					arg += command[i];
					continue;
				}
				else{
					if (arg != " ") args.push_back(arg);
					arg = "";
				}
			}

			if (arg != "") args.push_back(arg);

			if (args.size() == 1){
				if (args[0] == "ls") cyan->ls();
				else if (args[0] == "pwd") cout << crtpath << endl;
				else if (args[0] == "help"){
					cout << "ls [option]... ��ʾ��ǰ�ļ����������ļ����ļ�������ϸ��Ϣ\n";
					cout << "cd [path]... �����ļ���\n";
					cout << "pwd ��ʾ��ǰ����·��\n";
					cout << "mkdir [filename]... �ڵ�ǰ·���д����ļ���\n";
					cout << "rmdir [path]... ɾ�����ļ���\n";
					cout << "touch [filename]... �ڵ�ǰ·���д����ļ�\n";
					cout << "rm [path]... ɾ���ļ�\n";
					cout << "cat [path]... ��ʾ�ļ�����\n";
					cout << "vi [path]... ���ļ����������\n";
					cout << "mv [filename1]...[filename2]... �ı��ļ���\n";
					cout << "cp [path1]...[path2]... �����ļ�\n";
					cout << "chmod [mod]...[path]... �ı��ļ����ļ���Ȩ��\n";
					cout << "chgrp [group]... �ı��ļ����ļ���������\n";
					cout << "chown [owner]... �ı��ļ����ļ��������û�\n";

					cout << "chpwd [newpassword]...[user]... �ı��û�����\n";
					cout << "deluser [username]... ɾ���û�\n";
					cout << "adduser [username]...[password]...[group]... �����û�\n";
					cout << "su [username]...[password]... �л���¼�û�\n";
				}
				else if (args[0] == "cd") cout << "cd [path]... �����ļ���\n";
				else if (args[0] == "mkdir") cout << "mkdir [filename]... �ڵ�ǰ·���д����ļ���\n";
				else if (args[0] == "rmdir") cout << "rmdir [path]... ɾ�����ļ���\n";
				else if (args[0] == "cat") cout << "cat [path]... ��ʾ�ļ�����\n";
				else if (args[0] == "touch") cout << "touch [filename]... �ڵ�ǰ·���д����ļ�\n";
				else if (args[0] == "rm") cout << "rm [path]... ɾ���ļ�\n";
				else if (args[0] == "vi") cout << "vi [path]... ���ļ����������\n";
				else if (args[0] == "chmod") cout << "chmod [mod]...[path]... �ı��ļ����ļ���Ȩ��\n";
				else if (args[0] == "chgrp") cout << "chgrp [group]... �ı��ļ����ļ���������\n";
				else if (args[0] == "chown") cout << "chown [owner]... �ı��ļ����ļ��������û�\n";
				else if (args[0] == "mv") cout << "mv [filename1]...[filename2]... �ı��ļ���\n";
				else if (args[0] == "cp") cout << "cp [path1]...[path2]... �����ļ�\n";
				else if (args[0] == "deluser") cout << "deluser [username]... ɾ���û�\n";
				else if (args[0] == "chpwd") cout << "chpwd [newpassword]...[user]... �ı��û�����\n";
				else if (args[0] == "su") cout << "su [username]...[password]... �л���¼�û�\n";
				else if (args[0] == "adduser") cout << "adduser [username]...[password]...[group]... �����û�\n";
				else cout << "�Ҳ���ָ�" << endl;
			}
			else if (args.size() == 2){
				if (args[0] == "ls") cyan->ls(args[1]);
				else if (args[0] == "cd") cyan->cd(args[1]);
				else if (args[0] == "mkdir") cyan->mkdir(args[1]);
				else if (args[0] == "rmdir") cyan->rmdir(args[1]);
				else if (args[0] == "cat") cyan->cat(args[1]);
				else if (args[0] == "touch") cyan->touch(args[1]);
				else if (args[0] == "rm") cyan->rm(args[1]);
				else if (args[0] == "vi"){
					string txt;
					cin >> txt;
					cyan->vi(args[1], txt);
					continue;
				}
				else if (args[0] == "deluser"){
					if (user != "root") cout << "deluser:û��ɾ���û���Ȩ��!" << endl;
					else cyan->deluser(args[1]);
				}
				else if (args[0] == "chpwd"){
					cyan->chgpwd(args[1], user);
					cout << "�޸�����ɹ���" << endl;
				}
				else if (args[0] == "chmod") cout << "chmod [mod]...[path]... �ı��ļ����ļ���Ȩ��\n";
				else if (args[0] == "chgrp") cout << "chgrp [group]... �ı��ļ����ļ���������\n";
				else if (args[0] == "chown") cout << "chown [owner]... �ı��ļ����ļ��������û�\n";
				else if (args[0] == "mv") cout << "mv [filename1]...[filename2]... �ı��ļ���\n";
				else if (args[0] == "cp") cout << "cp [path1]...[path2]... �����ļ�\n";
				else if (args[0] == "su") cout << "su [username]...[password]... �л���¼�û�\n";
				else if (args[0] == "adduser") cout << "adduser [username]...[password]...[group]... �����û�\n";
				else cout << "�Ҳ���ָ�" << endl;
			}
			else if (args.size() == 3){

				if (args[0] == "chmod"){
					if (args[1].length() != 3)
						cout << "chmod:��������" << endl;

					else cyan->chmod(const_cast<char*>(args[1].c_str()), args[2]);
				}
				else if (args[0] == "chgrp") cyan->chgrp(args[1], args[2]);
				else if (args[0] == "chown") cyan->chown(args[1], args[2]);
				else if (args[0] == "mv") cyan->mv(args[1], args[2]);
				else if (args[0] == "cp") cyan->cp(args[1], args[2]);		
				else if (args[0] == "su"){
					if (cyan->login(args[1], args[2])){
						if (args[1] == "root") jdf = '#';
						else jdf = '@';
						user = args[1];
					}
					else cout << "su:�û������������!" << endl;
				}
				else if (args[0] == "adduser") cout << "adduser [username]...[password]...[group]... �����û�\n";
				else cout << "�Ҳ���ָ�" << endl;
			}
			else if (args.size() == 4){
				if (args[0] == "adduser"){
					if (user != "root") cout << "adduser:û������û���Ȩ��!" << endl;
					else cyan->adduser(args[1], args[2], args[3]);
				}				
			}
		
			cout << crtpath << jdf << " ";
		}

	}
	else{
		cout << "��½ʧ�ܣ�\n";
		panel();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	init();
	
	panel();
	/*cyan->touch("123");
	string txt="";
	for (int i = 0; i < 5; i++){
		for (int i = 0; i < 512; i++)
			txt += "s";
		cyan->vi("123", txt);
		txt = "";
	}*/
	beforeexit();

	return 0;
}

