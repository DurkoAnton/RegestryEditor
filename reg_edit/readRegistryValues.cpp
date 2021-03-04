#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::readParameterValue(string fullPathToTheKey){

	string parameterNameString;
	DWORD valueType;

	string pathToTheKey = "";
	
	if (fullPathToTheKey.find_first_of('\\') != -1)
		 pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	DWORD size = MAX_PATH;
	char parameterValue[MAX_PATH];
	fflush(stdin);

	parameterNameString = checkingForRegularExpression.inputAndCheckParameterName();

	if (RegGetValue(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), parameterNameString.c_str(), RRF_RT_ANY, (LPDWORD)& valueType, parameterValue, &size) != ERROR_SUCCESS)
		return ERROR_GET_VALUE;

	else
		if (!outputInformation.checkParameterTypeForOutput(valueType, parameterValue, size,parameterNameString))
			return ERROR_UNSUPPORTED_REG_TYPE;

	return NO_ERRORS;
}