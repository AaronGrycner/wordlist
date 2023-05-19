# wordlist

This program generates Hashcat style wordlists from a given dictionary file and a given mask.

Generates wordlists in chunks of 100,000 words to avoid memory issues and excess disk usage, 
and runs a command for each chunk generated.

## Usage

	In command substitute ^LIST^ where the original wordlist would go
	wordlist will then dynamically create a new wordlist for each chunk
	and run the command for each chunk generated.

	Syntax is wordlist [dictionary file] "[cmd]" [word format]
	ex. wordlist.txt "echo ^LIST^" 2@@@@@@@@@@@@$

	Word format...
			prefix with number 1-9 = number of unique words
	        @ = sequence of letters that form words
			$ = symbols
			! = numbers

			ex. 2@@@@@@@@@@@@$ = sequence of 12 letters that form 2 words followed by a symbol
