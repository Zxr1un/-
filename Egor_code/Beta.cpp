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
����� ��� ���������

������ ����� ������ 173 ��� ������ ������������ (��������� ������ ������ ) ��� ������ ������� ����� ����� ��������� ����� ��������� Bank_size
��������:
1) ���������� ��������
2) Big_check � ����� ������� � ���� ����� (������ � ������ ������� � ������� ��������)
3) �������� ��������� � end_screen � �����
4) ��������� ����������� (������ ������ ������ � ���������� �������� (����� ���� ��������� ������� ���� � game))

*/

struct Player
{
    /*int id;*/
    char letters[10] = { '-', '-',  '-', '-', '-', '-', '-', '-', '-', '-' };
    int bonuces = 0;
    string last_word_of_player = "0";
    bool bank_null = false;
};

struct Statistics //�������� �������� ��� ���� ���������, �� ������ ����� �����������
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
        if (choice.length() == 1 && !((choice[0] >= '�' && choice[0] <= '�') || (choice[0] == '�') || (choice[0] == '�') || !isdigit(choice[0]))) {
            switch (stoi(choice)) {
            case 1:
                printBorder(width);
                cout << endl;
                cout << setw(88) << "�������� ����...\n\n";
                printBorder(width);
                Start();
                break;
            case 2:
                Rules();
                break;
            case 3:
                if (confirmExit()) {
                    cout << "�����...\n";
                    return 0; // ����� �� ���������
                }
                break;
            default:
                cout << "�������� �����. ����������, ���������� �����.\n";
            }
        }
    } while (true);

    return 0;
}

void vuvod_igroka(bool first_round, Statistics names, short id, string last_word) {
    const int width = 156;
    printBorder(width);
    cout << endl;
    cout << setw(79) << "~~~ ��� ������: " << names.names[id] << " ~~~\n\n";
    printBorder(width);
    /* if (!first_round)*/
    cout << "\n\n    ��������� �����: " << last_word;
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
        cout << setw(90) << "�� ����� ������ �����?\n\n";
        cout << setw(89) << "��             ���\n";
        cout << setw(77) << " ";
        getline(cin, confirmation);

        clearConsole();

        if (confirmation == "��")
            return true;
        else if (confirmation == "���")
            return false;
        else
            cout << "�������� �����. ����������, ���������� �����.\n";
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
    cout << setw(90) << "~~~~~��������~~~~~\n\n";
    printBorder(width);
    cout << endl;
    cout << setw(92) << "~~~ 1. ������ ����  ~~~\n\n";
    cout << setw(94) << "~~~ 2. ��������� ������� ~~~\n\n";
    cout << setw(88) << "~~~ 3. ����� ~~~\n\n\n";
    cout << setw(84) << "��������: ";
}


void printHeading()
{
    const int width = 156;

    printBorder(width);
    cout << setw(90) << "����� ���������� � ���� ������" << endl;
    printBorder(width);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << "                                                ______    _____    _    _   _____    _____  _______   ______        \n";
    cout << "                                               | ____|   |  __ \\  | |  | | |  __ \\  |  _  ||__   __| |  ____|       \n";
    cout << "                                               | |__     | |__) | | |  | | | |  | |   | |     | |    | |__          \n";
    cout << "                                               |  __|    |  _  /  | |  | | | |  | |   | |     | |    |  __|         \n";
    cout << "                                               | |____   | | \\ \\  | |__| | | |__| |  _| |_    | |    | |____        \n";
    cout << "                                               |______|  |_|  \\_\\  \\____/  |_____/  |_____|   |_|    |______|       \n";

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    cout << setw(90) << "����������..." << endl;
    printBorder(width);

    cin.ignore();
    clearScreen();
}

void Rules() {
    const int width = 156;

    printBorder(width);
    cout << setw(90) << "~~~~~�������~~~~~\n\n";

    cout << "                                    || 1. ���� ����:                                                                         ||\n";
    cout << "                                    ||    - ������� ��� ����� ������ �����, ��������� ����� �� ������� ����.                 ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 2. ������ ����:                                                                       ||\n";
    cout << "                                    ||    - ������ ����� �������� �� 10 ��������� ��������� ������� ����.                    ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 3. ��� ������:                                                                        ||\n";
    cout << "                                    ||    - ����� ���������� ����� �� ����� ����.                                            ||\n";
    cout << "                                    ||    - ���� ����� ���������� �����, �� ������ ������������ ����,                        ||\n";
    cout << "                                    ||      ������ ���������� ���� � �����.                                                  ||\n";
    cout << "                                    ||    - ���� ����� ������ ���������� � ��� �� �����, �� �������                          ||\n";
    cout << "                                    ||      ������������� ����� ����������� ������, �� ����������                            ||\n";
    cout << "                                    ||      ����� �������������.                                                             ||\n";
    cout << "                                    ||    - ����� ���������� �������, ���� � ���� ������ �����, ��                           ||\n";
    cout << "                                    ||      �������� � ����� ���� ������.                                                    ||\n";
    cout << "                                    ||    ����������:                                                                        ||\n";
    cout << "                                    ||    - ���� � �� �� ����� �� ������ ������ ������������ ��������� ���.                  ||\n";
    cout << "                                    ||    - ���� ����� ���������� �������, �� �� ����� ����� �����                           ||\n";
    cout << "                                    ||      ���������� ����� �����, ������ ���������� ���� � �����.                          ||\n";
    cout << "                                    ||    - ����� ����, ��� ������ ����� ������ ���� ���, ��� ����������� ����������� �����. ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 4. ������:                                                                            ||\n";
    cout << "                                    ||    - �50-��-50� -- ����� ����� ����������� 5 ����, ������� �� ����� �� ��������.      ||\n";
    cout << "                                    ||    ����������:                                                                        ||\n";
    cout << "                                    ||   - ���������� ����� ��������� �����������, � ����� �����                             ||\n";
    cout << "                                    ||      ������ ����������� �� 2.                                                         ||\n";
    cout << "                                    ||    - ������� ������ -- ����� ����� �������� ���������� ���                            ||\n";
    cout << "                                    ||      ����� �� ������ ������ �� ��������������� ��� ����� �� ������ ���� ���������.    ||\n";
    cout << "                                    ||    ����������:                                                                        ||\n";
    cout << "                                    ||    - �������� ������� ������ �� ��������� � ����� ����� �� �����������.               ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 5. ��������� ����:                                                                    ||\n";
    cout << "                                    ||    - ���� �������������, ����� ��� ������ ��������� ���.                              ||\n";
    cout << "                                    ||                                                                                       ||\n";
    cout << "                                    || 6. ������:                                                                            ||\n";
    cout << "                                    ||    - ���������� ��� �����, ������� ������ ������� ����� ������.                       ||\n";
    cout << "                                    ||                                                                                       ||\n\n";

    cout << setw(90) << "~~~~~������� ����!~~~~~\n";
    printBorder(width);
    cout << endl;
    cout << "������� Enter ��� ����������� � ����...";
    cin.ignore();
    clearScreen();
}


void Start() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int players_ammount = input_number_of_players(); // ���������� ������� (�������� ����� � ������ �������, �� ���� ���)
    Statistics score;
    for (unsigned short i{}; i < players_ammount; i++) {
        score.names[i] = input_players_name(i, score);
    }
    score = game(players_ammount, score);
    Resaults_screen(score, players_ammount);
}

//������� ��� ����� ��� �������
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
            cout << setw(80) << "*** �����: " << which_player + 1 << " ***" << "\n        ������� ��� ���(��� ������ ���������� � ��������): ";
        }
        else {
            cout << setw(80) << "*** �����: " << which_player + 1 << " ***" << "\n\n        ������� ��� ���(��� ������ ���������� � ��������) � �� �������� ����� ������ ������� : ";

        }
        getline(cin, name);
        if (!name.empty()) {
            for (char c : name) {
                if (!((c >= '�' && c <= '�') || (c == '�') || (c == '�')) && (ispunct(c) || isspace(c))) {
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

// ������� ����� ���-�� �������
int input_number_of_players() {
    string num_of_players{};
    bool not_dumb = false, already_stupid = false;
    while (true) {
        if (!already_stupid)
            cout << "\n        ���������� ������� ���������� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
        getline(cin, num_of_players);
        if (!num_of_players.empty()) {
            if (num_of_players.length() == 1) {
                for (char c : num_of_players) {
                    if ((c >= '�' && c <= '�') || (c == '�') || (c == '�') || !isdigit(c)) {
                        not_dumb = false;
                        already_stupid = true;
                        cout << "\n        ������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
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
                    cout << "\n        ������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
                    cout << endl;
                }
            }
            else {
                already_stupid = true;
                cout << "        ������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
                cout << endl;
            }
        }
        else {
            already_stupid = true;
            cout << "        ������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
            cout << endl;
        }
    }
}

Statistics game(int players_ammount, Statistics names)
{
    const int width = 156;
    Statistics score = names;
    //132
    const int Bank_size = 173; //��� ������������ ����� ���� �� 1 ������ ������
    char Bank_of_latters[Bank_size]{}; // ���� ���� �� �������� �� 4 ����
    for (unsigned short i{}; i < Bank_size; i++) {
        Bank_of_latters[i] = '-';
    }
    alphabet_zapolnenie(Bank_of_latters); // ���������� ����� ����

    Player player_arr[7];
    string last_word = "0"; //����� �������� ��������� �������� �����
    string word;
    bool first_round = true;
    int step = 0; //����� ����

    for (int i = 0; i < players_ammount; i++)
    {
        player_arr[i].last_word_of_player = "1";
    }
    //������������� �������� �������(�� ������ ������� ������ �������� 1, ����� � ������� ��� ���� �� 1 ���)
    while (true)
    {
        for (int i = 0; i < players_ammount; i++)
        {
            add_letters_to_player(player_arr[i].letters, Bank_of_latters);
        } //������ ����� ���� ������� ������ � ������ ����


        int letters_ammount = 0; //������ �������� ���������� ���� � ����� �����
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
        cout << setw(82) << "� ����� ��������: " << letters_ammount << " ����\n\n\n\n\n\n\n\n";
        cout << "        ������� Enter ��� �����������......";

        cin.ignore();
        clearScreen();

        // ��� ������
        while (true)
        {
            int id = (step) % players_ammount;
            vuvod_igroka(first_round, names, id, last_word);
            cout << "\n";
            cout << setw(90) << "****** ���� ����� ****** \n\n" << setw(41) << " | ";
            for (int i = 0; i < 10; i++)
            {
                cout << player_arr[id].letters[i] << "   |   ";
            }
            cout << endl;
            // ����� ���������� �������� ������
            word = word_input_simpel_check(player_arr[id], player_arr, Bank_of_latters, players_ammount, names, id, letters_ammount, last_word);
            if (word == "0")
            {
                player_arr[id].last_word_of_player = "0";
                cout << endl << "                                                                   ...������� ����..." << endl;
                if (letters_ammount == 0)
                    player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
                break;
            }
            //������� ����

            bool check = big_check(word, names, players_ammount, id, player_arr[id]);
            if (check)
            {
                score.points[id] += scoring_of_players(check, word, last_word);
                cout << "\n   ����� �������\n                                                               ���� ����� ������: " << score.points[id] << " (+" << scoring_of_players(check, word, last_word) << ") " << endl;
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
                    cout << "   \n����� ���� ������� ��������\n                                                                  ���� ����� ������: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    if (letters_ammount == 0)
                        player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
                    break;
                }
                else
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "\n                                                   � ��������� ��� ������� ����� ������ �� ����� ����\n";
                    cout << "   \n����� ��������\n                                                                ���� ����� ������: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    if (letters_ammount == 0)
                        player_arr[id].bank_null = check_for_null_bank(player_arr[id].letters, id);
                    break;
                }
            }
        }

        // ��������� �������� �� �����
        int counter_for_skip_end{};
        for (unsigned short i{}; i < players_ammount; i++) {
            if (player_arr[i].last_word_of_player == "0") {
                counter_for_skip_end++;
            }
        }
        if (counter_for_skip_end == players_ammount) {
            cout << endl << "                                                                ��� ������ ���������� ���\n" << endl;
            printBorder(width);
            cout << "\n\n\n\n\n\n";
            cout << "   ������� Enter ��� �����������... ";
            break;
        }
        step++;
    }
    return score;
    system("pause");
    cin.ignore();
    clearScreen();
}
//����� cin.ignore � �����
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
    cout << setw(87) << "~~~~~ ������! ~~~~~ \n\n";
    printBorder(width);
    cout << "\n\n\n\n\n";   ///////////////////////////////////////////////////////////////////
    if (nulevue == ammount_of_players || sovpodenie == ammount_of_players) {
        cout << setw(96) << "*** ���� ����������� ������ ***\n\n\n";
    }
    else if (counter == 1)
        cout << setw(87) << "*** ���� �����������, ������� " << full_stat.names[max_score_id[0]] << " ***\n\n";
    else {
        cout << setw(87) << "*** ���� �����������, ��������: " << full_stat.names[max_score_id[0]] << ", " << full_stat.names[max_score_id[1]];
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
        cout << setw(60) << i + 1 << ". ����� " << full_stat.names[i] << " ������: " << full_stat.points[i] << " �����(-��)\n";
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
            cout << setw(90) << " � ��� ���� 2 ������: \n\n"
                << "                                                                      1. 50 �� 50 \n\n "
                << "                                                                    2. ������ ����� \n\n ";
        }
        else if (player.bonuces == 0 && player_with_letters) {
            cout << endl;
            cout << "                                          � ��� ������� ����� '������ �����', ���� ������ ��� ������������ ������� 2.\n\n";
        }
        else if (player.bonuces == 1) {
            cout << endl;
            cout << "                                          � ��� ������� ����� '������ �����', ���� ������ ��� ������������ ������� 2.\n\n";
        }
        else if (player.bonuces == 2 && letter_ammount >= 5) {

            cout << endl;
            cout << "                                             � ��� ������� ����� 50 �� 50. ������� 1 ���� ������ ���������������\n\n";
        }
        else {
            cout << endl;
            cout << "   � ��� �� �������� �������\n";
            cout << endl;
        }
        return 0;
    }

    else {
        int counter{};
        for (char c : word) {
            if (!(c >= '�' && c <= '�') && !(c == '�') && !(c == '�') && isdigit(c)) {
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
        cout << "                                �������� 5 ����(��� �������� � ������ ����������) �� ������ ������, ������� �� ������ ��������:\n ";
        cout << setw(73) << " ";
        getline(cin, letters);
        for (int i = 0; i < 10; i++)        // ����������� ���� ������
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
    cout << setw(90) << "***** ���� ����� ***** \n\n" << setw(40) << "   |   ";
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
            cout << "   ����� " << i + 1 << ": " << score.names[i] << "\n";
            cout << setw(10) << "�����: " << score.points[i] << "\n";
            cout << setw(10) << "�����: ";
            for (int j = 0; j < 10; j++)
            {
                cout << player_arr[i].letters[j] << " | ";
            }
            cout << endl;
        }
    }
    while (true) {
        cout << endl;
        cout << "                                                  ������� ����� ������ � ������� ������ ���������� ������:\n ";
        cout << setw(76) << " ";
        getline(cin, id_str);
        if (id_str.length() == 1 && !((id_str[0] >= '�' && id_str[0] <= '�') || (id_str[0] == '�')) && isdigit(id_str[0])) {
            id = stoi(id_str);
            if (id > 0 && id <= player_ammount && id != player_id + 1 && !player_arr[id].bank_null) { ///////////////////////////////////////////
                id--;
                break;
            }
        }
    }
    while (true) {
        cout << endl;
        cout << "                                                        ������� ����� ������� ������ �������� � ����:\n ";
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
        cout << "                                            ������� ����� ������� ������ �������� � ���������� ���� ������������:\n ";
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
    cout << setw(90) << "***** ���� ����� ***** \n\n" << setw(40) << "  |   ";
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
    char c[] = { '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�' };
    char g[] = { '�','�','�','�','�','�','�','�','�','�' };
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
    //���������� ������ �������� ��������
    srand(time(0));
    int letter_ammount = Bank_size - 1;
    for (int i = 0; i < Bank_size - 2; i++)
    {
        massive_alphabet[i] = buffer_alphabet[rand() % letter_ammount];
        //���������� �����
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
//���������� �� �����
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
            cout << "                                           ������� �����, ������������ �� ����� ����, ��� �������������� �������:\n\n ";
            cout << " ";
        }
        else if (already_dumb && player.bonuces != 3)
            cout << "                                            ������� �����, ������������ �� ����� ����, ��� �������������� �������: ";
        else
            cout << setw(93) << "������� �����, ������������ �� ����� ����: \n\n";
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
                cout << setw(110) << "����� ������ �������� �� �� ����� ��� 10-�� ���� \n\n";
                already_dumb = true;
                break;
            }
            else if (!(c >= '�' && c <= '�') /*&& !(c == '�')*/ && !(c == '�')) {
                cout << "������� ����� ��� �������� � ������ ��������� �������� �������: ";
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
//���������� �� �����
bool opros_players_about_new_word(string word, Statistics names, short player_ammount, short id) {
    {
        int count_of_plus = { 0 };
        string answer;
        for (int i = 0; i < player_ammount; i++)
        {
            if (i != id)
            {
                cout << "����� " << names.names[i] << " �������� �� �� � ��� ��� ����� " << word << " ������ ����� � ������� � ����������� ������ " << names.names[id] << ": ";
                getline(cin, answer);
                if (answer == "��" or "+" or "��")
                {
                    count_of_plus += 1;
                }
                else if (answer == "���" or "-" or "���")
                {
                    return false;
                    break;
                }
                else
                {
                    cout << "�������� ������������ �������� ���������� ������������� " << endl;
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
        cout << setw(105) << "������� �� ��, ��� ����� ���� ��������� ���������(��/���):  ";
        cout << setw(127) << " ";
        getline(cin, answ);
        if (answ == "��") {
            ofstream fin;
            fin.open("user_words.txt", ios::app);
            fin << word << "\n";
            fin.close();
            return true;
        }
        else if (answ == "���")
            return false;
    }
}
//���������� �� �����
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
        if (user_word[0] >= '�' && user_word[0] < '�') {
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
        else if (user_word[0] >= '�' && user_word[0] < '�') {
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
        else if (user_word[0] >= '�' && user_word[0] < '�') {
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
        else if (user_word[0] >= '�' && user_word[0] <= '�') {
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
//���������� ������
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