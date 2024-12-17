#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include <iomanip>
//#include <algorithm>

using namespace std;
/*
����� ��� ���������

����, � � ����� �������� �� ������� � ����� ������ ������� ��������� �������

+� ������� ��������� Statistics (���������� ���� � ����� �������), ����� ����� �� �������� � ��������� ���������� � ����������� �����������

����� big_check2 � ����������, ������ ���� �� �� �������������, � ������� �������� � ������� �����������, �� ��������
���� ����� ��� ������ ������� ��������

������� ������ � ������ ��� �������

*/

struct Player
{
    /*int id;*/
    char letters[10] = { '0', '0',  '0', '0', '0', '0', '0', '0', '0', '0' };
    int bonuces = 0;
    string last_word_of_player = "0";
};

struct Statistics //�������� �������� ��� ���� ���������, �� ������ ����� �����������
{
    int points[7] = { 0,0,0,0,0,0,0 };
    string names[7];
};


int bonuses(Player player, string word, short letter_ammount);
string input_players_name(short which_player, Statistics score);
int input_number_of_players();
void alphabet_zapolnenie(char massive_alphabet[]);
Statistics game(int players_ammount, Statistics names);
void add_letters_to_player(char pl_letters[], char Bank[]);
string word_input_simpel_check(Player& player, Player player_arr[], char letter_bank[], short player_ammount, Statistics score, short player_id, short letter_ammount);
bool big_check(string user_word, Player player);
bool big_check1(string user_word, Player player);
//bool big_check2(string user_word, Player player);
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player);
void remove_letters(string word, char letters_bank[]);
bool opros_players_about_new_word(string word);
void Resaults_screen(Statistics full_stat, short ammount_of_players);
void spizdi_letter(Player& player, Player player_arr[], short player_ammount, Statistics score, short plyer_id);
void fifty_fifty(Player& player, char letter_bank[]);
void maxsc();
void printHeading();
void Rules();
void Menu();
void printBorder(int width);
void clearScreen();
void Start();
bool confirmExit();
void clearConsole();



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

    int choice;

    do {
        Menu();
        cin >> choice;
        cin.ignore();

        clearConsole();

        switch (choice) {
        case 1:
            printBorder(width);
            cout << endl; 
            cout << setw(90) << "�������� ����...\n\n"; 
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
    } while (true);

    return 0;
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

    int confirmation;
    do {
        printBorder(width);
        cout << setw(90) << "�� ����� ������ �����?\n\n";
        cout << setw(89) << "1. ��          2. ���\n";
        cout << setw(77) << " ";
        cin >> confirmation;
        cin.ignore();

        clearConsole();

        switch (confirmation) {
        case 1:
            return true;
        case 2:
            return false;
        default:
            cout << "�������� �����. ����������, ���������� �����.\n";
        }
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
    cout << setw(87) << "~~~ 3. ����� ~~~\n\n\n";
    cout << setw(80) << "��������: ";
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
        if (!stupid_player)
            cout << setw(80) << "*** �����: " << which_player + 1 << " ***" << "\n         ������� ��� ���(��� ������ ���������� � ��������): ";
        else
            cout << setw(80) << "~~~�����: " << which_player + 1 << "!~~~" << "\n\n         ������� ��� ���(��� ������ ���������� � ��������) � �� �������� ����� ������ ������� : ";
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
            cout << "\n     ���������� ������� ���������� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
        getline(cin, num_of_players);
        if (!num_of_players.empty()) {
            if (num_of_players.length() == 1) {
                for (char c : num_of_players) {
                    if ((c >= '�' && c <= '�') || (c == '�') || (c == '�') || !isdigit(c)) {
                        not_dumb = false;
                        already_stupid = true;
                        cout << "\n     ������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
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
                    cout << "\n     ������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
                }
            }
        }
        else {
            already_stupid = true;
            cout << "������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
        }
    }
}

Statistics game(int players_ammount, Statistics names)
{
    const int width = 156;  
    Statistics score = names;
    char Bank_of_latters[132]; // ���� ���� �� �������� �� 4 ����
    for (unsigned short i{}; i < 132; i++) {
        Bank_of_latters[i] = '0';
    }
    alphabet_zapolnenie(Bank_of_latters); // ���������� ����� ����

    Player player_arr[7];
    string last_word = "0"; //����� �������� ��������� �������� �����
    string word;
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
        
        for (int i = 0; i < 132; i++)
        {
            if (Bank_of_latters[i] != '0')
            {
                letters_ammount++;
            }
        }
        cout << "\n� ����� ��������: " << letters_ammount << " ����\n";

        cin.ignore(); 
        clearScreen(); 
        
        // ��� ������
        while (true)
        {
            int id = (step) % players_ammount;
            printBorder(width);
            cout << endl; 
            cout << setw(80) << "~~~��� ������: " << names.names[id] << " ~~~\n\n"; 
            printBorder(width);   
            cout << "\n\n    ��������� �����: " << last_word;
            cout << "\n";
            cout << setw(90) << "****** ���� ����� ***** \n\n" << setw(41) << " | ";
            for (int i = 0; i < 10; i++)
            {
                cout << player_arr[id].letters[i] << "   |   ";
            }
            cout << endl;
            // ����� ���������� �������� ������
            word = word_input_simpel_check(player_arr[id], player_arr, Bank_of_latters, players_ammount, names, id, letters_ammount);
            if (word == "0")
            {
                player_arr[id].last_word_of_player = "0";
                cout << endl << "                                                                   ...������� ����..." << endl;
                break;
            }
            //������� ����

            cout << endl << "before: " << score.points[id] << endl; //������� (������� ������ ���� �� �����)
            bool check = big_check(word, player_arr[id]);
            if (check)
            {

                score.points[id] += scoring_of_players(check, word, last_word);
                cout << "\n����� �������.\n                                                               ���� ����� ������: " << score.points[id] << " (+" << scoring_of_players(check, word, last_word) << ") " << endl;
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
                    cout << "\n����� ���� ������� ��������.\n                                                                  ���� ����� ������: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    break;
                }
                else
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "\n                                                   � ��������� ��� ������� ����� ������ �� ����� ����.\n";
                    cout << "\n����� ��������.\n                                                                ���� ����� ������: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
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
            cout << endl << "��� ���������� ���, ����� ����." << endl;
            break;
        }
        step++;
    }

    system("pause");
    return score;
}

void Resaults_screen(Statistics full_stat, short ammount_of_players) {
    short max_score_id[7]{ -1,-1,-1,-1,-1,-1,-1 }, nulevue{}, max_points = full_stat.points[0], sovpodenie{}, counter{ 1 };
    max_score_id[0] = 0;
    for (unsigned short i{ 1 }; i < ammount_of_players; i++) {
        if (full_stat.points[max_score_id[0]] < full_stat.points[i]) {
            for (unsigned short j{}; j < counter; j++) {
                max_score_id[j] = -1;
            }
            max_score_id[0] = i;
            counter = 1;
        }
        else if (max_points == full_stat.points[i]) {
            max_score_id[counter] = i;
            counter++;
        }
        else if (full_stat.points[i] == 0)
            nulevue++;
    }
    if (nulevue == ammount_of_players)
        cout << "���� ����������� ������.";
    else if (counter == 1)
        cout << "���� �����������, " << full_stat.names[max_score_id[0]] << " ������ ������� ���������� ������.";
    else {
        cout << "���� �����������, ��������: " << full_stat.names[max_score_id[0]] << ", " << full_stat.names[max_score_id[1]];
        if (ammount_of_players > 2) {
            for (unsigned short i{ 2 }; i < ammount_of_players; i++) {
                if (max_score_id[i] != -1) {
                    cout << ", " << full_stat.names[max_score_id[i]];

                }
            }
        }
    }
}

int bonuses(Player player, string word, short letter_ammount) {
    const int width = 156;   
    if (word.empty()) {
        if (player.bonuces == 0 && letter_ammount != 0) {
            cout << endl << endl; 
            cout << setw(90) << " � ��� ���� 2 ������: \n\n"
                 << "    1. 50 �� 50 \n\n "
                 << "   2. ������ ����� \n\n ";
        }   
        else if (player.bonuces == 0) {
            cout << endl; 
            cout << "                                             � ��� �������� ������ ������ �����, ���� ������ ������������ ����� ������� 2.\n\n";
        }
        else if (player.bonuces == 1) {
            cout << endl; 
            cout << "                                             � ��� �������� ������ ������ �����, ���� ������ ������������ ����� ������� 2.\n\n";
        }
        else if (player.bonuces == 2 && letter_ammount != 0) { 
            cout << "� ��� �������� ������ 50 �� 50, ���� ������ ������������ ����� ������� 1.\n";
        }
        else {
            cout << "� ��� �� �������� ���������\n";
        }
        return 0;
    }
    
    else {
        int counter{};
        for (char c : word) {
            if (!(c >= '�' && c <= '�') && !(c == '�') && isdigit(c)) {
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
void fifty_fifty(Player& player, char letter_bank[]) {
    string letters;
    bool stupid_igrok = true;
    short counter{};
    char player_letters[10]{};

    while (stupid_igrok) {
        cout << endl;
        cout << "                                �������� 5 ����(��� �������� � ������ ����������) �� ������ ������, ������� �� ������ ��������:\n ";
        cout << setw(74) << " ";
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
                        player_letters[j] = '0';
                        break;
                    }
                }
                if (counter == letters.length())
                    stupid_igrok = false;
            }
        }
    }
    cout << endl; 
    /* for (unsigned short i{}; i < 5; i++) {
         letters[i] = player.letters[i];
     }*/
    for (char c : letters) {
        for (unsigned short i{}; i < 10; i++) {
            if (c == player.letters[i]) {
                player.letters[i] = '0';
                break;
            }
        }
    }
    add_letters_to_player(player.letters, letter_bank);
    for (int i = 0; i < 10; i++)
    {
        cout << player.letters[i] << " | ";
    }
    cout << endl;
}
void spizdi_letter(Player& player, Player player_arr[], short player_ammount, Statistics score, short player_id) {
    short id{}, my_letter_id{}, his_letter_id{};
    string my_letter{}, his_letter{}, id_str{};
    char buffer{};
    for (unsigned short i{}; i < player_ammount; i++) {
        if (i != player_id) {
            cout << "\n����� " << i + 1 << "���: " << score.names[i] << "\n";
            cout << "�����: " << score.points[i] << "\n";
            cout << "�����: ";
            for (int j = 0; j < 10; j++)
            {
                cout << player_arr[i].letters[j] << " | ";
            }
        }
    }
    while (true) {
        cout << "\n������� ����� ������ � ������� ������ ���������� ����� ������: ";
        getline(cin, id_str);
        if (id_str.length() == 1 && !((id_str[0] >= '�' && id_str[0] <= '�') || (id_str[0] == '�')) && isdigit(id_str[0])) {
            id = stoi(id_str);
            if (id > 0 && id <= player_ammount && id != player_id + 1) {
                id--;
                break;
            }
        }
    }
    while (true) {
        cout << "������ ����� ������� ������ �������� � ����: ";
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
        cout << "������ ����� ������� ������ �������� � ���������� ���� ������������: ";
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
    buffer = his_letter[0];
    player_arr[id].letters[his_letter_id] = my_letter[0];
    player.letters[my_letter_id] = buffer;
    cout << "���� �����: \n" << '|'; 
    for (int i = 0; i < 10; i++)
    {
        cout << player.letters[i] << " | ";
    }
    cout << endl;
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
            massive_alphabet[i + 1] = '�';
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
    //��� ����������������� ������ -- ��� ������ ��� ������� �������
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        if (pl_letters[i] == '0')
        {
            int rand_nomb;
            rand_nomb = rand() % 132;
            /* cout << "Random: ";
             cout << rand_nomb << ";";*/ //��� ��������� ������������
            if (Bank[rand_nomb] == '0')
            {
                int j = rand_nomb;
                while (j < 132)
                {
                    /*cout << endl << "j1: " << j << endl;*/
                    if (Bank[j] != '0')
                    {
                        pl_letters[i] = Bank[j];
                        /* cout << endl << i << " ��������� " << pl_letters[i] << endl;*/
                        Bank[j] = '0';
                        break;
                    }
                    j++;
                }
                /* cout << endl << "j: " << j << endl;*/
                if (j == 132)
                {
                    /* cout << endl << "break" << endl;*/
                    while (j > 0)
                    {
                        j--;
                        if (Bank[j] != '0')
                        {
                            pl_letters[i] = Bank[j];
                            Bank[j] = '0';
                            break;
                        }

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
string word_input_simpel_check(Player& player, Player player_arr[], char letter_bank[], short player_ammount, Statistics score, short player_id, short letter_ammount) {
    string user_word{};
    const int width = 156;
    bool check_complited = false, already_dumb = false;
    while (!check_complited) {
        user_word = "";
        bonuses(player, user_word, letter_ammount);
        if (!already_dumb && player.bonuces != 3) {
            cout << "                                              ������� ����� �� ����� 10-�� ���� ��� �������������� �������\n\n ";
            cout << setw(74) << " "; 
          }
        else
            cout << "                                               ������� ����� �� ����� 10-�� ���� ��� �������������� �������: ";
        getline(cin, user_word);
        if (user_word.empty()) {
            return "0";
        }
        switch (bonuses(player, user_word, letter_ammount)) {
        case 1:
            if (player.bonuces == 0) {
                player.bonuces = 1;
                fifty_fifty(player, letter_bank);
            }
            else if (player.bonuces == 2) {
                fifty_fifty(player, letter_bank);
                player.bonuces = 3;
            }
            continue;
        case 2:
            if (player.bonuces == 0) {
                player.bonuces = 2;
                spizdi_letter(player, player_arr, player_ammount, score, player_id);
            }
            else if (player.bonuces == 1) {
                spizdi_letter(player, player_arr, player_ammount, score, player_id);
                player.bonuces = 3;
            }
            continue;
        case 3:
            continue;
        }
        for (char c : user_word) {
            if (user_word.length() > 10) {
                cout << "����� ������ �������� �� �� ����� ��� 10-�� ����: ";
                already_dumb = true;
                break;
            }
            if (!(c >= '�' && c <= '�') /*&& !(c == '�')*/ && !(c == '�')) {
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
bool big_check1(string user_word, Player player) {
    //����, � ������� ���� �������
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
bool opros_players_about_new_word(string word) {
    string answ{};
    while (true) {
        cout << setw(105) << "������� �� ��, ��� ����� ���� ��������� ���������(��/���): ";
        cout << setw(127) << " ";  
        getline(cin, answ);
        if (answ == "��") {
            ofstream fin;
            fin.open("russian.txt", ios::app);
            fin << word << "\n";
            fin.close();
            return true;
        }
        else if (answ == "���")
            return false;
    }
}

//�������� ����� (� ��������� �������� � �� 2 ���������)
bool big_check(string user_word, Player player) {
    //����, � ������� ���� �������
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