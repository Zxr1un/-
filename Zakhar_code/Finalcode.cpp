#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;

struct Player
{
    int id;
    char letters[10] = { '0', '0',  '0', '0', '0', '0', '0', '0', '0', '0' };
};
bool big_check(string user_word, Player player);
string word_input_simpel_check();
void add_letters_to_player(char pl_letters[], char Bank[]);
void alphabet_zapolnenie(char massive_alphabet[]);
void remove_letters(string word, char letters_bank[]);


void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char alphabet[132];
    alphabet_zapolnenie(alphabet);

    Player pl1;
    string word;
    cout << endl << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << pl1.letters[i] << "  ;   ";
    }
    while (word != "0")
    {
        cout << endl << endl << "Алфавит перед итерацией: ";
        for (int i = 0; i < 132; i++)
        {
            cout << alphabet[i] << ";";
        }
        cout << endl << endl;


        add_letters_to_player(pl1.letters, alphabet);

        cout << endl << endl << "Изменённый алфавит: ";
        for (int i = 0; i < 132; i++)
        {
            cout << alphabet[i] << ";";
        }
        cout << endl << endl;


        cout << endl << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << pl1.letters[i] << "  ;   ";
        }
        cout << endl << endl;


        word = word_input_simpel_check();
        if (word == "0")
        {
            break;
        }
        cout << "\n" << word << endl;
        cout << big_check(word, pl1);
        if (big_check(word, pl1))
        {
            remove_letters(word , pl1.letters);
        }

        cout << endl << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << pl1.letters[i] << "  ;   ";
        }
        cout << endl << endl;
        
    }
  

    system("pause");

}



bool big_check(string user_word, Player player) {
    int counter{};
    char player_letters[10]{};
    for (unsigned short i{}; i < 10; i++) {
        player_letters[i] = player.letters[i];
    }
    CharLowerBuffA(player_letters, 10);
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
void add_letters_to_player(char pl_letters[], char Bank[])
{
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        if (pl_letters[i] == '0')
        {
            int rand_nomb;
            rand_nomb = rand() % 132;
            cout << "Random: ";
            cout << rand_nomb << ";"; //для провекрки рандомайзера
            if (Bank[rand_nomb] == '0')
            {
                int j = rand_nomb;
                while (j < 132)
                {
                    cout << endl << "j1: " << j << endl;
                    if (Bank[j] != '0')
                    {
                        pl_letters[i] = Bank[j];
                        cout << endl << "присвоено" << pl_letters[i] << endl;
                        Bank[j] = '0';
                        break;
                    }
                    j++;
                }
                cout << endl << "j: " << j << endl;
                if (j != 131)
                {
                    cout << endl << "break" << endl;
                    break;
                    
                }
                while (j >= 0)
                {
                    if (Bank[j] != '0')
                    {
                        pl_letters[i] = Bank[j];
                        Bank[j] = '0';
                        break;
                    }
                }
            }
            else
            {
                pl_letters[i] = Bank[rand_nomb];
                Bank[rand_nomb] = '0';
            }
        }
    }
}
string word_input_simpel_check() {
    string user_word{};
    bool check_complited = false, already_dumb = false;
    while (!check_complited) {
        if (!already_dumb)
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
            if (!(c >= 'а' && c <= 'я') /*&& !(c == 'Ё')*/ && !(c == 'ё')) {
                cout << "Введите слово без пробелов и только русскими буквами: ";
                check_complited = false;
                already_dumb = true;
                break;
            }
            else
                check_complited = true;
        }
    }
    return user_word;
}
void alphabet_zapolnenie(char massive_alphabet[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int counter = 224;
    for (unsigned i{}; i < 132; i++)
    {
        if (counter == 227)
        {
            massive_alphabet[i] = counter;
            massive_alphabet[i + 1] = 'ё';
            i++;
            counter++;
        }
        else if (counter == 255)
        {
            massive_alphabet[i] = counter;
            counter = 224;
        }
        else
        {
            massive_alphabet[i] = counter;
            counter++;
        }
    }
}

void remove_letters(string word, char letters_bank[])
{
    int size = word.length();
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (word[j] == letters_bank[i])
            {
                word[j] = '0';
                letters_bank[i] = '0';
                break;

            }
        }
    }
}


//доделать удаление букв
//допилить перевод всего в нижний регистр