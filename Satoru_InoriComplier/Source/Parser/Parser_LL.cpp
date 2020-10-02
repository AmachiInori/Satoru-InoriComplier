#include "Parser_LL.h"

LL::LL(lexicalAnalysis* _lexAna) : _lex(_lexAna) {}

parserNode* LL::creatNewNode(token* _token, std::string _idfi) {
        newedPN.push_back(new parserNode(_token, _idfi));
        return newedPN.back();
}

parserNode* LL::factor() {
    if (nowToken->getTokenType() == OPER) {
        parserNode* nowPN = this->creatNewNode(nullptr, "factor");
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
            nowPN->addChild(this->expressionC0());
            if ((nowToken->getTokenType() == OPER) && 
                (tempTkn = (operaToken*)nowToken) && 
                (tempTkn->getValueString() == ")")) {
                nowPN->addChild(this->creatNewNode(tempTkn, ")"));
                this->match();
            } else {
                //”Ô∑®¥ÌŒÛ ”“¿®∫≈ ß≈‰
            }
            return nowPN;
        }
    } 
    else if (nowToken->getTokenType() == NUM || nowToken->getTokenType() == STR) {
        parserNode* nowPN = this->creatNewNode(nowToken, "factor");
        return nowPN;
    }
    else if (nowToken->getTokenType() == ID) { //ID -> IDS FIRST
        idToken* majorId = (idToken*)nowToken;
        this->match();
        parserNode* proTail = this->idTail();
        if (proTail == nullptr) {
            parserNode* nowPN = this->creatNewNode(majorId, "id");
            return nowPN;
        } else {
            parserNode* nowPN = this->creatNewNode(nullptr, "idFactor");
            nowPN->addChild(this->creatNewNode(majorId, "id"));
            nowPN->addChild(proTail);
            return nowPN;
        }
    }
}

parserNode* LL::idTail() {
    parserNode* nowPN = this->creatNewNode(nullptr, "idFactor");
    if (nowToken->getTokenType() == OPER) {
        operaToken* tempTkn = (operaToken*)nowToken;
        if (tempTkn->getValueString() == "[") {
            nowPN->addChild(this->creatNewNode(tempTkn, "["));
            this->match();
            nowPN->addChild(this->expressionC0());
            if ((nowToken->getTokenType() == OPER) && 
                (tempTkn = (operaToken*)nowToken) && 
                (tempTkn->getValueString() == "]")) {
                nowPN->addChild(this->creatNewNode(tempTkn, "]"));
                this->match();
            } else {
                //”Ô∑®¥ÌŒÛ ”“¿®∫≈ ß≈‰
            }
        }
        else if (tempTkn->getValueString() == "(") {
            nowPN->addChild(this->creatNewNode(tempTkn, "("));
            this->match();
            nowPN->addChild(this->parameter());
            if ((nowToken->getTokenType() == OPER) && 
                (tempTkn = (operaToken*)nowToken) && 
                (tempTkn->getValueString() == ")")) {
                nowPN->addChild(this->creatNewNode(tempTkn, ")"));
                this->match();
            } else {
                //”Ô∑®¥ÌŒÛ ”“¿®∫≈ ß≈‰
            }
        }
    }
    return nullptr;
}