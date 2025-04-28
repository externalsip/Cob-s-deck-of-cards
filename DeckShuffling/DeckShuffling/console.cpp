#include "console.h"
using namespace std;

void console::DisplayMessage(string message) {
	cout << message << '\n';
}

void console::ClearConsole() {
	system("cls");
}