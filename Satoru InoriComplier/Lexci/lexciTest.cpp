#include "lex.h"
#include "DFA.h"

int main(){
    lexAna proc("C:\\Users\\Zhao Yufeng\\Documents\\VSCode\\C++\\Satoru InoriComplier\\Satoru InoriComplier\\lexciTest.sau");
    token* t = proc.getNextToken();
    while (t->getTokenType() != 0) {
        t->printToken();
        t = proc.getNextToken();
    }
    return 0;
}