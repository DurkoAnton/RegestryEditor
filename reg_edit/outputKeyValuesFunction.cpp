#include"functionPrototype.h"

bool RegistryFunctions::outputKeyValues(string fullPathToTheKey){
	
	TCHAR parameterName[MAX_PATH];
	DWORD lengthParameterName = MAX_PATH, sizeParameterValue = MAX_PATH;
	string tempStringForSearch = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));
	HKEY key;
	TCHAR *pathToTheKey = NULL;
	DWORD valueType;
	if (fullPathToTheKey.find_first_of('\\') == -1)
		pathToTheKey = NULL;
	else
	{
		pathToTheKey = new TCHAR[tempStringForSearch.length()];
		copy(tempStringForSearch.begin(), tempStringForSearch.end(), pathToTheKey);
		pathToTheKey[tempStringForSearch.length()] = '\0';
	}

	int i = 0, j = 0;
	char data[MAX_PATH];

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey, 0, KEY_WOW64_64KEY | KEY_QUERY_VALUE, (PHKEY)&key) != ERROR_SUCCESS)
		return false;
	do{

		lengthParameterName = MAX_PATH;
		sizeParameterValue = MAX_PATH;

		if (RegEnumValue(key, i, (LPSTR)&parameterName, (LPDWORD)lengthParameterName, NULL, (LPDWORD)&valueType, (LPBYTE)&data, (LPDWORD)&sizeParameterValue) != ERROR_SUCCESS){
			break;
		}

		j = 0;
		i++;
		cout << endl;
		while ((char)parameterName[j])
			cout << (char)parameterName[j++];
		cout << "   ";

		checkType(valueType, data, sizeParameterValue);
	} while (true);

	return true;
}