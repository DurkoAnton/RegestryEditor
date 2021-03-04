#include"functionPrototype.h"
#include<conio.h>
ResultOfRegistryFunctions RegistryFunctions::createNewKey(string fullPathToTheKey){

	string newKeyNameString;

	string pathToTheKey = "";

	if (fullPathToTheKey.find_first_of('\\') != -1)

	pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));
	
	HKEY key;

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), NULL, KEY_WOW64_64KEY | KEY_QUERY_VALUE | KEY_ALL_ACCESS, (PHKEY)&key) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	newKeyNameString = checkingForRegularExpression.inputAndCheckKeyName();
	
	if (RegCreateKeyEx(key, newKeyNameString.c_str(), 0, NULL,REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, NULL) != ERROR_SUCCESS){
		RegCloseKey(key);
		return ERROR_CREATE_KEY;
	}

	outputInformation.outputSuccessCreatingKey(newKeyNameString);

	RegCloseKey(key);

	return NO_ERRORS;
}
