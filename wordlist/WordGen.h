#ifndef WORDGEN_H
#define WORDGEN_H

#include <vector>
#include <string>
#include <fstream>
#include "Excepts.h"
#include "Iterators.h"

// generates words based on the format string and returns them for writing

using namespace std;

class WordGen
{
private:
	string format_string;

	vector<vector<string>> dictionary;

	vector<vector<char>> format_vec; // vector containing the format rules
	Iterators* its = nullptr;

	void get_parsed_vec();
	void check_valid_entry();

public:
	WordGen(vector<vector<string>> dict, string format);
	bool is_done() { return its->check_done(); }
	string next_word();
};

#endif