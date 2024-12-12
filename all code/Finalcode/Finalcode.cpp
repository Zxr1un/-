#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

struct Player {
    // структура с буквами пользователя, его айдишником, последним словом, и баллы
    int id;
    char letters[10];
    string last_world;
    int points;
};

int intermediate_value = { 0 };

bool checkfile(string search, fstream& fin);
char check_for_user_word(string user_word, Player current_player);
int Main_menu();
void start();
void game();
int end_screen();
void interface_end_screen();
void interface_Main_menu();
void interface_rules();
void interface_start();
void interface_game();
void interface_end_screen();
int normal_command_input(int min_command, int max_command);
int getRandomNumber(int i, int min, int max, int old_time_random);
void alpha_zapolnenie(char massive_alphabet[]);
void getting_letters(int amount_players);

int main()
{
    setlocale(LC_ALL, "russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int status = 1; //значения status: 0--завершение работы 1--нормальная работа
    fstream fin;
    fin.open("russian.txt"); //открытие файла с библиотекой
    int amount_players = 3;
    Player player1, player2, player3, player4;
    getting_letters(amount_players, player1); //Получение букв игроками в зависимости от их количества
    if (amount_players >= 2)
    {
        getting_letters(amount_players, player2);
        if (amount_players >= 3)
        {
            getting_letters(amount_players, player3);
            if (amount_players == 4)
                getting_letters(amount_players, player4);
        }
    }

    while (status == 1)
    {
        status = Main_menu();
        if (status == 0)
        {
            break;
        }

        start();

        game();

        status = end_screen();

    }
    return 0;
}




int getRandomNumber(int i, int old_time_random)
{
    int time_random;
    if (i == 0)
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        time_random = 1 + ltm->tm_sec;
        time_random = ((time_random + 354) * 64 - 74) / 8;
    }
    else
    {
        time_random = ((old_time_random + 354) * 64 - 74) / 8 + 34;
    }
    return time_random % 132;
}

void alpha_zapolnenie(char massive_alphabet[])
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

void getting_letters(int amount_players, Player player)
{
    char massive_alphabet[132];
    alpha_zapolnenie(massive_alphabet);
    int old_time_random = 0;
    for (int i{}; i < 10; i++)
    {
        intermediate_value = getRandomNumber(i, 0, 132, old_time_random);
        old_time_random = intermediate_value;
        if (massive_alphabet[intermediate_value] != 0)
        {
            player.letters[i] = massive_alphabet[intermediate_value];
            massive_alphabet[intermediate_value] = 0;
            cout << i + 1 << " буква в букваре 1 игрока это " << player.letters[i] << endl;
        }
        else
        {
            i--;
        }
    }
    /*if (amount_players >= 2)
    {
        char player_2_chars[10];
        for (int i{}; i < 10; i++)
        {
            intermediate_value = getRandomNumber(i, 0, 132, old_time_random);
            old_time_random = intermediate_value;
            if (massive_alphabet[intermediate_value] != 0)
            {
                player_2_chars[i] = massive_alphabet[intermediate_value];
                massive_alphabet[intermediate_value] = 0;
                cout << i + 1 << " буква в букваре 2 игрока это " << player_2_chars[i] << endl;
            }
            else
            {
                i--;
            }

        }
        if (amount_players >= 3)
        {
            char player_3_chars[10];
            for (int i{}; i < 10; i++)
            {
                intermediate_value = getRandomNumber(i, 0, 132, old_time_random);
                old_time_random = intermediate_value;
                if (massive_alphabet[intermediate_value] != 0)
                {
                    player_3_chars[i] = massive_alphabet[intermediate_value];
                    massive_alphabet[intermediate_value] = 0;
                    cout << i + 1 << " буква в букваре 3 игрока это " << player_3_chars[i] << endl;
                }
                else
                {
                    i--;
                }
            }
            if (amount_players == 4)
            {
                char player_4_chars[10];
                for (int i{}; i < 10; i++)
                {
                    intermediate_value = getRandomNumber(i, 0, 132, old_time_random);
                    old_time_random = intermediate_value;
                    if (massive_alphabet[intermediate_value] != 0)
                    {
                        player_4_chars[i] = massive_alphabet[intermediate_value];
                        massive_alphabet[intermediate_value] = 0;
                        cout << i + 1 << " буква в букваре 4 игрока это " << player_4_chars[i] << endl;
                    }
                    else
                    {
                        i--;
                    }
                }
            }
        }*/
    //}
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
    }
    else
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

//интерфейсы

// метка 

void rules()
{
    interface_rules();
    system("pause");
    system("cls");
}
// правила
int Main_menu()
{
    while (true)
    {
        interface_Main_menu();
        cout << "\nВведите \n 1--Начать партию \n 2--Правила \n 0--Выйти\n";
        int command;
        command = normal_command_input(0, 2);
        if (command == 2)
        {
            system("cls");
            rules();
        }
        else if (command == 0)
        {
            system("cls");
            return command;
        }
        else
        {
            system("cls");
            return command;
        }
        system("cls");

    }

}
// главное меню (начало)
void start()
{
    interface_start();
    system("pause");
    system("cls");
}
// начало игры (ввод количества игроков)
void game()
{
    interface_game();
    system("pause");
    system("cls");
}
// сама игра
int end_screen()
{
    interface_end_screen();
    system("pause");
    cout << "\n Игра закончены. Введите \n 1--Сыграть ещё партейку \n 0--Выйти\n";
    int command;
    command = normal_command_input(0, 1);
    system("cls");
    return command;
}
// конец игры и статистика


int normal_command_input(int min_command, int max_command)
{
    // функция ввода комманд
    // первое значение -- с какой цифры
    // второе значение -- по какую цифру
    //должна вводится числовая комманда
    cout << endl;
    int command;
    cin >> command;
    while (min_command > command or max_command < command)
    {
        cout << "\n\nНеверный ввод. Введите число от " << min_command << " до " << max_command << ": ";
        cin >> command;
    }
    return command;

}
// проверка ввода для команд


//интерфейсы
void interface_line()
{
    cout << "\n\n";
    cout << "========================================================================================================================";
    cout << "\n\n";
}
// просто строка из = на всю консоль
void interface_Main_menu()
{
    interface_line();
    cout << "\n                                            ИГРА \"ЭРУДИТ\" \n";
    interface_line();

}

void interface_rules()
{
    interface_line();
    cout << "\n                                             This is rules \n";
    interface_line();
}

void interface_start()
{
    interface_line();
    cout << "\n                                             This is start \n";
    interface_line();
}

void interface_game()
{
    interface_line();
    cout << "\n                                             This is game \n";
    interface_line();
}

void interface_end_screen()
{
    interface_line();
    cout << "\n                                             This is end \n";
    interface_line();
}


