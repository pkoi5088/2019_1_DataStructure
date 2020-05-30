#include "OrganizationTree.h"
#include <iostream>

int main() {
	string input, cmd;
	cout << "Input CEO Name : ";
	cin >> input;

	OrganizationTree company(input);

	cout << "CEO : " << input << "\n\n";
	cout << '\t' << "[Existing member] hires [New member]" << endl;
	cout << '\t' << "Fire [Existing member]" << endl;
	cout << '\t' << "Print" << endl;
	cout << '\t' << "Print People List : P" << endl;
	cout << '\t' << "Exit : Q\n" << endl;

	do {
		if (company.isEmpty()) {//사람이없으면
			company.set();//BOSS를 set
		}
		cout << "Command : ";
		cin >> cmd;
		if (cmd == "Fire" || cmd == "fire") {
			string name;
			cin >> name;
			company.fire(name);
		}
		else if (cmd == "Print" || cmd == "print") {
			company.print();
		}
		else if (cmd == "p" || cmd == "P")
			company.printPeople();
		else if (!(cmd == "Q" || cmd == "q")) {
			string tmp, name2;
			cin >> tmp >> name2;

			if (tmp != "hires")
				cout << "Strange Command" << endl;
			else
				company.hire(cmd, name2);
		}
	} while (cmd != "Q"&&cmd != "q");

	return 0;
}