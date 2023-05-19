#include "Reader.h"

Reader::Reader(string srcname) : src(srcname)
{
	parse_src();

	if (!check_files()) {
		throw FileNotOpen();
	}

	read_file();
	clean_dictionary();
}


void Reader::get_data(vector<vector<string>> &l)
{
	l = move(dictionary);
}

void Reader::read_file()
{
	int size{ read_max_word_size() };
	ifstream in;
	string temp;

	dictionary.resize(size);

	for (string s : srcs) {
		in.open(s);
		while (in.good()) {
			getline(in, temp);
			size = temp.size();

			dictionary[size - 1].push_back(temp);

			in.peek();
		}
		in.close();
	}
}

bool Reader::check_files()
{
	fstream file;

	for (string s : srcs) {
		file.open(s);
		if (!file) {
			return false;
		}
		file.close();
	}

	return true;
}

void Reader::parse_src()
{
	if (src.find(',') == string::npos)
		srcs.push_back(src);

	else {
		string temp;
		stringstream st(src);
		while (getline(st, temp, ',')) {
			srcs.push_back(temp);
		}
	}
}

void Reader::clean_dictionary()
{
	for (vector<string> &v : dictionary) {
		sort(v.begin(), v.end());
		vector<string>::iterator it = adjacent_find(v.begin(), v.end());

		while (it != v.end()) {
			v.erase(it);
			it = adjacent_find(v.begin(), v.end());
		}
	}
}

int Reader::read_max_word_size()
{
	ifstream in;
	int counter{};
	string temp;

	for (string s : srcs) {
		in.open(s);
		while (in.good()) {
			getline(in, temp);

			if (temp.size() > counter)
				counter = temp.size();
		}
		in.close();
	}

	return counter;
}