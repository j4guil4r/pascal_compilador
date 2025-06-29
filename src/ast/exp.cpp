#include "exp.h"
#include <stdexcept>

Exp::~Exp() {}

std::string Exp::binopToStr(BinaryOp op) {
    switch(op) {
        case PLUS_OP: return "+";
        case MINUS_OP: return "-";
        case MUL_OP: return "*";
        case DIV_OP: return "div";
        case MOD_OP: return "mod";
        case AND_OP: return "and";
        case OR_OP: return "or";
        case EQ_OP: return "=";
        case NEQ_OP: return "<>";
        case LT_OP: return "<";
        case LE_OP: return "<=";
        case GT_OP: return ">";
        case GE_OP: return ">=";
        default: throw std::runtime_error("Operador binario desconocido");
    }
}

// NumberExp
NumberExp::NumberExp(const string& num): num(num) {}
Value NumberExp::accept(Visitor *visitor) {
    return visitor->visit(this);
}


//BoolExp
BoolExp::BoolExp(bool v) : value(v) {}
Value BoolExp::accept(Visitor* visitor) { return visitor->visit(this); }

// IdentifierExp
IdentifierExp::IdentifierExp(const std::string& name) : name(name) {}
Value IdentifierExp::accept(Visitor* visitor) { return visitor->visit(this); }

// BinaryExp
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp op) : left(l), right(r), op(op) {}
BinaryExp::~BinaryExp() { delete left; delete right; }
Value BinaryExp::accept(Visitor* visitor) { return visitor->visit(this); }

// UnaryExp
UnaryExp::UnaryExp(Exp* e, const std::string& op) : expr(e), op(op) {}
UnaryExp::~UnaryExp() { delete expr; }
Value UnaryExp::accept(Visitor* visitor) { return visitor->visit(this); }

// FunctionCallExp
FunctionCallExp::FunctionCallExp(const std::string& name):funcName(name){}

FunctionCallExp::FunctionCallExp(const std::string& name, ExpList* args): funcName(name), args(args) {}

FunctionCallExp::~FunctionCallExp() {
    delete args;
}
Value FunctionCallExp::accept(Visitor* visitor) { return visitor->visit(this); }

// ExpList
ExpList::ExpList() {}

void ExpList::add(Exp* exp) {
    exps.push_back(exp);
}

void ExpList::accept(Visitor* visitor) {
    visitor->visit(this);
}

ExpList::~ExpList() {
    for (auto e : exps) {
        delete e;
    }
}