#include "MicroFB.cpp"

using namespace std;

int main() {
	MicroFB<string> MFB;
	string in_name;
	string extra_name;
	char cmd;

	cout << endl << "Commands:" << endl;
	cout << "  P <name>  : Create a person record of the specified name." << endl;
	cout << "  F <name1> <name2> : Record that the two specified people are friends." << endl;
	cout << "  U <name1> <name2>  : Record that the two specified people are no longer friends." << endl;
	cout << "  L <name>  : Print out the friends of the specified person." << endl;
	cout << "  Q <name1> <name2>   : Check whether the two people are friends." << endl;
	cout << "  X   : terminate the program." << endl;
	cout << endl;

	do {
		cout << endl << "Command : ";
		cin >> cmd;
		if (cmd == 'P' || cmd == 'p' || cmd == 'L' || cmd == 'l') {
			cin >> in_name;
		}
		else if (cmd == 'F' || cmd == 'f' || cmd == 'U' || cmd == 'u' || cmd == 'Q' || cmd == 'q') {
			cin >> in_name >> extra_name;
		}

		switch (cmd) {
		case 'P': case 'p':
			MFB.add(in_name);
			break;

		case 'F': case 'f':
			MFB.follow(in_name, extra_name);
			break;

		case 'U': case 'u':
			MFB.unfollow(in_name, extra_name);
			break;

		case 'L': case 'l':
			MFB.printFriend(in_name);
			break;

		case 'Q': case 'q':
			MFB.isFriend(in_name, extra_name);
			break;

		}
	} while (cmd != 'X'&&cmd != 'x');
}