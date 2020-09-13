#ifndef _LEXBASE_HPP_
#define _LEXBASE_HPP_
#include <string>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>

typedef char _tokenType;
typedef char _numType;
typedef int _keyWordType;

static const _tokenType ID = 1, NUM = 2, STR = 3, REMAIN = 4;
static const _numType INT = 1, FLT = 2;
static const _keyWordType TRUE = 1, FALSE = 2, IF = 3, ELSE = 4, ELIF = 5, GOTO = 6, SWITCH = 7, WHILE = 8, UNTIL = 9,
    FOR = 10, DO = 11, CONTINUE = 12, BREAK = 13, RETURN = 14, KWINT = 15, KWFLT = 16, KWCHAR = 17, KWLONG = 18, KWSHT = 19,
    KWDBL = 20, UNSIGNED = 21, SIGNED = 22, VOID = 23, CONST = 24;

inline bool isKeyWord(std::string _id) {
    const static std::unordered_map<std::string, _keyWordType> _remain = {
        {"true", TRUE}, {"false", FALSE}, 
        {"if", IF}, {"else", ELSE}, {"elif", ELIF}, {"goto", GOTO}, {"switch", SWITCH}, 
        {"while", WHILE}, {"until", UNTIL}, {"for", FOR}, {"do", DO}, {"continue", CONTINUE}, {"break", BREAK}, 
        {"return", RETURN}, 
        {"int", KWINT}, {"float", KWFLT}, {"char", KWCHAR}, {"long", KWLONG}, {"short", KWSHT}, {"double", KWDBL}, 
        {"unsigned", UNSIGNED}, {"signed", SIGNED}, {"void", VOID}, {"const", CONST}
    };
    if (_remain.find(_id) != _remain.end()) return true;
    else return false;
}
inline bool isDigit(char _c) { return _c >= '0' && _c <= '9'; }
inline bool isAlphabet(char _c) { return (_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z'); }
inline bool isIdChar(char _c) { return isAlphabet(_c) || _c == '_'; }
inline bool isOperatorChar(char _c) { 
    const static std::unordered_set<char> _oper = {
        '+', '-', '*', '/', '%', '&', '.', ',', '=', '<', '>', '|', '^'
    };
    if (_oper.find(_c) != _oper.end()) return true;
    else return false;
}

class tokenExpection {
public:
    std::string what;
    explicit tokenExpection(std::string exMsg) : what(exMsg) {};
};

class int_cstexpe_overflow : public tokenExpection {
    std::string overflowNumString;
public:
    explicit int_cstexpe_overflow(std::string &_ofns) : 
        overflowNumString(_ofns), tokenExpection("interge constexpr overflow in: " + _ofns) {};
};

class flt_cstexpe_overflow : public tokenExpection {
    std::string overflowNumString;
public:
    explicit flt_cstexpe_overflow(std::string &_ofns) : 
        overflowNumString(_ofns), tokenExpection("float constexpr overflow in: " + _ofns) {};
};

#endif