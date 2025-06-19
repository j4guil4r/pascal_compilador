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
    bool first = true;
    for (auto var: vd->vars) {
        if (!first) cout << ", ";
        cout << var;
        first = false;
    }
    cout << " : " <<vd->type << ';' << endl;
}

void PrintVisitor::visit(VarDecList* varDecList) {
    cout << "var "<<endl;
    for(auto vd : varDecList->vardecs)
        vd->accept(this);
}

void PrintVisitor::visit(FunDec* funDec) {
    if (funDec->returnType == "void") cout << "procedure ";
    else cout << "function ";
    cout << funDec->nombre << '(';

    if(!funDec->parametros.empty()) {
        bool first = true;
        for(auto p = funDec->parametros.begin(), t = funDec->tipos.begin();
            p != funDec->parametros.end() && t != funDec->tipos.end();
            p++, t++) {
            if (!first) cout << ";";
            cout << *p << " : " << *t;
            first = false;
        }
    }
    cout << ')';
    if (funDec->returnType != "void") {
        cout << " : " << funDec->returnType;
    }
    cout << ";" << endl;
    funDec->cuerpo->accept(this);
    cout << ";" << endl;
}

void PrintVisitor::visit(FunList* funList) {
    for(auto fun : funList->Fundcs) fun->accept(this);
}

void PrintVisitor::visit(AssignStmt *assign) {
    cout << assign->varName << " := ";
    assign->expr->accept(this);
}

void PrintVisitor::visit(PrintStmt* print) {
    cout << "writeln(";
    if (print->expressions  && !print->expressions->exps.empty()) {
        print->expressions->accept(this);
    }
    cout << ")";
}

void PrintVisitor::visit(IfStmt* ifStmt) {
    cout << "if ";
    ifStmt->condition->accept(this);
    cout << " then" << endl;
    ifStmt->thenBlock->accept(this);
    if (ifStmt->elseBlock) {
        cout << endl;
        cout << "else" << endl;
        ifStmt->elseBlock->accept(this);
    }
}

void PrintVisitor::visit(WhileStmt* whileStmt) {
    cout << "while ";
    whileStmt->condition->accept(this);
    cout << " do" << endl;
    whileStmt->body->accept(this);
}

void PrintVisitor::visit(ForStmt* forStmt) {
    cout << "for " << forStmt->varName << " := ";
    forStmt->startValue->accept(this);
    cout << (forStmt->isDownto ? " downto " : " to ");
    forStmt->endValue->accept(this);
    cout << " do" << endl;
    forStmt->body->accept(this);
}


int PrintVisitor::visit(BinaryExp* binary) {
    binary->left->accept(this);
    switch (binary->op) {
        case PLUS_OP: cout << " + "; break;
        case MINUS_OP: cout << " - "; break;
        case MUL_OP: cout << " * "; break;
        case DIV_OP: cout << " div "; break;
        case MOD_OP: cout << " mod "; break;
        case AND_OP: cout << " and "; break;
        case OR_OP: cout << " or "; break;
        case EQ_OP: cout << " = "; break;
        case NEQ_OP: cout << " <> "; break;
        case LT_OP: cout << " < "; break;
        case LE_OP: cout << " <= "; break;
        case GT_OP: cout << " > "; break;
        case GE_OP: cout << " >= "; break;
    }
    binary->right->accept(this);
    return 0;
}

int PrintVisitor::visit(UnaryExp* unary) {
    if (unary->op == "not") cout << "not ";
    else cout << unary->op;
    unary->expr->accept(this);
    return 0;
}

int PrintVisitor::visit(NumberExp* number) {
    cout << number->value;
    return 0;
}

int PrintVisitor::visit(BoolExp* boolExp) {
    cout << (boolExp->value ? "true" : "false");
    return 0;
}

int PrintVisitor::visit(IdentifierExp* id) {
    cout << id->name;
    return 0;
}

int PrintVisitor::visit(ExpList* expList) {
    bool first = true;
    for (auto exp : expList->exps) {
        if (!first) cout << ", ";
        exp->accept(this);
        first = false;
    }
    return 0;
}


int PrintVisitor::visit(FunctionCallExp* funcCall) {
    cout << funcCall->funcName;
    if (funcCall->args && !funcCall->args->exps.empty()) {
        cout << "(";
        funcCall->args->accept(this);
        cout << ")";
    }
    else cout << "()";
    return 0;
}

void PrintVisitor::visit(ProcedureCall* procCall) {
    cout << procCall->funcName;
    if (procCall->args && !procCall->args->exps.empty()) {
        cout << "(";
        procCall->args->accept(this);
        cout << ")";
    }
}