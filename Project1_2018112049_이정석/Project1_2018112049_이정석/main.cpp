#include "AddressBook.cpp"

using namespace std;

int main() {
	AddressBook<string> book;
	char cmd;
	do {
		cout << endl << "Commands:" << endl;
		cout << "  R : Read from a file" << endl;
		cout << "  + : Add a new entry" << endl;
		cout << "  - : Remove an entry" << endl;
		cout << "  W : Write to a file" << endl;
		cout << "  M : Select a month" << endl;
		cout << "  C : Clear AdressBook" << endl;
		cout << "  Q : Quit the program" << endl;
		cout << endl;
		cout << endl << "Command : ";
		cin >> cmd;
		cin.clear();

		switch (cmd) {
		case 'R': case 'r':
			book.read();
			break;

		case '+':
			if (book.full())
				cout << "Adress is full!" << endl;
			else
				book.add();
			break;

		case '-':
			if (book.empty())
				cout << "Adress is empty!" << endl;
			else
				book.remove();
			break;

		case 'W': case 'w':
			book.write();
			break;

		case 'M': case 'm':
			book.select();
			break;

		case 'C': case 'c':
			cout << "Clear AdressBook" << endl;
			book.clear();
			break;
		}
	} while (cmd != 'Q'&&cmd != 'q');
}