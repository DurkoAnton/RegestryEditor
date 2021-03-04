#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::copyKeys(string fullPathToTheSourceKey, string fullPathToTheDesctinationKey){

	string pathToTheFirstKey = "";
	string pathToTheSecondKey = "";

	if (fullPathToTheSourceKey.find_first_of('\\') != -1)
		pathToTheFirstKey = fullPathToTheSourceKey.substr(fullPathToTheSourceKey.find_first_of('\\') + 1, fullPathToTheSourceKey.length() - fullPathToTheSourceKey.find_first_of('\\'));

	if (fullPathToTheDesctinationKey.find_first_of('\\') != -1)
		pathToTheSecondKey = fullPathToTheDesctinationKey.substr(fullPathToTheDesctinationKey.find_first_of('\\') + 1, fullPathToTheDesctinationKey.length() - fullPathToTheDesctinationKey.find_first_of('\\'));

	HKEY sourceKey, destinationKey;
	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheSourceKey.substr(0, fullPathToTheSourceKey.find_first_of('\\'))), pathToTheFirstKey.c_str(), 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS | KEY_CREATE_SUB_KEY, (PHKEY)&sourceKey) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheDesctinationKey.substr(0, fullPathToTheDesctinationKey.find_first_of('\\'))), pathToTheSecondKey.c_str(), 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS | KEY_CREATE_SUB_KEY, (PHKEY)&destinationKey) != ERROR_SUCCESS){
		RegCloseKey(sourceKey);
		return ERROR_OPEN_KEY;
	}
	if (RegCopyTreeA(sourceKey, NULL, destinationKey) != ERROR_SUCCESS){
		RegCloseKey(sourceKey);
		RegCloseKey(destinationKey);
		return ERROR_COPY_KEYS;
	}

	outputInformation.outputSuccessCopyingKeys(fullPathToTheSourceKey, fullPathToTheDesctinationKey);

	RegCloseKey(sourceKey);
	RegCloseKey(destinationKey);
	return NO_ERRORS;
}