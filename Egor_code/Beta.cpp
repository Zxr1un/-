#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <cstdint>
#include <intrin.h>
//#include <algorithm>

using namespace std;
/*
МЕСТО ДЛЯ СООБЩЕНИЙ

Размер банка сейчас 173 для работы рандомайзеры (последний символ пустой ) для замены размера банка перед функциями стоят константы Bank_size
Изменено:
1) Заполнение алфавита
2) Big_check и опрос игроков о овом слове (работа с новыми файлами и быстрая проверка)
3) Исправил залипание в end_screen в конце
4) переписал рандомайзер (теперь чёткий рандом и сортировка символов (можно даже упростить подсчёт букв в game))

*/

struct Player
{
    /*int id;*/
    char letters[10] = { '-', '-',  '-', '-', '-', '-', '-', '-', '-', '-' };
    int bonuces = 0;
    string last_word_of_player = "0";
    bool bank_null = false;
};

struct Statistics //возможно обойдёмся без этой структуры, но Андрею может понадобится
{
    int points[7] = { 0,0,0,0,0,0,0 };
    string names[7];
};


int bonuses(Player player, string word, short letter_ammount, bool player_with_letters, bool already_dumb);
string input_players_name(short which_player, Statistics score);
int input_number_of_players();
void alphabet_zapolnenie(char massive_alphabet[]);
Statistics game(int players_ammount, Statistics names);
void add_letters_to_player(char pl_letters[], char Bank[]);
string word_input_simpel_check(Player& player, Player player_arr[], char letter_bank[], short player_ammount, Statistics score, short player_id, short letter_ammount, string last_word);
bool big_check(string user_word, Statistics names, short player_ammount, short id, Player player);
bool big_check1(string user_word, Player player);
//bool big_check2(string user_word, Player player);
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player);
void remove_letters(string word, char letters_bank[]);
bool opros_players_about_new_word(string word, Statistics names, short player_ammount, short id);
void Resaults_screen(Statistics full_stat, short ammount_of_players);
void spizdi_letter(Player& player, Player player_arr[], short player_ammount, Statistics score, short player_id, string last_word);
void fifty_fifty(Player& player, char letter_bank[], string last_word, short id, Statistics names);
void maxsc();
void printHeading();
void Rules();
void Menu();
void printBorder(int width);
void clearScreen();
void Start();
bool confirmExit();
void clearConsole();
bool check_for_null_bank(char player_bank[], short player_id);
void vuvod_igroka(bool first_round, Statistics names, short id, string last_word);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << " ";
    system("cls");
    maxsc();
    cout << " ";
    system("cls");
    printHeading();

    const int width = 156;

    string choice;

    do {
        Menu();
        getline(cin, choice);

        clearConsole();
        if (choice.length() == 1 && !((choice[0] >= 'А' && choice[0] <= 'я') || (choice[0] == 'ё') || (choice[0] == 'Ё') || !isdigit(choice[0]))) {
            switch (stoi(choice)) {
            case 1:
                printBorder(width);
                cout << endl;
                cout << setw(88) << "Начинаем игру...\n\n";
                printBorder(width);
                Start();
                break;
            case 2:
                Rules();
                break;
            case 3:
                if (confirmExit()) {
                    cout << "Выход...\n";
                    return 0; // Выход из программы
                }
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            }
        }
    } while (true);

    return 0;
}

void vuvod_igroka(bool first_round, Statistics names, short id, string last_word) {
    const int width = 156;
    printBorder(width);
    cout << endl;
    cout << setw(79) << "~~~ Ход игрока: " << names.names[id] << " ~~~\n\n";
    printBorder(width);
    /* if (!first_round)*/
    cout << "\n\n    Последнее слово: " << last_word;
    first_round = false;
}


bool check_for_null_bank(char player_bank[], short player_id) {
    short null_letter{};
    for (unsigned short i{}; i < 10; i++) {
        if (player_bank[i] == '-')
            null_letter++;
    }
    if (null_letter == 10)
        return true;
    else
        return false;
}


void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool confirmExit() {
    const int width = 156;

    string confirmation{};
    do {
        printBorder(width);
        cout << setw(90) << "Вы точно хотите выйти?\n\n";
        cout << setw(89) << "да             нет\n";
        cout << setw(77) << " ";
        getline(cin, confirmation);

        clearConsole();

        if (confirmation == "да")
            return true;
        else if (confirmation == "нет")
            return false;
        else
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
    } while (true);
}

void printBorder(int width) {
    for (int i = 0; i < width; ++i) cout << "=";
    cout << endl;
}

void clearScreen() {
    system("cls");
}

void maxsc()
{
    HWND Hwnd = GetForegroundWindow();
    ShowWindow(Hwnd, SW_MAXIMIZE);
}

void Menu() {
    const int width = 156;
    printBorder(width);
    cout << endl;
    cout << setw(90) << "~~~~~ВЫБЕРИТЕ~~~~~\n\n";
    printBorder(width);
    cout << endl;
    cout << setw(92) << "~~~ 1. Начать игру  ~~~\n\n";
    cout << setw(94) << "~~~ 2. Прочитать правила ~~~\n\n";
    cout << setw(88) << "~~~ 3. Выйти ~~~\n\n\n";
    cout << setw(84) << "Выберите: ";
}


void printHeading()
{
    const int width = 156;

    printBorder(width);
    cout << setw(90) << "Добро пожаловать в игру Эрудит" << endl;
    printBorder(width);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << "                                                ______    _____    _    _   _____    _____  _______   ______        \n";
    cout << "                                               | ____|   |  __ \\  | |  | | |  __ \\  |  _  ||__   __| |  ____|       \n";
    cout << "                                               | |__     | |__) | | |  | | | |  | |   | |     | |    | |__          \n";
    cout << "                                               |  __|    |  _  /  | |  | | | |  | |   | |     | |    |  __|         \n";
    cout << "                                               | |____   | | \\ \\  | |__| | | |__| |  _| |_    | |    | |____        \n";
    cout << "                                               |______|  |_|  \\_\\  \\____/  |_____/  |_____|   |_|    |______|       \n";

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << setw(90) << "Продолжить..." << endl;
    printBorder(width);

    cin.ignore();
    clearScreen();
}

void Rules() {
    const int width = 156;

    printBorder(width);
    cout << setw(90) << "~~~~~ПРАВИЛА~~~~~\n\n";

    cout << "                                    || 1. Цель игры:                                                                         ||\n";
    cout << "                                    ||    - Собрать как можно больше очков, составляя слова на игровом поле.                 ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 2. Начало игры:                                                                       ||\n";
    cout << "                                    ||    - Каждый игрок получает по 10 выбранных случайным образом букв.                    ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 3. Ход игрока:                                                                        ||\n";
    cout << "                                    ||    - Игрок составляет слово из своих букв.                                            ||\n";
    cout << "                                    ||    - Если слово составлено верно, то игроку присуждаются очки,                        ||\n";
    cout << "                                    ||      равные количеству букв в слове.                                                  ||\n";
    cout << "                                    ||    - Если слово игрока начинается с той же буквы, на которую                          ||\n";
    cout << "                                    ||      заканчивалось слово предыдущего игрока, то количество                            ||\n";
    cout << "                                    ||      очков увеличивается.                                                             ||\n";
    cout << "                                    ||    - Слово составлено неверно, если в него входят буквы, не                           ||\n";
    cout << "                                    ||      входящие в набор букв игрока.                                                    ||\n";
    cout << "                                    ||    ПРИМЕЧАНИЕ:                                                                        ||\n";
    cout << "                                    ||    - Одну и ту же букву из набора нельзя использовать несколько раз.                  ||\n";
    cout << "                                    ||    - Если слово составлено неверно, то из общей суммы очков                           ||\n";
    cout << "                                    ||      вычитается число очков, равное количеству букв в слове.                          ||\n";
    cout << "                                    ||    - После того, как каждый игрок сделал свой ход, ему добавляются недостающие буквы. ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 4. Бонусы:                                                                            ||\n";
    cout << "                                    ||    - «50-на-50» -- игрок может перечислить 5 букв, которые он хотел бы заменить.      ||\n";
    cout << "                                    ||    ПРИМЕЧАНИЕ:                                                                        ||\n";
    cout << "                                    ||   - Замененные буквы считаются отыгравшими, а сумма очков                             ||\n";
    cout << "                                    ||      игрока уменьшается на 2.                                                         ||\n";
    cout << "                                    ||    - «ПОМОЩЬ ДРУГА» -- игрок может заменить «ненужную» ему                            ||\n";
    cout << "                                    ||      букву из своего набора на «понравившуюся» ему букву из набора букв соперника.    ||\n";
    cout << "                                    ||    ПРИМЕЧАНИЕ:                                                                        ||\n";
    cout << "                                    ||    - Согласие второго игрока не требуется и сумма очков не уменьшается.               ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 5. Окончание игры:                                                                    ||\n";
    cout << "                                    ||    - Игра заканчивается, когда все игроки пропустят ход.                              ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 6. Победа:                                                                            ||\n";
    cout << "                                    ||    - Выигрывает тот игрок, который набрал большее число баллов.                       ||\n";
    cout << "                                    ||                                                                                       ||\n\n";

    cout << setw(90) << "~~~~~УДАЧНОЙ ИГРЫ!~~~~~\n";
    printBorder(width);
    cout << endl;
    cout << "Нажмите Enter для возвращения в меню...";
    cin.ignore();
    clearScreen();
}


void Start() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int players_ammount = input_number_of_players(); // количество игроков (задавать будем в другой функции, но пока так)
    Statistics score;
    for (unsigned short i{}; i < players_ammount; i++) {
        score.names[i] = input_players_name(i, score);
    }
    score = game(players_ammount, score);
    Resaults_screen(score, players_ammount);
}

//функция для ввода имён игроков
string input_players_name(short which_player, Statistics score) {
    string name;
    const int width = 156;
    bool check_complited = false, stupid_player = false;
    while (!check_complited) {
        cout << endl;
        printBorder(width);
        cout << endl;
        cout << endl;
        if (!stupid_player) {
            cout << setw(80) << "*** ИГРОК: " << which_player + 1 << " ***" << "\n        Введите своё имя(БЕЗ знаков пунктуации и пробелов): ";
        }
        else {
            cout << setw(80) << "*** ИГРОК: " << which_player + 1 << " ***" << "\n\n        Введите своё имя(БЕЗ знаков пунктуации и пробелов) и НЕ повторяя имена других игроков : ";

        }
        getline(cin, name);
        if (!name.empty()) {
            for (char c : name) {
                if (!((c >= 'А' && c <= 'я') || (c == 'ё') || (c == 'Ё')) && (ispunct(c) || isspace(c))) {
                    check_complited = false;
                    break;
                }
                else
                    check_complited = true;
            }
            if (check_complited) {
                for (string c : score.names) {
                    if (name == c) {
                        check_complited = false;
                        stupid_player = true;
                        break;
                    }
                }
            }
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
            cout << "\n        Пожалуйста введите количество игроков, которые будут участвовать(не более 7 (не менее 2)): ";
        getline(cin, num_of_players);
        if (!num_of_players.empty()) {
            if (num_of_players.length() == 1) {
                for (char c : num_of_players) {
                    if ((c >= 'А' && c <= 'я') || (c == 'ё') || (c == 'Ё') || !isdigit(c)) {
                        not_dumb = false;
                        already_stupid = true;
                        cout << "\n        Введите ЧИСЛО игроков, которые будут участвовать(не более 7 (не менее 2)): ";
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
                    cout << "\n        Введите ЧИСЛО игроков, которые будут участвовать(не более 7 (не менее 2)): ";
                    cout << endl;
                }
            }
            else {
                already_stupid = true;
                cout << "        Введите ЧИСЛО игроков, которые будут участвовать(не более 7 (не менее 2)): ";
                cout << endl;
            }
        }
        else {
            already_stupid = true;
            cout << "        Введите ЧИСЛО игроков, которые будут участвовать(не более 7 (не менее 2)): ";
            cout << endl;
        }
    }
}

Statistics game(int players_ammount, Statistics names)
{
    const int width = 156;
    Statistics score = names;
    //132
    const int Bank_size = 173; //для рандомайзера нужен банк на 1 символ больше
    char Bank_of_latters[Bank_size]{}; // банк букв из алфавита по 4 раза
    for (unsigned short i{}; i < Bank_size; i++) {
        Bank_of_latters[i] = '-';
    }
    alphabet_zapolnenie(Bank_of_latters); // заполнение банка букв

    Player player_arr[7];
    string last_word = "0"; //буфер хранящий последнее введённое слово
    string word;
    bool first_round = true;
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
        cout << endl;
        printBorder(width);

        for (int i = 0; i < Bank_size; i++)
        {
            if (Bank_of_latters[i] != '-')
            {
                letters_ammount++;
            }
        }
        cout << endl;
        cout << setw(82) << "В банке осталось: " << letters_ammount << " букв\n\n\n\n\n\n\n\n";
        cout << "        Нажмите Enter для продолжения......";

        cin.ignore();
        clearScreen();

        // ход игрока
        while (true)
        {
            int id = (step) % players_ammount;
            vuvod_igroka(first_round, names, id, last_word);
            cout << "\n";
            cout << setw(90) << "****** Ваши буквы ****** \n\n" << setw(41) << " | ";
            for (int i = 0; i < 10; i++)
            {
                cout << player_arr[id].letters[i] << "   |   ";
            }
            cout << endl;
            // вывод информации текущему игроку
            word = word_input_simpel_check(player_arr[id], player_arr, Bank_of_latters, players_ammount, names, id, letters_ammount, last_word);
            if (word == "0")
            {
                player_arr[id].last_word_of_player = "0";
                cout << endl << "                                                                   ...пропуск хода..." << endl;
                if (letters_ammount == 0)
                    player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
                break;
            }
            //пропуск хода

            bool check = big_check(word, names, players_ammount, id, player_arr[id]);
            if (check)
            {
                score.points[id] += scoring_of_players(check, word, last_word);
                cout << "\n   Слово принято\n                                                               Ваши баллы сейчас: " << score.points[id] << " (+" << scoring_of_players(check, word, last_word) << ") " << endl;
                last_word = word;
                player_arr[id].last_word_of_player = word;
                remove_letters(word, player_arr[id].letters);
                if (letters_ammount == 0)
                    player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
                break;
            }
            else
            {
                if (big_check1(word, player_arr[id]))
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "   \nСлово было введено неверное\n                                                                  Ваши баллы сейчас: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    if (letters_ammount == 0)
                        player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
                    break;
                }
                else
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "\n                                                   В следующий раз введите слово только из своих букв\n";
                    cout << "   \nСлово неверное\n                                                                Ваши баллы сейчас: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    if (letters_ammount == 0)
                        player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
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
            cout << endl << "                                                                Все игроки пропустили ход\n" << endl;
            printBorder(width);
            cout << "\n\n\n\n\n\n";
            cout << "   Нажмите Enter для продолжения... ";
            break;
        }
        step++;
    }
    return score;
    system("pause");
    cin.ignore();
    clearScreen();
}
//убрал cin.ignore в конце
void Resaults_screen(Statistics full_stat, short ammount_of_players) {
    cin.ignore();
    clearScreen();
    const int width = 156;
    short max_score_id[7]{ 0,-1,-1,-1,-1,-1,-1 }, nulevue{}, max_points = full_stat.points[0], sovpodenie{ 1 }, counter{ 1 };
    for (unsigned short i{ 1 }; i < ammount_of_players; i++) {
        if (full_stat.points[max_score_id[0]] < full_stat.points[i]) {
            for (unsigned short j{}; j < counter; j++) {
                max_score_id[j] = -1;
            }
            max_score_id[0] = i;
            counter = 1;
            sovpodenie = 1;
        }
        else if (max_points == full_stat.points[i]) {
            max_score_id[counter] = i;
            sovpodenie++;
            counter++;
        }
        else if (full_stat.points[i] == 0)
            nulevue++;
    }
    printBorder(width);
    cout << endl;
    cout << setw(87) << "~~~~~ ПОБЕДА! ~~~~~ \n\n";
    printBorder(width);
    cout << "\n\n\n\n\n";   ///////////////////////////////////////////////////////////////////
    if (nulevue == ammount_of_players || sovpodenie == ammount_of_players) {
        cout << setw(96) << "*** Игра завершилась ничьей ***\n\n\n";
    }
    else if (counter == 1)
        cout << setw(87) << "*** Игра завершилась, победил " << full_stat.names[max_score_id[0]] << " ***\n\n";
    else {
        cout << setw(87) << "*** Игра завершилась, победили: " << full_stat.names[max_score_id[0]] << ", " << full_stat.names[max_score_id[1]];
        cout << " ***\n\n\n";
        if (ammount_of_players > 2) {
            for (unsigned short i{ 2 }; i < ammount_of_players; i++) {
                if (max_score_id[i] != -1) {
                    cout << ", " << full_stat.names[max_score_id[i]];

                }
            }
        }
    }
    for (int i{}; i < ammount_of_players; i++) {
        cout << setw(60) << i + 1 << ". Игрок " << full_stat.names[i] << " набрал: " << full_stat.points[i] << " балла(-ов)\n";
    }
    cout << "\n\n\n\n\n";
    /*cin.ignore(1);*/
    system("pause");
    clearScreen();
}

int bonuses(Player player, string word, short letter_ammount, bool player_with_letters, bool already_dumb) {
    const int width = 156;
    if (word.empty()) {
        if (player.bonuces == 0 && letter_ammount >= 5 && player_with_letters) {
            cout << endl << endl;
            cout << setw(90) << " У вас есть 2 бонуса: \n\n"
                << "                                                                      1. 50 на 50 \n\n "
                << "                                                                    2. Помощь друга \n\n ";
        }
        else if (player.bonuces == 0 && player_with_letters) {
            cout << endl;
            cout << "                                          У вас остался бонус 'Помощь друга', если хотите его использовать введите 2.\n\n";
        }
        else if (player.bonuces == 1) {
            cout << endl;
            cout << "                                          У вас остался бонус 'Помощь друга', если хотите его использовать введите 2.\n\n";
        }
        else if (player.bonuces == 2 && letter_ammount >= 5) {

            cout << endl;
            cout << "                                             У вас остался бонус 50 на 50. Введите 1 если хотите воспользоваться\n\n";
        }
        else {
            cout << endl;
            cout << "   У вас не осталось бонусов\n";
            cout << endl;
        }
        return 0;
    }

    else {
        int counter{};
        for (char c : word) {
            if (!(c >= 'А' && c <= 'я') && !(c == 'ё') && !(c == 'Ё') && isdigit(c)) {
                counter++;
            }
        }
        if (counter == word.length()) {
            switch (stoi(word)) {
            case 1:
                if (letter_ammount != 0)
                    return 1;
            case 2:
                if (player_with_letters)
                    return 2;
            default:
                return 3;
            }
        }
    }
}
void fifty_fifty(Player& player, char letter_bank[], string last_word, short id, Statistics names) {
    string letters;
    bool stupid_igrok = true;
    short counter{};
    char player_letters[10]{};


    while (stupid_igrok) {
        cout << endl;
        cout << "                                Напишите 5 букв(без пробелов и знаков припенанию) из своего набора, которые вы хотите заменить:\n ";
        cout << setw(73) << " ";
        getline(cin, letters);
        for (int i = 0; i < 10; i++)        // буферизация букв игрока
        {
            player_letters[i] = player.letters[i];
        }
        if (letters.length() == 5)
        {
            for (unsigned short i{}; i < 5; i++) {
                for (unsigned short j{}; j < 10; j++)
                {
                    if (letters[i] == player_letters[j]) {
                        counter++;
                        player_letters[j] = '-';
                        break;
                    }
                }
                if (counter == letters.length())
                    stupid_igrok = false;
            }
        }
    }
    clearScreen();
    /* for (unsigned short i{}; i < 5; i++) {
         letters[i] = player.letters[i];
     }*/
    for (char c : letters) {
        for (unsigned short i{}; i < 10; i++) {
            if (c == player.letters[i]) {
                player.letters[i] = '-';
                break;
            }
        }
    }
    add_letters_to_player(player.letters, letter_bank);
    const int width = 156;
    vuvod_igroka(false, names, id, last_word);   ////////////////////////////////////////////////////////////////////////////////
    cout << endl;
    cout << endl;
    cout << setw(90) << "***** Ваши буквы ***** \n\n" << setw(40) << "   |   ";
    for (int i = 0; i < 10; i++)
    {
        cout << player.letters[i] << "  |    ";

    }
    cout << "\n\n";
}
void spizdi_letter(Player& player, Player player_arr[], short player_ammount, Statistics score, short player_id, string last_word) {
    short id{}, my_letter_id{}, his_letter_id{};
    string my_letter{}, his_letter{}, id_str{};
    char buffer{};
    const int width = 156;
    for (unsigned short i{}; i < player_ammount; i++) {
        if (i != player_id) {
            cout << endl;
            cout << "   Игрок " << i + 1 << ": " << score.names[i] << "\n";
            cout << setw(10) << "Баллы: " << score.points[i] << "\n";
            cout << setw(10) << "Буквы: ";
            for (int j = 0; j < 10; j++)
            {
                cout << player_arr[i].letters[j] << " | ";
            }
            cout << endl;
        }
    }
    while (true) {
        cout << endl;
        cout << "                                                  Введите номер игрока с которым хотите поменяться буквой:\n ";
        cout << setw(76) << " ";
        getline(cin, id_str);
        if (id_str.length() == 1 && !((id_str[0] >= 'а' && id_str[0] <= 'я') || (id_str[0] == 'ё')) && isdigit(id_str[0])) {
            id = stoi(id_str);
            if (id > 0 && id <= player_ammount && id != player_id + 1 && !player_arr[id].bank_null) { ///////////////////////////////////////////
                id--;
                break;
            }
        }
    }
    while (true) {
        cout << endl;
        cout << "                                                        Введите букву которую хотите поменять у себя:\n ";
        cout << setw(76) << " ";
        getline(cin, my_letter);
        if (my_letter.length() == 1) {
            bool correct_letter = false;
            for (unsigned short i{}; i < 10; i++) {
                if (player.letters[i] == my_letter[0]) {
                    my_letter_id = i;
                    correct_letter = true;
                    break;
                }
            }
            if (correct_letter)
                break;
        }
    }
    while (true) {
        cout << endl;
        cout << "                                            Введите букву которую хотите поменять у выбранного вами пользователя:\n ";
        cout << setw(76) << " ";
        getline(cin, his_letter);
        if (his_letter.length() == 1) {
            bool correct_letter = false;
            for (unsigned short i{}; i < 10; i++) {
                if (player_arr[id].letters[i] == his_letter[0]) {
                    his_letter_id = i;
                    correct_letter = true;
                    break;
                }
            }
            if (correct_letter)
                break;
        }
    }
    clearScreen();
    buffer = his_letter[0];
    player_arr[id].letters[his_letter_id] = my_letter[0];
    player.letters[my_letter_id] = buffer;
    cout << "\n";
    vuvod_igroka(false, score, player_id, last_word);
    cout << "\n";
    cout << setw(90) << "***** Ваши буквы ***** \n\n" << setw(40) << "  |   ";
    for (int i = 0; i < 10; i++)
    {
        cout << player.letters[i] << "  |    ";

    }
    cout << "\n\n";
}
void alphabet_zapolnenie(char massive_alphabet[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int Bank_size = 173;
    char buffer_alphabet[Bank_size];
    char c[] = { 'б','в','г','д','ж','з','й','к','л','м','н','п','р','с','т','ф','х','ц','ч','ш','щ','ь','ъ' };
    char g[] = { 'а','е','ё','и','о','у','ы','э','ю','я' };
    short counter{};
    for (unsigned short i{ 1 }; i < 13; i++) {
        if (i % 3 == 0) {
            for (unsigned short j{}; j < 23; j++) {
                buffer_alphabet[counter] = c[j];
                counter++;
            }
        }
        else {
            for (unsigned short j{}; j < 10; j++) {
                buffer_alphabet[counter] = g[j];
                counter++;
            }
        }
    }
    //заполнение общего алфавита рандомно
    srand(time(0));
    int letter_ammount = Bank_size - 1;
    for (int i = 0; i < Bank_size - 2; i++)
    {
        massive_alphabet[i] = buffer_alphabet[rand() % letter_ammount];
        //сортировка банка
        for (int j = 0; j < Bank_size - 1; j++)
        {
            if (buffer_alphabet[j] == '-')
            {
                for (int k = j; k < Bank_size - 1; k++)
                {
                    buffer_alphabet[k] = buffer_alphabet[k + 1];
                }
            }
        }
        letter_ammount--;
    }

}
//Переписано по плану
void add_letters_to_player(char pl_letters[], char Bank[])
{
    const int Bank_size = 173;
    for (int i = 0; i < 10; i++)
    {
        if (pl_letters[i] == '-')
        {
            /*cout << "\nEnter\n" << i << endl;*/
            for (int j = 0; j < Bank_size - 1; j++)
            {
                if (Bank[j] != '-')
                {
                    /*cout << "removed" << j << " " << Bank[j] << endl;*/
                    pl_letters[i] = Bank[j];
                    Bank[j] = '-';
                    break;
                }
            }
        }
    }
}
string word_input_simpel_check(Player& player, Player player_arr[], char letter_bank[], short player_ammount, Statistics score, short player_id, short letter_ammount, string last_word) {
    string user_word{};
    const int width = 156;
    bool check_complited = false, already_dumb = false, players_with_letters = true;
    short without_numb{};
    for (unsigned short i{}; i < player_ammount; i++) {
        if (i != player_id && player_arr[i].bank_null) {
            without_numb++;
        }
    }
    if (without_numb == player_ammount - 1) {
        players_with_letters = false;
    }
    while (!check_complited) {
        user_word = "";
        bonuses(player, user_word, letter_ammount, players_with_letters, already_dumb);
        if (!already_dumb && player.bonuces != 3) {
            cout << "                                           Введите слово, составленное из ваших букв, или воспользуйтесь бонусом:\n\n ";
            cout << " ";
        }
        else if (already_dumb && player.bonuces != 3)
            cout << "                                            Введите слово, составленное из ваших букв, или воспользуйтесь бонусом: ";
        else
            cout << setw(93) << "Введите слово, составленное из ваших букв: \n\n";
        cout << setw(73) << " ";
        getline(cin, user_word);
        if (user_word.empty()) {
            return "0";
        }
        switch (bonuses(player, user_word, letter_ammount, players_with_letters, already_dumb)) {
        case 1:
            if (player.bonuces == 0) {
                player.bonuces = 1;
                fifty_fifty(player, letter_bank, last_word, player_id, score);
            }
            else if (player.bonuces == 0 && !players_with_letters) {
                player.bonuces = 3;
                fifty_fifty(player, letter_bank, last_word, player_id, score);
            }
            else if (player.bonuces == 2) {
                fifty_fifty(player, letter_bank, last_word, player_id, score);
                player.bonuces = 3;
            }
            continue;
        case 2:
            if (player.bonuces == 0) {
                player.bonuces = 2;
                spizdi_letter(player, player_arr, player_ammount, score, player_id, last_word);
            }
            else if (player.bonuces == 0 && letter_ammount == 0) {
                player.bonuces = 3;
                spizdi_letter(player, player_arr, player_ammount, score, player_id, last_word);
            }
            else if (player.bonuces == 1) {
                spizdi_letter(player, player_arr, player_ammount, score, player_id, last_word);
                player.bonuces = 3;
            }
            continue;
        case 3:
            continue;
        }
        for (char c : user_word) {
            if (user_word.length() > 10) {
                cout << endl;
                cout << setw(110) << "Слово должно состоять из не более чем 10-ти букв \n\n";
                already_dumb = true;
                break;
            }
            else if (!(c >= 'а' && c <= 'я') /*&& !(c == 'Ё')*/ && !(c == 'ё')) {
                cout << "Введите слово без пробелов и только строчными русскими буквами: ";
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
                word[j] = '-';
                letters_bank[i] = '-';
                break;

            }
        }
    }
}
//Переписано по плану
bool opros_players_about_new_word(string word, Statistics names, short player_ammount, short id) {
    {
        int count_of_plus = { 0 };
        string answer;
        for (int i = 0; i < player_ammount; i++)
        {
            if (i != id)
            {
                cout << "Игрок " << names.names[i] << " согласны ли вы с тем что слово " << word << " должно войти в словарь и засчитаться игроку " << names.names[id] << ": ";
                getline(cin, answer);
                if (answer == "да" or "+" or "Да")
                {
                    count_of_plus += 1;
                }
                else if (answer == "нет" or "-" or "Нет")
                {
                    return false;
                    break;
                }
                else
                {
                    cout << "Введенно неккоректное значение пожалуйста переголосуйте " << endl;
                    i--;
                }
            }
        }
        if (count_of_plus == player_ammount - 1);
        {
            ofstream out("user_words.txt", ios::app);
            out << word << "\n";
            return true;
        }
    }
    string answ{};
    while (true) {
        cout << endl;
        cout << setw(105) << "Ситаете ли вы, что слово было правильно правильно(да/нет):  ";
        cout << setw(127) << " ";
        getline(cin, answ);
        if (answ == "да") {
            ofstream fin;
            fin.open("user_words.txt", ios::app);
            fin << word << "\n";
            fin.close();
            return true;
        }
        else if (answ == "нет")
            return false;
    }
}
//Переписано по плану
bool big_check(string user_word, Statistics names, short player_ammount, short id, Player player) {
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
        string stroka{};
        if (user_word[0] >= 'а' && user_word[0] < 'з') {
            fin.open("russian1.txt");
            while (getline(fin, stroka)) {
                if (stroka == user_word)
                {
                    fin.close();
                    return true;
                }
            }
            fin.close();
        }
        else if (user_word[0] >= 'з' && user_word[0] < 'м') {
            fin.open("russian2.txt");
            while (getline(fin, stroka)) {
                if (stroka == user_word)
                {
                    fin.close();
                    return true;
                }
            }
            fin.close();
        }
        else if (user_word[0] >= 'м' && user_word[0] < 'п') {
            fin.open("russian3.txt");
            while (getline(fin, stroka)) {
                if (stroka == user_word)
                {
                    fin.close();
                    return true;
                }
            }
            fin.close();
        }
        else if (user_word[0] >= 'п' && user_word[0] <= 'я') {
            fin.open("russian4.txt");
            while (getline(fin, stroka)) {
                if (stroka == user_word)
                {
                    fin.close();
                    return true;
                }
            }
            fin.close();
        }

        fstream file2;
        file2.open("user_words.txt");

        while (getline(file2, stroka))
        {

            // if (out[0] == user_word[0])
             //{
            if (user_word == stroka)
            {
                file2.close();
                return true;
            }

            // }
        }
        file2.close();
        return opros_players_about_new_word(user_word, names, player_ammount,id);

    }
    else
        return false;
}
//укооченная версия
bool big_check1(string user_word, Player player) {
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
                player_letters[i] = '-';
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