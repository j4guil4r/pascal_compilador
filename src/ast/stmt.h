#ifndef PASCAL_COMPILADOR_STMT_H
#define PASCAL_COMPILADOR_STMT_H
#include "exp.h"
#include <list>

class Stmt {
public:
    virtual ~Stmt() = 0;
    virtual void accept(Visitor* visitor) = 0;
};

// Declaraciones
class VarDec {
public:
    std::string type;
    std::list<std::string> vars;
    VarDec(std::string type, std::list<std::string> vars);
    void accept(Visitor* visitor);
    ~VarDec();
};

class VarDecList{
public:
    std::list<VarDec*> vardecs;
    VarDecList();
    void add(VarDec* vardec);
    void accept(Visitor* visitor);
    ~VarDecList();
};

class FunctionDeclaration {
public:
    std::string name;
    std::string returnType;
    std::list<VarDec> params;
    std::list<VarDec> locals;
    std::list<Stmt*> body;
    FunctionDeclaration(
        const std::string& name,
        const std::string& returnType,
        std::list<Stmt*>& body);
    void accept(Visitor* visitor);
    ~FunctionDeclaration();
};

// Sentencias
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
    Stmt* body;
    ForStmt();
    void accept(Visitor* visitor) override;
    ~ForStmt();
};
class StatementList {
public:
    std::list<Stmt*> stms;
    StatementList();
    void add(Stmt* stm);
    void accept(Visitor* visitor);
    ~StatementList();
};

class BlockStmt{
public:
    VarDecList* vardecs;
    StatementList* slist;
    BlockStmt(VarDecList* vardecs, StatementList* stms);
    void accept(Visitor* visitor);
    ~BlockStmt();
};

class Program {
public:
    BlockStmt* body;
    Program(BlockStmt* body);
    ~Program();
};

#endif //PASCAL_COMPILADOR_STMT_H
