#include "visitor.h"
#include "../ast/program.h"
#include "../ast/stmt.h"
#include "../ast/exp.h"

#include <iostream>
using namespace std;


void PrintVisitor::visit(Program* program) {
    cout << "program " << program->ProgramName << ';' << endl;
    program->body->accept(this);
    cout << '.' << endl;
}

void PrintVisitor::visit(BlockStmt* blockStmt){
    if (blockStmt->vardeclist) blockStmt->vardeclist->accept(this);
    if (blockStmt->fundeclist) blockStmt->fundeclist->accept(this);
    blockStmt->slist->accept(this);
}

void PrintVisitor::visit(StatementList* statementList) {
    cout << "begin" << endl;
    for (auto stmt : statementList->stms) {
        stmt->accept(this);
        cout << ";" << endl;
    }
    cout << "end";
}

void PrintVisitor::visit(VarDec *vd) {
    cout << "var ";
    bool first = true;
    for (auto var: vd->vars) {
        if (!first) cout << ", ";
        cout << var;
        first = false;
    }
    cout << vd->type << ';' << endl;
}