/*
 * @Description: 
 * @Version: Do not edit
 * @Autor: AmachiInori
 * @Date: 2020-09-26 11:53:39
 * @LastEditors: AmachiInori
 */
#ifndef SAT_LL_H_
#define SAT_LL_H_
#include "../../Include/parser_base.hpp"

class LL {
private:
    lexicalAnalysis* _lex;
    bool isFinished = false;
    token* nowToken;
    std::vector<parserNode*> newedPN;

    parserNode* creatNewNode(token* _token, std::string _idfi) {
        newedPN.push_back(new parserNode(_token, _idfi));
        return newedPN.back();
    }
    bool match(); //从缓冲区再拉一个token到nowtoken

    parserNode* expressionC0();
    parserNode* expressionC1();
    parserNode* factor();
    parserNode* idTail();
    parserNode* parameter();

    LL(const LL& banned);
    LL& operator=(const LL& banned);
public:
    LL(std::string _filename) {
        _lex = new lexicalAnalysis(_filename);
    }
    parserNode* runParserAnalysis();
};

#endif // !SAT_LL_H_