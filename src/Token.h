#include <string>
#include <iostream>

#ifndef TOKEN_INCLUDE
#define TOKEN_INCLUDE


class Token
{
public:
	int id;
	std::string text;
	Token(int id1, std::string text1);

	friend std::ostream &operator<<(std::ostream &out, const Token &t);

	void appendCharToText(char c);
};

#endif