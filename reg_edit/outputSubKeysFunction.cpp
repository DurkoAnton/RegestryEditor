#include"functionPrototype.h"

bool RegistryFunctions::outputSubKeys(string  fullPathToTheKey){

	
	TCHAR subKeysNames[MAX_PATH];
	DWORD size = MAX_PATH;

	HKEY key;
	TCHAR *pathToTheKey = NULL;
	string tempStringForSearch = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	if (fullPathToTheKey.find_first_of('\\') == -1)
		pathToTheKey = NULL;
	else
	{
		pathToTheKey = new TCHAR[tempStringForSearch.length()];
		copy(tempStringForSearch.begin(), tempStringForSearch.end(), pathToTheKey);
		pathToTheKey[tempStringForSearch.length()] = '\0';
	}

	int i = 0;

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey, NULL, KEY_WOW64_64KEY | KEY_ALL_ACCESS | KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return false;
	do{
		if (RegEnumKey(key, i, (LPSTR)&subKeysNames, size) != ERROR_SUCCESS)
			return true;
		i++;
		int j = 0;
		while ((char)subKeysNames[j])
			cout << (char)subKeysNames[j++];

		cout << endl << endl;
	} while (true);

	if (pathToTheKey != NULL)
		memset(pathToTheKey, 0, sizeof(pathToTheKey));

	return true;
}