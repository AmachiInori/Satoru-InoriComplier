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

#endif