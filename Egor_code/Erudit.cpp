#include <iostream>
#include <string>

using namespace std;
char aplha_zaplonenie(char a[132]);

char alpha[132]{};

struct Player {
	int id;
	string letters[10];
	string last_world;
	int points;
};

int main()
{
	setlocale(LC_ALL, "russian");
	const int range = 132;
	int counter = 192;
	char alpha[range]{};
	
}

static char alpha_zapolnenie(char a[132]) {
	int counter = 192;
	for (unsigned i{}; i < 132; i++) {
		if (counter == 197) {
			a[i] = counter;
			a[i + 1] = 'Ё';
			i++;
			counter++;
		}
		else if (counter == 223) {
			a[i] = counter;
			counter = 192;
		}
		else {
			a[i] = counter;
			counter++;
		}
	}
}