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
        else if (_iptc == '+' || _iptc == '-') {
            stateTo(NUM_MAIN_PONE_IN);
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
        else return false;
        break;

    case NUM_MAIN_PONE_IN: // 1
        if (isDigit(_iptc)) {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        else return false;
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
        else return true;
        break;

    case NUM10_FLT_DOT_IN: // 5
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INPUTING_DIGIT);
            return true;
        }
        else return false;
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
        else return false;
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
        else return false;
        break;
    
    case NUM10_FLT_INDEX_INPUT_DIGIT: // 8
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INDEX_INPUT_DIGIT);
            return true;
        }
        else return false;
        break;

    case NUM10_FLT_INDEX_PONE_IN: // 9
        if (isDigit(_iptc)) {
            stateTo(NUM10_FLT_INDEX_INPUT_DIGIT);
            return true;
        }
        else return false;
        break;
    }
}

token* DFA::getToken(){
    this->reset();
    std::string tempToken;
    char tempChar;
    while (tempChar = host->getNextChar()) {
        if (isEmptyChar(tempChar)) { // 被空白符分隔的串视为两个token
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(state);
                return bulidToken(tempAcc.first, tempToken);
            } else {
                throw(no_mode_matched(tempToken));
            }
        }

        tempToken.push_back(tempChar); // 空白符无论如何不能进入token中
        if (this->trans(tempChar)) {
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(state);
                if (tempAcc.second == 0) {
                    return bulidToken(tempAcc.first, tempToken);
                }
            }
        } else {
            if (DFAstate::isStateAcc(lastState)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(lastState);
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

token* DFA::bulidToken(_ACCstate _accKind, std::string _accString) {
    using namespace DFAstate;
    if (host->findInIdTable(_accString)) return &host->idTable[_accString];
    switch (_accKind) {
    case _NUM10_INT:
        return new intToken(_accString);
        break;
    case _END:
        return new token(0);
        break;
    default:
        break;
    }
}
#endif