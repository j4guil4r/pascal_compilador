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

using Value = variant<int32_t, uint32_t, int64_t, bool>;

class Environment {
private:
    vector<unordered_map<string, Value>> levels;
    vector<unordered_map<string, string>> type_levels;

    int search_rib(const string& var) {
        for (int i = levels.size() - 1; i >= 0; --i) {
            if (levels[i].count(var)) return i;
        }
        return -1;
    }

public:
    void clear() {
        levels.clear();
        type_levels.clear();
    }

    void add_level() {
        levels.emplace_back();
        type_levels.emplace_back();
    }

    bool remove_level() {
        if (!levels.empty()) {
            levels.pop_back();
            type_levels.pop_back();
            return true;
        }
        return false;
    }

    void add_var(const string& var, const string& type) {
        if (levels.empty()) {
            cerr << "Error: No hay niveles activos\n";
            exit(1);
        }

        if (type == "integer")
            levels.back()[var] = int32_t(0);
        else if (type == "unsigned")
            levels.back()[var] = uint32_t(0);
        else if (type == "longint")
            levels.back()[var] = int64_t(0);
        else if (type == "boolean")
            levels.back()[var] = false;
        else {
            cerr << "Tipo desconocido: " << type << "\n";
            exit(1);
        }

        type_levels.back()[var] = type;
    }

    void update(const string& var, const Value& val) {
        int idx = search_rib(var);
        if (idx == -1) {
            cerr << "Variable no declarada: " << var << "\n";
            exit(1);
        }
        levels[idx][var] = val;
    }
    // Verificar si una variable está declarada
    bool check(string x) {
        int idx = search_rib(x);
        return (idx >= 0);
    }

    Value lookup(const string& var) {
        int idx = search_rib(var);
        if (idx == -1) {
            cerr << "Variable no declarada: " << var << "\n";
            exit(1);
        }
        return levels[idx][var];
    }

    string lookup_type(const string& var) {
        int idx = search_rib(var);
        if (idx == -1) {
            cerr << "Variable no declarada: " << var << "\n";
            exit(1);
        }
        return type_levels[idx][var];
    }
};

#endif
