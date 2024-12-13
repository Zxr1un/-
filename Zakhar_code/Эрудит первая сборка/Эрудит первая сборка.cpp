#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;
/*
МЕСТО ДЛЯ СООБЩЕНИЙ

Егор, я в твоей проверке на словарь и буквы игрока дописал некоторые моменты

+Я добавил структуры Statistics (статистика игры и имена игроков), чтобы потом не мучаться с созданием интерфейса и глобальными переменными



*/







struct Player
{
    /*int id;*/
    char letters[10] = { '0', '0',  '0', '0', '0', '0', '0', '0', '0', '0' };
    /*int point = 0;*/
    string last_word_of_player = "0";
};

struct Statistics //возможно обойдёмся без этой структуры, но Андрею может понадобится
{
    int points[4] = {0,0,0,0};
    string names[4];
};


void alphabet_zapolnenie(char massive_alphabet[]);
Statistics game(int players_ammount);
void add_letters_to_player(char pl_letters[], char Bank[]);
string word_input_simpel_check();
bool big_check(string user_word, Player player);
bool big_check1(string user_word, Player player);
bool big_check2(string user_word, Player player);
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player);
void remove_letters(string word, char letters_bank[]);
bool opros_players_about_new_word(string word, fstream& fin);




void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int players_ammount = 4; // количество игроков (задавать будем в другой функции, но пока так)
    Statistics score;
    score = game(players_ammount);

    
}

Statistics game(int players_ammount)
{
    Statistics score;
    char Bank_of_latters[132]; // банк букв из алфавита по 4 раза
    alphabet_zapolnenie(Bank_of_latters); // заполнение банка букв

    Player player_arr[4];
    string last_word = "0"; //буфер хранящий последнее введённое слово
    string word;
    int step = 0; //номер хода
    
    for (int i = 0; i < players_ammount; i++)
    {
        player_arr[i].last_word_of_player = "1";
    }
    //инициализация играющих игроков(им вместо пустого ответа ставится 1, чтобы у каждого был хотя бы 1 ход)
    while (true)
    {

        for (int i = 0; i < players_ammount; i++)
        {
            add_letters_to_player(player_arr[i].letters, Bank_of_latters);
        } //выдача новых букв каждому игроку в начале хода


        int letters_ammount = 0; //начало подсчёта оставшихся букв в общем банке
        for (int i = 0; i < 132; i++)
        {
            if (Bank_of_latters[i] != '0')
            {
                letters_ammount++;
            }
        }
        cout << "\nВ банке осталось: " << letters_ammount << " букв\n";  //конец подсчёта оставшихся букв в общем банке

        // ход игрока
        while (true)
        {
            int id = (step) % players_ammount;
            cout << "\n\nХод игрока " << (id + 1) <<"\n\nПоследнее слово: "<< last_word<< "\n\nВаши буквы:  | ";
            for (int i = 0; i < 10; i++)
            {
                cout << player_arr[id].letters[i] << " | ";
            }
            cout << endl;
                                    // вывод информации текущему игроку
            word = word_input_simpel_check();
            if (word == "0")
            {
                player_arr[id].last_word_of_player = "0";
                cout << endl << "...пропуск хода..." << endl;
                break;
            }          
                            //пропуск хода

            cout << endl << "before: " << score.points[id] << endl; //отладка (сколько баллов было до этого)
            bool check = big_check(word, player_arr[id]);
            if (check)
            {
                
                score.points[id] += scoring_of_players(check, word, last_word);
                cout << "\nСлово принято.\nВаши баллы сейчас: " << score.points[id] << " (+" << scoring_of_players(check, word, last_word) << ") " << endl;
                last_word = word;
                player_arr[id].last_word_of_player = word;
                remove_letters(word, player_arr[id].letters);
                break;
            }
            else
            {
                if (big_check1(word, player_arr[id]))
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "\nСлово неверное.\nВаши баллы сейчас: " << score.points[id] <<" ("<< scoring_of_players(check, word, last_word)<<") " << endl;
                }
                else
                {
                    cout << "\nВведите слово только из своих букв.\n";
                }
               
            }
        }


        if ((player_arr[0].last_word_of_player == "0") and (player_arr[1].last_word_of_player == "0") and (player_arr[2].last_word_of_player == "0") and (player_arr[3].last_word_of_player == "0"))
        {
            cout << endl << "Все пропустили ход, конец игры." << endl;
            break;
        }//проверка на то что все пропустили ход
        step++;
    }

    system("pause");
    return score;
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
void add_letters_to_player(char pl_letters[], char Bank[])
{
    //все закоментированные строки -- это строки для отладки функции
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        if (pl_letters[i] == '0')
        {
            int rand_nomb;
            rand_nomb = rand() % 132;
           /* cout << "Random: ";
            cout << rand_nomb << ";";*/ //для провекрки рандомайзера
            if (Bank[rand_nomb] == '0')
            {
                int j = rand_nomb;
                while (j < 132)
                {
                    /*cout << endl << "j1: " << j << endl;*/
                    if (Bank[j] != '0')
                    {
                        pl_letters[i] = Bank[j];
                       /* cout << endl << i << " присвоено " << pl_letters[i] << endl;*/
                        Bank[j] = '0';
                        break;
                    }
                    j++;
                }
               /* cout << endl << "j: " << j << endl;*/
                if (j == 131)
                {
                   /* cout << endl << "break" << endl;*/
                    while (j >= 0)
                    {
                        if (Bank[j] != '0')
                        {
                            pl_letters[i] = Bank[j];
                            Bank[j] = '0';
                            break;
                        }
                        j--;
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




bool big_check1(string user_word, Player player) {
    //Егор, я дописал тебе костыль
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
        return true;
    }
    else
        return false;
}
bool big_check2(string user_word, Player player) {
    //Егор, я дописал тебе костыль
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
            return opros_players_about_new_word(user_word, fin);

        fin.close();
    }
    else
        return false;
}
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player)
{
    if (correct_answer == true)
    {
        if (answer[0] == answer_previous_player[answer_previous_player.length() - 1])
            return answer.length() * 2;
        else
            return answer.length();
    }
    else
    {
        return answer.length() * -1;
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


bool opros_players_about_new_word(string word, fstream& fin) {
    string answ{};
    bool already_dumb = false;
    while (true) {
        if (!already_dumb)
            cout << "Ситаете ли вы, что слово было правильно правильно(да/нет): ";
        getline(cin, answ);
        if (answ == "да")
            return true;
        else if (answ == "нет")
            return false;
        else
            already_dumb = true;
    }
}




//Проверка Егора (Я костылями разделил её на 2 отдельные)
bool big_check(string user_word, Player player) {
    //Егор, я дописал тебе костыль
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
            return opros_players_about_new_word(user_word, fin);

        fin.close();
    }
    else
        return false;
}