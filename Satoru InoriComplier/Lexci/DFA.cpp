//GB2312
#ifndef _DFA_CPP_
#define _DFA_CPP_
#include "DFA.h"
#include "lex.h"

DFA::DFA(lexAna* _host) : host(_host) {}

inline void DFA::stateTo(_DFAstate newState) {
    lastState = state;
    state = newState;
}

inline void DFA::reset()  { state = lastState = DFAstate::START; }

bool DFA::trans(char _iptc) {
    using namespace DFAstate;
    switch (this->state) {
    case START: // 0
        if (isDigit(_iptc) && _iptc != '0') {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        else if (isEmptyChar(_iptc)) {
            stateTo(START);
            return true;
        }
        else if (_iptc == '0') {
            stateTo(NUM_MAIN_FIRST_ZERO_IN);
            return true;
        } 
        else if (_iptc == 0) {
            stateTo(END);
            return true;
        }
        else if (isIdChar(_iptc)) {
            stateTo(ID_FIRST_CHAR_IN);
            return true;
        }
        else if (isReptbOperatorChar(_iptc)) {
            stateTo(OP_RPTB_FIRST_IN);
            return true;
        }
        else if (isSingleOperatorChar(_iptc)) {
            stateTo(OP_SINGLE_CHAR_IN);
            return true;
        }
        else if (isOpreatorCharOnlyDblWEqual(_iptc)) {
            stateTo(OP_NOMDBL_FIRST_IN);
            return true;
        }
        else if (_iptc == '"') {
            stateTo(STR_QUO_IN);
            return true;
        }
        break;

    case OP_NUM_MAIN_PONE_IN: // 此状态未启用
        if (isDigit(_iptc)) {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        if (_iptc == '=' || _iptc == host->getLastChar()) {
            stateTo(OP_DBL_ACC);
            return true;
        }
        break;

    case NUM10_MAIN_INPUTING_DIGIT: // 2
        if (isDigit(_iptc)) {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        else if (_iptc == 'U' || _iptc == 'u') {
            stateTo(NUM10_ACCEPT_UNSIGNED_INT);
            return true;
        }
        else if (_iptc == '.') {
            stateTo(NUM10_FLT_DOT_IN);
            return true;
        }

    case NUM10_ACCEPT_UNSIGNED_INT: // 3
        //错误情况：对于终点的状态进行了转换，应初始化。
        break;
    
    case NUM_MAIN_FIRST_ZERO_IN: // 4
        if (isDigit(_iptc)) {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            host->pointReturn(); // 此处回退一格，不会遇到双回退情况
            return true;
        }
        else if (_iptc == 'x') { //接16进制整数图
            return true;
        }
        else if (_iptc == 'X') { //接2进制整数图
            return true;
        }
        break;

    case NUM10_FLT_DOT_IN: // 5
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INPUTING_DIGIT);
            return true;
        }
        break;
    
    case NUM10_FLT_INPUTING_DIGIT: //6
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INPUTING_DIGIT);
            return true;
        } 
        else if (_iptc == 'e' || _iptc == 'E') {
            stateTo(NUM10_FLT_INDEX_E_IN);
            return true;
        } 
        break;

    case NUM10_FLT_INDEX_E_IN: // 7
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INDEX_INPUT_DIGIT);
            return true;
        }
        else if (_iptc == '+' || _iptc == '-') {
            stateTo(NUM10_FLT_INDEX_PONE_IN);
            return true;
        }
        break;
    
    case NUM10_FLT_INDEX_INPUT_DIGIT: // 8
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INDEX_INPUT_DIGIT);
            return true;
        }
        break;

    case NUM10_FLT_INDEX_PONE_IN: // 9
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INDEX_INPUT_DIGIT);
            return true;
        }
        break;
    
    case ID_FIRST_CHAR_IN: //10
        if (isIdChar(_iptc) || isDigit(_iptc)) {
            stateTo(ID_CHAR_INPUT);
            return true;
        }
        break;

    case ID_CHAR_INPUT: // 11
        if (isIdChar(_iptc) || isDigit(_iptc)) {
            stateTo(ID_CHAR_INPUT);
            return true;
        }
        break;

    case OP_NOMDBL_FIRST_IN: // 14
        if (_iptc == '=') {
            stateTo(OP_DBL_ACC);
            return true;
        }
        break;

    case OP_RPTB_FIRST_IN: // 16
        if (_iptc == '=' || _iptc == host->getLastChar()) {
            stateTo(OP_DBL_ACC);
            return true;
        }
        break;
    
    case STR_QUO_IN: // 17
        if (_iptc > 0) {
            stateTo(STR_CHAR_INPUT);
            return true;
        }
        break;
    
    case STR_CHAR_INPUT: //18
        if (_iptc == '"') {
            stateTo(STR_END_QUO_IN);
            return true;
        }
        else if (_iptc > 0) {
            stateTo(STR_CHAR_INPUT);
            return true;
        }
    }
    return false;
}

token* DFA::bulidToken(_ACCstate _accKind, std::string _accString) {
    using namespace DFAstate;
    if (host->findInIdTable(_accString)) return host->idTable[_accString];
    switch (_accKind) {
    case _NUM10_INT:
        return new intToken(_accString);
        break;
    case _NUM10_FLT:
        return new floatToken(_accString);
        break;
    case _NUM10_FLT_WITHE:
        return new floatToken(_accString);
        break;
    case _NUM10_UINT:
        return new UintToken(std::string(&_accString[0], &_accString[_accString.size() - 1]));
        break;
    case _ID: 
        {
            idToken* tempToken = new idToken(_accString);
            host->insertTable(tempToken);
            return tempToken;
            break;
        }
    case _OP:
        return new operaToken(_accString);
        break;
    case _END:
        return new token(0);
        break;
    case _STR:
        return new stringToken({&_accString[1], &_accString[_accString.length() - 1]});
        break;
    default:
        return new errToken();
        break;
    }
}

token* DFA::getToken(){
    this->reset();
    std::string tempToken;
    char tempChar;
    while (tempChar = host->getNextChar()) {

        if (isEmptyChar(tempChar)) { // 被空白符分隔的串视为两个token
            if (state == DFAstate::START) continue;
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(state);
                return bulidToken(tempAcc.first, tempToken);
            } else {
                throw(no_mode_matched(tempToken));
            }
        } // 此处需修改来适配string

        tempToken.push_back(tempChar); // 空白符无论如何不能进入token中
        if (this->trans(tempChar)) {
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(state);
                if (tempAcc.second == 0) {
                    return bulidToken(tempAcc.first, tempToken);
                }
            }
        } else {
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(state);
                if (tempAcc.second == 1) {
                    tempToken.pop_back();
                    host->pointReturn();
                }
                return bulidToken(tempAcc.first, tempToken);
            } else {
                throw(no_mode_matched(tempToken));
            }
        }
    }

    return new token();
}

#endif