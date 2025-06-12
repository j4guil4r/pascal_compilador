#ifndef PARSER_H
#define PARSER_H

#include "../scanner/scanner.h"
#include "../ast/program.h"

class Parser {
private:
    Scanner* scanner;
    Token *current, *previous;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    bool advance();
    bool isAtEnd();
public:

};
