#ifndef PASCAL_COMPILADOR_STMT_H
#define PASCAL_COMPILADOR_STMT_H
#include "exp.h"
#include "program.h"
#include <list>

// Sentencias
class Stmt {
public:
    virtual ~Stmt() = 0;
    virtual void accept(Visitor* visitor) = 0;
};
class StatementList;

class AssignStmt : public Stmt {
public:
    std::string varName;
    Exp* expr;
    AssignStmt(const std::string& name, Exp* e);
    void accept(Visitor* visitor) override;
    ~AssignStmt();
};

class PrintStmt : public Stmt {
public:
    ExpList* expressions;
    PrintStmt(){}
    PrintStmt(ExpList* exps);
    void accept(Visitor* visitor) override;
    ~PrintStmt();
};

class IfStmt : public Stmt {
public:
    Exp* condition;
    StatementList* thenBlock;
    StatementList* elseBlock;
    IfStmt(Exp* cond, StatementList* then, StatementList* elseStmt);
    void accept(Visitor* visitor) override;
    ~IfStmt();
};

class WhileStmt : public Stmt {
public:
    Exp* condition;
    StatementList* body;
    WhileStmt(Exp* cond, StatementList* body);
    void accept(Visitor* visitor) override;
    ~WhileStmt();
};

class ForStmt : public Stmt {
public:
    std::string varName;
    Exp* startValue;
    Exp* endValue;
    bool isDownto;
    StatementList* body;
    ForStmt(std::string varName,Exp* startValue,Exp* endValue,bool isDownto,StatementList* body);
    void accept(Visitor* visitor) override;
    ~ForStmt();
};

class ProcedureCall : public Stmt {
public:
    string funcName;
    ExpList* args;
    ProcedureCall(std::string funcName);
    ProcedureCall(const std::string& name, ExpList* args);
    void accept(Visitor* visitor) override;
    ~ProcedureCall();
};

class StatementList : public Stmt{
public:
    std::list<Stmt*> stms;
    StatementList();
    void add(Stmt* stm);
    void accept(Visitor* visitor);
    ~StatementList();
};

#endif //PASCAL_COMPILADOR_STMT_H
