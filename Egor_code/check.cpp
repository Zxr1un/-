#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Player {
	// структура с буквами пользователя, его айдишником, последним словом, и баллы
	int id;
	char letters[10]{};
	string last_world = " ";
	int points = 0;
};

string word_input_simpel_check();
bool big_check(string user_word, Player player);

string word_input_simpel_check() {
	string user_word{};
	bool check_complited = false, already_dumb = false;
	while (!check_complited) {
		if(!already_dumb)
			cout << "Введите слово из ваших 10-ти букв: ";
		getline(cin, user_word);
		if (user_word.empty()) {
			return "0";
		}
		for (char c : user_word) {
			if (user_word.length() > 10) {
				cout << "Слово должно состоять из не более чем 10-ти букв: ";
				already_dumb = true;
				break;
			}
			if (!(c >= 'А' && c <= 'я') && !(c == 'Ё') && !(c == 'ё')) {
				cout << "Введите слово без пробелов и только русскими буквами: ";
				check_complited = false;
				already_dumb = true;
				break;
			}else
				check_complited = true;
		}
	}
	return user_word;
}

void msssain() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Player player1;
	string word = "малина";
	int i{};
	for (char c : word) {
		player1.letters[i] = c;
		i++;
	}
	if (big_check("малина", player1)) {
		cout << "true";
	}
	else
		cout << "false";
}

bool big_check(string user_word, Player player) {
	int counter{};
	char player_letters[10]{};
	for (unsigned short i{}; i < 10; i++) {
		player_letters[i] = player.letters[i];
	}
	for (char c : user_word) {
		for (unsigned short i{}; i < 10; i++) {
			if (c == player_letters[i]) {
				counter++;
				player_letters[i] = '0';
				break;
			}
		}
	}
	if (counter == user_word.length()) {
		fstream fin;
		fin.open("russian.txt");
		using In = istream_iterator<string>;
		auto pos = find(In(fin), In(), user_word);
		if (pos != In())
			return true;
		else
			return false;
		fin.close();
	}
	else
		return false;
}