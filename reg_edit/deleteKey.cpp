#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions:: deleteKey(string fullPathToTheKey){
	

	string pathToTheKey = "";

	if (fullPathToTheKey.find_first_of('\\') != -1)

	pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	HKEY key;

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE | KEY_ALL_ACCESS, (PHKEY)&key) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	if (getCountSubKeysInKey(key)!=0)
		return ERROR_DELETE_KEY;
	else
	RegCloseKey(key);

	if (RegDeleteKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)
		return ERROR_DELETE_KEY;

	outputInformation.outputSuccessDeletingKey(fullPathToTheKey);
	return NO_ERRORS;
}