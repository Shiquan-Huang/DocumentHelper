#include <iostream>
#include "CfgHelper.h"
#include "ExcelHelper.h"
#include <map>
using namespace std;

int main(_In_ int argc, _In_reads_(argc) _Pre_z_ char** argv, _In_z_ char** envp)
{
	CCfgHelper cfgHelper;
	/*map<string, string> k_v = */cfgHelper.setKeyValue("Configure.txt","ProjecID","CHX004");
	/*for (map<string, string>::iterator it = k_v.begin(); it != k_v.end(); ++it)
	{
		cout << it->first << " == " << it->second << endl;
	}*/
	system("pause");
	return 0;
}