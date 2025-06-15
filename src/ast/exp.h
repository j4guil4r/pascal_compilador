#ifndef PASCAL_COMPILADOR_EXP_H
#define PASCAL_COMPILADOR_EXP_H

#include <string>
#include <list>
#include "../visitors/visitor.h"

// Operadores binarios
enum BinaryOp {
    PLUS_OP, MINUS_OP, MUL_OP, DIV_OP, MOD_OP, AND_OP, OR_OP, EQ_OP, NEQ_OP, LT_OP, LE_OP, GT_OP, GE_OP
};

class Exp {
public:
    virtual ~Exp() = 0;
    virtual int accept(Visitor* visitor) = 0;
    static std::string binopToStr(BinaryOp op);
};

// Expresiones básicas
class NumberExp : public Exp {
public:
    int value;
    NumberExp(int v);
    int accept(Visitor* visitor) override;
};

class BoolExp : public Exp {
public:
    bool value;
    BoolExp(bool v);
    int accept(Visitor* visitor) override;
};

class IdentifierExp : public Exp {
public:
    std::string name;
    IdentifierExp(const std::string& name);
    int accept(Visitor* visitor) override;
};

// Expresiones compuestas
class BinaryExp : public Exp {
public:
    Exp* left;
    Exp* right;
    BinaryOp op;
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    int accept(Visitor* visitor) override;
    ~BinaryExp();
};

class UnaryExp : public Exp {
public:
    Exp* expr;
    std::string op; // "-" o "not"
    UnaryExp(Exp* e, const std::string& op);
    int accept(Visitor* visitor) override;
    ~UnaryExp();
};

class FunctionCallExp : public Exp {
public:
    std::string funcName;
    ExpList* args;
    FunctionCallExp(const std::string& name, ExpList* args);
    int accept(Visitor* visitor) override;
    ~FunctionCallExp();
};

class ExpList {
    public:
    std::list<Exp*> exps;
    ExpList();
    void add(Exp* stm);
    void accept(Visitor* visitor);
    ~ExpList();
};


#endif //PASCAL_COMPILADOR_EXP_H
