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


Value PrintVisitor::visit(BinaryExp* binary) {
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

Value PrintVisitor::visit(UnaryExp* unary) {
    if (unary->op == "not") cout << "not ";
    else cout << unary->op;
    unary->expr->accept(this);
    return 0;
}

Value PrintVisitor::visit(NumberExp* number) {
    cout << number->num;
    return 0;
}

Value PrintVisitor::visit(BoolExp* boolExp) {
    cout << (boolExp->value ? "true" : "false");
    return 0;
}

Value PrintVisitor::visit(IdentifierExp* id) {
    cout << id->name;
    return 0;
}

Value PrintVisitor::visit(ExpList* expList) {
    bool first = true;
    for (auto exp : expList->exps) {
        if (!first) cout << ", ";
        exp->accept(this);
        first = false;
    }
    return 0;
}


Value PrintVisitor::visit(FunctionCallExp* funcCall) {
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

optional<int64_t> TypeEvalVisitor::extractInt64(const Value& v) {
    if (holds_alternative<int32_t>(v)) return static_cast<int64_t>(get<int32_t>(v));
    if (holds_alternative<uint32_t>(v)) return static_cast<int64_t>(get<uint32_t>(v));
    if (holds_alternative<int64_t>(v)) return get<int64_t>(v);
    return nullopt;
}

void TypeEvalVisitor::checkAssignmentType(const string& varName, const string& type, const Value& value) {
    if (type == "integer") {
        if (holds_alternative<int32_t>(value)) {
            env.update(varName, value);
        }else if (holds_alternative<uint32_t>(value)) {
            uint32_t val = get<uint32_t>(value);
            if (val <= INT32_MAX) {
                env.update(varName, int32_t(val));
            } else {
                cout << "Error: Desbordamiento al asignar unsigned a 'integer' en variable '" << varName << "'" << endl;
                exit(1);
            }
        } else if (holds_alternative<int64_t>(value)) {
            int64_t val = get<int64_t>(value);
            if (val >= INT32_MIN && val <= INT32_MAX) {
                env.update(varName, int32_t(val));
            } else {
                cout << "Error: Desbordamiento al asignar longint a 'integer' en variable '" << varName << "'" << endl;
                exit(1);
            }
        } else {
            cout << "Error: No se puede asignar tipo no numérico a 'integer' en variable '" << varName << "'" << endl;
            exit(1);
        }
    } else if (type == "longint") {
        if (holds_alternative<int64_t>(value)) {
            env.update(varName, value);
        } else if (holds_alternative<int32_t>(value)) {
            env.update(varName, int64_t(get<int32_t>(value)));
        } else if (holds_alternative<uint32_t>(value)) {
            env.update(varName, int64_t(get<uint32_t>(value)));
        } else {
            cout << "Error: No se puede asignar tipo no numérico a 'longint' en variable '" << varName << "'" << endl;
            exit(1);
        }
    } else if (type == "unsigned") {
        if (holds_alternative<uint32_t>(value)) {
            env.update(varName, value);
        } else if (holds_alternative<int32_t>(value)) {
            int32_t val = get<int32_t>(value);
            if (val >= 0) {
                env.update(varName, uint32_t(val));
            } else {
                cout << "Error: No se puede asignar valor negativo a 'unsigned' en variable '" << varName << "'" << endl;
                exit(1);
            }
        } else if (holds_alternative<int64_t>(value)) {
            int64_t val = get<int64_t>(value);
            if (val >= 0 && val <= UINT32_MAX) {
                env.update(varName, uint32_t(val));
            } else {
                cout << "Error: Desbordamiento al asignar longint o asignar valor negativo a 'unsigned' en variable '" << varName << "'" << endl;
                exit(1);
            }
        } else {
            cout << "Error: No se puede asignar tipo no numérico a 'unsigned' en variable '" << varName << "'" << endl;
            exit(1);
        }
    } else if (type == "boolean") {
        if (holds_alternative<bool>(value)) {
            env.update(varName, value);
        } else {
            cout << "Error: Se esperaba tipo boolean en asignación a variable '" << varName << "'" << endl;
            exit(1);
        }
    } else {
        cout << "Error: Tipo desconocido '" << type << "' en variable '" << varName << "'" << endl;
        exit(1);
    }
}


void TypeEvalVisitor::visit(Program* program) {
    env.add_level();
    program->body->accept(this);
    env.remove_level();
}

void TypeEvalVisitor::visit(BlockStmt* block) {
    if (block->vardeclist) block->vardeclist->accept(this);
    if (block->fundeclist) block->fundeclist->accept(this);
    if (block->slist) block->slist->accept(this);
}

void TypeEvalVisitor::visit(StatementList* statementList) {
    for (auto stmt : statementList->stms) {
        stmt->accept(this);
    }
}

void TypeEvalVisitor::visit(VarDec* vd) {
    for (const auto& var : vd->vars) {
        if (env.check(var)) {
            cout << "Error: Variable '" << var << "' ya declarada"<<endl;
            exit(1);
        }
        env.add_var(var, vd->type);
    }
}

void TypeEvalVisitor::visit(VarDecList* varDecList) {
    for (auto vd : varDecList->vardecs) {
        vd->accept(this);
    }
}

void TypeEvalVisitor::visit(FunDec* funcDec) {
    if (functions.count(funcDec->nombre)) {
        cout << "Error: Funcion '" << funcDec->nombre << "' ya definida"<<endl;
        exit(1);
    }
    functions[funcDec->nombre] = funcDec;
}

void TypeEvalVisitor::visit(FunList* funcDecList) {
    for (auto func : funcDecList->Fundcs) {
        func->accept(this);
    }
}

void TypeEvalVisitor::visit(AssignStmt* assign) {
    if (!env.check(assign->varName)) {
        cout << "Error: Variable '" << assign->varName << "' no declarada" << std::endl;
        exit(1);
    }

    string type = env.lookup_type(assign->varName);
    Value value = assign->expr->accept(this);
    checkAssignmentType(assign->varName, type, value);

    if (!functionNameStack.empty() && assign->varName == functionNameStack.top()) {
        functionReturnedStack.top()=true;
    }
}

void TypeEvalVisitor::visit(PrintStmt* print) {
    if (print->expressions) {
        print->expressions->accept(this);
        for (auto result:args) {
            printValue(result);
            cout<<" ";
        }
    }
    cout << endl;
}

void TypeEvalVisitor::visit(IfStmt* ifStmt) {
    Value cond = ifStmt->condition->accept(this);
    if (!holds_alternative<bool>(cond)) {
        cout << "Error: condición del while no es booleana" << std::endl;
        exit(1);
    }

    if (get<bool>(cond)) {
        ifStmt->thenBlock->accept(this);
    } else if (ifStmt->elseBlock) {
        ifStmt->elseBlock->accept(this);
    }
}

void TypeEvalVisitor::visit(WhileStmt* whileStmt) {
    while (true) {
        Value cond = whileStmt->condition->accept(this);
        if (!holds_alternative<bool>(cond)) {
            cout << "Error: condición del while no es booleana" << std::endl;
            exit(1);
        }
        if (!get<bool>(cond)) break;
        whileStmt->body->accept(this);
    }
}

void TypeEvalVisitor::visit(ForStmt* forStmt) {
    if (!env.check(forStmt->varName)) {
        cout << "Error: Variable de control '" << forStmt->varName << "' no declarada" << endl;
        exit(1);
    }

    string controlType = env.lookup_type(forStmt->varName);

    Value start = forStmt->startValue->accept(this);
    Value end = forStmt->endValue->accept(this);

    optional<int64_t> maybeStart = extractInt64(start);
    optional<int64_t> maybeEnd = extractInt64(end);

    if (!maybeStart || !maybeEnd) {
        cerr << "Error: Los límites del for no son numéricos válidos." << endl;
        exit(1);
    }

    int64_t i = maybeStart.value();
    int64_t to = maybeEnd.value();

    if (forStmt->isDownto) {
        if (i < to) {
            cout << "Error: En 'downto', el valor inicial (" << i << ") debe ser mayor o igual al final (" << to << ")" << endl;
            exit(1);
        }
        for (; i >= to; --i) {
            checkAssignmentType(forStmt->varName, controlType, i);
            forStmt->body->accept(this);
        }
    } else {
        if (i > to) {
            cout << "Error: En 'to', el valor inicial (" << i << ") debe ser menor o igual al final (" << to << ")" << endl;
            exit(1);
        }
        for (; i <= to; ++i) {
            checkAssignmentType(forStmt->varName, controlType, i);
            forStmt->body->accept(this);
        }
    }
}


void TypeEvalVisitor::visit(ProcedureCall* procCall) {
    if (!functions.count(procCall->funcName)) {
        cout << "Error: procedimiento '" << procCall->funcName << "' no declarado" << endl;
        exit(1);
    }
    if (procCall->args) {
        procCall->args->accept(this);
    }

    FunDec* func = functions[procCall->funcName];

    if (args.size() != func->tipos.size()) {
        cout << "Error: número incorrecto de argumentos para '" << procCall->funcName << "'" << endl;
        exit(1);
    }

    env.add_level();
    for (size_t i = 0; i < func->tipos.size(); ++i) {
        const string& paramName = func->parametros[i];
        const string& paramType = func->tipos[i];
        env.add_var(paramName, paramType);
        checkAssignmentType(paramName, paramType, args[i]);
    }
    args.clear();

    functionReturnedStack.push(false);
    functionNameStack.push(procCall->funcName);

    func->cuerpo->accept(this);

    if (functionReturnedStack.top()) {
        cout<<"Error interno: Algo anda mal en procedure, no deberia retornar nada"<<endl;
        exit(1);
    }
    functionReturnedStack.pop();
    functionNameStack.pop();
    env.remove_level();
}

Value TypeEvalVisitor::visit(NumberExp* number) {
    try {
        int64_t val = std::stoll(number->num);
        // Primero intentamos representarlo como int32_t si cabe
        if (val >= INT32_MIN && val <= INT32_MAX) {
            return static_cast<int32_t>(val);
        }
        // Si no cabe en int32_t pero sí en int64_t, lo retornamos como longint
        return val;

    } catch (const std::out_of_range&) {
        cout << "Error: Número literal fuera del rango de 'longint': " << number->num << endl;
        exit(1);
    } catch (const std::invalid_argument&) {
        cout << "Error: Número inválido (no numérico) '" << number->num << "'" << endl;
        exit(1);
    } catch (...) {
        cout << "Error: Fallo inesperado al procesar número '" << number->num << "'" << endl;
        exit(1);
    }
}


Value TypeEvalVisitor::visit(BoolExp* boolExp) {
    return boolExp->value;
}

Value TypeEvalVisitor::visit(IdentifierExp* id) {
    if (!env.check(id->name)) {
        cout << "Error: Variable '" << id->name << "' no declarada" << endl;
        exit(1);
    }
    return env.lookup(id->name);
}

Value TypeEvalVisitor::visit(UnaryExp* unary) {
    Value val = unary->expr->accept(this);

    if (unary->op == "not") {
        if (holds_alternative<bool>(val)) {
            return !get<bool>(val);
        }
        cout << "Error: 'not' requiere una expresión booleana" << endl;
        exit(1);
    }

    if (unary->op == "-") {
        if (holds_alternative<int32_t>(val)) return -get<int32_t>(val);
        if (holds_alternative<int64_t>(val)) return -get<int64_t>(val);
        // unsigned no debe permitir '-'
        if (holds_alternative<uint32_t>(val)) {
            cout << "Error: '-' no puede aplicarse a 'unsigned'" << endl;
            exit(1);
        }
        cout << "Error: '-' sólo puede aplicarse a valores numéricos" << endl;
        exit(1);
    }

    if (unary->op == "+") {
        if (holds_alternative<int32_t>(val)) return get<int32_t>(val);
        if (holds_alternative<int64_t>(val)) return get<int64_t>(val);
        if (holds_alternative<uint32_t>(val)) return get<uint32_t>(val);
        cout << "Error: '+' sólo puede aplicarse a valores numéricos" << endl;
        exit(1);
    }

    cout << "Error: Operador unario desconocido '" << unary->op << "'" << endl;
    exit(1);
}

Value TypeEvalVisitor::visit(BinaryExp* binary) {
    Value lhs = binary->left->accept(this);
    Value rhs = binary->right->accept(this);
    auto l = extractInt64(lhs), r = extractInt64(rhs);
    string op = binary->binopToStr(binary->op);

    if (op == "+" || op == "-" || op == "*" || op == "div" || op == "mod") {
        if (!l || !r) {
            cout << "Error: operación aritmética requiere valores numéricos" << endl;
            exit(1);
        }

        int64_t a = *l;
        int64_t b = *r;

        if (op == "+") {
            if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b)) {
                cout << "Error: desbordamiento en suma" << endl;
                exit(1);
            }
            return a + b;
        }
        if (op == "-") {
            if ((b < 0 && a > INT64_MAX + b) || (b > 0 && a < INT64_MIN + b)) {
                cout << "Error: desbordamiento en resta" << endl;
                exit(1);
            }
            return a - b;
        }
        if (op == "*") {
            if (a != 0 && (a > INT64_MAX / b || a < INT64_MIN / b)) {
                cout << "Error: desbordamiento en multiplicación" << endl;
                exit(1);
            }
            return a * b;
        }
        if (op == "div") {
            if (b == 0) {
                cout << "Error: división por cero" << endl;
                exit(1);
            }
            if (a == INT64_MIN && b == -1) {
                cout << "Error: desbordamiento en división" << endl;
                exit(1);
            }
            return a / b;
        }
        if (op == "mod") {
            if (b == 0) {
                cout << "Error: módulo por cero" << endl;
                exit(1);
            }
            return a % b;
        }
    }

    if (op == "and" || op == "or") {
        if (!holds_alternative<bool>(lhs) || !holds_alternative<bool>(rhs)) {
            cout << "Error: operación lógica requiere booleanos" << endl;
            exit(1);
        }
        if (op == "and") return get<bool>(lhs) && get<bool>(rhs);
        if (op == "or") return get<bool>(lhs) || get<bool>(rhs);
    }

    if (!l || !r) {
        cout << "Error: comparación requiere valores numéricos" << endl;
        exit(1);
    }
    if (op == "=") return *l == *r;
    if (op == "<>") return *l != *r;
    if (op == "<") return *l < *r;
    if (op == "<=") return *l <= *r;
    if (op == ">") return *l > *r;
    if (op == ">=") return *l >= *r;

    cout << "Error: operador binario desconocido '" << op << "'" << endl;
    exit(1);
}

Value TypeEvalVisitor::visit(FunctionCallExp* funcCall) {
    const string& name = funcCall->funcName;

    // Verificación de existencia
    if (!functions.count(name)) {
        cout << "Error: Función '" << name << "' no declarada" << endl;
        exit(1);
    }

    // Evaluar argumentos
    if (funcCall->args) {
        funcCall->args->accept(this);
    }

    FunDec* func = functions[name];

    if (args.size() != func->tipos.size()) {
        cout << "Error: número incorrecto de argumentos para '" << name << "'" << endl;
        exit(1);
    }

    // Preparar entorno de ejecución
    env.add_level();
    functionNameStack.push(name);
    functionReturnedStack.push(false);

    // Declarar parámetros
    for (size_t i = 0; i < func->tipos.size(); ++i) {
        const string& paramName = func->parametros[i];
        const string& paramType = func->tipos[i];
        env.add_var(paramName, paramType);
        checkAssignmentType(paramName, paramType, args[i]);
    }
    args.clear();

    // Declarar la variable de retorno (con el nombre de la función)
    env.add_var(name, func->returnType);

    // Ejecutar cuerpo
    func->cuerpo->accept(this);

    // Verificar si se retornó explícitamente
    if (!functionReturnedStack.top()) {
        cout << "Error: la función '" << name << "' no retornó ningún valor" << endl;
        exit(1);
    }

    // Obtener el valor de retorno
    if (!env.check(name)) {
        cout << "Error interno: la variable de retorno '" << name << "' no existe en el entorno" << endl;
        exit(1);
    }

    Value result = env.lookup(name);

    // Limpiar contexto
    functionReturnedStack.pop();
    functionNameStack.pop();
    env.remove_level();

    return result;
}


Value TypeEvalVisitor::visit(ExpList* expList) {
    args.clear();
    for (auto arg : expList->exps) {
        args.push_back(arg->accept(this));
    }
    return 0;
}
void TypeEvalVisitor::printValue(const Value& val) {
    std::visit([](const auto& v) {
        cout << v;
    }, val);
}