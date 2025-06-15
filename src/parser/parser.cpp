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
    return (current->type == Token::END);
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
        if (!match(Token::ID)) {
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
            if (!match(Token::ID)) {
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
        match(Token::PD);
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
            if (!match(Token::ID)) {
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
        match(Token::PD);
        if (!match(Token::COLON)) {
            cout << "Error: se esperaba un ':' despues de ')'." << endl;
            exit(1);
        }
        if (!match(Token::ID)) {
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

BlockStmt* Parser::parseBody() {
    VarDecList* vdl = parseVarDecList();
    FunList* funlist = parseFunDecList();
    if (!match(Token::BEGIN)) {
        cout << "Error: se esperaba un 'begin'." << endl;
        exit(1);
    }
    StatementList* sl = parseStatementList();
    if (!match(Token::END)) {
        cout << "Error: se esperaba un 'end'." << endl;
        exit(1);
    }
    return new BlockStmt(vdl,funlist, sl);
}

StatementList *Parser::parseStatementList() {
    return new StatementList();
}




