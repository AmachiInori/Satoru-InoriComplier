//GB2312
#ifndef _LEX_H_
#define _LEX_H_
#include "base.hpp"
#include "token.hpp"
#include "DFA.h"

class DFA;
class lexAna {
private:
    bool isRefilled = true;
    size_t lineNumber, lastLineNumber;
    size_t listNumber, lastListNumber;
    size_t nowPoint, lastPoint; //np��ʾ�ոձ����������char
    char lastChar, nowChar;
    const size_t bufferSize;
    std::unordered_map<std::string, token*> idTable; //Ӧ��ȷ������idTable�е�Ԫ�ؾ��ڶѿռ�
    std::ifstream infile;
    std::string fileName;
    DFA* dfaProcess;
    bool isInfileGood = true;
    
    std::string bufferA, bufferB;
    
    void _pointReturn();
    void fillBuffer(std::string* _buf);
    char newCharFromBuffer();
    bool insertTable(idToken* _idT);
    bool findInIdTable(std::string _str); //������Ѿ��е�token���Ͳ����½� �����������ɿ��ļ�����
public:
    lexAna(std::string _file);
    friend class DFA;
    // ���˵Ľӿ�
    token* getNextToken();
    // ��DFA�Ľӿ�
    char getNextChar();
    char getLastChar();
    void pointReturn();

    inline std::unordered_map<std::string, token*> getIdTable();
};

#endif