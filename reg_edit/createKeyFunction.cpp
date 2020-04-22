#include"functionPrototype.h"

bool RegistryFunctions:: createKey(string fullPathToTheKey){
	HKEY key;

	TCHAR *pathToTheKey=NULL, *newKeyName=NULL;
	string newKeyNameString;


	string tempStringForSearch = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	cout << endl << "Введите название нового ключа:" << endl;

	fflush(stdin);
	getline(cin, newKeyNameString);

	newKeyName = new TCHAR[newKeyNameString.length()];
	copy(newKeyNameString.begin(), newKeyNameString.end(), newKeyName);
	newKeyName[newKeyNameString.length()] = '\0';

	if (fullPathToTheKey.find_first_of('\\') == -1)
		pathToTheKey = NULL;

	else
	{
		pathToTheKey = new TCHAR[tempStringForSearch.length()];
		copy(tempStringForSearch.begin(), tempStringForSearch.end(), pathToTheKey);
		pathToTheKey[tempStringForSearch.length()] = '\0';
	}

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey, NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE|KEY_ALL_ACCESS, (PHKEY)&key) != ERROR_SUCCESS){
		return false;
	}

	if (RegCreateKeyEx(key, newKeyName, NULL, NULL, REG_OPTION_NON_VOLATILE|KEY_ALL_ACCESS, KEY_WRITE, NULL, (PHKEY)&key, NULL) != ERROR_SUCCESS){
		return false;
	}

	RegCloseKey(key);

	if (pathToTheKey!=NULL)
	memset(pathToTheKey, 0, sizeof(pathToTheKey));

	if (newKeyName != NULL)
	memset(newKeyName, 0, sizeof(newKeyName));

	return true;
}