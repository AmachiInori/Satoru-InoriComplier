/*
 * @Description: parserBase.hpp
 * @Version: 
 * @Autor: AmachiInori
 * @Date: 2020-09-25 00:08:00
 * @LastEditors: AmachiInori
 */
#ifndef _PASER_BASE_HPP_
#define _PASER_BASE_HPP_
#include "../lexical.hpp"

typedef uint8_t _operClass;

bool isRemainTokenRType(remainToken* _tk) {
    const static std::unordered_set<_keyWordType> _kwd = { 
        kwd::KWINT, kwd::KWFLT, kwd::KWCHAR, kwd::KWLONG, kwd::KWSHT, kwd::KWDBL, kwd::VOID 
    };
    return _kwd.find(_tk->getKwdType()) == _kwd.end();
}

bool isRemainTokenTypeQual(remainToken* _tk) {
    const static std::unordered_set<_keyWordType> _kwd = { 
        kwd::UNSIGNED, kwd::SIGNED, kwd::CONST 
    };
    return _kwd.find(_tk->getKwdType()) == _kwd.end();
}

_operClass getOperClass(operaToken* _optok) { //ÇëÌØÅÐµôÇ°×º¸ººÅ
    const static std::unordered_map<_operType, _operClass> _opclDic = {
        {61/*'='*/, 1}, {10069/*'+='*/, 1}, {11581/*'-='*/, 1}, {10813/*'*='*/, 1},
        {12093/*'/='*/, 1}, {9533/*'%='*/, 1}, 
        {15677/*'=='*/, 2}, {15933/*'>='*/, 2}, {15421/*'<='*/, 2}, {62/*'>'*/, 2}, {60/*'<'*/, 2}, 
        {8509/*'!='*/, 2},
        {31868/*'||'*/, 3}, {9766/*'&&'*/, 3}, {94/*'^'*/, 3}, {124/*'|'*/, 3}, {38/*'&'*/, 3},
        {15420/*'<<'*/, 4}, {15934/*'>>'*/, 4},
        {43/*'+'*/, 5}, {45/*'-'*/, 5}, 
        {42/*'*'*/, 6}, {37/*'%'*/, 6}, {47/*'/'*/, 6}, 
        {11051/*'++'*/, 7}, {15565/*'--'*/, 7}, 
        {33/*'!'*/, 8}, {126/*'~'*/, 8}, 
        {46/*'.'*/, 9}, {58/*':'*/, 9}
    };
    if (_opclDic.find(_optok->getOTP()) == _opclDic.end()) return 0;
    else return _opclDic.find(_optok->getOTP())->second;
    return 0;
}

class parser_error : public CodeExpection {
public:
    parser_error();
};

#endif