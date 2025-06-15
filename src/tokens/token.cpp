#include "token.h"
#include <iostream>

using namespace std;

Token::Token(Type type):type(type) { text = ""; }

Token::Token(Type type, char c):type(type) { text = string(1, c); }

Token::Token(Type type, const string& source, int first, int last):type(type) {
    text = source.substr(first, last);
}

std::ostream& operator<<(std::ostream& outs, const Token& tok) {
    switch (tok.type) {
        case Token::PROGRAM: outs << "TOKEN(PROGRAM)"; break;
        case Token::FUNCTION: outs << "TOKEN(FUNCTION)"; break;
        case Token::VAR: outs << "TOKEN(VAR)"; break;
        case Token::BEGIN: outs << "TOKEN(BEGIN)"; break;
        case Token::END: outs << "TOKEN(END)"; break;
        case Token::IF: outs << "TOKEN(IF)"; break;
        case Token::THEN: outs << "TOKEN(THEN)"; break;
        case Token::ELSE: outs << "TOKEN(ELSE)"; break;
        case Token::WHILE: outs << "TOKEN(WHILE)"; break;
        case Token::DO: outs << "TOKEN(DO)"; break;
        case Token::FOR: outs << "TOKEN(FOR)"; break;
        case Token::TO: outs << "TOKEN(TO)"; break;
        case Token::DOWNTO: outs << "TOKEN(DOWNTO)"; break;
        case Token::WRITELN: outs << "TOKEN(WRITELN)"; break;
        case Token::INTEGER: outs << "TOKEN(INTEGER)"; break;
        case Token::LONGINT: outs << "TOKEN(LONGINT)"; break;
        case Token::UNSIGNEDINT: outs << "TOKEN(UNSIGNEDINT)"; break;
        case Token::NOT: outs << "TOKEN(NOT)"; break;
        case Token::OR: outs << "TOKEN(OR)"; break;
        case Token::AND:outs << "TOKEN(AND)"; break;
        case Token::DIV: outs << "TOKEN(DIV)"; break;
        case Token::MOD: outs << "TOKEN(MOD)"; break;
        case Token::PC: outs << "TOKEN(;)"; break;
        case Token::DOT: outs << "TOKEN(.)"; break;
        case Token::COLON: outs << "TOKEN(:)"; break;
        case Token::COMMA: outs << "TOKEN(,)"; break;
        case Token::ASSIGN: outs << "TOKEN(:=)"; break;
        case Token::PI: outs << "TOKEN('(')"; break;
        case Token::PD: outs << "TOKEN(')')"; break;
        case Token::EQ: outs << "TOKEN(=)"; break;
        case Token::NOT_EQ: outs << "TOKEN(<>)"; break;
        case Token::LT: outs << "TOKEN(<)"; break;
        case Token::LE: outs << "TOKEN(<=)"; break;
        case Token::GT: outs << "TOKEN(>)"; break;
        case Token::GE: outs << "TOKEN(>=)"; break;
        case Token::PLUS: outs << "TOKEN(+)"; break;
        case Token::MINUS: outs << "TOKEN(-)"; break;
        case Token::MULT: outs << "TOKEN(*)"; break;
        case Token::ID: outs << "TOKEN(ID)"; break;
        case Token::PROCEDURE: outs << "TOKEN(PROCEDURE)"; break;
        case Token::NUM: outs << "TOKEN(NUM)"; break;
        case Token::ERR: outs << "TOKEN(ERR)"; break;
        case Token::FINISH: outs << "TOKEN(FINISH)"; break;
        default: outs << "TOKEN(UNKNOWN)"; break;
    }
    return outs;
}

std::ostream& operator << ( std::ostream& outs, const Token* tok ) {
    return outs << *tok;
}