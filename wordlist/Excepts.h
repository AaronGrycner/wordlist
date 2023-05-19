#ifndef EXCEPTS_H
#define EXCEPTS_H

#include <string>

using namespace std;

struct Exception {
	const char *msg;
	int code;
};

struct ListIndicatorNotFound : public Exception {
	ListIndicatorNotFound() : Exception{ msg = "\nno list indicator found in inputted argument!!!\n", code = 3} {}
};
struct FileNotOpen : public Exception {
	FileNotOpen() : Exception{ msg = "\nerror opening dictionary file!!!\n", code = 4 } {}
};
struct InvalidWordFormat : public Exception {
	InvalidWordFormat() : Exception{ msg = "\ninvalid inputted word format!!!\n", code = 5} {}
};

#endif
