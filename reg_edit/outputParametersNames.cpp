#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::outputParameterNamesInKey(string fullPathToTheKey){
	
	char parameterName[MAX_PATH];
	DWORD lengthParameterName = MAX_PATH, sizeParameterValue = MAX_PATH;

	string pathToTheKey = "";
	HKEY key;

	if (fullPathToTheKey.find_first_of('\\') != -1)
		pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	int i = 0, j = 0;

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), 0, KEY_WOW64_64KEY | KEY_QUERY_VALUE, (PHKEY)&key) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	DWORD countValuesInKey = getCountParametersInKey(key);

	if (countValuesInKey == 0) return ERROR_NOT_ARE_VALUES_IN_KEY;

	while (i<countValuesInKey){

		lengthParameterName = MAX_PATH;

		if (RegEnumValue(key, i, (LPSTR)&parameterName, (LPDWORD)&lengthParameterName, NULL, NULL,NULL,NULL) != ERROR_SUCCESS){
			return ERROR_ENUM_PARAMETERS;
		}
		i++;
		outputInformation.outputParameterName(parameterName, i,fullPathToTheKey);
	}

	outputInformation.outputWaitingKeyCode();

	return NO_ERRORS;
}

DWORD RegistryFunctions::getCountParametersInKey(HKEY key){

	DWORD countSubValues;

	if (RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, &countSubValues, NULL, NULL, NULL, NULL) != ERROR_SUCCESS){
		return ERROR_GET_INFORMATION_ABOUT_REGISTRY;
	}

	return countSubValues;
}

