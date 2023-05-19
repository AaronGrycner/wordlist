#ifndef WORDLIST_H
#define WORDLIST_H

#include "Reader.h"
#include "WordGen.h"
#include "Cmd.h"

// takes a format string, wordlist filename and generates a wordlist from it, returns data by chunks
class Wordlist
{
private:
	Reader *pRead; // class that handles reading of data from file/url
	WordGen *pGen = nullptr; // class that handles word generation for dynamic generation mode
	Cmd *pCmd; // class that handles command execution

	int fcount{}, returnval{}, mode{};
	string format_string, source;
	vector<vector<string>> dictionary;

	vector<string> get_data();

public:
	Wordlist(string file, string cmd, string format);
	~Wordlist() { delete pCmd; delete pGen; }
	int run();
};

#endif