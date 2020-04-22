#include"functionPrototype.h"

string checkStringForRegExp(){

	string s /*= "fqr\\\\dfgh\\\\a"*/;
	regex r("([^\\\\]+\\\\)+");
	regex r1("[^\\\\]+");
	//TCHAR t[20];
	//char tt[20];
	////t = tt;
	//cin >> t[1];
	//getline(cin,t)
	do{
		cout << endl << "¬ведите регул€рное выражение" << endl;
		fflush(stdin);
		getline(cin, s);

		if ((regex_match(s + "\\", r) && regex_match(s.substr(s.length() - 1, 1), r1)) || regex_match(s, r1))
			//cout << endl << "da";
			return s;
		else
			cout << "error134534";
	} while (1);
	system("pause");
	return 0;
}