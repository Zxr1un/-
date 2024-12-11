﻿#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;
char aplha_zaplonenie(char a[132]);
void checkfile(const string& search, ifstream& fin);

char alpha[132]{};

struct Player {
	int id;
	string letters[10];
	string last_world;
	int points;
};

int main()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	const int range = 132;
	int counter = 192;
	char alpha[range]{};
	ifstream fin;
	fin.open("russian.txt");
	checkfile("СИЛИКОН", fin);
}

void checkfile(const string& search, ifstream& fin)
{
	using In = istream_iterator<string>;
	auto pos = find(In(fin), In(), search);
	if (pos != In())
		cout << "слово найдено";
	else
		cout << "нет такого слова";
	fin.close();
}

/*static char alpha_zapolnenie(char a[132]) {
	int counter = 192;
	for (unsigned i{}; i < 132; i++) {
		if (counter == 197) {
			a[i] = counter;
			a[i + 1] = 'Ё';
			i++;
			counter++;
		}
		else if (counter == 223) {
			a[i] = counter;
			counter = 192;
		}
		else {
			a[i] = counter;
			counter++;
		}
	}
}*/