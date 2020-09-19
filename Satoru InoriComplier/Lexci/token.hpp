//comment by GB2312
#include "base.hpp"
#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

class token {
protected:
    _tokenType type;
public:
    explicit token(int tt = 0) : type(tt) {}; // type为0特指结束,为-1指错误
    inline _tokenType getTokenType() { return type; }
    virtual void printToken() { std::cout << (int)type << ' ' << "baseToken\n"; }
};

class errToken final : public token {
public:
    explicit errToken() : token(-1) {}; // type为0特指结束
    virtual void printToken() { std::cout << (int)type << ' ' << "ERRTOKEN\n"; }
};

class operaToken final : public token {
    _operType _otp = 0;
public:
    explicit operaToken(std::string otps) : token(OPER) {
        _otp = OPtoOTP(otps);
    }
    inline std::string getValueString() { return OTPtoOP(_otp); }
    inline _operType getOTP() { return _otp; }
    virtual void printToken() { std::cout << (int)type << ' ' << OTPtoOP(_otp) << ' ' << (int)_otp << ' ' << "operToken\n"; }
};

class numToken : public token {
protected:
    std::string exprValue;
    _numType numtype;
public:
    explicit numToken(const std::string &_exV, _numType nt = 0) : token(NUM), exprValue(_exV), numtype(nt) {};
    inline std::string getValueString() { return exprValue; }
    virtual void printToken() override { 
        std::cout << (int)type << ' ' << (int)numtype << ' ' << exprValue << ' ' << "baseNumber\n"; 
    }
};

class intToken final: public numToken {
    int64_t value = 0;
    bool isGoodNumber = true;
public:
    explicit intToken(const std::string &_exV) : numToken(_exV, INT) {
        for (size_t i = (_exV.front() == '-' || _exV.front() == '+') ? 1 : 0; i < _exV.length(); i++) {
            if (value > LLONG_MAX / 10.0) isGoodNumber = false;
            value *= 10;
            value += _exV[i] - '0';
        }
        if (_exV.front() == '-') value *= -1;
    }
    explicit intToken(const int64_t _int) : value(_int), numToken(std::string(std::to_string(_int)), INT) { }
    void printToken() override { 
        if (!isGoodNumber) std::cout << "warning: overflow ";
        std::cout << (int)type << ' ' << (int)numtype << ' ' << exprValue << ' ' << value << ' ' << "intToken\n"; 
    }
    inline int64_t getValueNum() { 
        if (isGoodNumber) {
            return value;
        } else {
            throw(int_cstexpe_overflow(exprValue));
        }
    }
};

class UintToken final : public numToken {
    uint64_t value = 0;
    bool isGoodNumber = true;
public:
    explicit UintToken(const std::string &_exV) : numToken(_exV, INT) {
        for (size_t i = (_exV.front() == '-' || _exV.front() == '+') ? 1 : 0; i < _exV.length(); i++) {
            if (value > UINT64_MAX / 10.0) isGoodNumber = false;
            value *= 10;
            value += _exV[i] - '0';
        }
        if (_exV.front() == '-') {
            value -= value;
            value -= value;
        }
    }
    void printToken() override { 
        if (!isGoodNumber) std::cout << "warning: overflow";
        std::cout << (int)type << ' ' << (int)numtype << ' ' << exprValue << ' ' << value << ' ' << "UintToken\n"; 
    }
    inline uint64_t getValueNum() { 
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
    explicit floatToken(const std::string &_exV) : numToken(_exV, FLT) { // 词法分析器保证传入这一token的串一定有句点
        double_t res = 0;
        double_t floatRes = 0;
        size_t dotLoca = 0;
        int32_t eLoca = -1;
        for (size_t i = 0; i < _exV.length(); i++) { // 此模块未做溢出修正
            if (_exV[i] == '.') {
                dotLoca = i;
            } else if (_exV[i] == 'e' || _exV[i] == 'E') {
                eLoca = i;
            }
        }
        for (size_t i = (_exV.front() == '-' || _exV.front() == '+') ? 1 : 0; i < dotLoca; i++) {
            if (value > DBL_MAX / 10.0) isGoodNumber = false;
            res *= 10;
            res += _exV[i] - '0';
        }
        for (size_t i = ((eLoca == -1) ? _exV.size() : eLoca) - 1; i > dotLoca; i--) {
            floatRes += _exV[i] - '0';
            floatRes /= 10;
        }
        res += floatRes;
        if (eLoca != -1) { // E后的文法规约是整数
            int32_t indexRes = 0;
            for (size_t i = eLoca + ((_exV[eLoca + 1] == '+' || _exV[eLoca + 1] == '-') ? 2 : 1); i < _exV.size(); i++) {
                indexRes *= 10;
                indexRes += _exV[i] - '0';
            }
            if (_exV[eLoca + 1] == '-') indexRes *= -1;
            if (res > DBL_MAX / pow(10, std::max(indexRes, 1))) isGoodNumber = false;
            res = res * pow(10, indexRes);
        }
        value = res;
    }
    void printToken() override { 
        if (!isGoodNumber) std::cout << "warning: overflow ";
        std::cout << (int)type << ' ' << (int)numtype << ' ' << exprValue << ' ' << value << ' ' << "fltToken\n"; 
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
    std::string originValue;
public:
    explicit stringToken(const std::string &_str) : token(STR), originValue(_str) {
        for (size_t i = 0; i < originValue.size(); i++) {
            if (originValue[i] == '\n' || originValue[i] == '\r') {
                originValue.erase(i, 1);
                i--;
            }
        }
        for (size_t i = 0; i < originValue.size(); i++) {
            if (i != originValue.size() - 1 && originValue[i] == '\\') {
                char tempChar = _str[i + 1];
                exprValue.push_back(ctrlChartoASC2(tempChar));
                i++;
            } else {
                exprValue.push_back(originValue[i]);
            }
        }
    }
    void printToken() override { 
        std::cout << (int)type << " \"" << originValue << "\" " << " " + exprValue << " stringToken\n"; 
    }
    inline std::string getValueString() { return exprValue; }
};

class idToken : public token {
protected:
    std::string idValue;
public:
    explicit idToken(const std::string &_str) : token(ID), idValue(_str) {
        if (isKeyWord(_str)) {
            //错误情况，表示符号表没有正常生效
        }
    }
    void printToken() override { 
        std::cout << (int)type << ' ' << idValue << ' '  << "idToken\n"; 
    }
    inline std::string getValueString() { return idValue; }
};

class remainToken final : public idToken {
    _keyWordType _kt;
public:
    explicit remainToken(const std::string &_str, _keyWordType kt) : 
        idToken(_str), _kt(kt) {
        token::type = REMAIN;
    }
    void printToken() override { 
        std::cout << (int)type << ' ' << idValue << ' ' << (int)_kt << " remainToken\n"; 
    }
};

#endif