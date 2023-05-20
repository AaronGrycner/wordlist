#include "Cmd.h"

// read command input by user
void Cmd::parse_inputted_command()
{
	size_t i{ cmd.find("^LIST^") };

	if (i == string::npos) {
		throw ListIndicatorNotFound();
	}
	else {
		index = i;
	}
}


Cmd::Cmd(string command) : cmd(command)
{
	parse_inputted_command();
	path = filesystem::current_path().string() + "/";
}

// runs the command
int Cmd::run_command(vector<string> chunk)
{
	int returnval{};

	write_chunk(chunk);
	make_batch_file();

	#ifdef _WIN32
	returnval = system((to_string(fcount) + ".bat").c_str());
	#endif
	
	#ifdef __linux__
	returnval = system((to_string(fcount) + ".sh").c_str());
	#endif

	del_files();

	return returnval;
}

// constructs the next command to be run
string Cmd::get_command()
{
	stringstream st;

	st << cmd.substr(0, index) << path << fcount << ".txt" << cmd.substr((index + INDICATOR_SIZE));
	
	return st.str();
}

// writes the chunk to a file
void Cmd::write_chunk(vector<string> data)
{
	++fcount;
	ofstream out(to_string(fcount) + ".txt");

	if (out) {
		for (string st : data) {
			out << st << endl;
		}
	}
	else {
		throw FileNotOpen();
	}

	out.close();
}

// cleanup files
void Cmd::del_files()
{
	stringstream st;

	#ifdef _WIN32
	st << "del " << fcount << ".txt";
	#endif

	#ifdef __linux__
	st << "rm " << fcount << ".txt";
	#endif

	system(st.str().c_str());

	st.str("");

	#ifdef _WIN32
	st << "del *.bat";
	#endif

	#ifdef __linux__
	st << "rm *.sh";
	#endif

	system(st.str().c_str());
}

// creates a batch/shell file to run the command
void Cmd::make_batch_file()
{
	#ifdef _WIN32
	ofstream batch(to_string(fcount) + ".bat");
	#endif

	#ifdef __linux__
	ofstream batch(to_string(fcount) + ".sh");
	#endif

	batch << get_command();
}