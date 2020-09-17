//GB2312
#ifndef _DFA_H_
#define _DFA_H_
#include "base.hpp"
#include "token.hpp"
#include "lex.h"

class lexAna;
class DFA {
private:
    lexAna* const host;
    _DFAstate state = DFAstate::START;
    _DFAstate lastState = DFAstate::START;
    
    inline void stateTo(_DFAstate newState);
    bool trans(char _iptc);
    token* bulidToken(_ACCstate _accKind, std::string _accString);

    DFA(const DFA& _a); //屏蔽复制构造函数
    DFA& operator=(const DFA& _a); //屏蔽赋值
public:
    explicit DFA(lexAna* _host);
    inline void reset();
    token* getToken();
};

#endif