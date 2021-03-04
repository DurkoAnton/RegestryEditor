#include"functionPrototype.h"

string CheckingForRegularExpression::inputAndCheckPathToTheKeyForRegExp(){

	string pathToTheKey;
	regex firstRegExpForCheckSlash;
	regex secondRegExpForCheckSlash;
	firstRegExpForCheckSlash = "([^\\\\]+\\\\)+";
	secondRegExpForCheckSlash = "[^\\\\]+";
	cout << endl << "Путь к ключу имеет вид: BASE_KEY\\key_1\\key_2\\...key_n" << endl<<endl;

	do{

		fflush(stdin);
		getline(cin, pathToTheKey);

		if ((regex_match(pathToTheKey + "\\", firstRegExpForCheckSlash) && regex_match(pathToTheKey.substr(pathToTheKey.length() - 1, 1), secondRegExpForCheckSlash)) || regex_match(pathToTheKey, secondRegExpForCheckSlash)){
			return pathToTheKey;
			/*if (pathToTheKey.length() > MAX_PATH)
				cout << endl << endl << "Ошибка ввода!Повторите." << endl << endl;
			else
			return pathToTheKey;*/
		}
		else
			cout <<endl<<endl<< "Ошибка ввода!Повторите."<<endl<<endl;
	} while (1);

	system("pause");
	return 0;
}

int CheckingForRegularExpression::inputAndCheckChoiseActionOfMenu( int leftRange, int rightRange){
	regex r("[0-9]+");

	string chooseAction;
	do{
		fflush(stdin);
		getline(cin, chooseAction);
		if (!regex_match(chooseAction, r)){
			cout << endl << "Введены некоректные символы.Повторите ввод!" << endl << endl;
			continue;
		}
		if (atoi(chooseAction.c_str())<leftRange || atoi(chooseAction.c_str())>rightRange){
			cout << endl << "Неверный выбор.Повторите ввод!" << endl << endl;
			continue;
		}
		else
			break;
	} while (true);
	system("cls");
	return atoi(chooseAction.c_str());
}

int CheckingForRegularExpression::inputAndCheckChoiseTypeOfParameter(int leftRange, int rightRange){
	regex r("[0-9]+");
	string newParameterType;
	
	do{
		fflush(stdin);
		getline(cin, newParameterType);

		if (!regex_match(newParameterType, r)){
			cout << endl << "Введены некоректные символы.Повторите ввод!"<<endl<<endl;
			continue;
		}
		if (atoi(newParameterType.c_str())<leftRange || atoi(newParameterType.c_str())>rightRange){
			cout << endl << "Неверный выбор.Повторите ввод!"<<endl<<endl;
			continue;
		}
		else
			break;

	} while (true);
	return atoi(newParameterType.c_str());
}

string CheckingForRegularExpression::inputAndCheckParameterName(){

	string parameterName;
	regex regexKeyName(".+");
	do{

		cout << endl <<endl<< "Введите имя параметра:" << endl << endl;
		fflush(stdin);
		getline(cin, parameterName);
		if (!regex_match(parameterName, regexKeyName))
			cout << endl << "Имя параметра не может быть нулевой длины. Повторите ввод!";
		else{
			if (parameterName.length() > MAX_PATH)
				cout << endl << endl << "Ошибка ввода!Повторите." << endl << endl;
			else
			break;
		}

	} while (true);

	return parameterName;
}

string CheckingForRegularExpression::inputAndCheckKeyName(){

	string keyName;
	regex regexKeyName("[^\\\\]+");
	do{

		cout << endl << endl << "Введите название нового ключа:" << endl;
		fflush(stdin);
		getline(cin, keyName);
		if (!regex_match(keyName, regexKeyName))
			cout << endl << "Имя параметра не может быть нулевой длины и не может содержать символа '\\'. Повторите ввод!";
		else{
		if (keyName.length() > MAX_PATH)
			cout << endl << endl << "Ошибка ввода!Повторите." << endl << endl;
		else
			break;
	}

	} while (true);
	return keyName;
}

DWORD CheckingForRegularExpression::inputAndCheckDWORDParameter(){

	string DWORDParameter;

	regex regexDWORDParameter("[0-9]+");
	do{

		fflush(stdin);
		getline(cin, DWORDParameter);
		if (!regex_match(DWORDParameter, regexDWORDParameter))
			cout << endl << "Параметр типа DWORD может состоять только из цифр. Повторите ввод!";
		else
			break;

	} while (true);
	return (DWORD)atoi(DWORDParameter.c_str());
}

DWORD64 CheckingForRegularExpression::inputAndCheckQWORDParameter(){

	string DWORDParameter;

	regex regexQWORDParameter("[0-9]+");
	do{

		fflush(stdin);
		getline(cin, DWORDParameter);
		if (!regex_match(DWORDParameter, regexQWORDParameter))
			cout << endl << "Параметр типа QWORD может состоять только из цифр. Повторите ввод!";
		else
			break;

	} while (true);
	return (DWORD64)atoi(DWORDParameter.c_str());
}