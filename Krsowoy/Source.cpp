#include "Input.h"
#include "List.h"
#include "Source.h"
#include "locale.h"


list<Agency>agency;
list<User>user;
char curr[20];

int main() {
	setlocale(LC_ALL, "rus");
	char ch;

	// ��������� ��� ������ �� �����
	LoadUsers();
	LoadAgency();
	do {
		system("cls");
		cout << "#############################################" << endl;
		cout << "#                 ���� �����                #" << endl;
		cout << "#############################################" << endl;
		cout << "# 1 #  ������������                         #" << endl;
		cout << "# 2 #  �����������                          #" << endl;
		cout << "# 0 #  �����                                #" << endl;
		cout << "#############################################" << endl;
		ch = _getch();
		switch (ch) {
		case '1': {
			if (LogAdmin() == 0)
				MenuAdmin();
		}break;
		case '2': {
			if (LogUser() == 0)
				menuuser();
		}break;
		case '0': {
			break;
		}
		}
	} while (ch != '0');
	//��������� ��� ������ � ����
	SaveUsers();
	SaveAgency();
	return 0;
}

void LoadUsers()
{
	//��������� ���� ��� ������:
	fstream file("users.txt", ios::in | ios::out);
	//��������� ������� �� ����
	if (!file.is_open()) {
		cout << "������ ����� users.txt" << endl;
		system("pause");
		return;
	}
	while (1) {
		User obj;
		file.read((char*)&obj, sizeof(User)); // ������ ������
		if (file.eof()) break; //���� ������ ����� �� ������� �� �����
		user.Push_Front(obj); //���������� ��������� ������ � ������
	}
	file.close(); //��������� ����
}

void SaveUsers()
{
	fstream out;
	//��������� ���� ��� ������:
	out.open("users.txt", ios::out | ios::trunc);
	//��������� ������� �� ����
	if (!out.is_open()) {
		cout << "������ ����� users.txt" << endl;
		system("pause");
		return;
	}
	while (user.getSize() != 0) { //���� ������ ������ �� ����� �����
		User obj = user.Pop_head(); //����������� ������� ������� ������ � ��������� ���������� obj � ������� ��� �� ������
		out.write((char*)&obj, sizeof(User));
		/*
		���������� ��������� obj � �������� ���� ����; ��� ����� ������ ����� ��������� obj
		� �������� ��������� �� obj � ������������� ����; ���������, ��� �
		��������� obj ��������� sizeof(User) ����
		*/
	}
	out.close(); //��������� ����
}

void LoadAgency()
{
	fstream file;
	file.open("center.txt", ios::in | ios::out);
	if (!file.is_open()) {
		system("cls");
		cout << "������ �������� ����� center.txt" << endl;
		system("pause");
		return;
	}
	while (1) {
		Agency obj;
		file.read((char*)&obj, sizeof(Agency));
		if (file.eof()) break;
		agency.Push_Front(obj);
	}
	file.close();
}

void SaveAgency()
{
	fstream file;
	file.open("center.txt", ios::out | ios::trunc);
	if (!file.is_open()) {
		system("cls");
		cout << "������ �������� ����� center.txt" << endl;
		system("pause");
		return;
	}
	while (agency.getSize() != 0) {
		Agency obj = agency.Pop_head();
		file.write((char*)&obj, sizeof(Agency));
	}
	file.close();
}

int LogAdmin()
{
	bool isUser = false;
	char pass[20], logi[20];
	cout << "#  �����  #" << endl;
	cin >> logi;
	cout << "#  ������  #" << endl;
	cin >> pass;
	for (int i = 0; i < user.getSize(); i++) {
		if (strcmp(user[i].login, logi) == 0 && strcmp(user[i].password, pass) == 0 && user[i].role == true)
		{
			isUser = true;
			strcpy_s(curr, user[i].login);
			break;
		}
	}
	if ((strcmp(pass, "admin") == 0 && strcmp(logi, "admin") == 0) || isUser == true)
	{
		return 0;
	}
	else {
		cout << "�������� ������" << endl;
		system("pause");
		return 1;
	}
}

int LogUser()
{
	int flag = 0;
	bool isUser = false;
	char pass[20], logi[20];
	char ch;
	do {
		system("cls");
		cout << "# 1 #  ����" << endl;
		cout << "# 2 #  �����������" << endl << endl;
		cout << "# 0 #  �����" << endl;
		cout << "#  ��� �����  #" << endl;

		ch = _getch();
		switch (ch) {
		case '1': {
			cout << "#  �����  #" << endl;
			cin >> logi;
			cout << "#  �����  #" << endl;
			cin >> pass;
			for (int i = 0; i < user.getSize(); i++) {
				if (strcmp(user[i].login, logi) == 0
					&& strcmp(user[i].password, pass) == 0
					&& user[i].role == false)
				{
					isUser = true;
					strcpy_s(curr, user[i].login);
				}
			}
			if (isUser == false) {
				cout << "$$$$$    �������� ������  $$$$$" << endl;
				system("pause");
			}
			else
				return 0;
		}break;
		case '2': {
			User newUser;
			cout << "$$$$$ ������� ������ ��� ����������� $$$$$" << endl;
			bool isUser2;
			do {
				isUser2 = true;
				cout << "[  �����  ]" << endl;
				cin >> newUser.login;
				for (int i = 0; i < user.getSize(); i++) {
					if (strcmp(user[i].login, newUser.login) == 0) {
						cout << "#  ����� ����� ��� �����������. ������� ������ �����  #" << endl;
						isUser2 = false;
						break;
					}
				}
			} while (!isUser2);
			cout << "#  �����  #" << endl;
			cin >> newUser.password;
			newUser.role = false;
			user.Push_Front(newUser);
			return 0;
		}break;
		case '0': {
			break;
		}
		}
	} while (ch != '0');
	return 1;
}

void MenuAdmin()
{
	char ch;
	do {
		system("cls");
		cout << "###############################################" << endl;
		cout << "                  �������������                " << endl;
		cout << "###############################################" << endl << endl;
		cout << "# 1 # ������ � �������" << endl;
		cout << "# 2 # ������ � ��������������" << endl;
		cout << endl << endl;
		cout << "# 0 # �����" << endl << endl;
		ch = _getch();
		switch (ch) {
		case '0': {
			break;
		}
		case '1': {
			Menu1();
			break;
		}
		case '2': {
			Menu2();
			break;
		}
		};
	} while (ch != '0');
	cout << endl;
}

void menuuser()
{
	char ch;
	do {
		system("cls");
		cout << "###############################################" << endl;
		cout << "                   �����������                 " << endl;
		cout << "###############################################" << endl << endl;
		cout << "# 1 #  ��������" << endl;
		cout << "# 2 #  ����������" << endl;
		cout << "# 3 #  ������������� �������" << endl;
		cout << "# 4 #  �����" << endl;
		cout << "\n# 0 #  �����" << endl;
		ch = _getch();
		switch (ch) {
		case '1': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				return;
			}
			ShowAgency();
			system("pause");
			break;
		}
		case '2': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			cout << "# 1 #  ����������� �� ��������� ������" << endl;
			cout << "# 2 # ����������� �� ����" << endl;
			cout << "# 3 # ����������� �� ���� ����������" << endl;
			int ch2 = InputInt(1, 4);
			if (ch2 == 1) SortByCountry();
			if (ch2 == 2) SortByPrice();
			if (ch2 == 3) SortByTransport();
			ShowAgency();
			system("pause");
			break;
		}
		case '3': {
			IndidvidualTask();
			break;
		}
		case '4': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			cout << "������� �������� ������" << endl;
			char country[40];
			strcpy_s(country, InputCharNames());
			SearchByName(country);
			system("pause");
			break;
		};
		case '0': {
			break;
		}
		};
	} while (ch != '0');
	cout << endl;
}

void Menu1() {
	char ch;
	do {
		system("cls");
		cout << "###############################################" << endl;
		cout << "                 ������ � �������              " << endl;
		cout << "###############################################" << endl << endl;
		cout << "# 1 #  ����������" << endl;
		cout << "# 2 #  ��������" << endl;
		cout << "# 3 #  ��������������" << endl;
		cout << "# 4 #  �����" << endl;
		cout << "# 5 #  ����������" << endl;
		cout << "# Z #  �������������� �������" << endl;
		cout << "# 6 #  �����" << endl << endl;
		cout << "# 0 #  �����" << endl;
		ch = _getch();
		switch (ch) {
		case '0': {
			break;
		}
		case '1': {
			AddAgency();
			break;
		}
		case '2': {
			system("cls");
			if (agency.getSize() == 0) { // ���������.. ���� ������ ������ ����� 0
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			ShowAgency();
			cout << "������� ����� ���������� ��������" << endl;
			int index = InputInt(1, agency.getSize());
			agency.Delete(index);
			cout << "������� �������" << endl;
			break;
		}
		case '3': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			ShowAgency();
			cout << "������� ����� �������������� ��������" << endl;
			int index = InputInt(1, agency.getSize());
			EditCenter(index);
			break;
		}
		case '4': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			cout << "������� �������� ������ ����������" << endl;
			char country[40];
			strcpy_s(country, InputCharNames());
			SearchByName(country);
			system("pause");
			break;
		}
		case '5': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			cout << "# 1 # ����������� �� ��������� ������" << endl;
			cout << "# 2 # ����������� �� ����" << endl;
			cout << "# 3 # ����������� �� ���� ����������" << endl;

			int ch2 = InputInt(1, 4);
			if (ch2 == 1) SortByCountry();
			if (ch2 == 2) SortByPrice();
			if (ch2 == 3) SortByTransport();
			ShowAgency();
			system("pause");
			break;
		}
		case 'z': {
			IndidvidualTask();
			break;
		}
		case '6': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			ShowAgency();
			system("pause");
			break;
		}
		}
	} while (ch != '0');
}

void Menu2() {
	char ch;
	do {
		system("cls");
		cout << "###############################################" << endl;
		cout << "            ������ � ��������������       " << endl;
		cout << "###############################################" << endl << endl;

		cout << "# 1 #  ����������" << endl;
		cout << "# 2 #  ��������" << endl;
		cout << "# 3 #  ��������������" << endl;
		cout << "# 4 #  �����" << endl << endl;
		cout << "\n# 0 #  �����" << endl;
		ch = _getch();
		switch (ch) {
		case '0': {
			break;
		}
		case '1': {
			AddUser();
			break;
		}
		case '2': {
			system("cls");
			int length = user.getSize();
			if (length == 0) {
				cout << "������ �����" << endl;
				system("pause");
				break;
			}
			ShowUser();
			int pos;
			cout << "������� ����� ���������� ��������" << endl;
			pos = InputInt(1, length);
			user.Delete(pos);
			cout << "������� �������" << endl;
			system("pause");
			break;
		}
		case '3': {
			EditUser();
			break;
		}
		case '4': {
			ShowUser();
			system("pause");
			break;
		}
		}
	} while (ch != '0');
}

void AddUser()
{
	system("cls");
	User newUser;
	cout << "������� �����" << endl;
	cin >> newUser.login;
	cout << "������� �����" << endl;
	cin >> newUser.password;
	cout << "����� ?" << endl;
	cout << "   0 - ���" << endl;
	cout << "   1 - ��" << endl;
	int h = InputInt(0, 1);
	if (h == 0)
		newUser.role = false;
	else
		newUser.role = true;
	for (int i = 0; i < user.getSize(); i++) {
		if (strcmp(user[i].login, newUser.login) == 0) {
			cout << "����� ����������� ��� �����������" << endl;
			system("pause");
			return;
		}
	}
	if (strcmp(newUser.login, "admin") == 0)
	{
		cout << "����� ����������� ��� �����������" << endl;
		system("pause");
		return;
	}
	user.Push_Front(newUser);
	cout << "������� ��������" << endl;
	system("pause");
}

void ShowUser()
{
	system("cls");
	for (int i = 0; i < user.getSize(); i++) {
		if (i == 0) cout << setw(2) << "#" << setw(15) << "�����" << setw(15) << "������" << setw(15) << "���" << endl;
		cout << setw(2) << i + 1 << setw(15) << user[i].login << setw(15) << user[i].password;
		if (user[i].role == false) cout << setw(15) << "0" << endl;
		else cout << setw(15) << "1" << endl;
	}
}

void EditUser()
{
	int length = user.getSize();
	if (length == 0) {
		cout << "������ �����" << endl;
		system("pause");
		return;
	}
	ShowUser();
	int pos;
	User editUser;
	cout << "������� ����� ��������" << endl;
	pos = InputInt(1, length);
	cout << "����� �����" << endl;
	cin >> editUser.login;
	for (int i = 0; i < length; i++) {
		if (strcmp(editUser.login, user[i].login) == 0) {
			cout << "����� ����������� ��� �����������" << endl;
			system("pause");
			return;
		}
	}
	cout << "������� ����� �����" << endl;
	cin >> editUser.password;
	cout << "����� ?" << endl;
	cout << "   0 - ���" << endl;
	cout << "   1 - ��" << endl;
	int h = InputInt(0, 1);
	if (h == 0)
		editUser.role = false;
	else
		editUser.role = true;
	user[pos - 1] = editUser;
	cout << "����������� ������� ������������" << endl;
	system("pause");
}

void AddAgency() {
	system("cls");
	Agency newAgency;
	cout << "�������� ��� �������" << endl;
	cout << "1 - �����" << endl;
	cout << "2 - ������������� ���" << endl;
	cout << "3 - �������" << endl;
	cout << "4 - ������" << endl;
	cout << "5 - �����" << endl;
	int type = InputInt(1, 6);
	newAgency.type = type;
	cout << "������� ������ ����������" << endl;
	strcpy_s(newAgency.country, InputCharNames());
	cout << "������� ��� ����������" << endl;
	strcpy_s(newAgency.transport, InputCharAll_25());
	cout << "������� ���������� ����" << endl;
	newAgency.dats = InputInt(1, 31);
	cout << "  �������" << endl;
	cout << "    1 - �������" << endl;
	cout << "    2 - ��� ��������" << endl;
	newAgency.meat = InputInt(1, 2);
	cout << "������� ��������" << endl;
	newAgency.price = InputInt(1, 99999);
	agency.Push_Front(newAgency);
	cout << endl << "������ ������� ���������" << endl;
	system("pause");
}

void EditCenter(int index) {
	cout << "1 - ��� �������" << endl;
	cout << "2 - ������ ����������" << endl;
	cout << "3 - ��� ����������" << endl;
	cout << "4 - ���������� ����" << endl;
	cout << "5 - �������" << endl;
	cout << "6 - ���������" << endl;
	int ch;
	ch = InputInt(1, 6);
	switch (ch) {
	case 1: {
		cout << "�������� ��� �������" << endl;
		cout << "1 - �����" << endl;
		cout << "2 - ������������� ���" << endl;
		cout << "3 - �������" << endl;
		cout << "4 - ������" << endl;
		cout << "5 - �����" << endl;
		int type = InputInt(1, 6);
		agency[index - 1].type = type;
	}break;
	case 2: {
		cout << "������� ������ ����������" << endl;
		strcpy_s(agency[index - 1].country, InputCharNames());
	}break;
	case 3: {
		cout << "������� ��� ����������" << endl;
		strcpy_s(agency[index - 1].transport, InputCharAll_25());
	}break;
	case 4: {
		cout << "������� ���������� ����" << endl;
		agency[index - 1].dats = InputInt(1, 31);

	}break;
	case 5: {
		cout << "  �������" << endl;
		cout << "    1 - �������" << endl;
		cout << "    2 - ��� ��������" << endl;
		agency[index - 1].meat = InputInt(1, 2);
	}break;
	case 6: {
		cout << "������� ��������" << endl;
		agency[index - 1].price = InputInt(1, 99999);
	}break;
	}
	cout << "������ ������� ��������" << endl;
	system("pause");
}

void ShowAgency() {
	system("cls");
	ShowTitle();
	for (int i = 0; i < agency.getSize(); i++) {
		cout << setw(2) << i + 1;
		switch (agency[i].type) {
		case 1:
			cout << setw(20) << "�����";
			break;
		case 2:
			cout << setw(20) << "�������������";
			break;
		case 3:
			cout << setw(20) << "�������";
			break;
		case 4:
			cout << setw(20) << "������";
			break;
		case 5:
			cout << setw(20) << "�����";
			break;
		}
		cout << setw(25) << agency[i].country;
		cout << setw(25) << agency[i].transport;
		cout << setw(15) << agency[i].dats;
		if (agency[i].meat == 1) cout << setw(20) << "�������";
		else cout << setw(20) << "��� ��������";
		cout << setw(15) << agency[i].price << endl;
	}
	cout << endl;
}

void ShowTitle() {
	cout << setw(2) << "##############################################################################";
	cout << setw(2) << "############################################" << endl;
	cout << setw(2) << "�" << setw(20) << "��� �������";
	cout << setw(25) << "������ ����������" << setw(25) << "��� ����������";
	cout << setw(15) << "���-�� ����";
	cout << setw(20) << "�������" << setw(15) << "���������" << endl;
}

void SortByCountry()
{
	for (int i = 0; i < agency.getSize() - 1; i++) {
		for (int j = i; j < agency.getSize(); j++)
			//���� i-�(�������) ������� ������ ����� j-�(���������) �������� ������ �� ������ �������
			if (strcmp(agency[i].country, agency[j].country) > 0) //srtcmp - ������� ����������� �����
				swap(agency[i], agency[j]);
	}
}

void SortByTransport()
{
	for (int i = 0; i < agency.getSize() - 1; i++) {
		for (int j = i; j < agency.getSize(); j++)
			//���� i-�(�������) ������� ������ ����� j-�(���������) �������� ������ �� ������ �������
			if (strcmp(agency[i].transport, agency[j].transport) > 0) //srtcmp - ������� ����������� �����
				swap(agency[i], agency[j]);
	}
}

void SortByPrice()
{
	for (int i = 0; i < agency.getSize() - 1; i++) {
		for (int j = i; j < agency.getSize(); j++)
			if (agency[i].price > agency[j].price)
				swap(agency[i], agency[j]);
	}
}

void ShowByIndex(int i) {
	cout << setw(2) << i + 1;
	switch (agency[i].type) {
	case 1:
		cout << setw(20) << "�����";
		break;
	case 2:
		cout << setw(20) << "�������������";
		break;
	case 3:
		cout << setw(20) << "�������";
		break;
	case 4:
		cout << setw(20) << "������";
		break;
	case 5:
		cout << setw(20) << "�����";
		break;
	}
	cout << setw(25) << agency[i].country;
	cout << setw(25) << agency[i].transport;
	cout << setw(15) << agency[i].dats;
	if (agency[i].meat == 1) cout << setw(20) << "�������";
	else cout << setw(20) << "��� ��������";
	cout << setw(15) << agency[i].price << endl;
}

void SearchByName(char* name)
{

	int k = -1;
	for (int i = 0; i < agency.getSize(); i++) {
		if (strcmp(name, agency[i].country) == 0)
			k = i;
	}
	if (k == -1)
	{
		cout << "�� ������" << endl;
	}
	else
	{
		ShowTitle();
		ShowByIndex(k);
	}
}

void IndidvidualTask() {
	system("cls");
	cout << "�������� ��� �������" << endl;
	cout << "1 - �����" << endl;
	cout << "2 - ������������� ���" << endl;
	cout << "3 - �������" << endl;
	cout << "4 - ������" << endl;
	cout << "5 - �����" << endl;
	int type = InputInt(1, 5);
	cout << "������� ����" << endl;
	double k = InputInt(1, 99999);
	list<Agency>templist;
	for (int i = 0; i < agency.getSize(); i++) {
		if (agency[i].price <= k && agency[i].type == type) {
			templist.Push_Front(agency[i]);
		}
	}
	if (templist.getSize() == 0)
	{
		cout << "������ �� ������" << endl;
	}
	else {
		for (int i = 0; i < templist.getSize() - 1; i++) {
			for (int j = i; j < templist.getSize(); j++) {
				if (templist[i].price < templist[j].price)
					swap(templist[i], templist[j]);
			}
		}
		cout << endl << endl;
		ShowTitle();
		for (int i = 0; i < templist.getSize(); i++) {
			cout << setw(2) << i + 1;
			switch (templist[i].type) {
			case 1:
				cout << setw(20) << "�����";
				break;
			case 2:
				cout << setw(20) << "�������������";
				break;
			case 3:
				cout << setw(20) << "�������";
				break;
			case 4:
				cout << setw(20) << "������";
				break;
			case 5:
				cout << setw(20) << "�����";
				break;
			}
			cout << setw(25) << templist[i].country;
			cout << setw(25) << templist[i].transport;
			cout << setw(15) << templist[i].dats;
			if (templist[i].meat == 1) cout << setw(20) << "�������";
			else cout << setw(20) << "��� ��������";
			cout << setw(15) << templist[i].price << endl;
		}
	}
	system("pause > NUL");
}