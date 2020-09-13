#include "base.hpp"
#ifndef _TOKEN_H_
#define _TOKEN_H_

class token {
protected:
    _tokenType type;
public:
    explicit token(int tt = 0) : type(tt) {};
    _tokenType getTokenType() { return type; }
};

class numToken : public token {
protected:
    std::string exprValue;
    _numType numtype;
public:
    explicit numToken(const std::string &_exV, _numType nt = 0) : token(NUM), exprValue(_exV), numtype(nt) {};
    std::string getValueString() { return exprValue; }
};

class intToken final : public numToken {
    int64_t value = 0;
    bool isGoodNumber = true;
public:
    explicit intToken(const std::string &_exV) : numToken(_exV, INT) {
        for (size_t i = (_exV.front() == '-' || _exV.front() == '+') ? 0 : 1; i < _exV.size(); i++) {
            if (value > LLONG_MAX / 10.0) isGoodNumber = false;
            value *= 10;
            value += _exV[i];
        }
        if (_exV.front() == '-') value *= -1;
    }
    int64_t getValueNum() { 
        if (isGoodNumber) {
            return value;
        } else {
            throw(int_cstexpe_overflow(exprValue));
        }
    }
};

class floatToken final : public numToken {
    double_t value = 0;
    bool isGoodNumber = true;
public:
};

#endif