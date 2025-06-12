#ifndef PASCAL_COMPILADOR_PROGRAM_H
#define PASCAL_COMPILADOR_PROGRAM_H

#include "stmt.h"
#include <list>

class Program {
public:
    std::string ProgramName;
    BlockStmt* body;
    Program(BlockStmt* body,std::string ProgramName);
    ~Program();
    void accept(Visitor* visitor);
};

// Declaraciones Var
class VarDec {
public:
    std::string type;
    std::list<std::string> vars;
    VarDec(std::string type, std::list<std::string> vars);
    void accept(Visitor* visitor);
    ~VarDec();
};

class VarDecList{
public:
    std::list<VarDec*> vardecs;
    VarDecList();
    void VarDecList::add(VarDec* vardec) {
        vardecs.push_back(vardec);
    }
    void accept(Visitor* visitor);
    ~VarDecList();
};

// Declaraciones Funciones
class FunDec {
public:
    std::string nombre;
    std::string returnType;
    std::list<std::string> parametros;
    std::list<std::string> tipos;
    BlockStmt* cuerpo;
    FunDec(std::string nombre,std::string returnType,BlockStmt* cuerpo);
    ~FunDec();
    void accept(Visitor* visitor);
};

class FunDecList{
public:
    std::list<FunDec*> Fundecs;
    void add(FunDec* fundec) {
        Fundecs.push_back(fundec);
    };
    void accept(Visitor* visitor);
    FunDecList();
    ~FunDecList();
};

//Body
class BlockStmt{
public:
    VarDecList* vardeclist;
    FunDecList* fundeclist;
    StatementList* slist;
    BlockStmt(VarDecList* vardecs,FunDecList* fundeclist,StatementList* stms);
    void accept(Visitor* visitor);
    ~BlockStmt();
};
#endif //PASCAL_COMPILADOR_PROGRAM_H
