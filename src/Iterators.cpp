#include "Iterators.h"

// gets next word by reading the format string and iterating through the vectors of iterators
// retrieving their respective values

Iterators::Iterators(const vector<vector<string>> &dict, vector<vector<char>> format, int c) : dictionary(dict), format_vec(format), chunk(c)
{
	make_iterators();
}

string Iterators::get_word()
{
	stringstream st;
	int strCount{}, numCount{}, symCount{}; // counters for the iterator vectors

	for (int i{}; i < format_vec.size(); ++i) {

		if (!format_vec[i].empty()) {
			char element = format_vec[i][0]; // the element being examined in the format vector

			// checks if elem is a number prefix
			if ((1 <= element - '0' && element - '0' <= 9)) {
				st << wordIts[strCount].get();
				++strCount;
			}

			// checks if elem is a number
			else if (element == '!') {
				st << *numIts[numCount];
				++numCount;
			}

			// checks if elem is a symbol
			else if (element == '$') {
				st << *symIts[symCount];
				++symCount;
			}
		}
	}

	done = increment_iterators();

	return st.str();
}

// returns false if all iterators have run out of possible combinations
bool Iterators::increment_iterators()
{
	int strCount{}, numCount{}, symCount{}; // the counters align the iterators with the format vector

	for (vector<char> element : format_vec) {

		if (!element.empty()) {

			// checks if elem is a number prefix of a word string
			if (1 <= element.front() - '0' && element.front() - '0' <= 9) {
				if (!wordIts[strCount].increment())
					return false;
				++strCount;
			}

			// checks if elem is a number
			else if (element.front() == '!') {
				if (++numIts[numCount] != numbers.end()) {
					return false;
				}
				else {
					numIts[numCount] = numbers.begin();
					++numCount;
				}
			}

			// checks if elem is a symbol
			else if (element.front() == '$') {
				if (++symIts[symCount] != symbols.end()) {
					return false;
				}
				else {
					symIts[symCount] = symbols.begin();
					++symCount;
				}
			}
		}
	}
	return true;
}

void Iterators::make_iterators() {
	for (int i{}; i < format_vec.size(); ++i) {
		char element{};

		if (!format_vec[i].empty()) {
			element = format_vec[i][0]; // the element being examined in the format vector

			// checks if elem is a number prefix
			if (1 <= element - '0' && element - '0' <= 9) {
				StringIterator temp(dictionary, format_vec[i].size(), element - '0');
				wordIts.push_back(temp);
			}

			// checks if elem is a number
			else if (element == '!') {
				NumberIterator temp;
				numIts.push_back(temp);
				numIts[numIts.size() - 1] = numbers.begin();
			}

			// checks if elem is a symbol
			else if (element == '$') {
				SymbolIterator temp;
				symIts.push_back(temp);
				symIts[symIts.size() - 1] = symbols.begin();
			}
		}
	}

	// sets the iterators for session resuming
	for (int i{}; i < (chunk * CHUNK_SIZE); ++i) {
		increment_iterators();
	}
}

void StringIterator::init_iterators()
{
	vector<int> temp;

	temp = sequences.at(sequence_index);

	// runs through the iterator vectors and sets their iterators to the first possible value
	for (int i{}; i < its.size(); ++i) {
		its[i] = dictionary[temp[i]-1].begin();
	}
}

void StringIterator::calc_sequences()
{
	vector<int> temp( words);
	size_t extra{ length };  // TODO   !!!!!!   TYPE WEIRDNESS, FIX, should not need to use size_t

	// run sequence algo on each numerical sequence to find all possible sequences
	sequence_algo(temp, 0, extra);
}

// recursive function containing the algorithm to find all sequences of word lengths
void StringIterator::sequence_algo(vector<int> &temp, int index, size_t extra)
{
	// checks that extra has not been distributed
	// when extra == 0, we have found a valid sequence
	while (extra >=0) {

		++temp[index];
		--extra;

		if (extra == 0) {
			if (no_zero(temp))
				sequences.push_back(temp);

			temp[index] = 0;
			break;
		}

		else if (index == temp.size() - 1)
			continue;

		else
			sequence_algo(temp, index + 1, extra);
	}
}

// returns true if at end
bool StringIterator::increment()
{
	bool flag{ false }; // flag is true if all iterators at end

	for (int i{}; i < its.size(); ++i) {
		auto &x{ dictionary[sequences[sequence_index][i] - 1]};

		// if current iterator is not at end, increment it and return false aka we are not at end
		if (++its[i] != x.end()) {
			return false;
		}
		else {
			its[i] = x.begin();
		}

		if (i + 1 != its.size()) {
			flag = true;
		}
	}

	if (flag) {
		
		// set new sequence index
		++sequence_index;

		// if no more sequences, return false and reset sequences
		if (sequence_index == sequences.size()) {
			sequence_index = 0;
			init_iterators();
			return true;
		}
		else {
			init_iterators();
			return false;
		}
	}
	return true;
}

string StringIterator::get()
{
	string seq;
	for (int i{}; i < its.size(); ++i) {
		seq += *its[i];
	}
	return seq;
}

bool StringIterator::no_zero(vector<int> v) {
	for (int i : v) {
		if (i == 0) {
			return false;
		}
	}
	return true;
}

StringIterator::StringIterator(const vector<vector<string>> &dict, size_t l, int w) : dictionary(dict), length(l), words(w)
{
	calc_sequences();
	for (int i{}; i < words; ++i) {
		vector<string>::iterator temp;
		its.push_back(temp);
	}
	init_iterators();
}