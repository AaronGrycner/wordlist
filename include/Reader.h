#ifndef READER_H
#define READER_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Excepts.h"

using namespace std;

// in charge of getting dictionary data from file/files

class Reader
{
private:
	string src;
	vector<string> srcs; // filenames to read from
	vector<vector<string>> dictionary;
	void read_file();
	bool check_files();
	void parse_src();
	void clean_dictionary();
	int read_max_word_size();

public:
	Reader(string srcname);
	void get_data(vector<vector<string>> &l);
};

#endif 