#ifndef SESSIONFILE_H
#define SESSIONFILE_H

#include "Excepts.h"
#include <string.h>
#include <vector>
#include <fstream>

/* Session File Format
*  
*  1. Mask
*  2. Command
*  3. Files
*  4. Chunk number
*/

const string SESSION_FILE = "session.txt";
using namespace std;

class SessionFile {

private:
	int chunk;
	string mask, command, files;
	
	bool read_session_file() {
		ifstream session_file(SESSION_FILE);
		if (session_file) {
			string temp;
			system("pwd");
			getline(session_file, mask);
			getline(session_file, command);
			getline(session_file, files);
			getline(session_file, temp);

			chunk = stoi(temp);

			session_file.close();
			return true;
		}
		session_file.close();
		return false;
	}
		
	void write_session_file() {
		ofstream session_file(SESSION_FILE);
		if (session_file.is_open()) {
			session_file << mask << endl;
			session_file << command << endl;
			session_file << files << endl; 
			session_file << chunk << endl;
		}
		session_file.close();
	}

	bool is_session() {
		fstream f(SESSION_FILE);
		return f.good();
	}

public:

	// if no session file found and argv has one argument ( -r ) throw exception
	SessionFile(vector<string> &args) {

		if (!is_session() && args[2] == "") {
			throw SessionFileNotFound();
		}

		else if (is_session()) {
			args.resize(5);
			read_session_file();
			args[1] = mask;
			args[2] = command;
			args[3] = files;
			args[4] = chunk;
		}

		else if (args[1] != "-r") {
			write_session_file();
		}
	} 
	
	bool update_file(int c) {
		ofstream session_file(SESSION_FILE);
		if (session_file) {
			chunk = c;
			write_session_file();
			return true;
		}
		return false;
	}
};

#endif
