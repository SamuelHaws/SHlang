#include <string>
#include <iostream>
#include "Token.h"

Token::Token(TokenType type) : type{ type } {}
Token::Token(TokenType type, std::string &text) : type{ type }, text{ text } {}

std::ostream &operator<<(std::ostream &out, const Token &t) {
	out << "type: " << t.type << "\ttext: " << t.text;
	return out;
}

void Token::appendCharToText(char c) { text += c; }