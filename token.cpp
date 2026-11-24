#include "token.hpp"
#include "tokentype.hpp"
#include <iostream>

Token::Token(TokenType type, std::string lexeme, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->line = line;
}

std::string Token::toString() {
    return (std::to_string(static_cast<int>(type)) + " " + lexeme + " " + std::to_string(line));
}