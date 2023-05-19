/*
	In command substitute ^LIST^ where the original wordlist would go
	wordlist will then dynamically create a new wordlist for each chunk
	and run the command for each chunk generated.

	Syntax is wordlist [dictionary file] "[cmd]" [word format]
	ex. wordlist.txt "echo ^LIST^" 2@@@@@@@@@@@@$

	Word format...
			prefix with number 1-9 = number of unique words
	        @ = sequence of letters that form words
			$ = symbols
			! = numbers

			ex. 2@@@@@@@@@@@@$ = sequence of 12 letters that form 2 words followed by a symbol

	TODO
	- !!!REDO Wordgen to accomodate new word format function!!!
	    - implement all necessary StringIterator functions

	- modularize (make classes for each function of the program)
	- add support for batch files
	- add more error handling
	- add support for multiple wordlists
	- add support for urls
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