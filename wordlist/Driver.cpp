/*
	TODO
	- add support for session resuming
	- add support for batch files
	- clean up code
	- document code
*/

#include "Wordlist.h"
#include "Header.h"

int main(int argc, char* argv[]) {
	Wordlist *list = nullptr;
	int returnval{};

	if ( argc != 4) {
		cout << "Usage: " << argv[0] << " <dictionary files seperated by commas> \"<command>\" <word format>" << endl;
		return 999;
	}
	try {
		list = new Wordlist(argv[1], argv[2], argv[3]);
	}
	catch (FileNotOpen e) {
				cout << endl << e.msg << endl;
		return e.code;
	}

	try {
		returnval = list->run();
	}
	catch (Exception e) {
		cout << endl << e.msg << endl;
		return e.code;
	}
	
	delete list;

	return returnval;
}