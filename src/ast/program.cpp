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
FunDec::FunDec(std::string nombre_,std::string returnType_,BlockStmt* cuerpo_){
    nombre=nombre_;
    returnType=returnType_;
    cuerpo=cuerpo_;
}

void FunDec::accept(Visitor* visitor) {
    visitor->visit(this);
}

FunDec::~FunDec() {
    delete cuerpo;
}

// Funcion List
FunList::FunList() {}

void FunList::accept(Visitor* visitor) {
    visitor->visit(this);
}

FunList::~FunList() {
    for (auto v : Fundcs) {
        delete v;
    }
}

//Body
BlockStmt::BlockStmt(VarDecList* vardecs,FunList* fundeclist, StatementList* stms)
    : vardeclist(vardecs), slist(stms), fundeclist(fundeclist) {}

void BlockStmt::accept(Visitor* visitor) {
    visitor->visit(this);
}

BlockStmt::~BlockStmt() {
    delete vardeclist;
    delete slist;
}