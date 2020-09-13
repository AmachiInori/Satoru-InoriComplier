#include <string>
#include <iostream>
#include <math.h>
#include <stdexcept>

typedef char _tokenType;
typedef char _numType;

static const _tokenType ID = 1, NUM = 2;
static const _numType INT = 1;

class tokenExpection {
public:
    explicit tokenExpection(std::string exMsg) : what(exMsg) {};
    std::string what;
};

class int_cstexpe_overflow : public tokenExpection {
    std::string overflowNumString;
public:
    explicit int_cstexpe_overflow(std::string &_ofns) : 
        tokenExpection("interge constexpr overflow"), overflowNumString(_ofns) {};
};