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
    Program* parseProgram();
    Stmt* parseStatement();
    StatementList* parseStatementList();
    VarDec* parseVarDec();
    VarDecList* parseVarDecList();
    BlockStmt* parseBody();
    FunDec* parseFunDec();
    ProceDec* parseProceDec();
    FunList* parseFunDecList();
public:
    Parser(Scanner* scanner);
};
