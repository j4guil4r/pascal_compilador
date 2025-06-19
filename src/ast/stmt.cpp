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
PrintStmt::PrintStmt(ExpList* exprs): expressions(exprs) {}

void PrintStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

PrintStmt::~PrintStmt() {
    delete expressions;
}

// IfStmt
IfStmt::IfStmt(Exp* cond, StatementList* then, StatementList* elseStmt)
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
WhileStmt::WhileStmt(Exp* cond, StatementList* body)
    : condition(cond), body(body) {}

void WhileStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

WhileStmt::~WhileStmt() {
    delete condition;
    delete body;
}

// ForStmt
ForStmt::ForStmt(std::string varName,Exp* startValue,Exp* endValue,bool isDownto,StatementList* body) : varName(varName), startValue(startValue), endValue(endValue), isDownto(isDownto), body(body) {}

void ForStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

ForStmt::~ForStmt() {
    delete startValue;
    delete endValue;
    delete body;
}

//ProcedureCall
ProcedureCall ::ProcedureCall(std::string funcName):funcName(funcName){}
ProcedureCall ::ProcedureCall (const std::string& name, ExpList* args): funcName(name), args(args) {}

ProcedureCall ::~ProcedureCall () {
    delete args;
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

