#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include "tokentype.hpp"
// holds properties of tokens (type, lexeme, and line)
class Token {
    private:
        TokenType type; // type of token we identify this to be
        std::string lexeme; // lexeme we read from raw source code
        int line; // line that we find this token on

    public:
        // initialize all private members
        Token(TokenType, std::string, int);

        // prints type, lexeme, and line
        std::string toString();
};

#endif