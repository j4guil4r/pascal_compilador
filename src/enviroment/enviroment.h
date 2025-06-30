#ifndef ENV
#define ENV

#include <unordered_map>
#include <list>
#include <vector>
#include <string>
#include <variant>
#include <iostream>
#include <cstdint>

using namespace std;

using Value = variant<monostate,int32_t, uint32_t, int64_t, bool>;

class Environment {
private:
    vector<unordered_map<string, Value>> levels;
    vector<unordered_map<string, string>> type_levels;
    vector<unordered_map<string, int>> offset_levels;

    int search_rib(const string& var) {
        for (int i = levels.size() - 1; i >= 0; --i) {
            if (levels[i].count(var)) return i;
        }
        return -1;
    }

public:
    int current_level() const {
        return levels.size();
    }

    void clear() {
        levels.clear();
        type_levels.clear();
        offset_levels.clear();
    }

    void add_level() {
        levels.emplace_back();
        type_levels.emplace_back();
        offset_levels.emplace_back();
    }

    bool remove_level() {
        if (!levels.empty()) {
            levels.pop_back();
            type_levels.pop_back();
            offset_levels.pop_back();
            return true;
        }
        return false;
    }

    void add_var(const string& var, const string& type) {
        if (levels.empty()) {
            cout << "Error: No hay niveles activos\n";
            exit(1);
        }

        if (type != "integer" && type != "unsignedint" && type != "longint" && type != "boolean") {
            cout << "Error: Tipo desconocido para declarar una variable: '" << type << "'\n";
            exit(1);
        }

        levels.back()[var] = std::monostate{}; // variable sin valor inicial
        type_levels.back()[var] = type;
    }

    void add_var_ofset(const string& var, int offset) {
        offset_levels.back()[var] = offset;
    }

    bool exists_in_level(int level, const string& var) const {
        if (level < 0 || level >= (int)levels.size()) return false;
        return levels[level].count(var) > 0;
    }

    int get_offset(int level, const string& var) const {
        if (level < 0 || level >= (int)offset_levels.size()) {
            cout << "Error: Nivel fuera de rango.\n";
            exit(1);
        }
        if (offset_levels[level].count(var) == 0) {
            cout << "Error: Variable '" << var << "' no tiene offset registrado.\n";
            exit(1);
        }
        return offset_levels[level].at(var);
    }


    void update(const string& var, const Value& val) {
        int idx = search_rib(var);
        if (idx == -1) {
            cout << "Variable no declarada: " << var << "\n";
            exit(1);
        }
        levels[idx][var] = val;
    }
    // Verificar si una variable está declarada
    bool check(string x) {
        int idx = search_rib(x);
        return (idx >= 0);
    }

    bool exists_in_current_level(const string& var) const {
        if (levels.empty()) return false;
        return levels.back().count(var) > 0;
    }


    Value lookup(const string& var) {
        int idx = search_rib(var);
        if (idx == -1) {
            cout << "Error: Variable no declarada: '" << var << "'\n";
            exit(1);
        }

        const Value& val = levels[idx][var];

        if (holds_alternative<std::monostate>(val)) {
            cout << "Error: La variable '" << var << "' no tiene un valor asignado.\n";
            exit(1);
        }

        return val;
    }

    string lookup_type(const string& var) {
        int idx = search_rib(var);
        if (idx == -1) {
            cout << "Variable no declarada: " << var << "\n";
            exit(1);
        }
        return type_levels[idx][var];
    }
};

#endif
