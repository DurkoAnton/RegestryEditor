#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::writeKeyInFile(string fullPathToTheKey){

	HKEY key = 0;
	HANDLE ProcessToken;
	string fileName;
	string catalogName = "SaveFiles\\";

	string pathToTheKey = "";

	if (fullPathToTheKey.find_first_of('\\') != -1)
		pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &ProcessToken);
	SetPrivilege(ProcessToken, SE_BACKUP_NAME, TRUE);

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE, (PHKEY)&key) == ERROR_SUCCESS){
		fflush(stdin);
		cout << endl << endl << endl << "Введите имя файла:"<<endl<<endl;
		getline(cin, fileName);

		fileName = catalogName + fileName;
		if (RegSaveKey(key, (LPCSTR)fileName.c_str(), NULL) != ERROR_SUCCESS){
			RegCloseKey(key);
			return ERROR_WRITE_KEY_IN_FILE;
		}
	}
	else
		return ERROR_OPEN_KEY;

	RegCloseKey(key);

	outputInformation.outputSuccessSavingKey(fullPathToTheKey, fileName);

	return NO_ERRORS;
}
BOOL RegistryFunctions::SetPrivilege(
	HANDLE hToken,        
	LPCTSTR lpszPrivilege, 
	BOOL bEnablePrivilege 
	)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(
		NULL,            
		lpszPrivilege, 
		&luid))        
	{
		printf("Ошибка: %u\n", GetLastError());
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if (!AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		printf("Ошибка: %u\n", GetLastError());
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		printf("Привилегия не найдена. \n");
		return FALSE;
	}

	return TRUE;
}
ResultOfRegistryFunctions RegistryFunctions::readKeyFromFile(string fullPathToTheKey){

	HKEY key = 0;
	HANDLE ProcessToken;
	string fileName;
	string catalogName = "SaveFiles\\";

	string pathToTheKey = "";
	
	if (fullPathToTheKey.find_first_of('\\') != -1)
		pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	/*OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &ProcessToken);
	SetPrivilege(ProcessToken, SE_BACKUP_NAME, TRUE);*/
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &ProcessToken);
	SetPrivilege(ProcessToken, SE_RESTORE_NAME, TRUE);

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE, (PHKEY)&key) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	fflush(stdin);
	cout << endl << endl << endl << "Введите имя файла:" << endl << endl;
	getline(cin, fileName);

	fileName = catalogName + fileName;
	if (RegRestoreKey(key, (LPCSTR)fileName.c_str(), REG_FORCE_RESTORE) != ERROR_SUCCESS){
		RegCloseKey(key);
		return ERROR_READ_KEY_FROM_FILE;
	}

	RegCloseKey(key);

	outputInformation.outputSuccessRestoringKey(fullPathToTheKey, fileName);

	return NO_ERRORS;
}

