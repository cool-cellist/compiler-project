#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <vector>
#include <string>
#include "tokentype.hpp"
#include "token.hpp"

// class to scan lexemes and get tokens
class Scanner {
    private:
        std::string source; // string that holds the text of the given file
        std::vector<Token> tokens; // list of tokens we vomit out after eating lexemes
        int start, current, line; //  keep track of location
        bool hadError; // error flag

        // token manipulation methods

        void scanToken();
        void addToken(TokenType);

        // status checkers / updaters
        
        bool isAtEnd();
        void error(int, std::string);
        void report(int, std::string, std::string);

        // lookaheads
        // current == current unconsumed character

        char advance(); // return + consume current
        bool match(char); // return match + consume current
        char peek(); // return current'

    public: 
        // initializes source, token, location status, and error status
        Scanner(std::string);

        // read lexemes, vomit tokens
        std::vector<Token> scanTokens();
};

#endif