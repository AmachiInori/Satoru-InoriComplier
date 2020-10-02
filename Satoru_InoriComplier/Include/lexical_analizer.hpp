// δ���ģ�����
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
    int readPoint = 0;//�Ѷ�����λ��
    bool isFinished = false;
    bool _isPrecdictGood = true;

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
    bool isPrecdictGood() const { return _isPrecdictGood; }
    explicit lexicalAnalysis(std::string filename) { 
        hostLex = new lexAna(filename);
        while (!isFinished) {
            this->_pullNextToken();
            if (tokenBuffer.back()->getTokenType() < 0) {
                _isPrecdictGood = false;
            }
        }
    }
    ~lexicalAnalysis() { delete hostLex; }
    bool finished() { return isFinished; }
    token* getNextToken() {
        return tokenBuffer[readPoint++];
    }
    token* lookForward(size_t length) { // TODO �������ģ��Ĺ������
        if (readPoint + length < tokenBuffer.size()) {
            return tokenBuffer[readPoint + length];
        } else return &_fatalToken;
    }
    token* lookBackward(size_t length) { //ע��length�������Ǹ��� // TODO �������ģ��Ĺ������
        if (readPoint - length >= 0) {
            return tokenBuffer[readPoint - length];
        } else return &_fatalToken;
    }
};

#endif