#include <string>
#include <iostream>
#include "Token.h"

Token::Token(int id1, std::string text1) { id = id1; text = text1; }

std::ostream &operator<<(std::ostream &out, const Token &t) {
	out << "id: " << t.id << "\ttext: " << t.text;
	return out;
}

void Token::appendCharToText(char c) { text += c; }