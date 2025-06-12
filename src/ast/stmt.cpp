#include "stmt.h"

// Stmt
Stmt::~Stmt() {}

// VarDec
VarDec::VarDec(std::string type, std::list<std::string> vars)
    : type(type), vars(vars) {}

void VarDec::accept(Visitor* visitor) {
    return visitor->visit(this);
}

VarDec::~VarDec() {}

// VarDecList
VarDecList::VarDecList() {}

void VarDecList::add(VarDec* vardec) {
    vardecs.push_back(vardec);
}

void VarDecList::accept(Visitor* visitor) {
    visitor->visit(this);
}

VarDecList::~VarDecList() {
    for (auto v : vardecs) {
        delete v;
    }
}

// FunctionDeclaration
FunctionDeclaration::FunctionDeclaration(const std::string& name,
                                         const std::string& returnType,
                                         std::list<Stmt*>& body)
    : name(name), returnType(returnType), body(body) {}

void FunctionDeclaration::accept(Visitor* visitor) {
    visitor->visit(this);
}

FunctionDeclaration::~FunctionDeclaration() {
    for (auto stmt : body) {
        delete stmt;
    }
}

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

// BlockStmt
BlockStmt::BlockStmt(VarDecList* vardecs, StatementList* stms)
    : vardecs(vardecs), slist(stms) {}

void BlockStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

BlockStmt::~BlockStmt() {
    delete vardecs;
    delete slist;
}

// Program
Program::Program(BlockStmt* body)
    : body(body) {}

Program::~Program() {
    delete body;
}
