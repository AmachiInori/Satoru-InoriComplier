/*
 * @Description: 
 * @Version: Do not edit
 * @Autor: AmachiInori
 * @Date: 2020-09-26 11:53:39
 * @LastEditors: AmachiInori
 */
#ifndef SAT_LL_H_
#define SAT_LL_H_
#include "parserBase.hpp"

class LL {
private:
    lexicalAnalysis* _lex;
    bool isFinished = false;
    token* nowToken;
    void match(); //从缓冲区再拉一个token到nowtoken

    void expressionC1();
    void factor();

    LL(const LL& banned);
    LL& operator=(const LL& banned);
public:
    LL(std::string _filename) {
        _lex = new lexicalAnalysis(_filename);
    }
    void runParserAnalysis();
};

#endif // !SAT_LL_H_