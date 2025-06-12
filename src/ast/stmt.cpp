#include "stmt.h"

// Stmt
Stmt::~Stmt() {}

// AssignStmt
AssignStmt::AssignStmt(const std::string& name, Exp* e)
    : varName(name), expr(e) {}

void AssignStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

AssignStmt::~AssignStmt() {
    delete expr;
}

// PrintStmt
PrintStmt::PrintStmt(const std::list<Exp*>& exprs)
    : expressions(exprs) {}

void PrintStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

PrintStmt::~PrintStmt() {
    for (auto e : expressions) {
        delete e;
    }
}

// IfStmt
IfStmt::IfStmt(Exp* cond, Stmt* then, Stmt* elseStmt)
    : condition(cond), thenBlock(then), elseBlock(elseStmt) {}

void IfStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

IfStmt::~IfStmt() {
    delete condition;
    delete thenBlock;
    if (elseBlock) delete elseBlock;
}

// WhileStmt
WhileStmt::WhileStmt(Exp* cond, Stmt* body)
    : condition(cond), body(body) {}

void WhileStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

WhileStmt::~WhileStmt() {
    delete condition;
    delete body;
}

// ForStmt
ForStmt::ForStmt() : startValue(nullptr), endValue(nullptr), isDownto(false), body(nullptr) {}

void ForStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

ForStmt::~ForStmt() {
    delete startValue;
    delete endValue;
    delete body;
}

//ProcedureCall
ProcedureCall ::ProcedureCall (const std::string& name, std::list<Exp*> args)
        : funcName(name), args(args) {}

ProcedureCall ::~ProcedureCall () {
    for (auto arg : args) delete arg;
}
void ProcedureCall ::accept(Visitor* visitor) { return visitor->visit(this); }

// StatementList
StatementList::StatementList() {}

void StatementList::add(Stmt* stm) {
    stms.push_back(stm);
}

void StatementList::accept(Visitor* visitor) {
    visitor->visit(this);
}

StatementList::~StatementList() {
    for (auto s : stms) {
        delete s;
    }
}

