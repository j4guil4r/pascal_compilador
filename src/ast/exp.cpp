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
NumberExp::NumberExp(int v) : value(v) {}
int NumberExp::accept(Visitor* visitor) { return visitor->visit(this); }

// IdentifierExp
IdentifierExp::IdentifierExp(const std::string& name) : name(name) {}
int IdentifierExp::accept(Visitor* visitor) { return visitor->visit(this); }

// BinaryExp
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp op) : left(l), right(r), op(op) {}
BinaryExp::~BinaryExp() { delete left; delete right; }
int BinaryExp::accept(Visitor* visitor) { return visitor->visit(this); }

// UnaryExp
UnaryExp::UnaryExp(Exp* e, const std::string& op) : expr(e), op(op) {}
UnaryExp::~UnaryExp() { delete expr; }
int UnaryExp::accept(Visitor* visitor) { return visitor->visit(this); }

// FunctionCallExp
FunctionCallExp::FunctionCallExp(const std::string& name, std::list<Exp*> args)
        : funcName(name), args(args) {}

FunctionCallExp::~FunctionCallExp() {
    for (auto arg : args) delete arg;
}
int FunctionCallExp::accept(Visitor* visitor) { return visitor->visit(this); }

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