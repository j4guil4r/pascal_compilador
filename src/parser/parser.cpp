#include <iostream>
#include <stdexcept>
#include "../tokens/token.h"
#include "../scanner/scanner.h"
#include "parser.h"

using namespace std;

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            cout << "Error de análisis, carácter no reconocido: " << current->text << endl;
            exit(1);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::FINISH);
}

Parser::Parser(Scanner* sc):scanner(sc) {
    previous = NULL;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        cout << "Error en el primer token: " << current->text << endl;
        exit(1);
    }
}

Program* Parser::parseProgram() {
    if (!match(Token::PROGRAM)) {
        cout << "Error: se esperaba 'program' al inicio" << endl;
        exit(1);
    }
    if (!match(Token::ID)) {
        cout << "Error: se esperaba ID despues de program" << endl;
        exit(1);
    }
    string nombre = current->text;
    if (!match(Token::PC)) {
        cout << "Error: se esperaba ';' despues del nombre del programa" << endl;
        exit(1);
    }
    BlockStmt* block= parseBody();
    if (!match(Token::DOT)) {
        cout << "Error: se esperaba '.' al final del programa" << endl;
        exit(1);
    }
    Program* p = new Program(block,nombre);
    return p;
}

BlockStmt* Parser::parseBody() {
    VarDecList* vdl = parseVarDecList();
    FunList* funlist = parseFunDecList();
    StatementList* sl = parseStatementList();
    return new BlockStmt(vdl,funlist, sl);
}

VarDecList* Parser::parseVarDecList() {
    VarDecList* vdl = new VarDecList();
    if (match(Token::VAR)) {
        VarDec* aux;
        aux = parseVarDec();
        while (aux != NULL) {
            vdl->add(aux);
            aux = parseVarDec();
        }
    }
    return vdl;
}

VarDec* Parser::parseVarDec() {
    VarDec* vd = NULL;
    list<string> ids;
    if (match(Token::ID)) {
        ids.push_back(previous->text);
        while (match(Token::COMMA)) {
            if (!match(Token::ID)) {
                cout << "Error: se esperaba una ID después de ','." << endl;
                exit(1);
            }
            ids.push_back(previous->text);
        }
        if (!match(Token::COLON)) {
            cout << "Error: se esperaba ':' después de listar las IDs." << endl;
            exit(1);
        }
        if (!(match(Token::INTEGER)|match(Token::UNSIGNEDINT)|match(Token::LONGINT))) {
            cout << "Error: se esperaba un tipo después de ':'." << endl;
            exit(1);
        }
        string type = previous->text;
        if (!match(Token::PC)) {
            cout << "Error: se esperaba un ';' al final de la declaración." << endl;
            exit(1);
        }
        vd = new VarDec(type, ids);
    }
    return vd;
}

FunDec* Parser::parseFunDec() {
    FunDec* vd = NULL;
    string nombre;
    string returntype;
    if (match(Token::PROCEDURE)) {
        returntype = "void";
        match(Token::ID);
        nombre = previous->text;
        match(Token::PI);
        list<string> parametros;
        list<string> tipos;
        int contador;
        while(match(Token::ID)) {
            contador = 1;
            parametros.push_back(previous->text);
            while (!match(Token::COLON)) {
                if (!match(Token::COMMA)) {
                    cout << "Error: se esperaba un ',' o ':' despues de la declaración." << endl;
                    exit(1);
                }
                if (!match(Token::ID)) {
                    cout << "Error: se esperaba una ID despues de ','." << endl;
                    exit(1);
                }
                parametros.push_back(previous->text);
                contador++;
            }
            if (!(match(Token::INTEGER)|match(Token::UNSIGNEDINT)|match(Token::LONGINT))) {
                cout << "Error: se esperaba un tipo de declaracion despues de ':'." << endl;
                exit(1);
            }
            for (int i=0;i<contador;i++) {
                tipos.push_back(previous->text);
            }
            if (!match(Token::PC)) {
                break;
            }
        }
        if (!match(Token::PD) ){
            cout << "Error: se esperaba un ')' o ';' despues del tipo de los argumentos de procedure." << endl;
                exit(1);
        }
        if (!match(Token::PC)) {
            cout << "Error: se esperaba un ';' despues de ')' de procedure" << endl;
            exit(1);
        }
        BlockStmt *block = parseBody();
        FunDec* fu=new FunDec(nombre,returntype,block);
        if (!match(Token::PC)) {
            cout << "Error: se esperaba un ';' al final de la funcion." << endl;
            exit(1);
        }
        fu->tipos=tipos;
        fu->parametros=parametros;
        return fu;
    }
    if (match(Token::FUNCTION)) {
        match(Token::ID);
        nombre = previous->text;
        match(Token::PI);
        list<string> parametros;
        list<string> tipos;
        int contador;
        while(match(Token::ID)) {
            contador = 1;
            parametros.push_back(previous->text);
            while (!match(Token::COLON)) {
                if (!match(Token::COMMA)) {
                    cout << "Error: se esperaba un ',' o ':' despues de la declaración." << endl;
                    exit(1);
                }
                if (!match(Token::ID)) {
                    cout << "Error: se esperaba una ID despues de ','." << endl;
                    exit(1);
                }
                parametros.push_back(previous->text);
                contador++;
            }
            if (!(match(Token::INTEGER)|match(Token::UNSIGNEDINT)|match(Token::LONGINT))) {
                cout << "Error: se esperaba un tipo de declaracion despues de ':'." << endl;
                exit(1);
            }
            for (int i=0;i<contador;i++) {
                tipos.push_back(previous->text);
            }
            if (!match(Token::PC)) {
                break;
            }
        }
        if (!match(Token::PD) ){
            cout << "Error: se esperaba un ')' o ';' despues del tipo de los argumentos de la funcion." << endl;
            exit(1);
        }
        if (!match(Token::COLON)) {
            cout << "Error: se esperaba un ':' despues de ')'." << endl;
            exit(1);
        }
        if (!(match(Token::INTEGER)|match(Token::UNSIGNEDINT)|match(Token::LONGINT))) {
            cout << "Error: se esperaba un tipo de retorno despues de ':'." << endl;
            exit(1);
        }
        returntype = previous->text;
        if (!match(Token::PC)) {
            cout << "Error: se esperaba un ';' despues del tipo de retorno." << endl;
            exit(1);
        }
        BlockStmt *block = parseBody();
        FunDec* fu=new FunDec(nombre,returntype,block);
        if (!match(Token::PC)) {
            cout << "Error: se esperaba un ';' al final de la funcion." << endl;
            exit(1);
        }
        fu->tipos=tipos;
        fu->parametros=parametros;
        return fu;
    }
    return vd;
}

FunList* Parser::parseFunDecList() {
    FunList* vdl = new FunList();
    FunDec* aux;
    aux = parseFunDec();
    while (aux != NULL) {
        vdl->add(aux);
        aux = parseFunDec();
    }
    return vdl;
}

StatementList* Parser::parseStatementList() {
    if (!match(Token::BEGIN)) {
        cout << "Error: se esperaba un 'begin'." << endl;
        exit(1);
    }
    StatementList* stl=new StatementList();
    Stmt* aux;
    aux = parseStatement();
    while (aux != NULL) {
        stl->add(aux);
        aux = parseStatement();
        if (!match(Token::PC)) {
            cout << "Error: se ';' despues de la sentencia." << endl;
            exit(1);
        }
    }
    if (!match(Token::END)) {
        cout << "Error: se esperaba un 'end'." << endl;
        exit(1);
    }
    return stl;
}

Stmt* Parser::parseStatement() {
    Stmt* s = NULL;
    Exp* e;
    if (current == NULL) {
        cout << "Error: Token actual es NULL" << endl;
        exit(1);
    }
    if (match(Token::ID)) {
        string lex = previous->text;
        if (match(Token::ASSIGN)) {
            e = parseCExp();
            s = new AssignStmt(lex, e);
        }else if (match(Token::PD)) {
            ExpList* exps=parseExpList();
            if (!match(Token::PD)) {
                cout << "Error: se esperaba un ')' después de la expresión." << endl;
                exit(1);
            }
            s = new ProcedureCall(lex, exps);
        }else {
            s = new ProcedureCall(lex);
        }

    }else if (match(Token::WRITELN)) {
        if (!match(Token::PI)) {
            cout << "Error: se esperaba un '(' después de 'print'." << endl;
            exit(1);
        }
        ExpList* exps = parseExpList();
        if (!match(Token::PD)) {
            cout << "Error: se esperaba un ')' después de la expresión." << endl;
            exit(1);
        }
        s = new PrintStmt(exps);
    }else if (match(Token::IF)){
        StatementList* then=nullptr;
        StatementList* else_=nullptr;
        e = parseCExp();
        if (!match(Token::THEN)) {
            cout << "Error: se esperaba 'then' después de la expresión." << endl;
            exit(1);
        }
        then=parseStatementList();
        if (match(Token::ELSE)) {
            else_=parseStatementList();
        }
        s = new IfStmt(e,then,else_);
    }else if (match(Token::WHILE)) {
        e = parseCExp();
        if (!match(Token::DO)) {
            cout << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        StatementList* stms = parseStatementList();
        s = new WhileStmt(e,stms);
    }else if (match(Token::FOR)) {
        if (!match(Token::ID)) {
            cout << "Error: se esperaba 'ID' después del For." << endl;
            exit(1);
            }
        string lex = previous->text;
        if (!match(Token::ASSIGN)) {
            cout << "Error: se esperaba un ':=' después del identificador." << endl;
            exit(1);
        }
        e = parseCExp();
        bool downto;
        if (match(Token::TO)) downto=false;
        else if (match(Token::DOWNTO)) downto=true;
        else {
            cout << "Error: se esperaba un TO o DOWNTO." << endl;
            exit(1);
        }
        Exp* end=parseCExp();
        if (!match(Token::DO)) {
            cout << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        StatementList* stms = parseStatementList();
        s = new ForStmt(lex,e,end,downto,stms);
    }else if (match(Token::BEGIN)) {
        s = parseStatementList();
        if (!match(Token::END)) {
            cout << "Error: se esperaba 'END' después de la lista de sentencias." << endl;
            exit(1);
        }
    }else {
        cout << "Error: sentencia no reconocida: " << *current << endl;
        exit(1);
    }
    return s;
}




