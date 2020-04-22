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
	RegistryFunctions registryFinction /*= new RegistryFunction()*/;
	int choise;
	fflush(stdin);
	while (true){

		showMenu();
		fflush(stdin);
		cin >> choise;
		fflush(stdin);
		switch (choise)
		{
		case 1:

			if (!registryFinction.readRegistryValue(checkStringForRegExp()))
				cout << endl << "Ошибка чтения";
			break;
		case 2:

			if (!registryFinction.createKey(checkStringForRegExp()))
				cout << endl << "Ошибка создания нового ключа";
			break;
		case 3:

			if (!registryFinction.deleteKey(checkStringForRegExp()))
				cout << endl << "Ошибка удаления ключа";
			break;
		case 4:
			writeRegistry(checkStringForRegExp());
			break;
		case 5:
			if (!registryFinction.deleteValue(checkStringForRegExp()))
				cout << endl << "Ошибка удаления значения";
			break;
		case 6:
			if (!registryFinction.getInformationForRegistry())
				cout << endl << "Ошибка получения информации о реестре";
			break;
		case 7:
			if (!registryFinction.outputSubKeys(checkStringForRegExp()))
				cout << endl << "Ошибка вывода подразделов";
			break;
		case 8:
			//	fflush(stdin);
			//	showRazdel();
			regCopy(checkStringForRegExp(), checkStringForRegExp());
			break;
		case 9:

			if (!registryFinction.outputKeyValues(checkStringForRegExp()))
				cout << endl << "Ошибка вывода имён параметров";
			break;
			/*case 10:
			fflush(stdin);
			showRazdel();
			writeFile(checkStringForRegExp());
			break;*/
			//case 11:
			//	readFile(checkStringForRegExp());
			//	break;
		case 12:
			//	fflush(stdin);
			//	showRazdel();
			infoKey(checkStringForRegExp());
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