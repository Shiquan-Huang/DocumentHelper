// CfgHelper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CfgHelper.h"
#include <fstream>
#include <iostream>

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 CfgHelper.h
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
		// 跳过空行、以/或#字符开头的行
		if (strLine.empty() || strLine.substr(0, 1) == "/" || strLine.substr(0, 1) == "#")
		{
			continue;
		}
		// 截去每行后面的注释部分
		int pos = -1;
		if ((pos = strLine.find("//")) != string::npos)
		{
			strLine = strLine.substr(0, pos);
		}
		// 去除头部不可见字符
		string::const_iterator ch = strLine.begin();
		while (' ' == *ch || '\r' == *ch || '\n' == *ch || '\t' == *ch || '\f' == *ch)
		{
			strLine.erase(0, strLine.find_first_not_of(*ch));
			ch = strLine.begin();
		}
		// 去除尾部不可见字符
		ch = strLine.end() - 1;
		while (' ' == *ch || '\r' == *ch || '\n' == *ch || '\t' == *ch || '\f' == *ch)
		{
			strLine.erase(strLine.find_last_not_of(*ch) + 1);
			ch = strLine.end() - 1;
		}
		// 寻找键值之间的分隔字符串
		string str_symbol = "";
		for (ch = strLine.begin(); ch != strLine.end(); ch++)
		{
			if (' ' == *ch || '\r' == *ch || '\n' == *ch || '\t' == *ch || '\f' == *ch || '=' == *ch)
			{
				str_symbol += *ch;
			}
		}
		// 通过键值之间的分隔字符串进行分隔截取键和值
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
