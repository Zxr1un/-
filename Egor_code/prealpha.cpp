#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <Windows.h>
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


int bonuses(Player player, string word);
string input_players_name(short which_player, Statistics score);
int input_number_of_players();
void alphabet_zapolnenie(char massive_alphabet[]);
Statistics game(int players_ammount, Statistics names);
void add_letters_to_player(char pl_letters[], char Bank[]);
string word_input_simpel_check(Player& player, Player player_arr[], char letter_bank[], short player_ammount, Statistics score, short player_id);
bool big_check(string user_word, Player player);
bool big_check1(string user_word, Player player);
//bool big_check2(string user_word, Player player);
int scoring_of_players(bool correct_answer, string answer, string answer_previous_player);
void remove_letters(string word, char letters_bank[]);
bool opros_players_about_new_word(string word);
bool proverk_na_konec_igru(int letters_ammount, Player player_arr[], int players_num);
void Resaults_screen(Statistics full_stat, short ammount_of_players);
void spizdi_letter(Player& player, Player player_arr[], short player_ammount, Statistics score, short plyer_id);
void fifty_fifty(Player& player, char letter_bank[]);




void main()
{
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
    bool check_complited = false, stupid_player = false;
    while (!check_complited) {
        if (!stupid_player)
            cout << "����� " << which_player + 1 << " ������� ��� ���(��� ������ ���������� � ��������): ";
        else
            cout << "����� " << which_player + 1 << " ������� ��� ���(��� ������ ���������� � ��������) � �� �������� ����� ������ �������: ";
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
            cout << "���������� ������� ���������� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
        getline(cin, num_of_players);
        if (!num_of_players.empty()) {
            if (num_of_players.length() == 1) {
                for (char c : num_of_players) {
                    if ((c >= '�' && c <= '�') || (c == '�') || (c == '�') || !isdigit(c)) {
                        not_dumb = false;
                        already_stupid = true;
                        cout << "������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
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
                    cout << "������� ����� �������, ������� ����� �����������(�� ����� 7 (�� ����� 2)): ";
                }
            }
        }
    }
}

Statistics game(int players_ammount, Statistics names)
{
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
        for (int i = 0; i < 132; i++)
        {
            if (Bank_of_latters[i] != '0')
            {
                letters_ammount++;
            }
        }
        if (letters_ammount != 0)
            cout << "\n� ����� ��������: " << letters_ammount << " ����\n";
        //����� �������� ���������� ���� � ����� �����
        else {
            if (proverk_na_konec_igru(letters_ammount, player_arr, players_ammount)) {
                cout << "\n��� ��� � ��� �� ���������� ���� ��� ����������� ����, ���� ��������";
                break;
            }
        }

        // ��� ������
        while (true)
        {
            int id = (step) % players_ammount;
            cout << "\n\n��� ������ " << (id + 1) << "\n\n��������� �����: " << last_word << "\n\n���� �����:  | ";
            for (int i = 0; i < 10; i++)
            {
                cout << player_arr[id].letters[i] << " | ";
            }
            cout << endl;
            // ����� ���������� �������� ������
            word = word_input_simpel_check(player_arr[id], player_arr, Bank_of_latters, players_ammount, names, id);
            if (word == "0")
            {
                player_arr[id].last_word_of_player = "0";
                cout << endl << "...������� ����..." << endl;
                break;
            }
            //������� ����

            cout << endl << "before: " << score.points[id] << endl; //������� (������� ������ ���� �� �����)
            bool check = big_check(word, player_arr[id]);
            if (check)
            {

                score.points[id] += scoring_of_players(check, word, last_word);
                cout << "\n����� �������.\n���� ����� ������: " << score.points[id] << " (+" << scoring_of_players(check, word, last_word) << ") " << endl;
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
                    cout << "\n����� ���� ������� ��������.\n���� ����� ������: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
                    break;
                }
                else
                {
                    score.points[id] += scoring_of_players(check, word, last_word);
                    cout << "\n� ��������� ��� ������� ����� ������ �� ����� ����.\n";
                    cout << "\n����� ��������.\n���� ����� ������: " << score.points[id] << " (" << scoring_of_players(check, word, last_word) << ") " << endl;
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
    short max_score_id{};
    for (unsigned short i{ 1 }; i < ammount_of_players; i++) {
        if (full_stat.points[max_score_id] < full_stat.points[i])
            max_score_id = i;
    }
    cout << "���� �����������, " << full_stat.names[max_score_id] << " ������ ������� ���������� ������.";
}

int bonuses(Player player, string word) {
    if (word.empty()) {
        if (player.bonuces == 0) {
            cout << "� ��� ���� ����������� ������������ 2 ������( 1 ��� 50 �� 50, 2 ��� ������ �����).\n";
        }
        else if (player.bonuces == 1) {
            cout << "� ��� �������� ������ ������ ����, ���� ������ ������������ ����� ������� 2.\n";
        }
        else if (player.bonuces == 2) {
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
            if (!(c >= '�' && c <= '�') && !(c == '�') && (isdigit(c) || isspace(c))) {
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
        cout << "�������� 5 ����(��� �������� � ������ ����������) �� ������ ������, ������� �� ������ ��������: ";
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
        if (id_str.length() == 1 && !((id_str[0] >= '�' && id_str[0] <= '�') || (id_str[0] == '�')) && !isalpha(id_str[0])) {
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
// ������� ��� �������� �� ����� ��-�� ���������� ���� (�� 2 ���� ����� ���������� ��������� �����, 
// ������� ���� � ����� ����� 0 ���� � � ������� ������ �� ����� ��� 2 ���� ��������� ����������
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
string word_input_simpel_check(Player& player, Player player_arr[], char letter_bank[], short player_ammount, Statistics score, short player_id) {
    string user_word{};
    bool check_complited = false, already_dumb = false;
    while (!check_complited) {
        user_word = "";
        bonuses(player, user_word);
        if (!already_dumb && player.bonuces != 3)
            cout << "������� ����� �� ����� 10-�� ���� ��� ����� ������: ";
        else
            cout << "������� ����� �� ����� 10-�� ����: ";
        getline(cin, user_word);
        if (user_word.empty()) {
            return "0";
        }
        switch (bonuses(player, user_word)) {
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
                cout << "����� ������ �������� �� �� ����� ��� 10-�� ���� ��� ����� ������: ";
                already_dumb = true;
                break;
            }
            if (!(c >= '�' && c <= '�') /*&& !(c == '�')*/ && !(c == '�')) {
                cout << "������� ����� ��� �������� � ������ ��������� �������� ������� ��� ����� ������: ";
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
        cout << "������� �� ��, ��� ����� ���� ��������� ���������(��/���): ";
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