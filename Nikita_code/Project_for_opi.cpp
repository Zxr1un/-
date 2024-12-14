#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Player {
    // структура с буквами пользователя, его айдишником, последним словом, и баллы
    // int id;
    char letters[10]{};
    string last_word = " ";
    int points = 0;
    string name;
};


Player players[6];
char massive_alphabet[132];
int i = { 0 };


int getRandomNumber(int i, int old_time_random);
void alpha_filling(char massive_alphabet[]);
void getting_letters(int amount_players, Player players[]);
void play();
string enter_words(Player players[], int i);
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player);
bool opros_players_about_propusk_hoda(Player players[], int now_player);
bool opros_players_about_new_word();

int main_menu();
void settings();

int main()
{
    setlocale(LC_ALL, "RU");

    while (true)
    {
        int main_menu_otvet = main_menu();
        if (main_menu_otvet == 1)
        {
            play();
        }
        if (main_menu_otvet == 2)
        {
            settings();
        }
        if (main_menu_otvet == 3)
        {
            break;
        }
    }
}

void play()
{
    int kol_players;
    cout << "Введите количество игроков: ";
    cin >> kol_players;
    alpha_filling(massive_alphabet);
    while (true)
    {
        for (int i = 0; i < kol_players; i++)
        {
            getting_letters(kol_players, players);
            enter_words(players, i);

        }
    }
}

int getRandomNumber(int i, int old_time_random)
{
    int time_random;
    if (i == 0)
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        time_random = 1 + ltm->tm_sec;
        time_random = ((time_random + 354) * 8 - 74) / 8;
    }
    else
    {
        time_random = ((old_time_random + 354) * 8 - 74) / 8;
    }
    return time_random % 132;
}


void alpha_filling(char massive_alphabet[])
{
    int counter = 192;
    for (unsigned i{}; i < 132; i++)
    {
        if (counter == 197)
        {
            massive_alphabet[i] = counter;
            massive_alphabet[i + 1] = 'Ё';
            i++;
            counter++;
        }
        else if (counter == 223)
        {
            massive_alphabet[i] = counter;
            counter = 192;
        }
        else
        {
            massive_alphabet[i] = counter;
            counter++;
        }
    }
}

void getting_letters(int amount_players, Player players[])
{
    int intermediate_value = {};
    for (int j = 0; j < amount_players; j++)
    {
        int old_time_random = 0;
        for (int i{}; i < 10; i++)
        {
            if (players[j].letters[i] != 1)
            {
                intermediate_value = getRandomNumber(i, old_time_random);
                old_time_random = intermediate_value;
                if (massive_alphabet[intermediate_value] != 0)
                {
                    players[j].letters[i] = massive_alphabet[intermediate_value];
                    massive_alphabet[intermediate_value] = 0;
                    cout << i + 1 << " буква в букваре " << j + 1 << " игрока это " << players[j].letters[i] << endl;
                }
                else
                {
                    i--;
                }
            }
        }
    }
}

string enter_words(Player players[], int i)
{
    cout << "Игрок под номером " << i + 1 << " (" << players[i].name << ") попробуйте составить слово из представленных букв, если вы не можете это сделать нажмите на пропуск хода (введите 1) " << endl;
    cout << "Далее представлены ваши буквы: ";
    for (int j = 1; j < 10; j++)
    {
        cout << players[i].letters[j] << " ";
    }
    cin >> players[i].last_word;
    return players[i].last_word;
}

bool check_correct_answer(Player players[], string answer)
{

}

int scoring_of_players(bool correct_answer, string answer, string answer_previous_player)
{
    if (correct_answer == true)
    {
        if (answer[answer.length() - 1] == answer_previous_player[1])
            return answer.length() * 2;
        else
            return answer.length();
    }
    else
    {
        if (opros_players_about_new_word() == true)
        {
            if (answer[answer.length() - 1] == answer_previous_player[1])
                return answer.length() * 2;
            else
                return answer.length();
        }
        else
            return answer.length() * -1;
    }
}

bool opros_players_about_new_word()
{
    return true;
}

bool opros_players_about_propusk_hoda(Player players[], int now_player)
{
    return true;
}

int main_menu()
{
    cout << "========================================================================================================================" << endl;
    cout << "========================================================================================================================" << endl;
    cout << "                                                    Игра Эрудит                                                         " << endl;
    cout << "========================================================================================================================" << endl;
    cout << "========================================================================================================================" << endl;
    cout << "1 - Играть" << endl;
    cout << "2 - Настройки" << endl;
    cout << "3 - Выход" << endl;
    int main_menu_otvet;
    cin >> main_menu_otvet;
    cout << "\033[2J\033[1;1H"; // почистить консоль
    return main_menu_otvet;
}

void settings()
{
    cout << "========================================================================================================================" << endl;
    cout << "========================================================================================================================" << endl;
    cout << "KFkf";
    cout << "========================================================================================================================" << endl;
    cout << "========================================================================================================================" << endl;
}