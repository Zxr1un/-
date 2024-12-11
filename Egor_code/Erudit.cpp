#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;
void alphabet_zapolnenie(char alphabet[]);
void checkfile(string search, fstream& fin);

char alpha[132]{};

struct Player {
	int id;
	string letters[10];
	string last_world;
	int points;
};

int main()
{
	char alphabet[132];
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	fstream fin;
	fin.open("russian.txt");
	checkfile("СИЛИКОН", fin);
	alphabet_zapolnenie(alphabet);
	for (char c : alphabet) {
		cout << c << "\n";
	}
}

void check_in_file(string search, fstream& fin)
{
	using In = istream_iterator<string>;
	auto pos = find(In(fin), In(), search);
	if (pos != In())
		cout << "слово найдено";
	else
		cout << "нет такого слова";
	fin.close();
}

void alphabet_zapolnenie(char alphabet[]) {
	int counter = 192;
	for (short i{}; i < 132; i++) {
		if (counter == 197) {
			alphabet[i] = counter;
			alphabet[i + 1] = 'Ё';
			i++;
			counter++;
		}
		else if (counter == 223) {
			alphabet[i] = counter;
			counter = 192;
		}
		else {
			alphabet[i] = counter;
			counter++;
		}
	}
}