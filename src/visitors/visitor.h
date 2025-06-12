//
// Created by Jose Aguilar on 9/06/2025.
//

#ifndef PASCAL_COMPILADOR_VISITOR_H
#define PASCAL_COMPILADOR_VISITOR_H

#include <string>
#include <list>

class Program;
class BlockStmt;
class FunDec;
class FunDecList;
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
    virtual void visit(FunDecList* funcDecList) = 0;

    // Sentencias
    virtual void visit(AssignStmt* assign) = 0;
    virtual void visit(PrintStmt* print) = 0;
    virtual void visit(IfStmt* ifStmt) = 0;
    virtual void visit(WhileStmt* whileStmt) = 0;
    virtual void visit(ForStmt* forStmt) = 0;
    virtual void visit(ProcedureCall* Procedurecall) = 0;

    // Expresiones
    virtual int visit(BinaryExp* binary) = 0;
    virtual int visit(UnaryExp* unary) = 0;
    virtual int visit(NumberExp* number) = 0;
    virtual int visit(IdentifierExp* id) = 0;
    virtual int visit(FunctionCallExp* funcCall) = 0;
};

class PrintVisitor : public Visitor {
public:
    void imprimir(Program* program);
    void visit(BlockStmt* block) override;


};

#endif //PASCAL_COMPILADOR_VISITOR_H
