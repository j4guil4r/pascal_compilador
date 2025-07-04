#include "visitor.h"
#include "../ast/program.h"
#include "../ast/stmt.h"
#include "../ast/exp.h"

#include <iostream>
using namespace std;

//PRINTVISITOR
void PrintVisitor::visit(Program* program) {
    cout << "program " << program->ProgramName << ';' << endl;
    program->body->accept(this);
    cout << '.' << endl;
}

void PrintVisitor::visit(BlockStmt* blockStmt){

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

//TYPEEVALVISITOR
void TypeEvalVisitor::checkAssignmentType(const string& varName, const string& type, const Value& value) {
    if (type == "integer") {
        if (holds_alternative<int32_t>(value)) {
            env.update(varName, value);
        }else if (holds_alternative<uint32_t>(value)) {
            uint32_t val = get<uint32_t>(value);
            if (val <= INT32_MAX) {
                env.update(varName, int32_t(val));
            } else {
                cerr << "Error: Desbordamiento al asignar en la variable 'integer': '" << varName << "'" << endl;
                exit(1);
            }
        } else if (holds_alternative<int64_t>(value)) {
            int64_t val = get<int64_t>(value);
            if (val >= INT32_MIN && val <= INT32_MAX) {
                env.update(varName, int32_t(val));
            } else {
                cerr << "Error: Desbordamiento al asignar en la variable 'integer': '" << varName << "'" << endl;
                exit(1);
            }
        } else {
            cerr << "Error: No se puede asignar un tipo boolean en la variable 'integer': '" << varName << "'" << endl;
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
            cerr << "Error: No se puede asignar un tipo boolean en la variable 'longint': '" << varName << "'" << endl;
            exit(1);
        }
    } else if (type == "unsignedint") {
        if (holds_alternative<uint32_t>(value)) {
            env.update(varName, value);
        } else if (holds_alternative<int32_t>(value)) {
            int32_t val = get<int32_t>(value);
            if (val >= 0) {
                env.update(varName, uint32_t(val));
            } else {
                cerr << "Error: No se puede asignar valor negativo en la variable 'unsigned': '" << varName << "'" << endl;
                exit(1);
            }
        } else if (holds_alternative<int64_t>(value)) {
            int64_t val = get<int64_t>(value);
            if (val >= 0 && val <= UINT32_MAX) {
                env.update(varName, uint32_t(val));
            } else if (val<0) {
                cerr << "Error: No se puede asignar un valor negativo en la variable 'unsigned': '" << varName << "'" << endl;
                exit(1);
            }
            else {
                cerr << "Error: Desbordamiento al asignar en la variable 'unsigned': '" << varName << "'" << endl;
                exit(1);
            }
        } else {
            cerr << "Error: No se puede asignar un tipo boolean en la variable 'unsigned': '" << varName << "'" << endl;
            exit(1);
        }
    } else if (type == "boolean") {
        if (holds_alternative<bool>(value)) {
            env.update(varName, value);
        } else {
            cerr << "Error: Se esperaba tipo boolean en asignación a variable '" << varName << "'" << endl;
            exit(1);
        }
    } else {
        cerr << "Error: Tipo desconocido '" << type << "' en variable '" << varName << "'" << endl;
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
        if (env.exists_in_current_level(var)) {
            cerr << "Error: Variable '" << var << "' ya declarada en el mismo ámbito" << endl;
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
        cerr << "Error: Funcion '" << funcDec->nombre << "' ya definida"<<endl;
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
        cerr << "Error: Variable '" << assign->varName << "' no declarada" << std::endl;
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
            //printValue(result);
            //cout<<" ";
        }
    }
    args.clear();
    //cout << endl;
}

void TypeEvalVisitor::visit(IfStmt* ifStmt) {
    Value cond = ifStmt->condition->accept(this);
    if (!holds_alternative<bool>(cond)) {
        cerr << "Error: condición del while no es booleana" << std::endl;
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
            cerr << "Error: condición del while no es booleana" << std::endl;
            exit(1);
        }
        if (!get<bool>(cond)) break;
        whileStmt->body->accept(this);
    }
}

void TypeEvalVisitor::visit(ForStmt* forStmt) {
    if (!env.check(forStmt->varName)) {
        cerr << "Error: Variable de control '" << forStmt->varName << "' no declarada" << endl;
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
            cerr << "Error: En 'downto', el valor inicial (" << i << ") debe ser mayor o igual al final (" << to << ")" << endl;
            exit(1);
        }
        for (; i >= to; --i) {
            checkAssignmentType(forStmt->varName, controlType, i);
            forStmt->body->accept(this);
        }
    } else {
        if (i > to) {
            cerr << "Error: En 'to', el valor inicial (" << i << ") debe ser menor o igual al final (" << to << ")" << endl;
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
        cerr << "Error: procedimiento '" << procCall->funcName << "' no declarado" << endl;
        exit(1);
    }

    FunDec* func = functions[procCall->funcName];

    if (func->returnType != "void") {
        cerr << "Error: La funcion '" << func->nombre << "' debe usarse solo en expresiones" << endl;
        exit(1);
    }

    if (procCall->args) {
        procCall->args->accept(this);
    }

    if (args.size() != func->tipos.size()) {
        cerr << "Error: número incorrecto de argumentos para '" << procCall->funcName << "'" << endl;
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
        cerr << "Error: Número literal fuera del rango de 'longint': " << number->num << endl;
        exit(1);
    } catch (const std::invalid_argument&) {
        cerr << "Error: Número inválido (no numérico) '" << number->num << "'" << endl;
        exit(1);
    } catch (...) {
        cerr << "Error: Fallo inesperado al procesar número '" << number->num << "'" << endl;
        exit(1);
    }
}


Value TypeEvalVisitor::visit(BoolExp* boolExp) {
    return boolExp->value;
}

Value TypeEvalVisitor::visit(IdentifierExp* id) {
    if (!env.check(id->name)) {
        cerr << "Error: Variable '" << id->name << "' no declarada" << endl;
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
        cerr << "Error: 'not' requiere una expresión booleana" << endl;
        exit(1);
    }

    if (unary->op == "-") {
        if (holds_alternative<int32_t>(val)) return -get<int32_t>(val);
        if (holds_alternative<int64_t>(val)) return -get<int64_t>(val);
        // unsigned no debe permitir '-'
        if (holds_alternative<uint32_t>(val)) {
            cerr << "Error: '-' no puede aplicarse a 'unsigned'" << endl;
            exit(1);
        }
        cerr << "Error: '-' sólo puede aplicarse a valores numéricos" << endl;
        exit(1);
    }

    if (unary->op == "+") {
        if (holds_alternative<int32_t>(val)) return get<int32_t>(val);
        if (holds_alternative<int64_t>(val)) return get<int64_t>(val);
        if (holds_alternative<uint32_t>(val)) return get<uint32_t>(val);
        cerr << "Error: '+' sólo puede aplicarse a valores numéricos" << endl;
        exit(1);
    }

    cerr << "Error: Operador unario desconocido '" << unary->op << "'" << endl;
    exit(1);
}

Value TypeEvalVisitor::visit(BinaryExp* binary) {
    Value lhs = binary->left->accept(this);
    Value rhs = binary->right->accept(this);
    auto l = extractInt64(lhs), r = extractInt64(rhs);
    string op = binary->binopToStr(binary->op);

    if (op == "+" || op == "-" || op == "*" || op == "div" || op == "mod") {
        if (!l || !r) {
            cerr << "Error: operación aritmética requiere valores numéricos" << endl;
            exit(1);
        }

        int64_t a = *l;
        int64_t b = *r;

        if (op == "+") {
            if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b)) {
                cerr << "Error: desbordamiento en suma" << endl;
                exit(1);
            }
            return a + b;
        }
        if (op == "-") {
            if ((b < 0 && a > INT64_MAX + b) || (b > 0 && a < INT64_MIN + b)) {
                cerr << "Error: desbordamiento en resta" << endl;
                exit(1);
            }
            return a - b;
        }
        if (op == "*") {
            if (a != 0 && (a > INT64_MAX / b || a < INT64_MIN / b)) {
                cerr << "Error: desbordamiento en multiplicación" << endl;
                exit(1);
            }
            return a * b;
        }
        if (op == "div") {
            if (b == 0) {
                cerr << "Error: división por cero" << endl;
                exit(1);
            }
            if (a == INT64_MIN && b == -1) {
                cerr << "Error: desbordamiento en división" << endl;
                exit(1);
            }
            return a / b;
        }
        if (op == "mod") {
            if (b == 0) {
                cerr << "Error: módulo por cero" << endl;
                exit(1);
            }
            return a % b;
        }
    }

    if (op == "and" || op == "or") {
        if (!holds_alternative<bool>(lhs) || !holds_alternative<bool>(rhs)) {
            cerr << "Error: operación lógica requiere booleanos" << endl;
            exit(1);
        }
        if (op == "and") return get<bool>(lhs) && get<bool>(rhs);
        if (op == "or") return get<bool>(lhs) || get<bool>(rhs);
    }

    if (!l || !r) {
        cerr << "Error: comparación requiere valores numéricos" << endl;
        exit(1);
    }
    if (op == "=") return *l == *r; //la igualdad entre variabkles solo defini con numeros
    if (op == "<>") return *l != *r;
    if (op == "<") return *l < *r;
    if (op == "<=") return *l <= *r;
    if (op == ">") return *l > *r;
    if (op == ">=") return *l >= *r;

    cerr << "Error: operador binario desconocido '" << op << "'" << endl;
    exit(1);
}

Value TypeEvalVisitor::visit(FunctionCallExp* funcCall) {
    const string& name = funcCall->funcName;

    // Verificación de existencia
    if (!functions.count(name)) {
        cerr << "Error: Función '" << name << "' no declarada" << endl;
        exit(1);
    }

    FunDec* func = functions[name];

    if (func->returnType == "void") {
        cerr << "Error: El procedimiento '" << name << "' no retorna valor y no puede usarse en una expresión" << endl;
        exit(1);
    }

    // Evaluar argumentos
    if (funcCall->args) {
        funcCall->args->accept(this);
    }

    if (args.size() != func->tipos.size()) {
        cerr << "Error: número incorrecto de argumentos para '" << name << "'" << endl;
        exit(1);
    }

    // Preparar entorno de ejecución
    env.add_level();

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
    functionNameStack.push(name);
    functionReturnedStack.push(false);
    // Ejecutar cuerpo
    func->cuerpo->accept(this);

    // Verificar si se retornó explícitamente
    if (!functionReturnedStack.top()) {
        cerr << "Error: la función '" << name << "' no retornó ningún valor" << endl;
        exit(1);
    }

    // Obtener el valor de retorno
    if (!env.check(name)) {
        cerr << "Error interno: la variable de retorno '" << name << "' no existe en el entorno" << endl;
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
    std::visit([](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, std::monostate>) {
        cout << "<sin valor>";
    } else if constexpr (std::is_same_v<T, bool>) {
        cout << (arg ? "true" : "false");
    } else {
        cout << arg;
    }
    }, val);
}

// GENCODE

void GenCodeVisitor::asignarOffset(const std::string& var) {
    offsetActual -= 8;
    env.add_var_ofset(var, offsetActual);
}

int GenCodeVisitor::obtenerOffset(const std::string& var, int& nivelesArriba) {
    for (int nivel = env.current_level(); nivel >= 1; nivel--) {
        if (env.exists_in_level(nivel, var)) {
            if (nivel == 1) {
                nivelesArriba = -1;
                return 0;
            } else if (nivel == env.current_level()) {
                nivelesArriba = 0;
                return env.get_offset(nivel - 1, var);
            } else {
                nivelesArriba = env.current_level() - nivel;
                return env.get_offset(nivel - 1, var);
            }
        }
    }
    cerr << "Error: Variable no declarada '" << var << "'\n";
    exit(1);
}

void GenCodeVisitor::generar(Program* p) {
    cout << ".data\n";
    cout << "print_fmt: .string \"%ld\\n\"\n";
    env.add_level();
    p->body->vardeclist->accept(this);
    cout<<".text\n";
    currentFunction = "main";
    p->accept(this);
    env.remove_level();
    cout << ".section .note.GNU-stack,\"\",@progbits\n";
}

void GenCodeVisitor::visit(Program* p) {
    cout << " .globl " << currentFunction << "\n";
    p->body->accept(this);
}

void GenCodeVisitor::visit(BlockStmt* b) {
    cout << currentFunction << ":\n";
    cout << " pushq %rbp\n";
    cout << " movq %rsp, %rbp\n";
    if (env.current_level()>1) {
        for (const auto& [reg, offset] : argRegMap) {
            cout << " mov " << reg << ", " << offset << "(%rbp)\n";
        }

        int actual=offsetActual;

        if (currentFunctionHasReturn) {
            env.add_var(currentFunction, "boolean");
            asignarOffset(currentFunction);
        }
        if (b->vardeclist) b->vardeclist->accept(this);
        if (-offsetActual > -actual) {
            cout << " subq $" << -offsetActual << ", %rsp\n";
        }
    }
    if (b->slist) {b->slist->accept(this);}

    // cargar valor de retorno en %rax si la función no es void
    if (currentFunctionHasReturn) {
        int offset = env.get_offset(env.current_level()-1, currentFunction);
        cout << " movq " << offset << "(%rbp), %rax\n";
    }

    cout << ".end_" << currentFunction << ":\n";
    cout << "leave\n";
    cout << "ret\n";

    if (b->fundeclist) b->fundeclist->accept(this);
}
void GenCodeVisitor::visit(VarDec* dec) {
    for (const auto& var : dec->vars) {
        env.add_var(var, dec->type);
        if (env.current_level() == 1) {
            cout << var << ": .quad 0\n";
        } else {
            asignarOffset(var);
        }
    }
}

void GenCodeVisitor::visit(VarDecList* list) {
    for (auto* decl : list->vardecs) decl->accept(this);
}

void GenCodeVisitor::visit(FunDec* f) {
    env.add_level();
    offsetActual=0;

    currentFunction = f->nombre;
    currentFunctionHasReturn = (f->returnType != "void");;
    cout << ".globl " << currentFunction << "\n";

    vector<string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    argRegMap.clear();

    for (size_t i = 0; i < f->parametros.size(); ++i) {
        const string& var = f->parametros[i];
        env.add_var(var, f->tipos[i]);
        asignarOffset(var);

        if (i < argRegs.size()) {
            argRegMap.push_back({argRegs[i], env.get_offset(env.current_level() - 1, var)});
        } else {
            cerr << "Error: demasiados parámetros en función '" << f->nombre << "'\n";
            exit(1);
        }
    }

    f->cuerpo->accept(this);
    env.remove_level();
}

void GenCodeVisitor::visit(AssignStmt* stmt) {
    stmt->expr->accept(this);
    int nivelesArriba;
    int offset = obtenerOffset(stmt->varName, nivelesArriba);

    if (nivelesArriba == -1) {
        cout << " movq %rax, " << stmt->varName << "(%rip)\n";
    } else if (nivelesArriba == 0) {
        cout << " movq %rax, " << offset << "(%rbp)\n";
    } else {
        cerr<<"No puedo acceder a variables locales de otras funciones aun"<<endl;
        exit(1);
    }
}

Value GenCodeVisitor::visit(IdentifierExp* e) {
    int nivelesArriba;
    int offset = obtenerOffset(e->name, nivelesArriba);

    if (nivelesArriba == -1) {
        cout << " movq " << e->name << "(%rip), %rax\n";
    } else if (nivelesArriba == 0) {
        cout << " movq " << offset << "(%rbp), %rax\n";
    } else {
        cerr<<"Todavia no puedo llamar a variables locales de otras funcioens"<<endl;
        exit(1);
    }
    return 0;
}

Value GenCodeVisitor::visit(NumberExp* e) {
    cout << " movq $" << e->num << ", %rax\n";
    return 0;
}

Value GenCodeVisitor::visit(BoolExp* e) {
    cout << " movq $" << (e->value ? 1 : 0) << ", %rax\n";
    return 0;
}

Value GenCodeVisitor::visit(BinaryExp* e) {
    if (e->op == MOD_OP || e->op == DIV_OP) {
        // Evaluar left
        e->left->accept(this); // %rax ← left
        cout << " pushq %rax\n";

        // Evaluar right
        e->right->accept(this); // %rax ← right
        cout << " movq %rax, %rcx\n";

        // Restaurar left en %rax
        cout << " popq %rax\n";

        // Sign extend
        cout << " cqto\n";
        cout << " idivq %rcx\n";

        if (e->op == MOD_OP) {
            cout << " movq %rdx, %rax\n";  // %rax ← residuo
        }

        return 0;
    }

    // Caso general para los demás operadores
    e->left->accept(this);
    cout << " pushq %rax\n"; // guarda left

    e->right->accept(this);
    cout << " movq %rax, %rcx\n"; // %rcx ← right
    cout << " popq %rax\n";       // %rax ← left

    switch (e->op) {
        case PLUS_OP:
            cout << " addq %rcx, %rax\n";
            break;

        case MINUS_OP:
            cout << " subq %rcx, %rax\n";
            break;

        case MUL_OP:
            cout << " imulq %rcx, %rax\n";
            break;

        case AND_OP:
            cout << " andq %rcx, %rax\n";
            break;

        case OR_OP:
            cout << " orq %rcx, %rax\n";
            break;

        case EQ_OP:
            cout << " cmpq %rcx, %rax\n";
            cout << " sete %al\n";
            cout << " movzbq %al, %rax\n";
            break;

        case NEQ_OP:
            cout << " cmpq %rcx, %rax\n";
            cout << " setne %al\n";
            cout << " movzbq %al, %rax\n";
            break;

        case LT_OP:
            cout << " cmpq %rcx, %rax\n";
            cout << " setl %al\n";
            cout << " movzbq %al, %rax\n";
            break;

        case LE_OP:
            cout << " cmpq %rcx, %rax\n";
            cout << " setle %al\n";
            cout << " movzbq %al, %rax\n";
            break;

        case GT_OP:
            cout << " cmpq %rcx, %rax\n";
            cout << " setg %al\n";
            cout << " movzbq %al, %rax\n";
            break;

        case GE_OP:
            cout << " cmpq %rcx, %rax\n";
            cout << " setge %al\n";
            cout << " movzbq %al, %rax\n";
            break;

        default:
            cerr << "Error: Operador binario no implementado: " << Exp::binopToStr(e->op) << endl;
            exit(1);
    }

    return 0;
}

Value GenCodeVisitor::visit(FunctionCallExp* e) {
    vector<string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int regIndex = 0;
    if (e->args) {
        for (Exp* arg : e->args->exps) {
            arg->accept(this);
            if (regIndex < argRegs.size()) {
                cout << " movq %rax, " << argRegs[regIndex++] << "\n";
            } else {
                cout << " pushq %rax\n";
            }
        }
    }

    cout << " call " << e->funcName << "\n";
    return 0;
}

void GenCodeVisitor::visit(ProcedureCall* e) {
    vector<string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int regIndex = 0;

    if (e->args) {
        for (auto arg : e->args->exps) {
            arg->accept(this);
            if (regIndex < argRegs.size()) {
                cout << " movq %rax, " << argRegs[regIndex++] << "\n";
            } else {
                cout << " pushq %rax\n";
            }
        }
    }

    cout << " call " << e->funcName << "\n";
}

void GenCodeVisitor::visit(PrintStmt* stmt) {
    if (stmt->expressions) {
        for (Exp* exp : stmt->expressions->exps) {
            exp->accept(this);
            cout << " movq %rax, %rsi\n";
            cout << " leaq print_fmt(%rip), %rdi\n";
            cout << " xorl %eax, %eax\n";
            cout << " call printf@PLT\n";
        }
    }
}

void GenCodeVisitor::visit(IfStmt* stm) {
    int label = labelCounter++;
    stm->condition->accept(this);
    cout << " cmpq $0, %rax" << endl;
    cout << " je else_" << label << endl;
    stm->thenBlock->accept(this);
    cout << " jmp endif_" << label << endl;
    cout << " else_" << label << ":" << endl;
    if (stm->elseBlock) stm->elseBlock->accept(this);
    cout << "endif_" << label << ":" << endl;
}

void GenCodeVisitor::visit(WhileStmt* stm) {
    int label = labelCounter++;
    string startLabel = "while_" + std::to_string(label);
    string endLabel = "endwhile_" + std::to_string(label);

    cout << startLabel << ":\n";
    stm->condition->accept(this);
    cout << " cmpq $0, %rax\n";
    cout << " je " << endLabel << "\n";
    stm->body->accept(this);
    cout << " jmp " << startLabel << "\n";
    cout << endLabel << ":\n";
}

void GenCodeVisitor::visit(ForStmt* stmt) {
    int label = labelCounter++;
    string loopLabel = "for_loop_" + to_string(label);
    string endLabel = "for_end_" + to_string(label);

    stmt->startValue->accept(this);
    cout << " movq %rax, %r12\n";
    stmt->endValue->accept(this);
    cout << " movq %rax, %r13\n";

    cout << loopLabel << ":\n";
    cout << " cmpq %r13, %r12\n";
    cout << (stmt->isDownto ? " jl " : " jg ") << endLabel << "\n";

    int nivelesArriba;
    int offset = obtenerOffset(stmt->varName, nivelesArriba);
    if (nivelesArriba == -1) {
        cout << " movq %r12, " << stmt->varName << "(%rip)\n";
    } else if (nivelesArriba == 0) {
        cout << " movq %r12, " << offset << "(%rbp)\n";
    } else {
        cerr<<"No puedo acceder a las variables locales de otras funciones aun"<<endl;
        exit(1);
    }

    stmt->body->accept(this);

    cout << " " << (stmt->isDownto ? "decq" : "incq") << " %r12\n";
    cout << " jmp " << loopLabel << "\n";
    cout << endLabel << ":\n";
}


void GenCodeVisitor::visit(FunList* list) {
    for (auto* f : list->Fundcs) f->accept(this);
}

void GenCodeVisitor::visit(StatementList* list) {
    for (auto* stmt : list->stms) stmt->accept(this);
}

Value GenCodeVisitor::visit(UnaryExp* e) {
    e->expr->accept(this);
    if (e->op == "-") {
        cout << " negq %rax\n";
    } else if (e->op == "not") {
        cout << " notq %rax\n";
    } else {
        cerr << "Operador unario no soportado: " << e->op << endl;
        exit(1);
    }
    return 0;
}

Value GenCodeVisitor::visit(ExpList* list) {
    return 0;
}


