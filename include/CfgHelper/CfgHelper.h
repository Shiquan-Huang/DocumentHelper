// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CFGHELPER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CFGHELPER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CFGHELPER_EXPORTS
#define CFGHELPER_API __declspec(dllexport)
#else
#define CFGHELPER_API __declspec(dllimport)
#endif
#include <map>
#include <string>
using namespace std;

// �����Ǵ� CfgHelper.dll ������
class CFGHELPER_API CCfgHelper {
public:
	CCfgHelper(void);
	// TODO:  �ڴ�������ķ�����
	map<string, string> getKeyValue(string cfgFilePath);

	int setKeyValue(string cfgFilePath);
};