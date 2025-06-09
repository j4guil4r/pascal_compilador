#ifndef PASCAL_COMPILADOR_SCANNER_H
#define PASCAL_COMPILADOR_SCANNER_H
#include "../tokens/token.h"

class Scanner {
private:
    std::string input;
    int first, current;
public:
    Scanner(const char* in_s);
    Token* nextToken();
    void reset();
    ~Scanner();
};

void test_scanner(Scanner* scanner);


#endif //PASCAL_COMPILADOR_SCANNER_H
