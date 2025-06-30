//
// Created by Jose Aguilar on 9/06/2025.
//

#ifndef PASCAL_COMPILADOR_VISITOR_H
#define PASCAL_COMPILADOR_VISITOR_H

#include <string>
#include <list>
#include <optional>
#include "../enviroment/enviroment.h"
#include <map>
#include <stack>

class Program;
class BlockStmt;
class FunDec;
class FunList;
class AssignStmt;
class PrintStmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class BinaryExp;
class UnaryExp;
class NumberExp;
class IdentifierExp;
class FunctionCallExp;
class VarDec;
class VarDecList;
class StatementList;
class ProcedureCall;
class ExpList;
class BoolExp;
class Exp;

class Visitor {
public:
    // Programa
    virtual void visit(Program* program) = 0;

    // Bloques
    virtual void visit(BlockStmt* block) = 0;
    virtual void visit(StatementList* StatementList) = 0;

    // Declaraciones
    virtual void visit(VarDec* varDec) = 0;
    virtual void visit(VarDecList* varDecList) = 0;

    //Funcion
    virtual void visit(FunDec* funcDec) = 0;
    virtual void visit(FunList* funcDecList) = 0;

    // Sentencias
    virtual void visit(AssignStmt* assign) = 0;
    virtual void visit(PrintStmt* print) = 0;
    virtual void visit(IfStmt* ifStmt) = 0;
    virtual void visit(WhileStmt* whileStmt) = 0;
    virtual void visit(ForStmt* forStmt) = 0;
    virtual void visit(ProcedureCall* Procedurecall) = 0;

    // Expresiones
    virtual Value visit(BinaryExp* binary) = 0;
    virtual Value visit(UnaryExp* unary) = 0;
    virtual Value visit(NumberExp* number) = 0;
    virtual Value visit(BoolExp* explist) = 0;
    virtual Value visit(IdentifierExp* id) = 0;
    virtual Value visit(FunctionCallExp* funcCall) = 0;
    virtual Value visit(ExpList* explist) = 0;
};

class PrintVisitor : public Visitor {
public:
    void visit (Program* program) override;
    void visit(BlockStmt* block) override;
    void visit(StatementList* statementList) override;
    void visit(VarDec* vd) override;
    void visit(VarDecList* varDecList) override;
    void visit(FunDec* funcDec) override;
    void visit(FunList* funcDecList) override;
    void visit(AssignStmt* assign) override;
    void visit(PrintStmt* print) override;
    void visit(IfStmt* ifStmt) override;
    void visit(WhileStmt* whileStmt) override;
    void visit(ForStmt* forStmt) override;
    Value visit(BinaryExp* binary) override;
    Value visit(UnaryExp* unary) override;
    Value visit(NumberExp* number) override;
    Value visit(BoolExp* boolExp) override;
    Value visit(IdentifierExp* id) override;
    Value visit(ExpList* expList) override;
    Value visit(FunctionCallExp* funcCall) override;
    void visit(ProcedureCall* procCall) override;

};

class TypeEvalVisitor : public Visitor {
private:
    Environment env;
    map<string, FunDec*> functions;
    stack<bool> functionReturnedStack;
    stack<string> functionNameStack;
    vector<Value> args;

    optional<int64_t> extractInt64(const Value& v);

    void checkAssignmentType(const string& var, const string& expectedType, const Value& val);

    // Conversión para imprimir con cout
    void printValue(const Value& val);

public:
    TypeEvalVisitor() {}

    // Programa y bloques
    void visit(Program* program) override;
    void visit(BlockStmt* block) override;
    void visit(StatementList* statementList) override;

    // Declaraciones
    void visit(VarDec* varDec) override;
    void visit(VarDecList* varDecList) override;
    void visit(FunDec* funcDec) override;
    void visit(FunList* funcDecList) override;

    // Sentencias
    void visit(AssignStmt* assign) override;
    void visit(PrintStmt* print) override;
    void visit(IfStmt* ifStmt) override;
    void visit(WhileStmt* whileStmt) override;
    void visit(ForStmt* forStmt) override;
    void visit(ProcedureCall* procCall) override;

    // Expresiones
    Value visit(BinaryExp* binary) override;
    Value visit(UnaryExp* unary) override;
    Value visit(NumberExp* number) override;
    Value visit(BoolExp* boolExp) override;
    Value visit(IdentifierExp* id) override;
    Value visit(FunctionCallExp* funcCall) override;
    Value visit(ExpList* expList) override;
};

// Declaración de la clase GenCodeVisitor adaptada con static link y entorno lexical
class GenCodeVisitor : public Visitor {
private:
    unordered_map<string, int> functionLevels;
    Environment env;
    int offsetActual = -8;
    bool currentFunctionHasReturn = false;
    int labelCounter = 0;
    string currentFunction;
    bool requiereStaticLink = false;
    vector<pair<string, int>> argRegMap;

    void asignarOffset(const std::string& var);
    int obtenerOffset(const std::string& var, int& nivelesArriba);
    void generarStaticLink(int nivelesArriba);

public:
    GenCodeVisitor(){};
    void generar(Program* p);

    // Visitantes de expresiones
    Value visit(NumberExp* exp) override;
    Value visit(BoolExp* exp) override;
    Value visit(IdentifierExp* exp) override;
    Value visit(BinaryExp* exp) override;
    Value visit(UnaryExp* exp) override;
    Value visit(FunctionCallExp* exp) override;
    Value visit(ExpList* expList) override;

    // Visitantes de instrucciones
    void visit(AssignStmt* stmt) override;
    void visit(PrintStmt* stmt) override;
    void visit(IfStmt* stmt) override;
    void visit(WhileStmt* stmt) override;
    void visit(ForStmt* stmt) override;
    void visit(ProcedureCall* stmt) override;

    // Declaraciones
    void visit(VarDec* decl) override;
    void visit(VarDecList* decls) override;
    void visit(FunDec* f) override;
    void visit(FunList* list) override;

    // Estructura
    void visit(StatementList* list) override;
    void visit(BlockStmt* b) override;
    void visit(Program* p) override;
};


#endif //PASCAL_COMPILADOR_VISITOR_H
