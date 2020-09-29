#include "Parser_LL.h"

parserNode* LL::factor() {
    parserNode* nowPN = this->creatNewNode(nullptr, "factor");
    if (nowToken->getTokenType() == OPER) {
        operaToken* tempTkn = (operaToken*)nowToken;
        if (tempTkn->getValueString() == "-" || tempTkn->getValueString() == "+") {
            nowPN->addChild(this->creatNewNode(tempTkn, tempTkn->getValueString()));
            this->match();
            nowPN->addChild(this->factor());
            return nowPN;
        } 
        else if (tempTkn->getValueString() == "(") {
            nowPN->addChild(this->creatNewNode(tempTkn, "("));
            this->match();
            nowPN->addChild(this->factor());
            nowPN->addChild(this->creatNewNode(nowToken, ")"));
            this->match();
            return nowPN;
        }
    } 
    else if (nowToken->getTokenType() == NUM || nowToken->getTokenType() == STR)
}