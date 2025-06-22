#ifndef PASCAL_COMPILADOR_EXP_H
#define PASCAL_COMPILADOR_EXP_H

#include <string>
#include <list>
#include "../visitors/visitor.h"
#include <cstdint>

// Operadores binarios
enum BinaryOp {
    PLUS_OP, MINUS_OP, MUL_OP, DIV_OP, MOD_OP, AND_OP, OR_OP, EQ_OP, NEQ_OP, LT_OP, LE_OP, GT_OP, GE_OP
};

class Exp {
public:
    bool tieneParen = false;
    virtual ~Exp() = 0;
    virtual int accept(Visitor* visitor) = 0;
    static std::string binopToStr(BinaryOp op);
};

class NumberExp : public Exp {
public:
    string num;
    NumberExp(string num);
    virtual string getType() const {return "??";};
    virtual int accept(Visitor* visitor) override;
    virtual int64_t getIntValue() const {return stoll(num);}
};

class IntExp : public NumberExp {
public:
    IntExp(string num);
    string getType() const {return "integer";}
    int accept(Visitor* visitor) override;
    int32_t getValue() const {return static_cast<int32_t>(getIntValue());}

};

class LongIntExp : public NumberExp {
public:
    LongIntExp(string num);
    string getType() const {return "longint";}
    int accept(Visitor* visitor) override;
    int64_t getValue() const {return static_cast<int64_t>(getIntValue());}
};

class UIntExp : public NumberExp {
public:
    UIntExp(string num);
    string getType() const {return "unsignedint";}
    int accept(Visitor* visitor) override;
    uint32_t getValue() const {return static_cast<uint32_t>(getIntValue());}
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
    FunctionCallExp(const std::string& name);
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
