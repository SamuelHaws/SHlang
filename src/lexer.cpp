#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
using namespace std;

// Advance filestream by character through 0 or more whitespace chars
char handleWhitespace(char &c, ifstream &fin)
{
	while (isspace(c) && !fin.eof()) {
		fin.get(c);
	}
	return c;
}

int main()
{
	// File stream for SHlang source file
	ifstream fin;
	fin.open("example.shlang");
	// All tokens for parser
	vector<Token> tokens;
	// Current token
	Token token = Token(1, "");
	// Current char in filestream
	char c;
	// Initialize first character
	if (!fin.eof())
	{
		fin.get(c);
	}
	while (!fin.eof())
	{
		// If whitespace is encountered, move to next non-whitespace char
		// and store token if meaningful
		if (isspace(c))
		{
			handleWhitespace(c, fin);
			if (token.text.length() > 0) {
				tokens.push_back(token);
				token.id = 1;
				token.text = "";
			}
		}
		// Otherwise, insert c into current token text and read next char
		else
		{
			token.appendCharToText(c);
			fin.get(c);
		}
	}
	// Append last token to tokens
	tokens.push_back(token);

	for (auto i : tokens)
		cout << i << endl;
	return 0;
}