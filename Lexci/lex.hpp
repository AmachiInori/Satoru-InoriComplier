#include "base.hpp"
#include "token.hpp"
#ifndef _LEX_HPP_
#define _LEX_HPP_

class lexAna {
private:
    size_t lineNumber = 0;
    size_t nowPoint = 0, lastPoint = 0;
    std::unordered_map<std::string, token> idTable;

    void insertTable(idToken _idT);
    bool findInIdTable(std::string _str); //如果是已经有的token，就不再新建
public:
    token getNextToken();
    char getNextChar();
    void pointReturn(size_t _l);
    inline std::unordered_map<std::string, token> getIdTable() { return idTable; }
};

class DFA {
private:
    const lexAna* host;
    _DFAstate state = DFAstate::START;
    bool trans(char _iptc);
public:
    void reset() { state = DFAstate::START; }
    token getToken();
};

bool DFA::trans(char _iptc) {
    using namespace DFAstate;
    switch (this->state) {
    case START: // 0
        if (isDigit(_iptc) && _iptc != '0') {
            state = NUM10_MAIN_INPUTING_DIGIT;
            return true;
        } else if (_iptc == '+' || _iptc == '-') {
            state = NUM_MAIN_PONE_IN;
            return true;
        } else if (_iptc == '0') {
            state = NUM_MAIN_FIRST_ZERO_IN;
            return true;
        } else return false;
        break;
    case NUM_MAIN_PONE_IN: // 1
        if (isDigit(_iptc)) {
            state = NUM10_MAIN_INPUTING_DIGIT;
            return true;
        } else return false;
        break;
    case NUM10_MAIN_INPUTING_DIGIT: // 2
        if (isDigit(_iptc)) {
            state = NUM10_MAIN_INPUTING_DIGIT;
            return true;
        }
    default:
        break;
    }
}

#endif