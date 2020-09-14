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

typedef uint16_t _DFAstate;
typedef uint16_t _ACCstate;
typedef int8_t _ACCaction;

namespace DFAstate {
    static const _DFAstate START = 0;
    static const _DFAstate NUM_MAIN_PONE_IN = 1;
    static const _DFAstate NUM10_MAIN_INPUTING_DIGIT = 2;
    static const _DFAstate NUM10_ACCEPT_UNSIGNED_INT = 3;
    static const _DFAstate NUM_MAIN_FIRST_ZERO_IN = 4;
    static const _DFAstate NUM10_FLT_DOT_IN = 5;
    static const _DFAstate NUM10_FLT_INPUTING_DIGIT = 6;
    static const _DFAstate NUM10_FLT_INDEX_E_IN = 7;
    static const _DFAstate NUM10_FLT_INDEX_PONE_IN = 9;
    static const _DFAstate NUM10_FLT_INDEX_INPUT_DIGIT = 8;

    static const _ACCstate _NUM10_INT = 1;
    static const _ACCstate _NUM10_UINT = 2;
    static const _ACCstate _NUM10_FLT = 3;
    static const _ACCstate _NUM10_FLT_WITHE = 4;

    static const std::unordered_map<_DFAstate, std::pair<_ACCstate, _ACCaction>> _acctable = {
        {NUM10_MAIN_INPUTING_DIGIT, {_NUM10_INT, -1}},
        {NUM10_ACCEPT_UNSIGNED_INT, {_NUM10_UINT, 0}},
        {NUM10_FLT_INPUTING_DIGIT, {_NUM10_FLT, -1}},
        {NUM10_FLT_INDEX_INPUT_DIGIT, {_NUM10_FLT_WITHE, -1}}
    };
};


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