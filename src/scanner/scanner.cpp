#include <cstring>
#include <iostream>
#include "scanner.h"

using namespace std;

Scanner::Scanner(const char* s):input(s),first(0), current(0) { }


bool is_white_space(char c) {return c == ' ' || c == '\n' || c == '\r' || c == '\t';}

Token* Scanner::nextToken() {
    Token* token;
    while (current < input.length() &&  is_white_space(input[current]) ) current++;
    if (current >= input.length()) return new Token(Token::FINISH);
    char c  = input[current];
    first = current;

    if (isdigit(c)) {
        current++;
        while (current < input.length() && isdigit(input[current]))
            current++;
        token = new Token(Token::NUM, input, first, current - first);
    }

    else if (isalpha(c) || c == '_') {
        current++;
        while (current < input.length() && (isalnum(input[current]) || input[current] == '_'))
            current++;
        string word = input.substr(first, current - first);
        if (word == "writeln") {
            token = new Token(Token::WRITELN, word, 0, word.length());
        } else if (word == "if") {
            token = new Token(Token::IF, word, 0, word.length());
        } else if (word == "then") {
            token = new Token(Token::THEN, word, 0, word.length());
        } else if (word == "else") {
            token = new Token(Token::ELSE, word, 0, word.length());
        } else if (word == "while") {
            token = new Token(Token::WHILE, word, 0, word.length());
        }
        else if (word == "do") {
            token = new Token(Token::DO, word, 0, word.length());
        }else if (word == "for") {
            token = new Token(Token::FOR, word, 0, word.length());
        }
        else if (word == "var") {
            token = new Token(Token::VAR, word, 0, word.length());
        }
        else if (word == "program") {
            token = new Token(Token::PROGRAM, word, 0, word.length());
        }
        else if (word == "boolean") {
            token = new Token(Token::BOOL, word, 0, word.length());
        }
        else if (word == "true") {
            token = new Token(Token::TRUE, word, 0, word.length());
        }
        else if (word == "false") {
            token = new Token(Token::FALSE, word, 0, word.length());
        }
        else if (word == "function") {
            token = new Token(Token::FUNCTION, word, 0, word.length());
        }
        else if (word == "begin") {
            token = new Token(Token::BEGIN, word, 0, word.length());
        }
        else if (word == "end") {
            token = new Token(Token::END, word, 0, word.length());
        }
        else if (word == "to") {
            token = new Token(Token::TO, word, 0, word.length());
        }
        else if (word == "downto") {
            token = new Token(Token::DOWNTO, word, 0, word.length());
        }
        else if (word == "integer") {
            token = new Token(Token::INTEGER, word, 0, word.length());
        }
        else if (word == "longint") {
            token = new Token(Token::LONGINT, word, 0, word.length());
        }
        else if (word == "unsignedint") {
            token = new Token(Token::UNSIGNEDINT, word, 0, word.length());
        }
        else if (word == "procedure") {
            token = new Token(Token::PROCEDURE, word, 0, word.length());
        }
        else if (word == "not") {
            token = new Token(Token::NOT, word, 0, word.length());
        }
        else if (word == "or") {
            token = new Token(Token::OR, word, 0, word.length());
        }
        else if (word == "and") {
            token = new Token(Token::AND, word, 0, word.length());
        }
        else if (word == "div") {
            token = new Token(Token::DIV, word, 0, word.length());
        }
        else if (word == "mod") {
            token = new Token(Token::MOD, word, 0, word.length());
        }

        else {
            token = new Token(Token::ID, word, 0, word.length());
        }
    }

    else if (strchr("+-*()=;,.:<>", c)) {
        switch (c) {
            case '+': token = new Token(Token::PLUS, c); break;
            case '-': token = new Token(Token::MINUS, c); break;
            case '*': token = new Token(Token::MULT, c); break;
            case '(': token = new Token(Token::PI, c); break;
            case ')': token = new Token(Token::PD, c); break;
            case ';': token = new Token(Token::PC, c); break;
            case ',': token = new Token(Token::COMMA, c); break;
            case ':':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::ASSIGN, ":=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::COLON, c);
                }
                break;
            case '=': token = new Token(Token::EQ, c); break;
            case '<':
                if (current + 1 < input.length()) {
                    if (input[current + 1] == '=') {
                        token = new Token(Token::LE, "<=", 0, 2);
                        current++;
                    } else if (input[current + 1] == '>') {
                        token = new Token(Token::NOT_EQ, "<>", 0, 2);
                        current++;
                    } else {
                        token = new Token(Token::LT, c);
                    }
                } else {
                    token = new Token(Token::LT, c);
                }
                break;
            case '>':
                if (current + 1 < input.length() && input[current + 1] == '=') {
                    token = new Token(Token::GE, ">=", 0, 2);
                    current++;
                } else {
                    token = new Token(Token::GT, c);
                }
                break;
            case '.': token = new Token(Token::DOT, c); break;
            default:
                cout << "No debería llegar acá" << endl;
                token = new Token(Token::ERR, c);
                break;
        }
        current++;
    }

    else {
        token = new Token(Token::ERR, c);
        current++;
    }
    return token;
}

void Scanner::reset() {
    first = 0;
    current = 0;
}

Scanner::~Scanner() { }

void test_scanner(Scanner* scanner) {
    Token* current;
    cout << "Iniciando Scanner:" << endl<< endl;
    while ((current = scanner->nextToken())->type != Token::FINISH) {
        if (current->type == Token::ERR) {
            cout << "Error en scanner - carácter inválido: " << current->text << endl;
            break;
        } else {
            cout << *current << endl;
        }
        delete current;
    }
    delete current;
}