#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include "Token.h"
#include "TokenTypes.h"
using namespace std;

bool strIsDigit(string s) 
{
	for (char const &c : s)
	{
		if (!isdigit(c)) return false;
	}
	return true;
}

// TODO: Add other rules
// A valid identifier must not start with a number, and all chars must be alphanumeric
bool isValidIdentifier(string s)
{
	if (isdigit(s[0])) return false;
	for (char const &c : s)
	{
		if (!isalnum(c)) return false;
	}
	return true;
}

// Create token from lexeme, add token to tokens, and reset lexeme to empty string
void addToken(vector<Token> &tokens, string &lexeme)
{
	// tokenType to be included in Token initialization
	TokenType tokenType;
	// TODO: Convert these to sets
	vector<string> arithmeticOps = { "+", "-", "*", "/" };
	vector<string> compareOps = { "==", "!=", "<", ">", "<=", ">=", "&&", "||" };
	vector<string> dataTypes = { "int", "char", "boolean" }; // for now
	if (lexeme.length() == 0)
	{
		cerr << "0 length lexeme in addToken()" << endl;
		return;
	}
	if (lexeme.compare("(") == 0) tokenType = LPAREN;
	else if (lexeme.compare(")") == 0) tokenType = RPAREN;
	else if (lexeme.compare("{") == 0) tokenType = LBRACKET;
	else if (lexeme.compare("}") == 0) tokenType = RBRACKET;
	else if (lexeme.compare(",") == 0) tokenType = COMMA;
	else if (lexeme.compare(";") == 0) tokenType = SEMICOLON;
	else if (lexeme.compare("if") == 0) tokenType = IF;
	else if (lexeme.compare("else") == 0) tokenType = ELSE;
	else if (lexeme.compare("return") == 0) tokenType = RETURN;
	else if (lexeme.compare("for") == 0) tokenType = FOR;
	else if (lexeme.compare("while") == 0) tokenType = WHILE;
	else if (lexeme.compare("=") == 0) tokenType = ASSIGN;
	else if (lexeme.compare("!") == 0) tokenType = NEGATE;
	else if (find(dataTypes.begin(), dataTypes.end(), lexeme) != dataTypes.end()) tokenType = DATA_TYPE;
	else if (find(arithmeticOps.begin(), arithmeticOps.end(), lexeme) != arithmeticOps.end()) tokenType = OP_ARITHMETIC;
	else if (find(compareOps.begin(), compareOps.end(), lexeme) != compareOps.end()) tokenType = OP_COMPARE;
	else if (strIsDigit(lexeme)) tokenType = NUMBER;
	else if (isValidIdentifier(lexeme)) tokenType = IDENTIFIER;
	else
	{
		cerr << "Invalid lexeme found: " << lexeme << endl;
		exit(1);
	}

	tokens.push_back(Token(tokenType, lexeme));
	lexeme = "";
}

// Reads characters from file, extracts lexemes, calls addToken to populate tokens
vector<Token> getTokens(string filename) {
	// Valid token lexemes
	// set<string> validTokenLexemes = { "+","-","*","/","==","!=","<",">","<=",">=","&&","||","int","char","boolean","(",")","{","}",",",";","if","else","return","for","return","for","while","=","!" };
	// File stream for SHlang source file (closes automatically at end of scope)
	ifstream fin;
	fin.open(filename);
	// All tokens for parser
	vector<Token> tokens;
	// Current lexeme to be tokenized 
	string lexeme = "";
	// Current char in filestream
	char c;
	// Initialize first character
	if (!fin.eof())
	{
		fin.get(c);
	}
	while (!fin.eof())
	{
		// If whitespace is encountered, move to next non-whitespace char and add token
		if (isspace(c))
		{
			// Advance filestream through 0 or more whitespace chars
			while (isspace(c) && !fin.eof()) {
				fin.get(c);
			}
			// Add token of lexeme prior to whitespace if present
			if (lexeme.length() > 0)
			{
				addToken(tokens, lexeme);
			}
		}
		// If c not whitespace
		else
		{
			// Found char that is not part of number, identifier or reserved keyword
			if (!isalnum(c))
			{
				if (lexeme.length() > 0)
				{
					// Alphanumeric followed by non-alphanumeric present
					if (isalnum(lexeme[lexeme.length() - 1]))
					{
						addToken(tokens, lexeme);
					}
					// Else, multichar non-number/non-identifier token
				}
				// In any case, append c to lexeme
				lexeme += c;
				// If current lexeme is a valid token
				//if (validTokenLexemes.find(lexeme) != validTokenLexemes.end())
				//{
				//	lexeme += c;
				//}
				fin.get(c);
			}
			// c is part of number, identifier or reserved keyword
			else
			{
				// Non-alphanumeric followed by alphanumeric present
				if (lexeme.length() > 0 && !isalnum(lexeme[lexeme.length() - 1]))
				{
					addToken(tokens, lexeme);
				}
				lexeme += c;
				fin.get(c);
			}
		}
	}

	addToken(tokens, lexeme);

	return tokens;
}

int main()
{
	vector<Token> tokens = getTokens("example.shlang");
	for (auto i : tokens)
		cout << i << endl;
	return 0;
}