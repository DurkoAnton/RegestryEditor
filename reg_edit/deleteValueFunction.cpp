#include "functionPrototype.h"

bool RegistryFunctions::deleteValue(string fullPathToTheKey){

	HKEY key;
	TCHAR *pathToTheKey = NULL, *parameterName = NULL;
	string parameterNameString;

	string tempStringForSearch = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));
	
	if (fullPathToTheKey.find_first_of('\\') == -1)
		pathToTheKey = NULL;
	else
	{
		pathToTheKey = new TCHAR[tempStringForSearch.length()];
		copy(tempStringForSearch.begin(), tempStringForSearch.end(), pathToTheKey);
		pathToTheKey[tempStringForSearch.length()] = '\0';
	}

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey, NULL, KEY_WOW64_64KEY | KEY_ALL_ACCESS, &key) != ERROR_SUCCESS)
		return false;

	fflush(stdin);
	getline(cin, parameterNameString);

	parameterName = new TCHAR[parameterNameString.length()];
	copy(parameterNameString.begin(), parameterNameString.end(), parameterName);
	parameterName[parameterNameString.length()] = '\0';

	if (RegDeleteValue(key, parameterName) != ERROR_SUCCESS)
		return false;

	RegCloseKey(key);

	if (pathToTheKey != NULL)
		memset(pathToTheKey, 0, sizeof(pathToTheKey));

	if (parameterName != NULL)
		memset(parameterName, 0, sizeof(parameterName));

	return true;
}