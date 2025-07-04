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
            cerr << "Error de análisis, carácter no reconocido: " << current->text << endl;
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
        cerr << "Error en el primer token: " << current->text << endl;
        exit(1);
    }
}

Program* Parser::parseProgram() {
    if (!match(Token::PROGRAM)) {
        cerr << "Error: se esperaba 'program' al inicio" << endl;
        exit(1);
    }
    if (!match(Token::ID)) {
        cerr << "Error: se esperaba ID despues de program" << endl;
        exit(1);
    }
    string nombre = previous->text;
    if (!match(Token::PC)) {
        cerr << "Error: se esperaba ';' despues del nombre del programa" << endl;
        exit(1);
    }
    BlockStmt* block= parseBody();
    if (!match(Token::DOT)) {
        cerr << "Error: se esperaba '.' al final del programa" << endl;
        exit(1);
    }
    Program* p = new Program(block,nombre);
    return p;
}

BlockStmt* Parser::parseBody() {
    BlockStmt* b = NULL;
    VarDecList* vdl1 = parseVarDecList();
    FunList* funlist = parseFunDecList();
    VarDecList* vdl2 = parseVarDecList();
    StatementList* sl = parseStatementList();
    if (!vdl1->vardecs.empty() && !vdl2->vardecs.empty()) {
        cerr << "Error: se se detectaron dos blokes de declaracion de variables 'VAR'." << endl;
        exit(1);
    }
    if (!vdl2->vardecs.empty()) { b = new BlockStmt(vdl2, funlist, sl); }
    else{
        b = new BlockStmt(vdl1,funlist, sl);
        b->firstVarDec = true;
    }
    return b;

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
                cerr << "Error: se esperaba una ID después de ','." << endl;
                exit(1);
            }
            ids.push_back(previous->text);
        }
        if (!match(Token::COLON)) {
            cerr << "Error: se esperaba ':' después de listar las IDs." << endl;
            exit(1);
        }
        if (!(match(Token::INTEGER) || match(Token::UNSIGNEDINT) || match(Token::LONGINT) || match(Token::BOOL))) {
            cerr << "Error: se esperaba un tipo después de ':'." << endl;
            exit(1);
        }
        string type = previous->text;
        if (!match(Token::PC)) {
            cerr << "Error: se esperaba un ';' al final de la declaración." << endl;
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
    if (current == NULL) {
        cerr << "Error: Token actual es NULL" << endl;
        exit(1);
    }
    if (match(Token::PROCEDURE)) {
        returntype = "void";
        match(Token::ID);
        nombre = previous->text;
        vector<string> parametros;
        vector<string> tipos;
        if (match(Token::PI)) {
            int contador;
            while(match(Token::ID)) {
                contador = 1;
                parametros.push_back(previous->text);
                while (!match(Token::COLON)) {
                    if (!match(Token::COMMA)) {
                        cerr << "Error: se esperaba un ',' o ':' despues de la declaración." << endl;
                        exit(1);
                    }
                    if (!match(Token::ID)) {
                        cerr << "Error: se esperaba una ID despues de ','." << endl;
                        exit(1);
                    }
                    parametros.push_back(previous->text);
                    contador++;
                }
                if (!(match(Token::INTEGER) || match(Token::UNSIGNEDINT) || match(Token::LONGINT) || match(Token::BOOL))) {
                    cerr << "Error: se esperaba un tipo después de ':'." << endl;
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
                cerr << "Error: se esperaba un ')' o ';' despues del tipo de los argumentos de procedure." << endl;
                exit(1);
            }
        }
        if (!match(Token::PC)) {
            cerr << "Error: se esperaba un ';' despues de ')' de procedure" << endl;
            exit(1);
        }
        BlockStmt *block = parseBody();
        FunDec* fu=new FunDec(nombre,returntype,block);
        if (!match(Token::PC)) {
            cerr << "Error: se esperaba un ';' al final de la funcion." << endl;
            exit(1);
        }
        fu->tipos=tipos;
        fu->parametros=parametros;
        return fu;
    }
    else if (match(Token::FUNCTION)) {
        match(Token::ID);
        nombre = previous->text;
        vector<string> parametros;
        vector<string> tipos;
        if (match(Token::PI)) {
            int contador;
            while(match(Token::ID)) {
                contador = 1;
                parametros.push_back(previous->text);
                while (!match(Token::COLON)) {
                    if (!match(Token::COMMA)) {
                        cerr << "Error: se esperaba un ',' o ':' despues de la declaración." << endl;
                        exit(1);
                    }
                    if (!match(Token::ID)) {
                        cerr << "Error: se esperaba una ID despues de ','." << endl;
                        exit(1);
                    }
                    parametros.push_back(previous->text);
                    contador++;
                }
                if (!(match(Token::INTEGER)|match(Token::UNSIGNEDINT)|match(Token::LONGINT)|(match(Token::BOOL)))) {
                    cerr << "Error: se esperaba un tipo de declaracion despues de':'." << endl;
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
                cerr << "Error: se esperaba un ')' o ';' despues del tipo de los argumentos de la funcion." << endl;
                exit(1);
            }
        }
        if (!match(Token::COLON)) {
            cerr << "Error: se esperaba un ':' despues de ')'." << endl;
            exit(1);
        }
        if (!(match(Token::INTEGER) || match(Token::UNSIGNEDINT) || match(Token::LONGINT) || match(Token::BOOL))) {
            cerr << "Error: se esperaba un tipo después de ':'." << endl;
            exit(1);
        }
        returntype = previous->text;
        if (!match(Token::PC)) {
            cerr << "Error: se esperaba un ';' despues del tipo de retorno." << endl;
            exit(1);
        }
        BlockStmt *block = parseBody();
        FunDec* fu=new FunDec(nombre,returntype,block);
        if (!match(Token::PC)) {
            cerr << "Error: se esperaba un ';' al final de la funcion." << endl;
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
        cerr << "Error: se esperaba un 'begin'." <<current->text<<" "<<previous->text<< endl;
        exit(1);
    }
    StatementList* stl=new StatementList();
    Stmt* aux;
    aux = parseStatement();
    while (aux != NULL) {
        if (!match(Token::PC)) {
            cerr << "Error: se esperaba ';' despues de la sentencia."<< endl;
            exit(1);
        }
        stl->add(aux);
        aux = parseStatement();
    }
    if (!match(Token::END)) {
        cerr << "Error: se esperaba un 'end'." << endl;
        exit(1);
    }
    return stl;
}

Stmt* Parser::parseStatement() {
    Stmt* s = NULL;
    Exp* e;
    if (current == NULL) {
        cerr << "Error: Token actual es NULL" << endl;
        exit(1);
    }
    if (match(Token::ID)) {
        string lex = previous->text;
        if (match(Token::ASSIGN)) {
            e = parseCExp();
            s = new AssignStmt(lex, e);
        }else if (match(Token::PI)) {
            if (!match(Token::PD)) {
                ExpList* exps=parseExpList();
                if (!match(Token::PD)) {
                  cerr << "Error: se esperaba un ')' después de la expresión." << endl;
                  exit(1);
                }
                s = new ProcedureCall(lex, exps);
            }
            else {
                s = new ProcedureCall(lex);
            }
        }
        else s = new ProcedureCall(lex);
    }else if (match(Token::WRITELN)) {
        if (!match(Token::PI)) {
            cerr << "Error: se esperaba un '(' después de 'print'." << endl;
            exit(1);
        }
        if (!match(Token::PD)) {
            ExpList* exps = parseExpList();
            if (!match(Token::PD)) {
                cerr << "Error: se esperaba un ')' después de la expresión." << endl;
                exit(1);
            }
            s = new PrintStmt(exps);
        }
        else {
            s =new PrintStmt();
        }
    }else if (match(Token::IF)){
        StatementList* then=nullptr;
        StatementList* else_=nullptr;
        e = parseCExp();
        if (!match(Token::THEN)) {
            cerr << "Error: se esperaba 'then' después de la expresión." << endl;
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
            cerr << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        StatementList* stms = parseStatementList();
        s = new WhileStmt(e,stms);
    }else if (match(Token::FOR)) {
        if (!match(Token::ID)) {
            cerr << "Error: se esperaba 'ID' después del For." << endl;
            exit(1);
            }
        string lex = previous->text;
        if (!match(Token::ASSIGN)) {
            cerr << "Error: se esperaba un ':=' después del identificador." << endl;
            exit(1);
        }
        e = parseCExp();
        bool downto;
        if (match(Token::TO)) downto=false;
        else if (match(Token::DOWNTO)) downto=true;
        else {
            cerr << "Error: se esperaba un TO o DOWNTO." << endl;
            exit(1);
        }
        Exp* end=parseCExp();
        if (!match(Token::DO)) {
            cerr << "Error: se esperaba 'do' después de la expresión." << endl;
            exit(1);
        }
        StatementList* stms = parseStatementList();
        s = new ForStmt(lex,e,end,downto,stms);
    }else if (current->type==Token::BEGIN) {
        s = parseStatementList();
    }
    return s;
}

ExpList* Parser::parseExpList() {
    ExpList* exps=new ExpList();
    Exp* aux;
    aux = parseCExp();
    while (match(Token::COMMA)) {
        exps->add(aux);
        aux = parseCExp();
    }
    exps->add(aux);
    return exps;
}

Exp* Parser::parseCExp(){
    Exp* left = parseExpression();
    if (match(Token::LT) || match(Token::LE) || match(Token::EQ) || match(Token::NOT_EQ) || match(Token::GE) || match(Token::GT)) {
        BinaryOp op;
        if (previous->type == Token::LT){
            op = LT_OP;
        }
        else if (previous->type == Token::LE){
            op = LE_OP;
        }
        else if (previous->type == Token::EQ){
            op = EQ_OP;
        }
        else if (previous->type == Token::NOT_EQ){
            op = NEQ_OP;
        }
        else if (previous->type == Token::GE){
            op = GE_OP;
        }
        else if (previous->type == Token::GT){
            op = GT_OP;
        }
        Exp* right = parseExpression();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseExpression() {
    Exp* left = parseTerm();
    while (match(Token::PLUS) || match(Token::MINUS) || match(Token::OR)) {
        BinaryOp op;
        if (previous->type == Token::PLUS){
            op = PLUS_OP;
        }
        else if (previous->type == Token::MINUS){
            op = MINUS_OP;
        }
        else if (previous->type == Token::OR){
            op = OR_OP;
        }
        Exp* right = parseTerm();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseTerm() {
    Exp* left = parseFactor();
    while (match(Token::MULT) || match(Token::DIV)|| match(Token::MOD) || match(Token::AND)) {
        BinaryOp op;
        if (previous->type == Token::MULT){
            op = MUL_OP;
        }
        else if (previous->type == Token::DIV){
            op = DIV_OP;
        }
        else if (previous->type == Token::MOD){
            op = MOD_OP;
        }
        else if (previous->type == Token::AND){
            op = AND_OP;
        }
        Exp* right = parseFactor();
        left = new BinaryExp(left, right, op);
    }
    return left;
}

Exp* Parser::parseFactor() {
    Exp* e;
    Exp* e1;
    Exp* e2;
    if (match(Token::TRUE)){
        return new BoolExp(1);
    }else if (match(Token::FALSE)){
        return new BoolExp(0);
    }
    else if (match(Token::NUM)) {
        string value = previous->text;
        return new NumberExp(value);
    }
    else if (match(Token::ID)) {
        string s = previous->text;
        if (match(Token::PI)) {
            if (!match(Token::PD)) {
                ExpList* exps = parseExpList();
                if (!match(Token::PD)){
                    cerr << "Falta paréntesis derecho en la llamada a la funcion" << endl;
                    exit(0);
                }
                return new FunctionCallExp(s,exps);
            }
            return new FunctionCallExp(s);
        }
        return new IdentifierExp(s);
    }
    else if (match(Token::PI)){
        e = parseCExp();
        if (!match(Token::PD)){
            cerr << "Falta paréntesis derecho" << endl;
            exit(0);
        }
        e->tieneParen = true;
        return e;
    }
    else if (match(Token::NOT)){
        string s = previous->text;
        Exp* a = parseFactor();
        e = new UnaryExp(a,s);
        return e;
    }
    else if (match(Token::MINUS)){
        string s = previous->text;
        Exp* a = parseFactor();
        e = new UnaryExp(a,s);
        return e;
    }
    else if (match(Token::PLUS)){
        string s = previous->text;
        Exp* a = parseFactor();
        e = new UnaryExp(a,s);
        return e;
    }
    cerr << "Error: se esperaba un número o identificador."<<*previous<<*current << endl;
    exit(0);
}

