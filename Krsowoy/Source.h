#pragma once
#include "List.h"

struct Agency {
	int type = 0; //тип путевки
	char country[25] = ""; //страна прибытие
	char transport[25] = ""; // вид транспорта
	int dats = 0; //кол-во дней
	int meat = 0; //тип обсл. еды
	double price = 0; //стоимост
};

struct User {
	char login[20] = "";//логин
	char password[20] = "";//парол
	bool role = false;//рол
};

void LoadUsers(); //Считывание данных пользователей из файла в список

void SaveUsers();//Запись в файл данных пользователей из списка в файл

void LoadAgency(); //Считывание данных о детей из файла в список

void SaveAgency(); //Запис данных о детей из списка в файл

int LogAdmin(); //Авторизация админа

int LogUser(); //Авторизация пользователя

void MenuAdmin(); //меню админа

void menuuser(); //меню ползователя

void Menu1(); //меню работы с данными

void Menu2(); //меню работы с ползователями

void AddUser(); //Добавление данных пользователя

void ShowUser(); //Просмотр Пользователей

void EditUser(); //Редактирование данных пользователя

void AddAgency(); //Добавление данных

void EditCenter(int index); //Редактирование данных о ребёнка

void ShowAgency(); //Просмотр данных

void ShowTitle(); //вывод 

void SortByCountry(); //сортировка (название страны)

void SortByTransport(); //сортировка (транспорт)

void SortByPrice(); //сортировка по цене

void ShowByIndex(int i); //вывод по индексу

void SearchByName(char* name); //поиск по имени

void IndidvidualTask(); //Функция идз
