#ifndef CMD_H
#define	CMD_H

#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Excepts.h"

// Cmd class handles execution of system calls 

using namespace std;

const size_t INDICATOR_SIZE{ 6 };

class Cmd
{
private:
	string cmd, path;
	vector<string> chunk;
	int index{}, fcount{};// index is the position of the list indicator character
	void parse_inputted_command();
	string get_command(); // returns the next valid command to execute, takes the current file number as an argument
	void write_chunk(vector<string> chunk);
	void del_files();
	void make_batch_file();

public:
	Cmd(string cmd);
	int run_command(vector<string> chunk);
};

#endif