// CfgHelper.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "CfgHelper.h"
#include <fstream>
#include <iostream>

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� CfgHelper.h
CCfgHelper::CCfgHelper()
{
    return;
}

map<string, string> CCfgHelper::getKeyValue(string cfgFilePath)
{
	ifstream file;
	file.open(cfgFilePath, ios::in);
	if (!file.is_open()) 
	{
		cout << "Open the cfg failed!" << endl;
		return map<string, string>();
	}
	std::string strLine;
	map<string, string> k_v;
	while (getline(file, strLine))
	{
		// �������С���/��#�ַ���ͷ����
		if (strLine.empty() || strLine.substr(0, 1) == "/" || strLine.substr(0, 1) == "#")
		{
			continue;
		}
		// ��ȥÿ�к����ע�Ͳ���
		int pos = -1;
		if ((pos = strLine.find("//")) != string::npos)
		{
			strLine = strLine.substr(0, pos);
		}
		// ȥ��ͷ�����ɼ��ַ�
		string::const_iterator ch = strLine.begin();
		while (' ' == *ch || '\r' == *ch || '\n' == *ch || '\t' == *ch || '\f' == *ch)
		{
			strLine.erase(0, strLine.find_first_not_of(*ch));
			ch = strLine.begin();
		}
		// ȥ��β�����ɼ��ַ�
		ch = strLine.end() - 1;
		while (' ' == *ch || '\r' == *ch || '\n' == *ch || '\t' == *ch || '\f' == *ch)
		{
			strLine.erase(strLine.find_last_not_of(*ch) + 1);
			ch = strLine.end() - 1;
		}
		// Ѱ�Ҽ�ֵ֮��ķָ��ַ���
		string str_symbol = "";
		for (ch = strLine.begin(); ch != strLine.end(); ch++)
		{
			if (' ' == *ch || '\r' == *ch || '\n' == *ch || '\t' == *ch || '\f' == *ch || '=' == *ch)
			{
				str_symbol += *ch;
			}
		}
		// ͨ����ֵ֮��ķָ��ַ������зָ���ȡ����ֵ
		int pos_symbol = strLine.find(str_symbol);
		if (pos_symbol != string::npos)
		{
			string str_key = strLine.substr(0, pos_symbol);
			string str_value = strLine.substr(pos_symbol + str_symbol.size(), strLine.size() - str_symbol.size() - pos_symbol);
			//cout << str_key << " ==> " << str_value << endl;
			k_v.insert(make_pair(str_key, str_value));
		}
	}
	return k_v;
}

int CCfgHelper::setKeyValue(string cfgFilePath)
{
	return 0;
}
