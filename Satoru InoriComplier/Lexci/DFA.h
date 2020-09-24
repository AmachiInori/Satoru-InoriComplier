/*
 * @Description: 
 * @Version: Do not edit
 * @Autor: AmachiInori
 * @Date: 2020-09-16 16:29:32
 * @LastEditors: AmachiInori
 */
//GB2312
#ifndef _DFA_H_
#define _DFA_H_
#include "lexciBase.hpp"
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
    std::vector<token*> newedToken;
    
    friend class lexAna; // 向词法分析器的接口
    explicit DFA(lexAna* _host);
    ~DFA();
    inline void reset();
    token* getToken();

    DFA(const DFA& banned); // 覆盖缺省类方法
    DFA& operator=(const DFA& banned);
};

#endif