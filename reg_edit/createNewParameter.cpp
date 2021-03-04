#include"functionPrototype.h"

ResultOfRegistryFunctions RegistryFunctions::createNewParameter(string fullPathToTheKey){

	string parameterNameString, setValue;
	DWORD parameterType;

	string pathToTheKey = "";

	if (fullPathToTheKey.find_first_of('\\') != -1)
		pathToTheKey = fullPathToTheKey.substr(fullPathToTheKey.find_first_of('\\') + 1, fullPathToTheKey.length() - fullPathToTheKey.find_first_of('\\'));

	HKEY key;
	if (RegOpenKeyEx(tranformStringToHKEY(fullPathToTheKey.substr(0, fullPathToTheKey.find_first_of('\\'))), pathToTheKey.c_str(), 0, KEY_WOW64_64KEY | KEY_SET_VALUE, (PHKEY)&key) != ERROR_SUCCESS)
		return ERROR_OPEN_KEY;

	parameterNameString = checkingForRegularExpression.inputAndCheckParameterName();

	parameterType = setParameterType();

	if (!inputParameterValue(parameterType, key, parameterNameString)){
		RegCloseKey(key);
		return ERROR_CREATE_PARAMETER;
	}

	RegCloseKey(key);

	return NO_ERRORS;
}

bool RegistryFunctions::inputParameterValue(DWORD type, HKEY key, string parameterName){
	DWORD dwordValue;
	DWORD64 qwordValue;
	BYTE settingValue[MAX_PATH];
	BYTE **settingMultiValue; int j = 0;
	string string;
	fflush(stdin);

	cout << endl<<endl << "Введите значение нового параметра:" << endl;
	switch (type)
	{
	case REG_QWORD:
		qwordValue = checkingForRegularExpression.inputAndCheckQWORDParameter();
		if (RegSetValueEx(key, parameterName.c_str(), 0, type, (BYTE*)&qwordValue, sizeof(qwordValue)) != ERROR_SUCCESS)
			return false;
		outputInformation.outputNewParameter(parameterName, "REG_QWORD", to_string(qwordValue));
		break;
	case REG_DWORD:
		dwordValue = checkingForRegularExpression.inputAndCheckDWORDParameter();
		
		if (RegSetValueEx(key, parameterName.c_str(), 0, type, (BYTE*)&dwordValue, sizeof(dwordValue)) != ERROR_SUCCESS)
			return false;
		outputInformation.outputNewParameter(parameterName, "REG_DWORD", to_string(dwordValue));
		break;
	case REG_SZ:
		getline(cin, string);
		if (RegSetValueEx(key, parameterName.c_str(), 0, type, (BYTE*)string.c_str(), string.length()) != ERROR_SUCCESS)
			return false;
		outputInformation.outputNewParameter(parameterName, "REG_SZ", string);
		break;
	case REG_EXPAND_SZ:
		getline(cin, string);
		if (RegSetValueEx(key, parameterName.c_str(), 0, type, (BYTE*)string.c_str(), string.length()) != ERROR_SUCCESS)
			return false;
		outputInformation.outputNewParameter(parameterName, "REG_EXPAND_SZ", string);
		break;
	case REG_BINARY:
		getline(cin, string);
		if (RegSetValueEx(key, parameterName.c_str(), 0, type, (BYTE*)string.c_str(), string.length()) != ERROR_SUCCESS)
			return false;
		outputInformation.outputNewParameter(parameterName, "REG_BINARY", string);
		break;
	default:
		return false;
	}
	return true;
}

DWORD RegistryFunctions::setParameterType(){

	cout << endl <<  "Поддерживаемые типы данных:" << endl;
	cout << endl << "1. REG_SZ";
	cout << endl << "2. REG_DWORD";
	cout << endl << "3. REG_BINARY";
	cout << endl << "4. REG_EXPAND_SZ";
	cout << endl << "5. REG_QWORD"<<endl;
	cout << endl << endl << "Выберите тип данных для нового параметра." << endl;

	int parameterType;

	parameterType = checkingForRegularExpression.inputAndCheckChoiseTypeOfParameter(1, 5);

	switch (parameterType)
	{
	case 1:
		return REG_SZ;
	case 2:
		return REG_DWORD;
	case 3:
		return REG_BINARY;
	case 4:
		return REG_EXPAND_SZ;
	case 5:
		return REG_QWORD;
		
	default:
		break;
	}
}
