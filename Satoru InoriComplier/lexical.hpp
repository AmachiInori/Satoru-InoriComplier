#ifndef STR_LEXICAL
#define STR_LEXICAL
#include "Lexci/DFA.h"
#include "Lexci/lex.h"

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
    token* lookForward(size_t length) {
        while ((int64_t)readPoint + (int64_t)length >= (int64_t)tokenBuffer.size() && !isFinished) {
            this->_pullNextToken();
        } 

        if (readPoint + length >= tokenBuffer.size()) { // 二种截止情况
            return &_emptyToken;
        } else {
            return tokenBuffer[readPoint + length];
        }
    }
    token* lookBackward(size_t length) { //注意length不允许是负数
        if (readPoint - length < 0) return &_fatalToken; //不支持的操作
        return tokenBuffer[readPoint - length];
    }
};

#endif