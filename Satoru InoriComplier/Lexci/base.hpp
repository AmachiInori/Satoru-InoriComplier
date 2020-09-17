//GB2312
#ifndef _LEXBASE_HPP_
#define _LEXBASE_HPP_
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

typedef char _tokenType;
typedef char _numType;
typedef int _keyWordType;
typedef uint16_t _operType;

static const _tokenType ID = 1, NUM = 2, STR = 3, REMAIN = 4, OPER = 5;
static const _numType INT = 1, FLT = 2;
static const _keyWordType TRUE = 1, FALSE = 2, IF = 3, ELSE = 4, ELIF = 5, GOTO = 6, SWITCH = 7, WHILE = 8, UNTIL = 9,
    FOR = 10, DO = 11, CONTINUE = 12, BREAK = 13, RETURN = 14, KWINT = 15, KWFLT = 16, KWCHAR = 17, KWLONG = 18, KWSHT = 19,
    KWDBL = 20, UNSIGNED = 21, SIGNED = 22, VOID = 23, CONST = 24;
const static std::unordered_map<std::string, _keyWordType> _remain = {
    {"true", TRUE}, {"false", FALSE}, 
    {"if", IF}, {"else", ELSE}, {"elif", ELIF}, {"goto", GOTO}, {"switch", SWITCH}, 
    {"while", WHILE}, {"until", UNTIL}, {"for", FOR}, {"do", DO}, {"continue", CONTINUE}, {"break", BREAK}, 
    {"return", RETURN}, 
    {"int", KWINT}, {"float", KWFLT}, {"char", KWCHAR}, {"long", KWLONG}, {"short", KWSHT}, {"double", KWDBL}, 
    {"unsigned", UNSIGNED}, {"signed", SIGNED}, {"void", VOID}, {"const", CONST}
};

inline bool isKeyWord(std::string _id) {
    if (_remain.find(_id) != _remain.end()) return true;
    else return false;
}
inline bool isDigit(char _c) { return _c >= '0' && _c <= '9'; }
inline bool isAlphabet(char _c) { return (_c >= 'a' && _c <= 'z') || (_c >= 'A' && _c <= 'Z'); }
inline bool isIdChar(char _c) { return isAlphabet(_c) || _c == '_'; }
inline bool isSingleOperatorChar(char _c) { 
    const static std::unordered_set<char> _oper = {
        '[', ']', '.', ',', '(', ')'
    };
    if (_oper.find(_c) != _oper.end()) return true;
    else return false;
}
inline bool isReptbOperatorChar(char _c) { // 后可以接续自己或者等号
    const static std::unordered_set<char> _oper = {
        '/', '%', '&', '=', '<', '>', '|', '+', '-'
    };
    if (_oper.find(_c) != _oper.end()) return true;
    else return false;
}
inline bool isOpreatorCharOnlyDblWEqual(char _c) { // 后仅仅可以接续自己
    const static std::unordered_set<char> _oper = {
        '*', '^'
    };
    if (_oper.find(_c) != _oper.end()) return true;
    else return false;
}
inline bool isEmptyChar(char _c) { return _c == ' ' || _c == '\n' || _c == '\r' || _c == -1 || _c == '#'; }
inline bool isSynChar(char _c) { return _c == '{' || _c == '}'; } // 同步词法单元
//做一下分隔符;

typedef uint16_t _DFAstate;
typedef uint16_t _ACCstate;
typedef int8_t _ACCaction;

namespace DFAstate {
    static const _DFAstate START = 0;
    static const _DFAstate OP_NUM_MAIN_PONE_IN = 1;
    static const _DFAstate NUM10_MAIN_INPUTING_DIGIT = 2;
    static const _DFAstate NUM10_ACCEPT_UNSIGNED_INT = 3;
    static const _DFAstate NUM_MAIN_FIRST_ZERO_IN = 4;
    static const _DFAstate NUM10_FLT_DOT_IN = 5;
    static const _DFAstate NUM10_FLT_INPUTING_DIGIT = 6;
    static const _DFAstate NUM10_FLT_INDEX_E_IN = 7;
    static const _DFAstate NUM10_FLT_INDEX_PONE_IN = 9;
    static const _DFAstate NUM10_FLT_INDEX_INPUT_DIGIT = 8;
    static const _DFAstate ID_FIRST_CHAR_IN = 10;
    static const _DFAstate ID_CHAR_INPUT = 11;
    //12号无了(悲)
    static const _DFAstate OP_SINGLE_CHAR_IN = 13;
    static const _DFAstate OP_NOMDBL_FIRST_IN = 14;
    static const _DFAstate OP_DBL_ACC = 15;
    static const _DFAstate OP_RPTB_FIRST_IN = 16;
    static const _DFAstate END = UINT16_MAX;

    static const _ACCstate _NUM10_INT = 1;
    static const _ACCstate _NUM10_UINT = 2;
    static const _ACCstate _NUM10_FLT = 3;
    static const _ACCstate _NUM10_FLT_WITHE = 4;
    static const _ACCstate _ID = 5;
    static const _ACCstate _OP = 6;
    static const _ACCstate _END = UINT16_MAX;

    static std::unordered_map<_DFAstate, std::pair<_ACCstate, _ACCaction>> _acctable = {
        {NUM10_MAIN_INPUTING_DIGIT, {_NUM10_INT, 1}},
        {NUM_MAIN_FIRST_ZERO_IN, {_NUM10_INT, 0}},
        {OP_NUM_MAIN_PONE_IN, {_OP, 1}},
        {NUM10_ACCEPT_UNSIGNED_INT, {_NUM10_UINT, 0}},
        {NUM10_FLT_INPUTING_DIGIT, {_NUM10_FLT, 1}},
        {NUM10_FLT_INDEX_INPUT_DIGIT, {_NUM10_FLT_WITHE, 1}},
        {ID_FIRST_CHAR_IN, {_ID, 1}},
        {ID_CHAR_INPUT, {_ID, 1}},
        {OP_SINGLE_CHAR_IN, {_OP, 0}},
        {OP_NOMDBL_FIRST_IN, {_OP, 1}},
        {OP_DBL_ACC, {_OP, 0}},
        {OP_RPTB_FIRST_IN, {_OP, 1}},
        {END, {_END, 0}}
    };
    inline bool isStateAcc(_DFAstate _state) { return _acctable.find(_state) != _acctable.end(); }
    inline std::pair<_ACCstate, _ACCaction> getAccState(_DFAstate _state) { 
        if (isStateAcc(_state)) return _acctable[_state];
        else return {0, 0};
    }
};


class STRExpection {
public:
    std::string what;
    explicit STRExpection(std::string exMsg) : what(exMsg) {};
};

class int_cstexpe_overflow : public STRExpection {
    std::string overflowNumString;
public:
    explicit int_cstexpe_overflow(std::string &_ofns) : 
        overflowNumString(_ofns), STRExpection("interge constexpr overflow in: " + _ofns) {};
};

class flt_cstexpe_overflow : public STRExpection {
    std::string overflowNumString;
public:
    explicit flt_cstexpe_overflow(std::string &_ofns) : 
        overflowNumString(_ofns), STRExpection("float constexpr overflow in: " + _ofns) {};
};

class no_mode_matched : public STRExpection {
    std::string errorString;
public:
    explicit no_mode_matched(std::string &_ofns) : 
        errorString(_ofns), STRExpection("no mode matched with " + _ofns) {};
};

class can_not_return_back : public STRExpection {
    size_t errorLine;
public:
    explicit can_not_return_back(size_t _ofns) : 
        errorLine(_ofns), STRExpection("buffer can't return back at line " + _ofns) {};
};

class can_not_open_file : public STRExpection {
    std::string errorString;
public:
    explicit can_not_open_file(std::string &_file) :
        errorString(_file), STRExpection("file wrong " + _file) {};
};

#endif