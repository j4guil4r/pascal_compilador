#ifndef PASCAL_COMPILADOR_TOKEN_H
#define PASCAL_COMPILADOR_TOKEN_H
#include <string>

class Token {
public:
    enum Type {
        PROGRAM,
        FUNCTION,
        VAR,
        BEGIN,
        END,
        IF,
        THEN,
        ELSE,
        WHILE,
        DO,
        FOR,
        TO,
        DOWNTO,
        WRITELN,
        INTEGER,
        LONGINT,
        UNSIGNEDINT,
        NOT,
        OR,
        AND,
        DIV,
        MOD,
        PC,
        DOT,
        COLON,
        COMMA,
        ASSIGN,
        EQ,
        NOT_EQ,
        LT,
        LE,
        GT,
        GE,
        PLUS,
        MINUS,
        MULT,
        PI,
        PD,
        ID,
        NUM,
        PROCEDURE,
        ERR,
        FINISH,
        BOOL,
        TRUE,
        FALSE
    };
    Type type;
    std::string text;

    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const std::string& source, int first, int last);

    friend std::ostream& operator<<(std::ostream& outs, const Token& tok);
    friend std::ostream& operator<<(std::ostream& outs, const Token* tok);

};

#endif //PASCAL_COMPILADOR_TOKEN_H
