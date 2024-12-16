#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Player {
    // структура с буквами пользователя, его айдишником, последним словом, и баллы
    char letters[10]{};
    string last_word = " ";
    int points = 0;
    string name;
};


Player players[6];
char massive_alphabet[132];
int i = { 0 };


void enter_names(Player players[], int count_of_players);
int getRandomNumber(int i, int old_time_random); // Функция для получения случайных элементов которые используется для случайного взятия букв из банка букв
void alpha_filling(char massive_alphabet[]); // Заполняет банк букв 4 алфавитами
void getting_letters(int amount_players, Player players[]); // Обновляет список букв всем игрокам у кого их нет
void play(); // Основная функция игры
string enter_words(Player players[], int i); // Функция ввода слова игрока также идёт проверка на то были ли использованы буквы из букв игрока
bool check_correct_answer(Player player[], int i, int count_of_players); // Проверяет существование такого слова в списке слов и вынесенея вопроса об существовании слова если такого слова не было найдено в списке возможных слов
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player); // Присвоение очков игроку
bool opros_players_about_propusk_hoda(Player players[], int now_player); // Опрос игроков нужно ли им пропустить сейчас ход (из за невозможности составить слово)
bool opros_players_about_new_word(Player players[], int count_players, int now_player); // Опрос игроков о добавлении нового слова в список слов

int main_menu();
void settings();


int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251); // Ввод в консоль русских символов
    SetConsoleOutputCP(1251); // Вывод в консоли русских символов
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
    enter_names(players, kol_players);
    alpha_filling(massive_alphabet);
    while (true)
    {
        for (int i = 0; i < kol_players; i++)
        {
            getting_letters(kol_players, players); //Выводит буквы красиво
            enter_words(players, i); // Ввод слова
            if (i == 0)
            {
                scoring_of_players(check_correct_answer(players, i, kol_players), players[i].last_word, players[kol_players - 1].last_word);
            }
            else
            {
                scoring_of_players(check_correct_answer(players, i, kol_players), players[i].last_word, players[i - 1].last_word);
            }
            
        }
    }
}

void enter_names(Player players[], int count_of_players)
{
    for (int i = 0; i < count_of_players; i++)
    {
        cout << "Игрок под номером " << i + 1 << " введите своё имя или никнейм который будет использоваться в игре: ";
        cin >> players[i].name;
    }
}

int getRandomNumber(int i, int old_time_random)
{
    int time_random, time_random_min, time_random_hour;
    if (i == 0)
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        time_random = 1 + ltm->tm_sec;
        time_random_min = 1 + ltm->tm_min;
        time_random_hour = 1 + ltm->tm_hour;
        time_random = ((time_random + time_random_min + time_random_hour + 354) * 8 - 73) / 8;
    }
    else
    {
        time_random = ((old_time_random + 354) * 8 - 73) / 8;
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
                if (massive_alphabet[intermediate_value] != 1)
                {
                    players[j].letters[i] = massive_alphabet[intermediate_value];
                    massive_alphabet[intermediate_value] = 1;
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
    int count_answer, count_good_chars = { 0 }; //Количество букв в ответе и количество совпавших букв этого ответа с списком букв у игрока
    cout << "Игрок под номером " << i + 1 << " (" << players[i].name << ") попробуйте составить слово из представленных букв, если вы не можете это сделать нажмите на пропуск хода (введите 1) " << endl;
    cout << "Далее представлены ваши буквы: ";
    for (int j = 0; j < 10; j++)
    {
        cout << players[i].letters[j] << " ";
    }
    cin >> players[i].last_word;
    count_answer = players[i].last_word.length();
    for (int j = 0; j < count_answer; j++)
        players[i].last_word[j] = toupper(players[i].last_word[j]);
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < count_answer; k++)
        {
            if (players[i].letters[j] == players[i].last_word[k])
            {
                count_good_chars += 1;
                players[i].letters[j] = 1;
            }
        }
    }
    if (count_answer == count_good_chars)
    {
        return players[i].last_word;
    }
    else
    {
        cout << "Вы ввели неправильное слово которое не соответствует вашим буквам, пропуск хода" << endl;
        return players[i].last_word + "6";
    }
}

bool check_correct_answer(Player player[], int i, int count_of_players)
{
    int counter{};
    string stroka;
    fstream fin;
    fin.open("russian.txt");
    while (getline(fin, stroka))
    {
        if (stroka == player[i].last_word)
            return true;
    }
    if (player[i].last_word[player[i].last_word.length()] != 6)
    {
        if (opros_players_about_new_word(players, count_of_players, i) != true)
            return false;
    }
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
        return (answer.length() - 1) * -1;
}
    
bool opros_players_about_new_word(Player players[], int count_players, int now_player)
{
    int count_of_plus = { 0 };
    string answer;
    for (int i = 0; i < count_players; i++)
    {
        if (i != now_player)
        {
            cout << "Игрок " << players[i].name << " согласны ли вы с тем что слово " << players[now_player].last_word << " должно войти в словарь и засчитаться игроку " << players[now_player].name << ": ";
            cin >> answer;
            if (answer == "да" or "+" or "Да")
            {
                count_of_plus += 1;
            }
            else if (answer == "нет" or "-" or "Нет")
            {
                count_of_plus += 0;
            }
            else
            {
                cout << "Введенно неккоректное значение пожалуйста переголосуйте " << endl;
                i--;
            }
        }
    }
    if (count_of_plus == count_players - 1)
    {
        ofstream out("russian.txt", ios::app);
        out << players[now_player].last_word << "\n";
        return true;
    }
    else
    {
        return false;
    }
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