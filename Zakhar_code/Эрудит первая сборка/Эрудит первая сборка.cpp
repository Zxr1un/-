#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <Windows.h>
//#include <algorithm>

using namespace std;
/*
МЕСТО ДЛЯ СООБЩЕНИЙ

Егор, я в твоей проверке на словарь и буквы игрока дописал некоторые моменты

+Я добавил структуры Statistics (статистика игры и имена игроков), чтобы потом не мучаться с созданием интерфейса и глобальными переменными

Захар big_check2 я закементил, просто пока он не использовался, я добавил проверки и немного отполировал, всё работает
надо будет как нибудь занятся бонусами

добавил функию с вводам имён игроков

Егор, я добавил в твой ввод игроков проверку на повторяющиеся имена (Но если считаешь ненужным, можем удалить потом) и удалил свои лишние функции.
И ещё у меня есть предложение по поводу окончания игры, но это потом обсудим.


---------добавить проверку на да/нет в opros_players



*/







struct Player
{
    /*int id;*/
    char letters[10] = { '0', '0',  '0', '0', '0', '0', '0', '0', '0', '0' };
    int bonuces = 0;
    string last_word_of_player = "0";
};

struct Statistics //возможно обойдёмся без этой структуры, но Андрею может понадобится
{
    int points[7] = { 0,0,0,0,0,0,0 };
    string names[7];
};


int bonuses(Player player, string word);
string input_players_name(short which_player);
int input_number_of_players();
void alphabet_zapolnenie(char massive_alphabet[]);
Statistics game(int players_ammount, Statistics names);
void add_letters_to_player(char pl_letters[], char Bank[]);
string word_input_simpel_check(Player& player);
bool big_check(string user_word, Player player);
bool big_check1(string user_word, Player player);
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player);
void remove_letters(string word, char letters_bank[]);
bool opros_players_about_new_word(string word);
bool proverk_na_konec_igru(int letters_ammount, Player player_arr[], int players_num);
void Resaults_screen(Statistics full_stat, short ammount_of_players);
void spizdi_letter();
void fifty_fifty();




void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int players_ammount = input_number_of_players(); // количество игроков (задавать будем в другой функции, но пока так)
    Statistics score;
    for (unsigned short i{}; i < players_ammount; i++) {
        score.names[i] = input_players_name(i);
        // дописал проверку на повторяющиеся имена (можно удалить если не надо)
        for (short j = 0; j < i; j++)
        {
            if (score.names[i] == score.names[j])
            {
                cout << "\nТакое имя уже существует, введите другое: ";
                score.names[i] = input_players_name(i);
                j = -1; //ставлю -1 т.к. в конце итерации прибавится 1
                cout << endl;
            }
        }
        //конец проверки на повторяющиеся имена
    }
    score = game(players_ammount, score);
    Resaults_screen(score, players_ammount);
}
//функция для ввода имён игроков
string input_players_name(short which_player) {
    string name;
    bool check_complited = false;
    while (!check_complited) {
        cout << "Игрок " << which_player + 1 << " Введите своё имя(БЕЗ знаков пунктуации и пробелов): ";
        getline(cin, name);
        for (char c : name) {
            if (!((c >= 'А' && c <= 'я') || (c == 'ё') || (c == 'Ё')) && (ispunct(c) || isspace(c))) {
                check_complited = false;
                break;
            }
            else
                check_complited = true;
        }
    }
    return name;
}
// функция ввода кол-ва игроков
int input_number_of_players() {
    string num_of_players{};
    bool not_dumb = false, already_stupid = false;
    while (true) {
        if (!already_stupid)
            cout << "Пожалуйста введите количество игроков, которые будут участвовать(не более 7 (не менее 2)): ";
        getline(cin, num_of_players);
        for (char c : num_of_players) {
            if ((c >= 'А' && c <= 'я') || (c == 'ё') || (c == 'Ё') || !isdigit(c)) {
                not_dumb = false;
                already_stupid = true;
                cout << "Введите ЧИСЛО игроков, которые будут участвовать(не более 7 (не менее 2)): ";
                break;
            }
            else {
                not_dumb = true;
            }
        }
        if (not_dumb && stoi(num_of_players) <= 7 && stoi(num_of_players) > 1)
            return stoi(num_of_players);
        else if (not_dumb) {
            already_stupid = true;
            cout << "Введите ЧИСЛО игроков, которые будут участвовать(не более 7 (больше 0)): ";
        }
    }
}

Statistics game(int players_ammount, Statistics names)
{
    Statistics score = names;
    char Bank_of_latters[132]; // банк букв из алфавита по 4 раза
    alphabet_zapolnenie(Bank_of_latters); // заполнение банка букв

    Player player_arr[7];
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
        if (letters_ammount != 0)
            cout << "\nВ банке осталось: " << letters_ammount << " букв\n";
        //конец подсчёта оставшихся букв в общем банке
        else {
            if (proverk_na_konec_igru(letters_ammount, player_arr, players_ammount)) {
                cout << "\nТак как у вас не достаточно букв для продолжения игры, Игра окончена";
                break;
            }
        }

        // ход игрока
        while (true)
        {
            int id = (step) % players_ammount;
            cout << "\n\nХод игрока " << (id + 1) << "\n\nПоследнее слово: " << last_word << "\n\nВаши буквы:  | ";

            for (int i = 0; i < 10; i++)
            {
                cout << player_arr[id].letters[i] << " | ";
            }
            cout << endl;
            // вывод информации текущему игроку
            word = word_input_simpel_check(player_arr[id]);
            if (word == "0")
            {
                player_arr[id].last_word_of_player = "0";
                cout << endl << "...пропуск хода..." << endl;
                break;
            }
            //пропуск хода

            cout << endl << "before: " << score.points[id] << endl; //отладка (сколько баллов было до этого)
            bool check = big_check(word, player_arr[id]);
            //cout << "\nCheck: " << check << endl;  //отладка
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
                    cout << "\nСлово было введено неверное.\nВаши баллы сейчас: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    break;
                }
                else
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "\nВ следующий раз введите слово только из своих букв.\n";
                    cout << "\nСлово неверное.\nВаши баллы сейчас: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    break;
                }
            }
        }

        // переписал проверку на скипы
        int counter_for_skip_end{};
        for (unsigned short i{}; i < players_ammount; i++) {
            if (player_arr[i].last_word_of_player == "0") {
                counter_for_skip_end++;
            }
        }
        if (counter_for_skip_end == players_ammount) {
            cout << endl << "Все пропустили ход, конец игры." << endl;
            break;
        }
        //if ((player_arr[0].last_word_of_player == "0") and (player_arr[1].last_word_of_player == "0") and (player_arr[2].last_word_of_player == "0") and (player_arr[3].last_word_of_player == "0"))
        //{
        //    cout << endl << "Все пропустили ход, конец игры." << endl;
        //    break;
        //}//проверка на то что все пропустили ход
        step++;
        /*if(step == 2)
            break;*/
    }

    system("pause");
    return score;
}

void Resaults_screen(Statistics full_stat, short ammount_of_players) {
    short max_score_id{};
    for (unsigned short i{ 1 }; i < ammount_of_players; i++) {
        if (full_stat.points[max_score_id] < full_stat.points[i])
            max_score_id = i;
    }
    cout << "Игра завершилась, " << full_stat.names[max_score_id] << " набрал большее количество баллов.";
}

int bonuses(Player player, string word) {
    if (word.empty()) {
        if (player.bonuces == 0) {
            cout << "У вас есть возможность использовать 2 бонуса( 1 для 50 на 50, 2 для помощь друга).\n";
        }
        else if (player.bonuces == 1) {
            cout << "У вас осталось только помощь друг, если хотите использовать бонус введите 2.\n";
        }
        else if (player.bonuces == 2) {
            cout << "У вас осталось только 50 на 50, если хотите использовать бонус введите 1.\n";
        }
        else {
            cout << "У вас не осталось подсказок\n";
        }
        return 0;
    }
    else {
        int counter{};
        for (char c : word) {
            if (!(c >= 'а' && c <= 'я') && !(c == 'ё') && (isdigit(c) || isspace(c))) {
                counter++;
            }
        }
        if (counter == word.length()) {
            switch (stoi(word)) {
            case 1:
                return 1;
            case 2:
                return 2;
            default:
                return 3;
            }
        }
    }
}
void fifty_fifty() {
    cout << "50 na 50\n";
}
void spizdi_letter() {
    cout << "spizdi bukvu\n";
}

// функция для проверки на конец из-за недостатка букв (из 2 букв почти невозможно составить слово, 
// поэтому если в общем банке 0 букв и у каждого игрока не более чем 2 игра считается оконченной
//*Захар* есть предложение по этому поводу, как будешь свободен, обсудим.
bool proverk_na_konec_igru(int letters_ammount, Player player_arr[], int players_num) {
    for (unsigned short i{}; i < players_num; i++) {
        short counter{};
        for (unsigned short j{}; j < 10; j++) {
            if (player_arr[i].letters[j] != '0')
                counter++;
        }
        if (counter > 2) {
            return false;
        }
    }
    return true;
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
//4-ёх кратное заполнение банка алфавитом
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
//случайное добавление букв игроку из общего банка
string word_input_simpel_check(Player& player) {
    string user_word{};
    bool check_complited = false, already_dumb = false;
    while (!check_complited) {
        user_word = "";
        bonuses(player, user_word);
        if (!already_dumb)
            cout << "Введите слово из ваших 10-ти букв или номер бонуса: ";
        getline(cin, user_word);
        if (user_word.empty()) {
            return "0";
        }
        switch (bonuses(player, user_word)) {
        case 1:
            if (player.bonuces == 0) {
                player.bonuces = 1;
                fifty_fifty();
            }
            else if (player.bonuces == 2) {
                fifty_fifty();
                player.bonuces = 3;
            }
            continue;
        case 2:
            if (player.bonuces == 0) {
                player.bonuces = 2;
                spizdi_letter();
            }
            else if (player.bonuces == 1) {
                spizdi_letter();
                player.bonuces = 3;
            }
            continue;
        case 3:
            cout << "Введите слово из ваших 10-ти букв или номер бонуса: ";
            continue;
        }
        for (char c : user_word) {
            if (user_word.length() > 10) {
                cout << "Слово должно состоять из не более чем 10-ти букв или номер бонуса: ";
                already_dumb = true;
                break;
            }
            if (!(c >= 'а' && c <= 'я') /*&& !(c == 'Ё')*/ && !(c == 'ё')) {
                cout << "Введите слово без пробелов и только строчными русскими буквами или номер бонуса: ";
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
//базово проверяет ввод слова (чтобы были только русские букв) и вызывает бонусы
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
//укороченная версия big_check для вывода информации пользователю, что он ввёл слово не из своих букв(В целом можно убрать, но пока пускай будет)
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
//функций подсчёта баллов за ход (у Никиты работала неправильно, были проблемы с индексами, переделано)
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
//удаление использованных символов
bool opros_players_about_new_word(string word) {
    string answ{};
    while (true) {
        cout << "Ситаете ли вы, что слово было правильно правильно(да/нет): ";
        getline(cin, answ);
        if (answ == "да") {
            ofstream fin;
            fin.open("russian.txt", ios::app);
            fin << word << "\n";
            fin.close();
            return true;
        }
        else if (answ == "нет")
            return false;
    }
}
//опрос игроков на правильность слова, если его нету в нашем словаре

//Проверка Егора (*Захар* добавил укороченную версию этой проверки big_check1)
bool big_check(string user_word, Player player) {
    int counter{};
    char player_letters[10]{};
    for (unsigned short i{}; i < 10; i++) {
        player_letters[i] = player.letters[i];
    }
    CharLowerBuffA(player_letters, 10); // наверное уже не нужно, но пусть будет
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
        if (pos != In()) {
            fin.close();
            return true;
        }
        else {
            fin.close();
            return opros_players_about_new_word(user_word);
        }
    }
    else
        return false;
}