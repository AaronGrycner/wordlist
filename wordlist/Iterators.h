#ifndef ITERATORS_H
#define ITERATORS_H

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef vector<string>::const_iterator SymbolIterator;
typedef vector<char>::const_iterator NumberIterator;

// iterators class manages iterators for the three subtypes, ensuring their movement and initialization
// also returns the word value constructed by each of their values


class StringIterator {

private:
	vector<vector<string>::const_iterator> its;
	const vector<vector<string>> &dictionary;
	vector<vector<int>> sequences; // possible sequences of word lengths
	size_t length{};
	int words{}, sequence_index{};
	void calc_sequences();
	void sequence_algo(vector<int>& vec, int index, size_t extra);

	void init_iterators();
	bool no_zero(vector<int> v);

public:
	string get();
	bool increment();
	StringIterator(const vector<vector<string>> &dict, size_t l, int w); // letter sequence iterator constructor
};


// ITERATOR MANAGER CLASS

class Iterators {
private:
	vector<char> numbers{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	vector<string> symbols{ "!", "@", "#", "$", "%", "&", "?" };

	bool done{ false };
	const vector<vector<string>> &dictionary;
	vector<vector<char>> format_vec;

	vector<StringIterator> wordIts;
	vector<SymbolIterator> symIts;
	vector<NumberIterator> numIts;

	bool increment_iterators();
	void make_iterators();

public:
	Iterators(const vector<vector<string>> &dict, vector<vector<char>> format);
	string get_word();
	bool check_done() { return done; }
};







#endif