#include "program.h"

// Program
Program::Program(BlockStmt* body,std::string ProgramName_)
    : body(body),ProgramName(ProgramName_) {}

Program::~Program() {
    delete body;
}

// VarDec
VarDec::VarDec(std::string type, std::list<std::string> vars)
    : type(type), vars(vars) {}

void VarDec::accept(Visitor* visitor) {
    return visitor->visit(this);
}

VarDec::~VarDec() {}

// VarDecList
VarDecList::VarDecList() {}

void VarDecList::accept(Visitor* visitor) {
    visitor->visit(this);
}

VarDecList::~VarDecList() {
    for (auto v : vardecs) {
        delete v;
    }
}

// FunDec
FunDec::FunDec(std::string nombre,std::string returnType,BlockStmt* cuerpo):nombre(nombre), returnType(returnType), cuerpo(cuerpo) {}

void FunDec::accept(Visitor* visitor) {
    visitor->visit(this);
}

FunDec::~FunDec() {
    delete cuerpo;
}

// FunDecList
FunDecList::FunDecList() {}

void FunDecList::accept(Visitor* visitor) {
    visitor->visit(this);
}

FunDecList::~FunDecList() {
    for (auto v : Fundecs) {
        delete v;
    }
}

//Body
BlockStmt::BlockStmt(VarDecList* vardecs,FunDecList* fundeclist, StatementList* stms)
    : vardeclist(vardecs), slist(stms), fundeclist(fundeclist) {}

void BlockStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

BlockStmt::~BlockStmt() {
    delete vardeclist;
    delete slist;
}