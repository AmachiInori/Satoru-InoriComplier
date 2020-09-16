#ifndef _LEX_H_
#define _LEX_H_
#include "base.hpp"
#include "token.hpp"
#include "DFA.h"

class DFA;
class lexAna {
private:
    size_t lineNumber, lastLineNumber;
    size_t nowPoint, lastPoint; //np��ʾ�ոձ����������char
    char lastChar, nowChar;
    const size_t bufferSize;
    std::unordered_map<std::string, token> idTable;
    std::ifstream infile;
    std::string fileName;
    DFA* dfaProcess;
    bool isInfileGood = true;
    
    std::string bufferA, bufferB;
    
    void fillBuffer(std::string* _buf);
    char newCharFromBuffer();
    void insertTable(idToken _idT);
    bool findInIdTable(std::string _str); //������Ѿ��е�token���Ͳ����½� �����������ɿ��ļ�����
public:
    lexAna(std::string _file);
    friend class DFA;
    // ���˵Ľӿ�
    token* getNextToken();
    // ��DFA�Ľӿ�
    char getNextChar();
    void pointReturn();

    inline std::unordered_map<std::string, token> getIdTable();
};

#endif