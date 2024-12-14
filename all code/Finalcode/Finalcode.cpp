#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

struct Player {
    // структура с буквами пользователя, его айдишником, последним словом, и баллы
    // int id;
    char letters[10]{};
    string last_world = " ";
    int points = 0;
};


Player Players[6];
int intermediate_value = {};
char massive_alphabet[132];

int getRandomNumber(int i, int old_time_random);
void alpha_filling(char massive_alphabet[]);
void getting_letters(int amount_players, Player players[]);

int main()
{
    setlocale(LC_ALL, "RU");
    getting_letters(4, Players);
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
    alpha_filling(massive_alphabet);
    for (int j = 0; j < amount_players; j++)
    {
        int old_time_random = 0;
        for (int i{}; i < 10; i++)
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