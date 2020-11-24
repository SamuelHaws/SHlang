#include <string>
#include <iostream>
#include "TokenTypes.h"

#ifndef TOKEN_INCLUDE
#define TOKEN_INCLUDE


class Token
{
public:
	TokenType type;
	std::string text;
	
	Token(TokenType type);
	Token(TokenType type, std::string &text);

	friend std::ostream &operator<<(std::ostream &out, const Token &t);

	void appendCharToText(char c);
};

#endif