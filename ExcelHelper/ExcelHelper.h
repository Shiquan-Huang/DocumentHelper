// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� EXCELHELPER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// EXCELHELPER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef EXCELHELPER_EXPORTS
#define EXCELHELPER_API __declspec(dllexport)
#else
#define EXCELHELPER_API __declspec(dllimport)
#endif

// �����Ǵ� ExcelHelper.dll ������
class EXCELHELPER_API CExcelHelper {
public:
	CExcelHelper(void);
	// TODO:  �ڴ�������ķ�����
};