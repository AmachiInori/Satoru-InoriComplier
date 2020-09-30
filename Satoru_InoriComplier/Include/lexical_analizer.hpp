/*
 * @Description: lexical.hpp
 * @Version: 0.10
 * @Autor: AmachiInori
 * @Date: 2020-09-19 01:42:27
 * @LastEditors: AmachiInori
 */
#ifndef STR_LEXICAL
#define STR_LEXICAL
#include "../Source/Lexical/lexical.h"
#include "../Source/Lexical/lexical_DFA.h"

extern token _emptyToken;
extern token _errToken;
extern token _fatalToken;

class lexicalAnalysis {
private: 
    lexAna* hostLex;
    std::vector<token*> tokenBuffer;
    int readPoint = -1;//已读过的位置
    bool isFinished = false;

    lexicalAnalysis(const lexicalAnalysis& banned);
    lexicalAnalysis& operator=(const lexicalAnalysis& banned);
    void _pullNextToken() { 
        token* tempToken = hostLex->getNextToken();
        if (tempToken->getTokenType() == 0) {
            isFinished = true;
        }
        if (isFinished) return;
        tokenBuffer.push_back(tempToken); 
    } 
public:
    explicit lexicalAnalysis(std::string filename) { hostLex = new lexAna(filename); }
    ~lexicalAnalysis() { delete hostLex; }
    bool finished() { return isFinished; }
    token* getNextToken() {
        readPoint++;
        return this->lookForward(0);
    }
    token* lookForward(size_t length) { // TODO 测试这个模块的工作情况
        while ((int64_t)readPoint + (int64_t)length >= (int64_t)tokenBuffer.size() && !isFinished) {
            this->_pullNextToken();
        } 

        if (readPoint + length >= tokenBuffer.size()) { // 二种截止情况
            return &_emptyToken;
        } else {
            return tokenBuffer[readPoint + length];
        }
    }
    token* lookBackward(size_t length) { //注意length不允许是负数 // TODO 测试这个模块的工作情况
        if (readPoint - length < 0) return &_fatalToken; //不支持的操作
        return tokenBuffer[readPoint - length];
    }
};

#endif