#pragma once
#include "List.h"

struct Agency {
	int type = 0; //��� �������
	char country[25] = ""; //������ ��������
	char transport[25] = ""; // ��� ����������
	int dats = 0; //���-�� ����
	int meat = 0; //��� ����. ���
	double price = 0; //��������
};

struct User {
	char login[20] = "";//�����
	char password[20] = "";//�����
	bool role = false;//���
};

void LoadUsers(); //���������� ������ ������������� �� ����� � ������

void SaveUsers();//������ � ���� ������ ������������� �� ������ � ����

void LoadAgency(); //���������� ������ � ����� �� ����� � ������

void SaveAgency(); //����� ������ � ����� �� ������ � ����

int LogAdmin(); //����������� ������

int LogUser(); //����������� ������������

void MenuAdmin(); //���� ������

void menuuser(); //���� �����������

void Menu1(); //���� ������ � �������

void Menu2(); //���� ������ � �������������

void AddUser(); //���������� ������ ������������

void ShowUser(); //�������� �������������

void EditUser(); //�������������� ������ ������������

void AddAgency(); //���������� ������

void EditCenter(int index); //�������������� ������ � ������

void ShowAgency(); //�������� ������

void ShowTitle(); //����� 

void SortByCountry(); //���������� (�������� ������)

void SortByTransport(); //���������� (���������)

void SortByPrice(); //���������� �� ����

void ShowByIndex(int i); //����� �� �������

void SearchByName(char* name); //����� �� �����

void IndidvidualTask(); //������� ���
