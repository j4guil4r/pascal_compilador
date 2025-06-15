#ifndef PARSER_H
#define PARSER_H

#include "../scanner/scanner.h"
#include "../ast/program.h"
using namespace std;

class Parser {
private:
    Scanner* scanner;
    Token *current, *previous;
    bool match(Token::Type ttype);
    bool check(Token::Type ttype);
    bool advance();
    bool isAtEnd();
    Exp* parseCExp();
    Exp* parseExpression();
    Exp* parseTerm();
    Exp* parseFactor();
    Stmt* parseStatement();
    StatementList* parseStatementList();
    VarDec* parseVarDec();
    VarDecList* parseVarDecList();
    BlockStmt* parseBody();
    FunDec* parseFunDec();
    FunList* parseFunDecList();
public:
    Parser(Scanner* scanner);
    Program* parseProgram();
};

#endif // PARSER_H