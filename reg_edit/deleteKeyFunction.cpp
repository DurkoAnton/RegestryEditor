#include"functionPrototype.h"

bool RegistryFunctions:: deleteKey(string fullPathToTheKey){

	TCHAR *findedKey;
	string pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	if (fullPathToTheKey.find_first_of('\\') == -1)
		return false;
	else
	{
		findedKey = new TCHAR[pathToTheKey.length()];
		copy(pathToTheKey.begin(), pathToTheKey.end(), findedKey);
		findedKey[pathToTheKey.length()] = '\0';
	}

	if (RegDeleteKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), findedKey, KEY_WOW64_64KEY, 0) != ERROR_SUCCESS){
		return false;
	}
	return true;
}