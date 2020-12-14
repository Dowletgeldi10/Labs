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

	// загружаем все данные из файла
	LoadUsers();
	LoadAgency();
	do {
		system("cls");
		cout << "#############################################" << endl;
		cout << "#                 Меню входа                #" << endl;
		cout << "#############################################" << endl;
		cout << "# 1 #  Админстратор                         #" << endl;
		cout << "# 2 #  Ползователь                          #" << endl;
		cout << "# 0 #  Выход                                #" << endl;
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
	//Сохраняем все данные в файл
	SaveUsers();
	SaveAgency();
	return 0;
}

void LoadUsers()
{
	//Открываем файл для чтения:
	fstream file("users.txt", ios::in | ios::out);
	//Проверяем открыто ли файл
	if (!file.is_open()) {
		cout << "Ошибка файла users.txt" << endl;
		system("pause");
		return;
	}
	while (1) {
		User obj;
		file.read((char*)&obj, sizeof(User)); // читаем строку
		if (file.eof()) break; //если читали конец то выходим из цикла
		user.Push_Front(obj); //записываем считанные данные в список
	}
	file.close(); //закрываем файл
}

void SaveUsers()
{
	fstream out;
	//Открываем файл для записи:
	out.open("users.txt", ios::out | ios::trunc);
	//Проверяем открыто ли файл
	if (!out.is_open()) {
		cout << "Ощибка файла users.txt" << endl;
		system("pause");
		return;
	}
	while (user.getSize() != 0) { //пока размер списка не равен нулью
		User obj = user.Pop_head(); //присваываем текущий элемент списка в временную переменную obj и удаляем его из списка
		out.write((char*)&obj, sizeof(User));
		/*
		Записываем структуру obj в открытый нами файл; для этого узнаем адрес структуры obj
		и приводим указатель на obj к однобайтовому типу; указываем, что в
		структуре obj находится sizeof(User) байт
		*/
	}
	out.close(); //закрываем файл
}

void LoadAgency()
{
	fstream file;
	file.open("center.txt", ios::in | ios::out);
	if (!file.is_open()) {
		system("cls");
		cout << "Ощибка открытие файла center.txt" << endl;
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
		cout << "Ощибка открытие файла center.txt" << endl;
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
	cout << "#  Логин  #" << endl;
	cin >> logi;
	cout << "#  Пароль  #" << endl;
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
		cout << "Неверные данные" << endl;
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
		cout << "# 1 #  Вход" << endl;
		cout << "# 2 #  Регистрация" << endl << endl;
		cout << "# 0 #  Назад" << endl;
		cout << "#  Ваш выбор  #" << endl;

		ch = _getch();
		switch (ch) {
		case '1': {
			cout << "#  Логин  #" << endl;
			cin >> logi;
			cout << "#  Парол  #" << endl;
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
				cout << "$$$$$    Неверные данные  $$$$$" << endl;
				system("pause");
			}
			else
				return 0;
		}break;
		case '2': {
			User newUser;
			cout << "$$$$$ Вврдите данные для регистрации $$$$$" << endl;
			bool isUser2;
			do {
				isUser2 = true;
				cout << "[  Логин  ]" << endl;
				cin >> newUser.login;
				for (int i = 0; i < user.getSize(); i++) {
					if (strcmp(user[i].login, newUser.login) == 0) {
						cout << "#  Такой логин уже существуеть. Вводите другой логин  #" << endl;
						isUser2 = false;
						break;
					}
				}
			} while (!isUser2);
			cout << "#  Парол  #" << endl;
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
		cout << "                  АДМИНИСТРАТОР                " << endl;
		cout << "###############################################" << endl << endl;
		cout << "# 1 # Работа с данными" << endl;
		cout << "# 2 # Работа с пользователями" << endl;
		cout << endl << endl;
		cout << "# 0 # Выход" << endl << endl;
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
		cout << "                   ПОЛЗОВАТЕЛЬ                 " << endl;
		cout << "###############################################" << endl << endl;
		cout << "# 1 #  просмотр" << endl;
		cout << "# 2 #  сортировка" << endl;
		cout << "# 3 #  индивидульное задание" << endl;
		cout << "# 4 #  поиск" << endl;
		cout << "\n# 0 #  выход" << endl;
		ch = _getch();
		switch (ch) {
		case '1': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "список пусть" << endl;
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
				cout << "список пусть" << endl;
				system("pause");
				break;
			}
			cout << "# 1 #  Сортировать по названием страны" << endl;
			cout << "# 2 # Сортировать по цену" << endl;
			cout << "# 3 # Сортировать по виду транспорта" << endl;
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
				cout << "список пусть" << endl;
				system("pause");
				break;
			}
			cout << "Введите название страны" << endl;
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
		cout << "                 РАБОТА С ДАННЫМИ              " << endl;
		cout << "###############################################" << endl << endl;
		cout << "# 1 #  Добавление" << endl;
		cout << "# 2 #  Удаление" << endl;
		cout << "# 3 #  Редактирование" << endl;
		cout << "# 4 #  Поиск" << endl;
		cout << "# 5 #  Сортировка" << endl;
		cout << "# Z #  Индивидуальное задание" << endl;
		cout << "# 6 #  Вывод" << endl << endl;
		cout << "# 0 #  Назад" << endl;
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
			if (agency.getSize() == 0) { // проверяем.. если размер списка равен 0
				cout << "Список пусть" << endl;
				system("pause");
				break;
			}
			ShowAgency();
			cout << "Вводите номер удаляемого элемента" << endl;
			int index = InputInt(1, agency.getSize());
			agency.Delete(index);
			cout << "Успешно удалено" << endl;
			break;
		}
		case '3': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "Список пусть" << endl;
				system("pause");
				break;
			}
			ShowAgency();
			cout << "Вводите номер редактируемого элемента" << endl;
			int index = InputInt(1, agency.getSize());
			EditCenter(index);
			break;
		}
		case '4': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "Список пусть" << endl;
				system("pause");
				break;
			}
			cout << "Введите название страну пребывание" << endl;
			char country[40];
			strcpy_s(country, InputCharNames());
			SearchByName(country);
			system("pause");
			break;
		}
		case '5': {
			system("cls");
			if (agency.getSize() == 0) {
				cout << "Список пусть" << endl;
				system("pause");
				break;
			}
			cout << "# 1 # Сортировать по названием страны" << endl;
			cout << "# 2 # Сортировать по цену" << endl;
			cout << "# 3 # Сортировать по виду транспорта" << endl;

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
				cout << "Список пусть" << endl;
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
		cout << "            РАБОТА С ПОЛЬЗОВАТЕЛЯМИ       " << endl;
		cout << "###############################################" << endl << endl;

		cout << "# 1 #  Добавление" << endl;
		cout << "# 2 #  Удаление" << endl;
		cout << "# 3 #  Редактирование" << endl;
		cout << "# 4 #  Вывод" << endl << endl;
		cout << "\n# 0 #  Назад" << endl;
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
				cout << "Список пусть" << endl;
				system("pause");
				break;
			}
			ShowUser();
			int pos;
			cout << "Вводите номер удаляемого элемента" << endl;
			pos = InputInt(1, length);
			user.Delete(pos);
			cout << "Успешно удалено" << endl;
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
	cout << "Вводите логин" << endl;
	cin >> newUser.login;
	cout << "Вводите парол" << endl;
	cin >> newUser.password;
	cout << "Админ ?" << endl;
	cout << "   0 - нет" << endl;
	cout << "   1 - да" << endl;
	int h = InputInt(0, 1);
	if (h == 0)
		newUser.role = false;
	else
		newUser.role = true;
	for (int i = 0; i < user.getSize(); i++) {
		if (strcmp(user[i].login, newUser.login) == 0) {
			cout << "Такой пользовател уже существуеть" << endl;
			system("pause");
			return;
		}
	}
	if (strcmp(newUser.login, "admin") == 0)
	{
		cout << "Такой пользовател уже существуеть" << endl;
		system("pause");
		return;
	}
	user.Push_Front(newUser);
	cout << "Успешно дабавлен" << endl;
	system("pause");
}

void ShowUser()
{
	system("cls");
	for (int i = 0; i < user.getSize(); i++) {
		if (i == 0) cout << setw(2) << "#" << setw(15) << "Логин" << setw(15) << "Пароль" << setw(15) << "Рол" << endl;
		cout << setw(2) << i + 1 << setw(15) << user[i].login << setw(15) << user[i].password;
		if (user[i].role == false) cout << setw(15) << "0" << endl;
		else cout << setw(15) << "1" << endl;
	}
}

void EditUser()
{
	int length = user.getSize();
	if (length == 0) {
		cout << "Список пусть" << endl;
		system("pause");
		return;
	}
	ShowUser();
	int pos;
	User editUser;
	cout << "Вводите номер элемента" << endl;
	pos = InputInt(1, length);
	cout << "Новый логин" << endl;
	cin >> editUser.login;
	for (int i = 0; i < length; i++) {
		if (strcmp(editUser.login, user[i].login) == 0) {
			cout << "Такой пользовател уже существуеть" << endl;
			system("pause");
			return;
		}
	}
	cout << "Вводите новый парол" << endl;
	cin >> editUser.password;
	cout << "Админ ?" << endl;
	cout << "   0 - нет" << endl;
	cout << "   1 - да" << endl;
	int h = InputInt(0, 1);
	if (h == 0)
		editUser.role = false;
	else
		editUser.role = true;
	user[pos - 1] = editUser;
	cout << "Пользовател успешно редактирован" << endl;
	system("pause");
}

void AddAgency() {
	system("cls");
	Agency newAgency;
	cout << "Выберитк тип путевки" << endl;
	cout << "1 - Отдых" << endl;
	cout << "2 - Экскурсионный туп" << endl;
	cout << "3 - Лечение" << endl;
	cout << "4 - Шопинг" << endl;
	cout << "5 - Круиз" << endl;
	int type = InputInt(1, 6);
	newAgency.type = type;
	cout << "Вводите Страну прибывание" << endl;
	strcpy_s(newAgency.country, InputCharNames());
	cout << "Вводите вид транспорта" << endl;
	strcpy_s(newAgency.transport, InputCharAll_25());
	cout << "Вводите количество дней" << endl;
	newAgency.dats = InputInt(1, 31);
	cout << "  ПИТАНИЕ" << endl;
	cout << "    1 - Завтрак" << endl;
	cout << "    2 - Все включено" << endl;
	newAgency.meat = InputInt(1, 2);
	cout << "Вводите стоимост" << endl;
	newAgency.price = InputInt(1, 99999);
	agency.Push_Front(newAgency);
	cout << endl << "Данные успешно добаылены" << endl;
	system("pause");
}

void EditCenter(int index) {
	cout << "1 - Тип путевки" << endl;
	cout << "2 - Страна пребывание" << endl;
	cout << "3 - Вид транспорта" << endl;
	cout << "4 - Количество дней" << endl;
	cout << "5 - Питание" << endl;
	cout << "6 - Стоимость" << endl;
	int ch;
	ch = InputInt(1, 6);
	switch (ch) {
	case 1: {
		cout << "Выберитк тип путевки" << endl;
		cout << "1 - Отдых" << endl;
		cout << "2 - Экскурсионный туп" << endl;
		cout << "3 - Лечение" << endl;
		cout << "4 - Шопинг" << endl;
		cout << "5 - Круиз" << endl;
		int type = InputInt(1, 6);
		agency[index - 1].type = type;
	}break;
	case 2: {
		cout << "Вводите Страну прибывание" << endl;
		strcpy_s(agency[index - 1].country, InputCharNames());
	}break;
	case 3: {
		cout << "Вводите вид транспорта" << endl;
		strcpy_s(agency[index - 1].transport, InputCharAll_25());
	}break;
	case 4: {
		cout << "Вводите количество дней" << endl;
		agency[index - 1].dats = InputInt(1, 31);

	}break;
	case 5: {
		cout << "  ПИТАНИЕ" << endl;
		cout << "    1 - Завтрак" << endl;
		cout << "    2 - Все включено" << endl;
		agency[index - 1].meat = InputInt(1, 2);
	}break;
	case 6: {
		cout << "Вводите стоимост" << endl;
		agency[index - 1].price = InputInt(1, 99999);
	}break;
	}
	cout << "Данные успешно изменены" << endl;
	system("pause");
}

void ShowAgency() {
	system("cls");
	ShowTitle();
	for (int i = 0; i < agency.getSize(); i++) {
		cout << setw(2) << i + 1;
		switch (agency[i].type) {
		case 1:
			cout << setw(20) << "Отдых";
			break;
		case 2:
			cout << setw(20) << "Экскурсионный";
			break;
		case 3:
			cout << setw(20) << "Лечение";
			break;
		case 4:
			cout << setw(20) << "Шопинг";
			break;
		case 5:
			cout << setw(20) << "Круиз";
			break;
		}
		cout << setw(25) << agency[i].country;
		cout << setw(25) << agency[i].transport;
		cout << setw(15) << agency[i].dats;
		if (agency[i].meat == 1) cout << setw(20) << "Завтрак";
		else cout << setw(20) << "Все включено";
		cout << setw(15) << agency[i].price << endl;
	}
	cout << endl;
}

void ShowTitle() {
	cout << setw(2) << "##############################################################################";
	cout << setw(2) << "############################################" << endl;
	cout << setw(2) << "№" << setw(20) << "Тип путевки";
	cout << setw(25) << "Страна прибывание" << setw(25) << "Вид транспорта";
	cout << setw(15) << "Кол-во дней";
	cout << setw(20) << "Питание" << setw(15) << "Стоимость" << endl;
}

void SortByCountry()
{
	for (int i = 0; i < agency.getSize() - 1; i++) {
		for (int j = i; j < agency.getSize(); j++)
			//если i-й(текущий) элемент списка болше j-й(следующий) элемента списка то меняем местами
			if (strcmp(agency[i].country, agency[j].country) > 0) //srtcmp - фуекция сравнивания сторк
				swap(agency[i], agency[j]);
	}
}

void SortByTransport()
{
	for (int i = 0; i < agency.getSize() - 1; i++) {
		for (int j = i; j < agency.getSize(); j++)
			//если i-й(текущий) элемент списка болше j-й(следующий) элемента списка то меняем местами
			if (strcmp(agency[i].transport, agency[j].transport) > 0) //srtcmp - фуекция сравнивания сторк
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
		cout << setw(20) << "Отдых";
		break;
	case 2:
		cout << setw(20) << "Экскурсионный";
		break;
	case 3:
		cout << setw(20) << "Лечение";
		break;
	case 4:
		cout << setw(20) << "Шопинг";
		break;
	case 5:
		cout << setw(20) << "Круиз";
		break;
	}
	cout << setw(25) << agency[i].country;
	cout << setw(25) << agency[i].transport;
	cout << setw(15) << agency[i].dats;
	if (agency[i].meat == 1) cout << setw(20) << "Завтрак";
	else cout << setw(20) << "Все включено";
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
		cout << "Не найден" << endl;
	}
	else
	{
		ShowTitle();
		ShowByIndex(k);
	}
}

void IndidvidualTask() {
	system("cls");
	cout << "Выберите тип путевки" << endl;
	cout << "1 - Отдых" << endl;
	cout << "2 - Экскурсионный тур" << endl;
	cout << "3 - Лечение" << endl;
	cout << "4 - Шопинг" << endl;
	cout << "5 - Круиз" << endl;
	int type = InputInt(1, 5);
	cout << "Вводите цену" << endl;
	double k = InputInt(1, 99999);
	list<Agency>templist;
	for (int i = 0; i < agency.getSize(); i++) {
		if (agency[i].price <= k && agency[i].type == type) {
			templist.Push_Front(agency[i]);
		}
	}
	if (templist.getSize() == 0)
	{
		cout << "Ничего не найден" << endl;
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
				cout << setw(20) << "Отдых";
				break;
			case 2:
				cout << setw(20) << "Экскурсионный";
				break;
			case 3:
				cout << setw(20) << "Лечение";
				break;
			case 4:
				cout << setw(20) << "Шопинг";
				break;
			case 5:
				cout << setw(20) << "Круиз";
				break;
			}
			cout << setw(25) << templist[i].country;
			cout << setw(25) << templist[i].transport;
			cout << setw(15) << templist[i].dats;
			if (templist[i].meat == 1) cout << setw(20) << "Завтрак";
			else cout << setw(20) << "Все включено";
			cout << setw(15) << templist[i].price << endl;
		}
	}
	system("pause > NUL");
}