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
    char letters[10]{' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    string last_word = " ";
    int points = 0;
    string name;
    bool skip_enter = false;
    int bonus50 = 1;
    int bonusswap = 1;
};


Player players[6];
char massive_alphabet[172];
int i = { 0 };
int main_menu_otvet;


void enter_names(Player players[], int count_of_players);
int getRandomNumber(int i, int old_time_random); // Функция для получения случайных элементов которые используется для случайного взятия букв из банка букв
void alpha_filling(char massive_alphabet[]); // Заполняет банк букв
void getting_letters(Player players[], int now_player); // Обновляет список букв игроку
void play(); // Основная функция игры
void enter_words(Player players[], int now_player, int count_of_players); // Функция ввода слова игрока 
bool check_correct_answer(Player player[], int i, int count_of_players); // Проверяет существование такого слова в списке слов и вынесенея вопроса об существовании слова если такого слова не было найдено в списке возможных слов также идёт проверка на то были ли использованы буквы из букв игрока
void scoring_of_players(Player players[], int now_player, bool correct_answer, string answer_previous_player); // Присвоение очков игроку
bool opros_players_about_new_word(Player players[], int count_players, int now_player); // Опрос игроков о добавлении нового слова в список слов
void bonus5050(Player players[], int now_player, int count_of_players); // Игрок выбирает половину букв которые ему нужно заменить на новые буквы из словаря
bool bonus_swap_char(Player players[], int now_player, int count_of_players); // Игрок обменивается буквой с другим игроком
bool check_end_game(Player players[], int count_of_players); // Проверяет пропустили ли ходы все игроки и если да то завершает программу

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
        else
        {
            continue;
        }
    }
}


void play()
{
    int kol_players;
    cout << "Введите количество игроков: ";
    cin >> kol_players;
    alpha_filling(massive_alphabet);
    enter_names(players, kol_players);
    while (check_end_game(players, kol_players) == false)
    {
        for (int now_player = 0; now_player < kol_players; now_player++)
        {
            getting_letters(players, now_player);
        }
        for (int now_player = 0; now_player < kol_players; now_player++)
        {
            enter_words(players, now_player, kol_players); // Ввод слова
            if (now_player == 0)
            {
                scoring_of_players(players, now_player, check_correct_answer(players, now_player, kol_players), players[kol_players - 1].last_word);
            }
            else
            {
                scoring_of_players(players, now_player, check_correct_answer(players, now_player, kol_players), players[now_player - 1].last_word);
            }
            cout << "Количество очков игрока " << players[now_player].name << " равно " << players[now_player].points << endl << endl;
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
    int time_random;
    if (i == 0)
        srand(time(0));
    time_random = rand();
    return time_random % 172;
}


void alpha_filling(char massive_alphabet[])
{
    char c[23] = { 'б','в','г','д','ж','з','й','к','л','м','н','п','р','с','т','ф','х','ц','ч','ш','щ','ь','ъ' };
    char g[10] = { 'а','е','ё','и','о','у','ы','э','ю','я' };
    short counter{};
    for (unsigned short i{ 1 }; i < 13; i++) {
        if (i % 3 == 0) {
            for (unsigned short j{}; j < 23; j++) {
                massive_alphabet[counter] = c[j];
                counter++;
            }
        }
        else {
            for (unsigned short j{}; j < 10; j++) {
                massive_alphabet[counter] = g[j];
                counter++;
            }
        }
    }
}


void getting_letters(Player players[], int now_player)
{
    int intermediate_value = {};
    int old_time_random = 0;
    for (int i{}; i < 10; i++)
    {
        if (players[now_player].letters[i] == ' ')
        {
            intermediate_value = getRandomNumber(i, old_time_random);
            old_time_random = intermediate_value;
            if (massive_alphabet[intermediate_value] != ' ')
            {
                players[now_player].letters[i] = massive_alphabet[intermediate_value];
                massive_alphabet[intermediate_value] = ' ';
            }
            else
            {
                i--;
            }
        }
    }
}


void enter_words(Player players[], int now_player, int count_of_players)
{
    string nothing = "";
    cout << "Игрок под номером " << now_player + 1 << " (" << players[now_player].name << ") попробуйте составить слово из представленных букв, если вы не можете это сделать нажмите на пропуск хода (ничего не вводите) " << endl;
    cout << "Далее представлены ваши буквы: ";
    for (int j = 0; j < 10; j++)
    {
        cout << players[now_player].letters[j] << ' ';
    }
    cout << endl;
    if (players[now_player].bonus50 == 1)
    {
        cout << "Вы имеете бонус замены половины букв (-2 балла), чтобы его активировать введите '50'" << endl;
    }
    if (players[now_player].bonusswap == 1)
    {
        cout << "Вы имеете бонус обмена 1 буквы с любым игроком, чтобы его активировать введите 'обменбукв'" << endl;
    }
    cin >> players[now_player].last_word;
    if (players[now_player].last_word == "50" and players[now_player].bonus50 == 1)
    {
        bonus5050(players, now_player, count_of_players);
    }
    else if (players[now_player].last_word == "обменбукв")
    {
        bonus_swap_char(players, now_player, count_of_players);
    }
    else if (players[now_player].last_word == nothing)
    {
        cout << "Вы пропустили ход " << endl;
        players[now_player].skip_enter = true;
    }
}


bool check_correct_answer(Player player[], int now_player, int count_of_players)
{
    int counter{};
    int count_answer, count_good_chars = { 0 };
    string stroka, answer;
    fstream fin;
    fin.open("russian.txt");
    answer = players[now_player].last_word;
    count_answer = players[now_player].last_word.length();
    for (int k = 0; k < count_answer; k++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (players[now_player].letters[j] == answer[k])
            {
                count_good_chars += 1;
                players[now_player].letters[j] = ' ';
                answer[k] = '!';
            }
        }
    }
    if (count_answer <= count_good_chars)
    {
        while (getline(fin, stroka))
        {
            if (stroka == player[now_player].last_word)
            {
                return true;
            }
        }
        if (opros_players_about_new_word(players, count_of_players, now_player) != true)
        {
            cout << "Всенародным голосованием слово " << player[now_player].last_word << " не было принято ";
            return false;
        }
        else
            return true;
    }
    else
    {
        cout << "Буквы в слове не соответствуют буквам в словаре игрока" << endl;
        return false;
    }
}


void scoring_of_players(Player players[], int now_player, bool correct_answer, string answer_previous_player)
{
    if (correct_answer == true)
    {
        if (players[now_player].last_word[0] == answer_previous_player[answer_previous_player.length() - 1])
        {
            cout << "Количество ваших очков стало увеличилось на " << players[now_player].last_word.length() * 2 << endl;
            players[now_player].points += players[now_player].last_word.length() * 2;
        }
        else
        {
            
            players[now_player].points += players[now_player].last_word.length();
            cout << "Количество ваших очков стало увеличилось на " << players[now_player].last_word.length() << endl;
        }
    }
    else
    {
        cout << "Количество ваших очков стало уменьшилось на " << players[now_player].last_word.length() << endl;
        players[now_player].points += players[now_player].last_word.length() * (-1);
    }
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


void bonus5050(Player players[], int now_player, int count_of_players)
{
    string answer;
    cout << "Перечислите без пробелов набор букв (5 штук) которые хотите заменить: ";
    cin >> answer;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (players[now_player].letters[i] == answer[j])
                players[now_player].letters[i] = ' ';
        }
    }
    players[now_player].points -= 2;
    players[now_player].bonus50 -= 1;
    getting_letters(players, now_player);
    cout << "\033[2J\033[1;1H"; // почистить консоль
    enter_words(players, now_player, count_of_players);
}


bool bonus_swap_char(Player players[], int now_player, int count_of_players)
{
    string answer;
    char answer1, answer2;
    for (int i = 0; i < count_of_players; i++)
    {
        if (i != now_player)
        {
            cout << players[i].name << " имееет буквы: ";
            for (int j = 0; j < 10; j++)
                cout << players[i].letters[j] << " ";
            cout << endl;
        }
    }
    while (true)
    {
        int index_of_player = 8;
        cout << "Введите игрока (имя или номер) с которым вы хотите обменятся буквами: ";
        cin >> answer;
        for (int i = 0; i < count_of_players; i++)
        {
            if (answer == players[i].name or (i + 1))
                index_of_player = i;
        }
        if (index_of_player != 8)
        {
            cout << "Выберете свою букву которую вы хотите изменить: ";
            cin >> answer1;
            cout << "Выберите букву своего товарища которую вы хотите изъять: ";
            cin >> answer2;
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if (players[now_player].letters[j] == answer1 and players[index_of_player].letters[k] == answer2)
                    {
                        swap(players[now_player].letters[j], players[index_of_player].letters[j]);
                        players[now_player].bonusswap -= 1;
                        cout << "\033[2J\033[1;1H"; // почистить консоль
                        enter_words(players, now_player, count_of_players);
                        return true;
                    }
                }
            }
        }
    }
}


bool check_end_game(Player players[], int count_of_players)
{
    int exit_counts = 0;
    for (int i = 0; i < count_of_players; i++)
    {
        if (players[i].skip_enter == true)
            exit_counts += 1;
    }
    if (exit_counts == count_of_players)
        return true;
    else
        return false;
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