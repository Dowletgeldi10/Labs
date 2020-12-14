#pragma once
#include "Header.h"

template<typename T>
T InputInt(T interval, T interval2) {
	T number;
	bool flag = true;
	do {
		try {
			flag = false;
			cin >> number;
			if (!cin.good() || cin.peek() != '\n') {
				cout << "������� �� �����" << endl << "   �������� ������ ���� ����" << endl;
				throw 1;
			}
			else if (number < interval || number > interval2) {
				cout << "������� ����� � ��������� �� " << interval << " �� " << interval2 << endl;
				throw 1;
			}
		}
		catch (...) {
			cin.clear();
			rewind(stdin);
			flag = true;
		}
	} while (flag);
	return number;
}

char* InputCharNames();

char* InputCharAll_25();


char* InputNumbersChar();

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};

Date getLocalDate();