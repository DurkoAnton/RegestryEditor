#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include<Windows.h>
#include<string>
#include<locale.h>
#include<regex>
#include<tchar.h>
//#define MAX_LENGTH_
using namespace std;

class RegistryFunctions{
public:
	RegistryFunctions(){}
	~RegistryFunctions(){}

	bool readRegistryValue(string);
	bool createKey(string);
	bool deleteKey(string);
	bool deleteValue(string);
	bool getInformationForRegistry();
	bool outputSubKeys(string);
	bool outputKeyValues(string);
};
void checkType(DWORD, char *, DWORD);
void outputNumValue(char*);
void outputRegBinary(char*r);
BOOL SetPrivilege(HANDLE, LPCTSTR, BOOL );
void showMenu();
HKEY inputRazdel(string );
HKEY tranformStringToHKEY(string);
void outputCharValue(char *, DWORD);
void outputRegBinary(char *, DWORD);
void outputNumValue(char *, DWORD );
void checkType(DWORD , char *, DWORD );

void inputSettingValue(DWORD, HKEY, TCHAR *);
DWORD setType();
void writeRegistry(string);

void infoRegistry();
void regCopy(string , string);
void writeFile(string);
string checkStringForRegExp();

void infoKey(string);

