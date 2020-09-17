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

    DFA(const DFA& _a); //���θ��ƹ��캯��
    DFA& operator=(const DFA& _a); //���θ�ֵ
public:
    explicit DFA(lexAna* _host);
    inline void reset();
    token* getToken();
};

#endif