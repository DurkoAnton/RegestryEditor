#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include<iostream>
#include<Windows.h>
#include<string>
#include<locale.h>
#include<regex>
#include<tchar.h>
#include"functionPrototype.h"

int main(){

	setlocale(LC_ALL, "russian");
	
	RegistryFunctions registryFinction;
	CheckingForRegularExpression regularExpression;
	OutputResultFunction outputInformation;

	string pathToTheKey, pathToTheKey_;

	fflush(stdin);

	while (true){

		outputInformation.showMenu();
		fflush(stdin);
		
		switch (regularExpression.inputAndCheckChoiseActionOfMenu(0,12))
		{
		case 1:

			cout << endl << "¬ведите путь к ключу, где расположен считываемый параметр." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.readParameterValue(pathToTheKey));
			break;
		case 3:

			cout << endl << "¬ведите путь к ключу, где расположен новый ключ параметр.\nЌовый ключ не может быть подразделом HKLM или HKU." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.createNewKey(pathToTheKey));
			break;
		case 4:
			
			cout << endl << "¬ведите путь к ключу, который будет удалЄн." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.deleteKey(pathToTheKey));
			break;
		case 2:

			cout << endl << "¬ведите путь к ключу, где будет расположен новый параметр." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.createNewParameter(pathToTheKey));
			break;
		case 5:

			cout << endl << "¬ведите путь к ключу, где расположен удал€емый параметр." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.deleteParameter(pathToTheKey));
			break;
		case 6:

			outputInformation.processResultOfFunction(registryFinction.getInformationAboutRegistry());
			break;
		case 7:
			
			cout << endl << "¬ведите путь к ключу, имена подразделов которого будут выведены на экран." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.outputSubKeysNames(pathToTheKey));
			break;
		case 9:
			
			cout << endl << "¬ведите путь к ключу-источнику." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();

			cout << endl<<endl << "¬ведите путь к ключу-приЄмнику." << endl;
			pathToTheKey_ = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.copyKeys(pathToTheKey,pathToTheKey_));
			break;
		case 8:

			cout << endl << "¬ведите путь к ключу, имена параметров которого будут выведены на экран." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.outputParameterNamesInKey(pathToTheKey));
			break;
		case 10:

			cout << endl << "¬ведите путь к ключу, который будет сохранен в файл." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.writeKeyInFile(pathToTheKey));
			break;
		case 11:

			cout << endl << "¬ведите путь к ключу, в который будет считан файл." << endl;
			pathToTheKey = regularExpression.inputAndCheckPathToTheKeyForRegExp();
			outputInformation.processResultOfFunction(registryFinction.readKeyFromFile(pathToTheKey));
			break;
		case 0:
			return 0;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}