#ifndef WORDLIST_H
#define WORDLIST_H

#include "SessionFile.h"
#include "Reader.h"
#include "WordGen.h"
#include "Cmd.h"

// takes a format string, wordlist filename and generates a wordlist from it, returns data by chunks
class Wordlist
{
private:
	SessionFile *pSess; // class that handles session file creation and reading
	Reader *pRead; // class that handles reading of data from file/url
	WordGen *pGen = nullptr; // class that handles word generation for dynamic generation mode
	Cmd *pCmd; // class that handles command execution

	int fcount{}, returnval{}, chunk{};
	string mask;
	vector<vector<string>> dictionary;

	vector<string> get_data();

public:
	Wordlist(int argc, vector<string> &args);
	~Wordlist() { delete pCmd; delete pGen; delete pSess; }
	int run();
};

#endif