#include "Parser_LL.h"

void LL::factor() {
    if (nowToken->getTokenType() == OPER) {
        operaToken* tempTkn = (operaToken*)nowToken;
        if (tempTkn->getValueString() == "-") {
            this->match();
            this->factor();
            if (tempTkn->getValueString() == ")") {
                this->match();
                return;
            } else {
                
            }
        }
        if (tempTkn->getValueString() == "(") {

        }
    }
}