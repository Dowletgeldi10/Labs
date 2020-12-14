#include "Input.h"

char* InputCharNames() {
	char* tmp;
	bool flag = true;
	int length;
	do {
		tmp = new char[80];
		try {
			flag = false;
			rewind(stdin);
			cin.clear();
			cin.getline(tmp, 80);
			if (strnlen_s(tmp, 80) == 0) throw 1;
			length = strlen(tmp);
			for (int i = 0; tmp[i]; i++) {
				if ((tmp[i] < 'A' || tmp[i] > 'Z') && (tmp[i] < 'a' || tmp[i] > 'z')
					&& tmp[i] != ' ')
				{
					cout << "Введено неправильные данные" << endl;
					cout << "  Поле должно содержжать только латинские или английские буквы" << endl;
					throw 1;
				}
			}
		}
		catch (...) {
			_flushall();
			flag = true;
			delete[] tmp;
		}
	} while (flag);
	return tmp;
}

char* InputCharAll_25()
{
	char* tmp;
	bool flag = true;
	int length;
	do {
		tmp = new char[80];
		try {
			flag = false;
			rewind(stdin);
			cin.clear();
			cin.getline(tmp, 80);
			if (strnlen_s(tmp, 80) == 0) throw 1;
			length = strlen(tmp);
			if (length > 25) {
				cout << "Слишком болшое слово" << endl;
				throw 1;
			}
		}
		catch (...) {
			_flushall();
			flag = true;
			delete[] tmp;
		}
	} while (flag);
	return tmp;
}

char* InputNumbersChar()
{
	char* tmp;
	bool flag = true;
	int length;
	do {
		tmp = new char[80];
		try {
			flag = false;
			rewind(stdin);
			cin.clear();
			cin.getline(tmp, 80);
			length = strlen(tmp);
			for (int i = 0; i < length; i++) {
				if ((tmp[i] == ' ') || (tmp[i] < '0' && tmp[i] > '9'))
				{
					cout << "Поле должен содержать только цифпы" << endl;
					throw 1;
				}
			}
		}
		catch (...) {
			_flushall();
			flag = true;
			delete[] tmp;
		}
	} while (flag);
	return tmp;
}

Date getLocalDate() {
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);
	Date currentdate;
	currentdate.day = localtime.tm_mday;
	currentdate.month = 1 + localtime.tm_mon;
	currentdate.year = 1900 + localtime.tm_year;
	return currentdate;
}
