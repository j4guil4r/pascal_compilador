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
    //TODO: Preguntarle al profe sobre la gramatica y el orden.
    if (blockStmt->firstVarDec) {
        if (blockStmt->vardeclist) blockStmt->vardeclist->accept(this);
        if (blockStmt->fundeclist) blockStmt->fundeclist->accept(this);
    }
    else {
        if (blockStmt->fundeclist) blockStmt->fundeclist->accept(this);
        if (blockStmt->vardeclist) blockStmt->vardeclist->accept(this);
    }
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
    if (!varDecList->vardecs.empty()) cout << "var "<<endl;
    for(auto vd : varDecList->vardecs)
        vd->accept(this);
}

void PrintVisitor::visit(FunDec* funDec) {
    if (funDec->returnType == "void") cout << "procedure ";
    else cout << "function ";
    cout << funDec->nombre << '(';

    vector<string> parametrosVec(funDec->parametros.begin(), funDec->parametros.end());

    bool first = true;
    for (int i = 0; i < parametrosVec.size() && i < funDec->tipos.size(); ++i) {
        if (!first) cout << "; ";
        cout << parametrosVec[i] << " : " << funDec->tipos[i];
        first = false;
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
    if(binary->tieneParen) cout << '(';
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
    if(binary->tieneParen) cout << ')';
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


//===========================================================================//
//AUX TV:
bool TypeVisitor::isNumericType(int type) {
    return type == TYPE_INTEGER || type == TYPE_LONGINT || type == TYPE_UNSIGNEDINT;
}

int TypeVisitor::getResultType(int leftType, int rightType) {
    // Si ambos son iguales, conserva el tipo
    if (leftType == rightType) return leftType;

    // Reglas de promoción de tipos
    if (leftType == TYPE_LONGINT || rightType == TYPE_LONGINT) {
        return TYPE_LONGINT;
    }
    if (leftType == TYPE_UNSIGNEDINT || rightType == TYPE_UNSIGNEDINT) {
        return TYPE_UNSIGNEDINT;
    }
    return TYPE_INTEGER;
}

string TypeVisitor::typeToString(int type) {
    switch(type) {
        case TYPE_INTEGER: return "integer";
        case TYPE_LONGINT: return "longint";
        case TYPE_UNSIGNEDINT: return "unsignedint";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_VOID: return "void";
        default: return "unknown";
    }
}

//--------------------------------------------------------------------------//
void TypeVisitor::visit(Program* program) {
    env.add_level();
    program->body->accept(this);
    env.remove_level();
}

void TypeVisitor::visit(BlockStmt* block) {
    env.add_level();

    if (block->vardeclist) block->vardeclist->accept(this);
    if (block->fundeclist) block->fundeclist->accept(this);
    if (block->slist) block->slist->accept(this);

    env.remove_level();
}

void TypeVisitor::visit(StatementList* statementList) {
    for (auto stmt : statementList->stms) {
        stmt->accept(this);
    }
}

void TypeVisitor::visit(VarDec* vd) {
    for (const auto& var : vd->vars) {
        if (env.check(var)) {
            cerr << "Error semántico: Variable '" << var << "' ya declarada" << endl;
            continue;
        }
        env.add_var(var, vd->type);
    }
}

void TypeVisitor::visit(VarDecList* varDecList) {
    for (auto vd : varDecList->vardecs) {
        vd->accept(this);
    }
}

void TypeVisitor::visit(FunDec* funcDec) {

    for (const auto& type : funcDec->tipos) {
        if (type == "void") {
            cerr << "Error: Parámetro no puede ser de tipo void" << endl;
        }
    }

    // Registrar función en la tabla
    functionTable[funcDec->nombre] = make_pair(funcDec->tipos, funcDec->returnType);
    retornoFuncActual = funcDec->returnType;

    // Nuevo ámbito para parámetros y locales
    env.add_level();

    // Registrar parámetros
    auto pIt = funcDec->parametros.begin();
    auto tIt = funcDec->tipos.begin();
    while (pIt != funcDec->parametros.end() && tIt != funcDec->tipos.end()) {
        env.add_var(*pIt, *tIt);
        ++pIt;
        ++tIt;
    }

    // Procesar cuerpo
    funcDec->cuerpo->accept(this);

    // Verificar que las funciones no void tengan return
    if (funcDec->returnType != "void") {
        // Aquí deberías verificar que haya al menos un return
        // (necesitarías un atributo adicional para rastrear esto)
    }

    env.remove_level();
} // <----- REVISAR

void TypeVisitor::visit(FunList* funcDecList) {
    for (auto funcDec : funcDecList->Fundcs) {
        funcDec->accept(this);
    }
}

void TypeVisitor::visit(AssignStmt* assign) {
    if (!env.check(assign->varName)) {
        cerr << "Error semántico: Variable '" << assign->varName << "' no declarada" << endl;
        return;
    }

    string varType = env.lookup_type(assign->varName);
    int exprType = assign->expr->accept(this);
    string exprTypeStr = typeToString(exprType);

    if (varType != exprTypeStr) {
        cerr << "Error de tipos: No se puede asignar " << exprTypeStr << " a '" << assign->varName << "' de tipo " << varType << endl;
    }
}

void TypeVisitor::visit(PrintStmt* print) {
    if (print->expressions) {
        for (auto exp : print->expressions->exps) {
            exp->accept(this);
        }
    }
}

void TypeVisitor::visit(IfStmt* ifStmt) {
    int condType = ifStmt->condition->accept(this);
    if (condType != TYPE_BOOLEAN) {
        cerr << "Error de tipos: La condición del if debe ser booleana" << endl;
    }

    ifStmt->thenBlock->accept(this);
    if (ifStmt->elseBlock) {
        ifStmt->elseBlock->accept(this);
    }
}

void TypeVisitor::visit(WhileStmt* whileStmt) {
    int condType = whileStmt->condition->accept(this);
    if (condType != TYPE_BOOLEAN) {
        cerr << "Error de tipos: La condición del while debe ser booleana" << endl;
    }
    whileStmt->body->accept(this);
}

void TypeVisitor::visit(ForStmt* forStmt) {
    if (!env.check(forStmt->varName)) {
        cerr << "Error semántico: Variable de control '" << forStmt->varName << "' no declarada" << endl;
    }
    else {
        string varType = env.lookup_type(forStmt->varName);
        if (varType != "integer" && varType != "longint") {
            cerr << "Error de tipos: Variable de control '" << forStmt->varName << "' debe ser integer o longint" << endl;
        }
    }

    int startType = forStmt->startValue->accept(this);
    int endType = forStmt->endValue->accept(this);

    if (!isNumericType(startType) || !isNumericType(endType)) {
        cerr << "Error de tipos: Límites del for deben ser numéricos" << endl;
    }

    forStmt->body->accept(this);
}

int TypeVisitor::visit(BinaryExp* binary) {
    int leftType = binary->left->accept(this);
    int rightType = binary->right->accept(this);

    switch(binary->op) {
        case PLUS_OP: case MINUS_OP: case MUL_OP: case DIV_OP: case MOD_OP:
            // Operaciones aritméticas
            if (!isNumericType(leftType) || !isNumericType(rightType)) {
                cerr << "Error: Operación aritmética con tipos no numéricos" << endl;
                return TYPE_UNKNOWN;
            }
            return getResultType(leftType, rightType);

        case AND_OP: case OR_OP:
            // Operaciones lógicas
            if (leftType != TYPE_BOOLEAN || rightType != TYPE_BOOLEAN) {
                cerr << "Error: Operación lógica con tipos no booleanos" << endl;
                return TYPE_UNKNOWN;
            }
            return TYPE_BOOLEAN;

        case EQ_OP: case NEQ_OP:
            // Igualdad/desigualdad
            if ((leftType == TYPE_BOOLEAN && rightType != TYPE_BOOLEAN) ||
                (rightType == TYPE_BOOLEAN && leftType != TYPE_BOOLEAN)) {
                cerr << "Error: Comparación entre boolean y no boolean" << endl;
                return TYPE_UNKNOWN;
            }
            return TYPE_BOOLEAN;

        case LT_OP: case LE_OP: case GT_OP: case GE_OP:
            // Comparaciones
            if (!isNumericType(leftType) || !isNumericType(rightType)) {
                cerr << "Error: Comparación con tipos no numéricos" << endl;
                return TYPE_UNKNOWN;
            }
            return TYPE_BOOLEAN;
    }
    return TYPE_UNKNOWN;
}

int TypeVisitor::visit(UnaryExp* unary) {
    int exprType = unary->expr->accept(this);

    if (unary->op == "not") {
        if (exprType != TYPE_BOOLEAN) {
            cerr << "Error: Operador 'not' requiere operando booleano" << endl;
            return TYPE_UNKNOWN;
        }
        return TYPE_BOOLEAN;
    }
    else { // Operador -
        if (!isNumericType(exprType)) {
            cerr << "Error: Operador '-' requiere operando numérico" << endl;
            return TYPE_UNKNOWN;
        }
        if (exprType == TYPE_UNSIGNEDINT) {
            cerr << "Unsigned int no lleva signo" << endl;
            return TYPE_UNKNOWN;
        }
        return exprType; // Conserva el tipo (integer, longint, etc)
    }
}

int TypeVisitor::visit(NumberExp* number) {
    //return 1; // integer
    return TYPE_INTEGER;
}

int TypeVisitor::visit(BoolExp* boolExp) {
    //return 2; // boolean
    return TYPE_BOOLEAN;
}

int TypeVisitor::visit(IdentifierExp* id) {
    if (!env.check(id->name)) {
        cerr << "Error semántico: Variable '" << id->name << "' no declarada" << endl;
        return 0; // tipo desconocido
    }

    string type = env.lookup_type(id->name);
    return (type == "integer") ? 1 :
           (type == "boolean") ? 2 : 0;
}

int TypeVisitor::visit(ExpList* expList) {
    // Verificamos cada expresión pero retornamos el tipo del último elemento
    int lastType = 0;
    for (auto exp : expList->exps) {
        lastType = exp->accept(this);
    }
    return lastType;
}

int TypeVisitor::visit(FunctionCallExp* funcCall) {
    if (!functionTable.count(funcCall->funcName)) {
        cerr << "Error semántico: Función '" << funcCall->funcName << "' no declarada" << endl;
        return 0;
    }

    auto& funcInfo = functionTable[funcCall->funcName];
    const auto& paramTypes = funcInfo.first;

    // Verificar número de parámetros
    if (funcCall->args && funcCall->args->exps.size() != paramTypes.size()) {
        cerr << "Error semántico: Número incorrecto de argumentos para '"
             << funcCall->funcName << "' (esperaba " << paramTypes.size()
             << ", obtuvo " << funcCall->args->exps.size() << ")" << endl;
        return 0;
    }

    // Verificar tipos de parámetros
    if (funcCall->args) {
        size_t i = 0;
        for (auto exp : funcCall->args->exps) {
            int argType = exp->accept(this);
            string expectedType = paramTypes[i];
            string actualType = (argType == 1) ? "integer" :
                                (argType == 2) ? "boolean" : "unknown";

            if (expectedType != actualType) {
                cerr << "Error de tipos: Argumento " << (i+1) << " de '"
                     << funcCall->funcName << "' debería ser " << expectedType
                     << " pero es " << actualType << endl;
            }
            i++;
        }
    }

    // Retornar el tipo de retorno de la función
    return (funcInfo.second == "integer") ? 1 :
           (funcInfo.second == "boolean") ? 2 : 0;
}

void TypeVisitor::visit(ProcedureCall* procCall) {
    if (!functionTable.count(procCall->funcName)) {
        cerr << "Error semántico: Procedimiento '" << procCall->funcName << "' no declarado" << endl;
        return;
    }

    auto& procInfo = functionTable[procCall->funcName];

    // Verificar que sea un procedimiento (retorno void)
    if (procInfo.second != "void") {
        cerr << "Error semántico: '" << procCall->funcName << "' es una función, no un procedimiento" << endl;
    }

    // Verificación de parámetros (similar a FunctionCallExp)
    if (procCall->args) {
        if (procCall->args->exps.size() != procInfo.first.size()) {
            cerr << "Error semántico: Número incorrecto de argumentos para '"
                 << procCall->funcName << "'" << endl;
            return;
        }

        size_t i = 0;
        for (auto exp : procCall->args->exps) {
            int argType = exp->accept(this);
            string expectedType = procInfo.first[i];
            string actualType = (argType == 1) ? "integer" :
                                (argType == 2) ? "boolean" : "unknown";

            if (expectedType != actualType) {
                cerr << "Error de tipos: Argumento " << (i+1) << " de '"
                     << procCall->funcName << "' debería ser " << expectedType
                     << " pero es " << actualType << endl;
            }
            i++;
        }
    }
}