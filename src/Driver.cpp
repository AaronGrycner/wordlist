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
	vector<string> args;

	// put argv into vector
	for (int i{}; i < argc; ++i) {
		args.push_back(argv[i]);
	}

	if (argc != 4 && argc != 2) {
		cout << "Usage: " << argv[0] << " <dictionary files seperated by commas> \"<command>\" <word format>   or," << endl 
			<< "dictionary -r to resume previous session";
		return -1;
	}

	try {
		list = new Wordlist(argc, args);
		returnval = list->run();
	}
	catch (Exception e) {
		cout << endl << e.msg << endl;
		return e.code;
	}
	
	delete list;

	return returnval;
}