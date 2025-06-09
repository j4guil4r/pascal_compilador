#ifndef PASCAL_COMPILADOR_PROGRAM_H
#define PASCAL_COMPILADOR_PROGRAM_H

#include "stmt.h"
#include <list>

class Program {
public:
    std::list<VarDeclaration> globalVars;
    std::list<FunctionDeclaration> functions;
    BlockStmt* mainBlock;

    Program(const std::list<VarDeclaration>& globals,
            const std::list<FunctionDeclaration>& funcs,
            BlockStmt* block);
    ~Program();
    int accept(Visitor* visitor);
};

#endif //PASCAL_COMPILADOR_PROGRAM_H
