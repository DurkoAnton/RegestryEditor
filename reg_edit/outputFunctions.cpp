#include"functionPrototype.h"
#include<conio.h>
void OutputResultFunction::outputStringValue(char *data, DWORD size){
	int i = 0;
	while (i < size)
		cout << data[i++];
	cout << endl << endl;
}
void OutputResultFunction::outputRegBinaryValue(char *r, DWORD size){
	int i = 0;
	while (i < size-1){
		cout <<hex<<(int)r[i] << " ";
		i++;
	}
	cout << endl << endl;
}
void OutputResultFunction::outputNumericValue(char *r, DWORD size){
	int i = 0;
	wchar_t wr[MAX_PATH];
	swprintf(wr, L"%s", r);
	wcout << (int)wr[i++];

	cout << endl << endl;
}
bool OutputResultFunction::checkParameterTypeForOutput(DWORD parameterType, char *parameterValue, DWORD parameterSize,string parameterName){

	switch (parameterType){
	case REG_SZ:

		outputParameterNameAndType(parameterName, "REG_SZ");
		cout << "Значение: ";
		outputStringValue(parameterValue, parameterSize);
		outputWaitingKeyCode();
		return true;
	case REG_DWORD:

		outputParameterNameAndType(parameterName, "REG_DWORD");
		cout << "Значение: ";
		outputNumericValue(parameterValue, parameterSize);
		outputWaitingKeyCode();
		return true;
	case REG_BINARY:

		outputParameterNameAndType(parameterName, "REG_BINARY");
		cout << "Значение: ";
		outputRegBinaryValue(parameterValue, parameterSize);
		outputWaitingKeyCode();
		return true;
	case REG_EXPAND_SZ:

		outputParameterNameAndType(parameterName, "REG_EXPAND_SZ");
		cout << "Значение: ";
		outputStringValue(parameterValue, parameterSize);
		outputWaitingKeyCode();
		return true;
	case REG_MULTI_SZ:

		outputParameterNameAndType(parameterName, "REG_MULTI_SZ");
		cout << "Значение: ";
		outputStringValue(parameterValue, parameterSize);
		outputWaitingKeyCode();
		return true;
	case REG_QWORD:

		outputParameterNameAndType(parameterName, "REG_DWORD");
		cout << "Значение: ";
		outputNumericValue(parameterValue, parameterSize);
		outputWaitingKeyCode();
		return true;
	}
	return false;
}

void OutputResultFunction::showMenu(){
	system("cls");
	cout << endl << "Выберите функцию для работы с реестром:" << endl;
	cout << endl << "1. Чтение из реестра" << endl;
	cout << endl << "2. Запись параметра в реестр" << endl;
	cout << endl << "3. Создание ключа" << endl;
	cout << endl << "4. Удаление ключа " << endl;
	cout << endl << "5. Удаление параметра" << endl;
	cout << endl << "6. Информация о реестре" << endl;
	cout << endl << "7. Вывод подразделов" << endl;
	cout << endl << "8. Вывод параметров" << endl;
	cout << endl << "9. Копирование подразделов" << endl;
	cout << endl << "10. Резервная запись в файл" << endl;
	cout << endl << "11. Резервное чтение из файла" << endl;
	cout << endl << "0. Выход из программы" << endl;
}

void OutputResultFunction::processResultOfFunction(ResultOfRegistryFunctions typevalue){

	if (typevalue == NO_ERRORS)
		return;

	system("cls");
	cout << "Вывод:" << endl << endl;

	switch (typevalue){
	case ERROR_OPEN_KEY:
		cout << endl << "Ошибка открытия ключа!Проверьте введённый путь." << endl;
		break;
	case ERROR_GET_VALUE:
		cout << endl << "Ошибка получения значения параметра!Проверьте введённый путь и имя параметра." << endl;
		break;
	case ERROR_CREATE_KEY:
		cout << endl << "Ошибка создания ключа!Проверьте введённый путь и имя параметра." << endl;
		break;
	case ERROR_DELETE_KEY:
		cout << endl << "Ошибка удаления ключа!Проверьте отсутствие подключей удаляемого ключа." << endl;
		break;
	case ERROR_DELETE_PARAMETER:
		cout << endl << "Ошибка удаления параметра!Проверьте путь к ключу и имя параметра." << endl;
		break;
	case ERROR_COPY_KEYS:
		cout << endl << "Ошибка копирования ключа!Проверьте путь к ключу и имя параметра." << endl;
		break;
	case ERROR_NOT_ARE_SUB_KEYS:
		cout << endl << "Данный раздел не содержит подразделов." << endl;
		break;
	case ERROR_NOT_ARE_VALUES_IN_KEY:
		cout << endl << "Данный ключ не содержит параметров." << endl;
		break;
	case ERROR_UNSUPPORTED_REG_TYPE:
		cout << endl << "Неподдерживаемый тип данных!" << endl;
		break;
	case ERROR_WRITE_KEY_IN_FILE:
		cout << endl << "Ошибка записи ключа в файл!Проверьте привелегии резервного копирования." << endl;
		break;
	case ERROR_READ_KEY_FROM_FILE:
		cout << endl << "Ошибка чтения ключа из файла!Проверьте имя файла и привелегии резервного копирования." << endl;
		break;
	case ERROR_CREATE_PARAMETER:
		cout << endl << "Ошибка создания нового параметра!Проверьте введённые характиристики." << endl;
		break;
	case ERROR_ENUM_PARAMETERS:
		cout << endl << "Ошибка перечисления параметров!Проверьте введённые характиристики." << endl;
		break;
	case ERROR_ENUM_SUB_KEYS:
		cout << endl << "Ошибка перечисления подразделов!Проверьте введённые характиристики." << endl;
		break;
	case ERROR_GET_INFORMATION_ABOUT_REGISTRY:
		cout << endl << "Ошибка получения информации о памяти реестра." << endl;
		break;
	}
	outputWaitingKeyCode();
}

void  OutputResultFunction::outputParameterNameAndType(string parameterName,string parameterType){
	system("cls");
	cout << endl << "Вывод:" << endl << endl;
	cout << endl << "Имя параметра: " << parameterName << endl << endl;
	cout << "Тип: "<<parameterType << endl << endl;
}


void  OutputResultFunction::outputNewParameter(string parameterName, string parameterType, string parameterValue ){

	system("cls");
	cout << endl << "Вывод:" << endl << endl;
	cout << endl << "Имя параметра: " << parameterName << endl << endl;
	cout << "Тип: " << parameterType << endl << endl;
	cout << "Значение: " << parameterValue << endl << endl;

	outputWaitingKeyCode();
}

void OutputResultFunction::outputKeyName(char *keyName,int index){
	int i = 0;
	if (index == 1){
		system("cls");
		cout << endl << "Вывод:" << endl << endl << endl;
	}
	cout << index << ". ";
	while (keyName[i])
		cout << keyName[i++];

	cout << endl << endl; 
}

void OutputResultFunction::outputWaitingKeyCode(){
	cout << endl << "Нажмите любую клавишу для перехода в меню..." << endl;
	_getche();
}

void OutputResultFunction::outputSuccessCreatingKey(string newKeyNameString){
	system("cls");
	cout << "Вывод:" << endl << endl;
	cout << endl << "Cоздан ключ с именем " << "''" << newKeyNameString << "''" << endl;

	outputWaitingKeyCode();
}

void OutputResultFunction::outputSuccessDeletingKey(string  fullPathToTheKey){
	system("cls");
	cout << "Вывод: " << endl << endl;
	cout << endl << "Ключ " << fullPathToTheKey << " удалён." << endl;

	outputWaitingKeyCode();

}

void OutputResultFunction::outputSuccessSavingKey(string  fullPathToTheKey,string fileName){
	system("cls");
	cout << endl << "Вывод:" << endl << endl;
	cout << endl << "Ключ " << fullPathToTheKey<<" сохранён в файл " << fileName << "." << endl << endl;

	outputWaitingKeyCode();
}

void OutputResultFunction::outputSuccessRestoringKey(string  fullPathToTheKey, string fileName){
	system("cls");
	cout << endl << "Вывод:" << endl << endl;
	cout << endl << "Файл " << fileName << " считан в ключ " << fullPathToTheKey << "." << endl << endl;

	outputWaitingKeyCode();
}

void OutputResultFunction::outputParameterName(char *keyName, int index,string fullPathToTheKey){
	int i = 0;
	if (index == 1){
		system("cls");
		cout << endl << "Вывод:" << endl << endl << endl;
		cout << "Параметры ключа " << fullPathToTheKey << ":" << endl << endl << endl;
	}
	cout << index << ". ";
	while (keyName[i])
		cout << keyName[i++];

	cout << endl << endl;
}

void OutputResultFunction::outputSuccessDeletingParameter(string parameterNameString,string pathToTheKey){
	system("cls");
	cout << endl << "Вывод: " << endl << endl;
	cout << endl << "Параметр " << parameterNameString << " удалён из ключа "<<pathToTheKey <<"."<< endl;

	outputWaitingKeyCode();
}

void OutputResultFunction::outputSuccessCopyingKeys(string pathToTheKeySource, string pathToTheKeyDestination){
	system("cls");
	cout << endl << "Вывод: " << endl << endl;
	cout << endl << "Ключ " << pathToTheKeySource << " скопирован в ключ " << pathToTheKeyDestination << "." << endl;

	outputWaitingKeyCode();
}
