//
// Created by Jose Aguilar on 9/06/2025.
//

#ifndef PASCAL_COMPILADOR_VISITOR_H
#define PASCAL_COMPILADOR_VISITOR_H

#include <string>
#include <list>

class Program;
class Block;
class VarDeclaration;
class FunctionDeclaration;
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

class Visitor {
public:
    // Programa
    virtual void visit(Program* program) = 0;

    // Bloques
    virtual void visit(Block* block) = 0;

    // Declaraciones
    virtual void visit(VarDeclaration* varDec) = 0;
    virtual void visit(FunctionDeclaration* funcDec) = 0;

    // Sentencias
    virtual void visit(AssignStmt* assign) = 0;
    virtual void visit(PrintStmt* print) = 0;
    virtual void visit(IfStmt* ifStmt) = 0;
    virtual void visit(WhileStmt* whileStmt) = 0;
    virtual void visit(ForStmt* forStmt) = 0;

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
    void visit(Block* block) override;


};

#endif //PASCAL_COMPILADOR_VISITOR_H
