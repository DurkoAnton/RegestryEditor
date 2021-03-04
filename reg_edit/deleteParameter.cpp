#include "functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::deleteParameter(string fullPathToTheKey){

	HKEY key;
	string parameterNameString;

	string pathToTheKey = "";
	
	if (fullPathToTheKey.find_first_of('\\') != -1)

		pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), NULL, KEY_WOW64_64KEY | KEY_ALL_ACCESS, &key) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	parameterNameString = checkingForRegularExpression.inputAndCheckParameterName();

	if (RegDeleteValue(key, parameterNameString.c_str()) != ERROR_SUCCESS)
		return ERROR_DELETE_PARAMETER;

	outputInformation.outputSuccessDeletingParameter(parameterNameString, fullPathToTheKey);

	RegCloseKey(key);

	return NO_ERRORS;
}