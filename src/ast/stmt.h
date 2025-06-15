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
    std::list<Exp*> expressions;
    PrintStmt(const std::list<Exp*>& exprs);
    void accept(Visitor* visitor) override;
    ~PrintStmt();
};

class IfStmt : public Stmt {
public:
    Exp* condition;
    Stmt* thenBlock;
    Stmt* elseBlock;
    IfStmt(Exp* cond, Stmt* then, Stmt* elseStmt = nullptr);
    void accept(Visitor* visitor) override;
    ~IfStmt();
};

class WhileStmt : public Stmt {
public:
    Exp* condition;
    Stmt* body;
    WhileStmt(Exp* cond, Stmt* body);
    void accept(Visitor* visitor) override;
    ~WhileStmt();
};

class ForStmt : public Stmt {
public:
    std::string varName;
    Exp* startValue;
    Exp* endValue;
    bool isDownto;
    BlockStmt* body;
    ForStmt(std::string varName,Exp* startValue,Exp* endValue,bool isDownto,BlockStmt* body);
    void accept(Visitor* visitor) override;
    ~ForStmt();
};

class ProcedureCall : public Stmt {
public:
    std::string funcName;
    std::list<Exp*> args;
    ProcedureCall(const std::string& name, std::list<Exp*> args);
    void accept(Visitor* visitor) override;
    ~ProcedureCall();
};

class StatementList {
public:
    std::list<Stmt*> stms;
    StatementList();
    void add(Stmt* stm);
    void accept(Visitor* visitor);
    ~StatementList();
};

#endif //PASCAL_COMPILADOR_STMT_H
