#include "lexical.hpp"

int main(){
    lexicalAnalysis proc("C:\\Users\\Zhao Yufeng\\Documents\\VSCode\\C++\\Satoru InoriComplier\\Satoru InoriComplier\\lexciTest.sau");
    token* t = proc.lookForward(1);
    t->printToken();
    while (t->getTokenType() > 0 || t->getTokenType() == -1) {
        t = proc.lookForward(1);
        t->printToken();
        proc.getNextToken();
    }
    return 0;
}