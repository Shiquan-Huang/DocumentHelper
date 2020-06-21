// CfgHelper.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "CfgHelper.h"
#include <fstream>
#include <iostream>
#include <vector>

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
		file.close();
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
	file.close();
	return k_v;
}

int CCfgHelper::setKeyValue(string cfgFilePath, string strKey, string strVal)
{
	// ��һ�����ȶ�ȡԭ�ļ�����
	ifstream file;
	file.open(cfgFilePath, ios::in);
	if (!file.is_open())
	{
		cout << "Open the cfg failed!" << endl;
		file.close();
		return -1;
	}
	std::string curLine;
	map<string, string> k_v;
	vector<vector<string>> str_kv_info;
	while (getline(file, curLine))
	{
		string strLine = curLine;
		string str_key = "";
		string str_value = "";
		vector<string> line_str_info;
		// �������С���/��#�ַ���ͷ����
		if (strLine.empty() || strLine.substr(0, 1) == "/" || strLine.substr(0, 1) == "#")
		{
			line_str_info.push_back(curLine);
			line_str_info.push_back("");
			line_str_info.push_back("");
			str_kv_info.push_back(line_str_info);
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
			str_key = strLine.substr(0, pos_symbol);
			str_value = strLine.substr(pos_symbol + str_symbol.size(), strLine.size() - str_symbol.size() - pos_symbol);
		}
		line_str_info.push_back(curLine);
		line_str_info.push_back(str_key);
		line_str_info.push_back(str_value);
		str_kv_info.push_back(line_str_info);
	}
	file.close();
	// �ڶ�������ȡ�����滻��ֵ
	for (auto &line_info : str_kv_info)
	{
		if (line_info[1] == strKey)
		{
			int _pos = line_info[0].find(line_info[2]);
			int len = line_info[2].size();
			line_info[0].replace(_pos, len, strVal);
			line_info[2] = strVal;
		}
	}
	// ���������滻��ֵ����������д��
	ofstream write_file;
	write_file.open(cfgFilePath, ios::trunc);
	if (!write_file.is_open())
	{
		cout << "Write the cfg failed!" << endl;
		write_file.close();
		return -1;
	}
	for (int i = 0; i < str_kv_info.size(); i++)
	{
		if (i < str_kv_info.size() - 1)
		{
			write_file << str_kv_info[i][0] << "\n";
		}
		else
		{
			write_file << str_kv_info[i][0];
		}
	}
	write_file.close();
	return 0;
}
