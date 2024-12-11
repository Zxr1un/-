#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Player {
	// структура с буквами пользователя, его айдишником, последним словом, и баллы
	int id;
	char letters[10];
	string last_world;
	int points;
};

bool checkfile(string search, fstream& fin);
char check_for_user_word(string user_word, Player current_player);
//скелеты функций

void ddmain()
{
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	Player player1{};
	char letters[10] = {'А','Р','К','А','Р','А','Р','К','А','Р'};
	for (unsigned short i{}; i < 10; i++) {
		player1.letters[i] = letters[i];
	}
	//26-29 вводится список букв игрока, он должен рандомам вводится
	fstream fin;
	fin.open("russian.txt");//открытие файла с библиотекой
	if (checkfile("прикол", fin)) {//тут должно вводиться 
		char check = check_for_user_word("АРКА", player1);
		if (check == 'c')
			cout << "человек ввёл правильное слово";
		//тут программа должна идти дальше
		else if (check == 'e')
			cout << "Человек ввёл слово с цифрами/пунктуацией или пробелами";
		// просьба ввести ещё раз
		else if (check == 'i')
			cout << "Человек ввёл слово состоящее не тольео из букв в его банке";
		// идёт отсчёт баллов
		else
			cout << "Человек ввёл пустую строку";
		// пропуск хода
	}
}

char check_for_user_word(string user_word, Player current_player) {
	// возвращает код
	// с - correct
	// e - invalid enter
	// i - использованны буквы невходящие в банк букв игрока
	if (user_word.length() != 0) {
		int counter{};
		char player_letters[10]{};
		bool alredy_was_used = false;
		for (unsigned short i{}; i < 10; i++) {
			player_letters[i] = current_player.letters[i];
		}
		for (char c : user_word) {
			if (isdigit(c) || ispunct(c) || isspace(c))
				return 'e';
			for (unsigned short i{}; i < 10; i++) {
				if (c == player_letters[i] && !alredy_was_used) {
					counter++;
					player_letters[i] = '0';
					alredy_was_used = true;
				}
			}
			alredy_was_used = false;
		}
		if (counter == user_word.length())
			return 'c';
		else
			return 'i';
	}else
		return 'o';
}

bool checkfile(string search, fstream& fin)
// функция проверяет есть ли такое слово в нашем словаре
{
	using In = istream_iterator<string>;
	auto pos = find(In(fin), In(), search);
	if (pos != In())
		return true;
	else
		return false;
	fin.close();
}