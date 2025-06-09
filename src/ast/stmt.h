#ifndef PASCAL_COMPILADOR_STMT_H
#define PASCAL_COMPILADOR_STMT_H
#include "exp.h"
#include <list>

class Stmt {
public:
    virtual ~Stmt() = 0;
    virtual int accept(Visitor* visitor) = 0;
};

// Declaraciones
class VarDeclaration {
public:
    std::string type;
    std::list<std::string> vars;
    VarDeclaration(const std::string& type, const std::list<std::string>& vars);
    int accept(Visitor* visitor);
};

class FunctionDeclaration {
public:
    std::string name;
    std::string returnType;
    std::list<VarDeclaration> params;
    std::list<VarDeclaration> locals;
    std::list<Stmt*> body;
    FunctionDeclaration();
    int accept(Visitor* visitor);
    ~FunctionDeclaration();
};

// Sentencias
class AssignStmt : public Stmt {
public:
    std::string varName;
    Exp* expr;
    AssignStmt(const std::string& name, Exp* e);
    int accept(Visitor* visitor) override;
    ~AssignStmt();
};

class PrintStmt : public Stmt {
public:
    std::list<Exp*> expressions;
    PrintStmt(const std::list<Exp*>& exprs);
    int accept(Visitor* visitor) override;
    ~PrintStmt();
};

class IfStmt : public Stmt {
public:
    Exp* condition;
    Stmt* thenBlock;
    Stmt* elseBlock;
    IfStmt(Exp* cond, Stmt* then, Stmt* elseStmt = nullptr);
    int accept(Visitor* visitor) override;
    ~IfStmt();
};

class WhileStmt : public Stmt {
public:
    Exp* condition;
    Stmt* body;
    WhileStmt(Exp* cond, Stmt* body);
    int accept(Visitor* visitor) override;
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
    int accept(Visitor* visitor) override;
    ~ForStmt();
};

class BlockStmt : public Stmt {
public:
    std::list<Stmt*> statements;
    BlockStmt(const std::list<Stmt*>& stmts);
    int accept(Visitor* visitor) override;
    ~BlockStmt();
};


#endif //PASCAL_COMPILADOR_STMT_H
