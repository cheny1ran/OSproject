// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// OperatingSystem.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO:  �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������


const int ISIZE = 20;
const int BSIZE = 100;

vector<user*> users;
string crtpath = "";

inode* inod[ISIZE];
block* blk[BSIZE];
cls1* c1blk[ISIZE];
cls2* c2blk[ISIZE];


user* cyan=new user();	//root
user* crtuser = cyan;

