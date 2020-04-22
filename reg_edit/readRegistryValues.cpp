#include"functionPrototype.h"

bool RegistryFunctions::readRegistryValue(string fullPathToTheKey){

	string parameterNameString;
	TCHAR *pathToTheKey, *parameterName;
	DWORD valueType;
	string tempStringForSearch = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	if (fullPathToTheKey.find_first_of('\\') == -1)
		pathToTheKey = NULL;

	else
	{
		pathToTheKey = new TCHAR[tempStringForSearch.length()];
		copy(tempStringForSearch.begin(), tempStringForSearch.end(), pathToTheKey);
		pathToTheKey[tempStringForSearch.length()] = '\0';
	}
	DWORD size = MAX_PATH;
	char parameterValue[MAX_PATH];
	fflush(stdin);
	cout << endl << "Введите имя параметра:" << endl;
	getline(cin, parameterNameString);

	parameterName = new TCHAR[parameterNameString.length()];
	copy(parameterNameString.begin(), parameterNameString.end(), parameterName);
	parameterName[parameterNameString.length()] = '\0';

	if (RegGetValue(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey, parameterName, RRF_RT_ANY, (LPDWORD)& valueType, parameterValue, &size) != ERROR_SUCCESS) {
		return false;
	}
	else{
		checkType(valueType, parameterValue, size);
	}

	memset(pathToTheKey, 0, sizeof(pathToTheKey));
	memset(parameterName, 0, sizeof(parameterName));

	return true;
}