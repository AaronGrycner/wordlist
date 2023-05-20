#include "Wordlist.h"

// REWORK TO MAKE COMPATIBLE WITH SESSION RESUME

// takes a wordlist file and command, writes a chunk of data, calls cmd object to run command, then deletes the chunk and begins again
Wordlist::Wordlist(int argc, vector<string> &args)	
{
	try {
		pSess = new SessionFile(args);
	}
	catch (SessionFileNotFound e) {
		throw e;
	}

	pRead = new Reader(args[3]);
	pCmd = new Cmd(args[2]);
	mask = args[1];

}

int Wordlist::run()
{
	// read dictionary
	try {
		pRead->get_data(dictionary);
	}
	catch (Exception e) {
		throw e;
	}
	delete pRead;

	// generate words
	try {
		pGen = new WordGen(dictionary, mask, chunk);
	}
	catch (Exception e) {
		throw e;
	}

	// run command
	int count{};
	while (!pGen->is_done() && returnval == 0) {

		returnval = pCmd->run_command(get_data());

		if (!pSess->update_file(count))
			throw SessionFileUpdateError();

		++count;
	}

	return returnval;
}

vector<string> Wordlist::get_data()
{
	vector<string> temp;

	for (int i{chunk}; i < CHUNK_SIZE && !pGen->is_done(); ++i) {
		temp.push_back(pGen->next_word());
	}

	return temp;
}