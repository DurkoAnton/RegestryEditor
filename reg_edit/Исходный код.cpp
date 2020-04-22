#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include<Windows.h>
#include<string>
#include<locale.h>
#include<regex>
#include<tchar.h>
#include"functionPrototype.h"


void showMenu(){
	cout << endl << "1. Чтение из реестра" << endl;
	cout << endl << "2. Создание ключа" << endl;
	cout << endl << "3. Удаление ключа" << endl;
	cout << endl << "4. Запись значения " << endl;
	cout << endl << "5. Удаление значения" << endl;
	cout << endl << "6. Информация о реестре" << endl;
	cout << endl << "7. Вывод подраделов" << endl;
	cout << endl << "8. Копирование раздела" << endl;
	cout << endl << "9. Вывод значений" << endl;
	cout << endl << "10. Запись в файл" << endl;
	cout << endl << "11. Информация о ключе" << endl;

}
void showRazdel(){
	cout << endl << "1. HKEY_CLASSES_ROOT" << endl << "2. HKEY_CURRENT_USER" << endl << "3. HKEY_LOCAL_MACHINE" << endl << "4. HKEY_USERS" << endl << "5. HKEY_CURRENT_CONFIG" << endl;
}
HKEY inputRazdel(string s){
	//regex r("[1-5]+");
	////string s;
	//do{
	//	//getline(cin, s);
	//	if (!regex_match(s, r)){
	//		cout << endl << "errorrn1";
	//	}
	//	else
	//		break;
	//} while (1);

	switch (atoi(s.c_str()))
	{
	case 1:
		return HKEY_CLASSES_ROOT;
	case 2:
		return HKEY_CURRENT_USER;
	case 3:
		cout << "3333333";
		return HKEY_LOCAL_MACHINE;
	case 4:
		return HKEY_USERS;
	case 5:
		return HKEY_CURRENT_CONFIG;
	}
}
HKEY tranformStringToHKEY(string section){
	if (!strcmp(section.c_str(), "hkey_local_machine")){
		//cout << "da";
		return HKEY_LOCAL_MACHINE;
	}
	if (!strcmp(section.c_str(), "hkey_current_user"))
		return HKEY_CURRENT_USER;
	if (!strcmp(section.c_str(), "hkey_users"))
		return HKEY_USERS;
	if (!strcmp(section.c_str(), "hkey_classes_root"))
		return HKEY_CLASSES_ROOT;
	if (!strcmp(section.c_str(), "hkey_current_config"))
		return HKEY_CURRENT_CONFIG;
}

void outputCharValue(char *r,DWORD size){
	int i = 0;
	while (i<size)
		cout << (char)r[i++];
}
void outputRegBinary(char *r, DWORD size){
	int i = 0;
	while (i<size-1)
		cout << r[i++] << " ";
		/*if ((i + 1) % 4 == 0)
			cout << endl;*/
}
void outputNumValue(char *r,DWORD size){
	int i = 0;
	wchar_t wr[MAX_PATH];
	swprintf(wr, L"%s", r);
	cout << endl;
//	while (i<size)
		wcout << (int)wr[i++];
}
void checkType(DWORD type, char *s,DWORD size){
	switch (type){
	case REG_SZ:
		outputCharValue(s,size);
		break;
	case REG_DWORD:
		outputNumValue(s,size);
		break;
	case REG_BINARY:
		outputRegBinary(s,size);
		break;
	case REG_EXPAND_SZ:
		outputCharValue(s,size);
		break;
	case REG_MULTI_SZ:
		//cout << "mult";
		outputCharValue(s,size);
		break;
	case REG_QWORD:
		outputNumValue(s,size);
		break;
	}
}



void inputSettingValue(DWORD type, HKEY key, TCHAR * findedValue){
	DWORD temp;
	DWORD tem;
	DWORD64 s;
	DOUBLE d;
	string value;
	BYTE settingValue[MAX_PATH];
	fflush(stdin);
	switch (type)
	{
	case REG_QWORD:
		cin >> s;
		if (RegSetValueEx(key, findedValue, 0, type, (BYTE*)&s, sizeof(s)) != ERROR_SUCCESS)
			cout << "Error setting" << endl;
		break;
	case REG_DWORD:
		cin >> temp;
		if (RegSetValueEx(key, findedValue, 0, type, (BYTE*)&temp, sizeof(temp)) != ERROR_SUCCESS)
			cout << "Error setting" << endl;
		break;
	case REG_SZ:
		cout << "value reg_sz= ";
		cin >> settingValue;
		
		if (RegSetValueEx(key, findedValue, 0, type, settingValue, sizeof(settingValue)) != ERROR_SUCCESS)
			cout << "Error setting" << endl;
		break;
	case REG_EXPAND_SZ:
		cout << "value exp= ";
		cin >> settingValue;

		if (RegSetValueEx(key, findedValue, 0, type, settingValue, sizeof(settingValue)) != ERROR_SUCCESS)
			cout << "Error setting" << endl;
		break;
	case REG_BINARY:
		cout << "value exp= ";
		cin >> settingValue;

		if (RegSetValueEx(key, findedValue, 0, type, settingValue, sizeof(type)) != ERROR_SUCCESS)
			cout << "Error setting" << endl;
		break;
	default:
		break;
	}
}
DWORD setType(){
	cout << endl << "Выберите вводимый тип данных1" << endl;
	cout << endl << "1. REG_SZ";
	cout << endl << "2. REG_DWORD";
	cout << endl << "3. REG_BINARY";
	cout << endl << "4. REG_EXPAND_SZ";
	cout << endl << "5. REG_MULTI_SZ";
	cout << endl << "6. REG_QWORD";

	int type;
	fflush(stdin);
	cin >> type;

	switch (type)
	{
	case 1:
		return REG_SZ;
		break;
	case 2:
		return REG_DWORD;
		break;
	case 3:
		return REG_BINARY;
		break;
	case 4:
	//	cout << endl << "4. REG_EXPAND_SZ";
		return REG_EXPAND_SZ;
		break;
	case 5:
		return REG_MULTI_SZ;
	case 6:
		return REG_QWORD;
	default:
		break;
	}

}
void writeRegistry(string str){
	HKEY key;
	TCHAR *findedKey, *findedValue;
	BYTE settingValue[MAX_PATH];
	string value, setValue;
	DWORD type;
	string s = str.substr(str.find_first_of('\\') + 2, str.length() - str.find_first_of('\\'));

	if (str.find_first_of('\\') == -1)
		findedKey = NULL;
	else
	{
		findedKey = new TCHAR[s.length()];
		copy(s.begin(), s.end(), findedKey);
		findedKey[s.length()] = '\0';
	}

	/*findedKey = new TCHAR[str.length()];
	copy(str.begin(), str.end(), findedKey);
	findedKey[str.length()] = '\0';*/

	if (RegOpenKeyEx(tranformStringToHKEY(str.substr(0, str.find_first_of('\\'))), findedKey, 0, KEY_WOW64_64KEY | KEY_SET_VALUE, (PHKEY)&key) != ERROR_SUCCESS)
		cout << "Error opening" << endl;
	fflush(stdin);
	type = setType();
	
	cout << "value11 = ";
	fflush(stdin);
	getline(cin, value);
	findedValue = new TCHAR[value.length()];
	copy(value.begin(), value.end(), findedValue);
	findedValue[value.length()] = '\0';
	//getline(cin, settingValue);
	fflush(stdin);
	inputSettingValue(type, key, findedValue);
	/*cin >> settingValue;


	if (RegSetValueEx(key, findedValue, 0, type, settingValue, 3) != ERROR_SUCCESS)
	cout << "Error setting"<<endl;*/
	RegCloseKey(key);
}

bool RegistryFunctions :: getInformationForRegistry(){
	DWORD s1, s2;
	if (GetSystemRegistryQuota(&s1, &s2) == 0)
		return false;
	cout << endl << "Текущий размер   = " << s2 <<" байт";
	cout << endl << "Свободного места = " << s1 <<" байт";
	return true;
}

void regCopy(string str1, string str2){

	string s = str1.substr(str1.find_first_of('\\') + 2, str1.length() - str1.find_first_of('\\'));
	TCHAR *findedKey;
	TCHAR *findedKey1;
	if (str1.find_first_of('\\') == -1)
		findedKey = NULL;
	else
	{
		findedKey = new TCHAR[s.length()];
		copy(s.begin(), s.end(), findedKey);
		findedKey[s.length()] = '\0';
	}
	s = str2.substr(str2.find_first_of('\\') + 2, str2.length() - str2.find_first_of('\\'));
	if (str2.find_first_of('\\') == -1)
		findedKey1 = NULL;
	else
	{
		findedKey1 = new TCHAR[s.length()];
		copy(s.begin(), s.end(), findedKey1);
		findedKey1[s.length()] = '\0';
	}

	HKEY key, key1;
	if (RegOpenKeyEx(tranformStringToHKEY(str1.substr(0, str1.find_first_of('\\'))), findedKey, 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS | KEY_CREATE_SUB_KEY, (PHKEY)&key) != ERROR_SUCCESS)
		cout << "er1";
	if (RegOpenKeyEx(tranformStringToHKEY(str2.substr(0, str2.find_first_of('\\'))), findedKey1, 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS | KEY_CREATE_SUB_KEY, (PHKEY)&key1) != ERROR_SUCCESS)
		cout << "er2";
	if (RegCopyTree(key1, NULL, key) != ERROR_SUCCESS)
		cout << "er3";
	RegCloseKey(key);
	RegCloseKey(key1);

}
void writeFile(string str){
	TCHAR *findedKey, *findedValue = NULL;

	DWORD type; HKEY key = 0;
	HANDLE ProcessToken;
	
	string s = str.substr(str.find_first_of('\\') + 2, str.length() - str.find_first_of('\\'));
	if (str.find_first_of('\\') == -1)
		findedKey = NULL;
	else
	{
		findedKey = new TCHAR[s.length()];
		copy(s.begin(), s.end(), findedKey);
		findedKey[s.length()] = '\0';
	}
	findedKey = new TCHAR[str.length()];
	copy(str.begin(), str.end(), findedKey);
	findedKey[str.length()] = '\0';

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &ProcessToken);
	SetPrivilege(ProcessToken, SE_BACKUP_NAME, TRUE);
	//	cout << "]]]";
	if (RegOpenKeyEx(tranformStringToHKEY(str.substr(0, str.find_first_of('\\'))), findedKey, NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE, (PHKEY)&key) == ERROR_SUCCESS){
		if (RegSaveKey(key, (LPCSTR)"file2.txt", NULL) == ERROR_SUCCESS){
			cout << "no";
		}
		else
			cout << "da";
	}
	else
		cout << "no1";
	RegCloseKey(key);
}
BOOL SetPrivilege(
	HANDLE hToken,          // access token handle
	LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
	BOOL bEnablePrivilege   // to enable or disable privilege
	)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(
		NULL,            // lookup privilege on local system
		lpszPrivilege,   // privilege to lookup 
		&luid))        // receives LUID of privilege
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.

	if (!AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		printf("AdjustTokenPrivileges error: %u\n", GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)

	{
		printf("The token does not have the specified privilege. \n");
		return FALSE;
	}

	return TRUE;
}
void readFile(string str){
	TCHAR *findedKey, *findedValue = NULL;

	DWORD type; HKEY key = 0;
	HANDLE ProcessToken;
	findedKey = new TCHAR[str.length()];
	copy(str.begin(), str.end(), findedKey);
	findedKey[str.length()] = '\0';
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &ProcessToken);
	SetPrivilege(ProcessToken, SE_BACKUP_NAME, TRUE);
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &ProcessToken);

	SetPrivilege(ProcessToken, SE_RESTORE_NAME, TRUE);

	//	cout << "]]]";
	if (RegOpenKeyEx(HKEY_CURRENT_USER, findedKey, NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE, (PHKEY)&key) == ERROR_SUCCESS){
		if (RegRestoreKey(HKEY_CURRENT_USER, (LPCSTR)"file2.txt", REG_FORCE_RESTORE) == ERROR_SUCCESS){
			cout << "no";
		}
		else
			cout << "da";
	}
	RegCloseKey(key);
}

//void saveValue(HKEY key,string str){
//	if (RegQueryMultipleValues(key,))
//}
//void regNotify(HKEY key){
//	if (RegNotifyChangeKeyValue(key,TRUE,REG_NOTIFY_CHANGE_NAME|REG_NOTIFY_CHANGE_LAST_SET,))
//}

void infoKey(string str){
	HKEY key;
	TCHAR *findedKey;
	DWORD countKeys,countValues;
	FILETIME lastChange,lastCreate;

	string s = str.substr(str.find_first_of('\\') + 2, str.length() - str.find_first_of('\\'));
	//string s = str.substr(str.find_first_of('\\') + 2, str.length() - str.find_first_of('\\'));
	if (str.find_first_of('\\') == -1)
		findedKey = NULL;
	else
	{
		findedKey = new TCHAR[s.length()];
		copy(s.begin(), s.end(), findedKey);
		findedKey[s.length()] = '\0';
	}
	/*findedKey = new TCHAR[str.length()];
	copy(str.begin(), str.end(), findedKey);
	findedKey[str.length()] = '\0';
*/
	if (RegOpenKeyEx(tranformStringToHKEY(str.substr(0, str.find_first_of('\\'))), findedKey, 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS | KEY_CREATE_SUB_KEY, (PHKEY)&key) != ERROR_SUCCESS)
		cout << "er1";

	if (RegQueryInfoKey(key, NULL, NULL, NULL, &countKeys, NULL, NULL, &countValues, NULL, NULL, NULL,(FILETIME *)&lastChange) != ERROR_SUCCESS){
		cout << "er2";
	}
	cout <<endl<< countKeys;
	cout <<endl<< countValues;
	SYSTEMTIME time;
	FileTimeToSystemTime(&lastChange, &time);
	cout << endl << lastChange.dwHighDateTime<<endl<<lastChange.dwLowDateTime;
}
