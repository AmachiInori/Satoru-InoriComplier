#include "base.hpp"
#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

class token {
protected:
    _tokenType type;
public:
    explicit token(int tt = 0) : type(tt) {};
    inline _tokenType getTokenType() { return type; }
    inline virtual void printToken() { std::cout << type << ' ' << "baseToken\n"; }
};

class numToken : public token {
protected:
    std::string exprValue;
    _numType numtype;
public:
    explicit numToken(const std::string &_exV, _numType nt = 0) : token(NUM), exprValue(_exV), numtype(nt) {};
    inline std::string getValueString() { return exprValue; }
    inline virtual void printToken() override { 
        std::cout << type << ' ' << numtype << ' ' << exprValue << ' ' << "baseNumber\n"; 
    }
};

class intToken final : public numToken {
    int64_t value = 0;
    bool isGoodNumber = true;
public:
    explicit intToken(const std::string &_exV) : numToken(_exV, INT) {
        for (size_t i = (_exV.front() == '-' || _exV.front() == '+') ? 0 : 1; i < _exV.length(); i++) {
            if (value > LLONG_MAX / 10.0) isGoodNumber = false;
            value *= 10;
            value += _exV[i];
        }
        if (_exV.front() == '-') value *= -1;
    }
    inline void printToken() override { 
        std::cout << type << ' ' << numtype << ' ' << exprValue << ' ' << value << ' ' << "intToken\n"; 
    }
    inline int64_t getValueNum() { 
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
    explicit floatToken(const std::string &_exV) : numToken(_exV, FLT) {
        size_t dotLoca = 0;
        int eLoca = -1;
        for (size_t i = 0; i < _exV.length(); i++) {
            if (_exV[i] == '.') {
                dotLoca = i;
            } else if (_exV[i] == 'e' || _exV[i] == 'E') {
                eLoca = i;
            }
        }
    }
    inline void printToken() override { 
        std::cout << type << ' ' << numtype << ' ' << exprValue << ' ' << value << ' ' << "fltToken\n"; 
    }
    inline double_t getValueNum() { 
        if (isGoodNumber) {
            return value;
        } else {
            throw(flt_cstexpe_overflow(exprValue));
        }
    }
};

class stringToken final : public token {
    std::string exprValue;
public:
    explicit stringToken(const std::string &_str) : token(STR), exprValue(_str) {};
    inline void printToken() override { 
        std::cout << type << ' ' << exprValue << ' ' << "stringToken\n"; 
    }
    inline std::string getValueString() { return exprValue; }
};

class idToken : public token {
protected:
    std::string idValue;
public:
    explicit idToken(const std::string &_str) : token(ID), idValue(_str) {
        if (isKeyWord(_str)) {
            *this = remainToken(_str);
        }
    }
    inline void printToken() override { 
        std::cout << type << ' ' << idValue << ' '  << "idToken\n"; 
    }
    inline std::string getValueString() { return idValue; }
};

class remainToken final : public idToken {
public:
    explicit remainToken(const std::string &_str) : idToken(_str) {
        token::type = REMAIN;
    }
};

#endif