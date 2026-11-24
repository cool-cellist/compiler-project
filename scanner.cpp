#include "scanner.hpp"
#include <iostream>

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "", line));

    return tokens;
}

void Scanner::scanToken() {
    char c = advance();

    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;

        case '!': addToken(match('=') ? TokenType::NOT_EQUAL : TokenType::NOT); break;
        case '=' : addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;

        case '/':
            if (match('/')) {
                // comment goes until the end of the line
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
        break;

        case ' ':
        case '\r':
        case '\t':
            // ignore whitespace
            break;

        case '\n':
            line++;
            break;

        default:
            error(line, "Unexpected character.");
            hadError = true;
    break;
    }
}

Scanner::Scanner(std::string source) {
    this->source = source;
    start = 0;
    current = start;
    line = 1;
}

void Scanner::addToken(TokenType type) {
    tokens.push_back(Token(type, source.substr(start, current-start), line));
}


/* status checkers / updaters */

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::error(int line, std::string message) {
    report(line, "", message);
}

void Scanner::report(int line, std::string where, std::string message) {
    std::cout << "[line " + std::to_string(line) + "] Error" + where + ": " + message;
    hadError = true;
}




/* lookaheads */

char Scanner::advance() {
    return source[current++];
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return 0;
    return source[current];
}