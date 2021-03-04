#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::getInformationAboutRegistry(){
	system("cls");
	cout << endl << "Вывод:" << endl << endl;
	DWORD freeMemory, allMemory;
	if (GetSystemRegistryQuota(&freeMemory, &allMemory) == 0)
		return ERROR_GET_INFORMATION_ABOUT_REGISTRY;
	cout << endl << "Текущий размер реестра = " << allMemory << " байт";
	cout << endl << "Максимальный размер реестра = " << freeMemory << " байт"<<endl;
	outputInformation.outputWaitingKeyCode();
	return NO_ERRORS;
}

HKEY RegistryFunctions::tranformStringToHKEY(string section){
	if (!_strcmpi(section.c_str(), "hkey_local_machine"))
		return HKEY_LOCAL_MACHINE;
	if (!_strcmpi(section.c_str(), "hkey_current_user"))
		return HKEY_CURRENT_USER;
	if (!_strcmpi(section.c_str(), "hkey_users"))
		return HKEY_USERS;
	if (!_strcmpi(section.c_str(), "hkey_classes_root"))
		return HKEY_CLASSES_ROOT;
	if (!_strcmpi(section.c_str(), "hkey_current_config"))
		return HKEY_CURRENT_CONFIG;
}
