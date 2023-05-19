#include "Wordlist.h"

// takes a wordlist file and command, writes a chunk of data, calls cmd object to run command, then deletes the chunk and begins again
Wordlist::Wordlist(string src, string cmd, string form) : source(src), pRead(new Reader(src)), pCmd(new Cmd(cmd)), format_string(form)
{
}

int Wordlist::run()
{
	try {
		pRead->get_data(dictionary);
	}
	catch (Exception e) {
		throw e;
	}

	delete pRead;

	try {
		pGen = new WordGen(dictionary, format_string);
	}
	catch (Exception e) {
		throw e;
	}

	while (!pGen->is_done() && returnval == 0) {
		returnval = pCmd->run_command(get_data());
	}

	return returnval;
}

vector<string> Wordlist::get_data()
{
	vector<string> temp;

	for (int i{}; i < CHUNK_SIZE && !pGen->is_done(); ++i) {
		temp.push_back(pGen->next_word());
	}

	return temp;
}