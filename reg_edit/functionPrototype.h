#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include<Windows.h>
#include<string>
#include<locale.h>
#include<regex>
#include<tchar.h>
#include<conio.h>
using namespace std;

enum ResultOfRegistryFunctions{
	NO_ERRORS,
	ERROR_OPEN_KEY,
	ERROR_GET_VALUE,
	ERROR_CREATE_KEY,
	ERROR_DELETE_KEY,
	ERROR_DELETE_PARAMETER,
	ERROR_GET_INFORMATION_ABOUT_REGISTRY,
	ERROR_COPY_KEYS,
	ERROR_CREATE_PARAMETER,
	ERROR_UNSUPPORTED_REG_TYPE,
	ERROR_WRITE_KEY_IN_FILE,
	ERROR_READ_KEY_FROM_FILE,
	ERROR_ENUM_SUB_KEYS,
	ERROR_ENUM_PARAMETERS,
	ERROR_NOT_ARE_SUB_KEYS,
	ERROR_NOT_ARE_VALUES_IN_KEY
};

class CheckingForRegularExpression{

public:

	CheckingForRegularExpression(){}
	~CheckingForRegularExpression(){}

	string inputAndCheckPathToTheKeyForRegExp();
	int inputAndCheckChoiseActionOfMenu(int, int);
	int inputAndCheckChoiseTypeOfParameter(int, int);
	string inputAndCheckParameterName();
	string inputAndCheckKeyName();
	DWORD inputAndCheckDWORDParameter();
	DWORD64 inputAndCheckQWORDParameter();
};

class OutputResultFunction{

public:
	OutputResultFunction(){}
	~OutputResultFunction(){}
	void showMenu();
	void processResultOfFunction(ResultOfRegistryFunctions);
	bool checkParameterTypeForOutput(DWORD, char *, DWORD,string);

	void outputStringValue(char *, DWORD);
	void outputParameterType(DWORD);
	void outputNumericValue(char *, DWORD);
	void outputRegBinaryValue(char *, DWORD);

	void outputParameterNameAndType(string,string);
	void outputParameterName(char*, int,string);
	void outputNewParameter(string, string, string);
	void outputKeyName(char*,int);
	void outputWaitingKeyCode();
	void outputSuccessCreatingKey(string);
	void outputSuccessDeletingKey(string);
	void outputSuccessDeletingParameter(string,string);
	void outputSuccessSavingKey(string,string);
	void outputSuccessRestoringKey(string, string);
	void outputSuccessCopyingKeys(string, string);
};

class RegistryFunctions{

private:
	OutputResultFunction outputInformation;
	CheckingForRegularExpression checkingForRegularExpression;
public:
	RegistryFunctions(){}
	~RegistryFunctions(){}

	ResultOfRegistryFunctions readParameterValue(string);
	ResultOfRegistryFunctions createNewParameter(string);

	ResultOfRegistryFunctions createNewKey(string);
	ResultOfRegistryFunctions deleteKey(string);

	ResultOfRegistryFunctions deleteParameter(string);

	ResultOfRegistryFunctions getInformationAboutRegistry();

	ResultOfRegistryFunctions outputSubKeysNames(string);
	ResultOfRegistryFunctions outputParameterNamesInKey(string);

	DWORD getCountParametersInKey(HKEY);
	DWORD getCountSubKeysInKey(HKEY);

	ResultOfRegistryFunctions copyKeys(string, string);
	
	bool inputParameterValue(DWORD, HKEY, string);
	DWORD setParameterType();
	ResultOfRegistryFunctions writeKeyInFile(string);
	ResultOfRegistryFunctions readKeyFromFile(string);

	BOOL SetPrivilege(HANDLE, LPCTSTR, BOOL);

	HKEY tranformStringToHKEY(string);
};








