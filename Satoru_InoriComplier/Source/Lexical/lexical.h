/*
 * @Description: lex.h
 * @Version: 0.10
 * @Autor: AmachiInori
 * @Date: 2020-09-16 16:38:17
 * @LastEditors: AmachiInori
 */
//comment by GB2312
#ifndef _LEX_H_
#define _LEX_H_
#include "../../Include/lexical_base.hpp"
#include "../../Include/token.hpp"
#include "lexical_DFA.h"

class DFA;
class lexAna {
private:
    bool isRefilled = false;
    size_t lineNumber, lastLineNumber;
    size_t listNumber, lastListNumber;
    size_t nowPoint, lastPoint; //np��ʾ�ոձ����������char
    char lastChar, nowChar;
    const size_t bufferSize;
    bool isInfileGood = true;

    std::unordered_map<std::string, token*> idTable; //Ӧ��ȷ������idTable�е�Ԫ�ؾ��ڶѿռ�
    std::ifstream infile;
    std::string fileName;
    DFA* dfaProcess;
    std::string bufferA, bufferB;
    
    void _pointReturn();
    void fillBuffer(std::string* _buf);
    char newCharFromBuffer();
    bool insertTable(idToken* _idT);
    bool findInIdTable(std::string _str); //������Ѿ��е�token���Ͳ����½� �����������ɿ��ļ�����

    lexAna(const lexAna& banned);
    lexAna& operator=(const lexAna& banned);

    // ��DFA�Ľӿ�
    friend class DFA;
    char getNextChar();
    char getLastChar();
    void pointReturn();
public:
    lexAna(std::string _file);
    ~lexAna();

    // ���˵Ľӿ� ��Ϊ��Ҫͨ���˴���������û������Ϊ��Ԫ+˽�е���ʽ
    token* getNextToken();
    std::unordered_map<std::string, token*> getIdTable();
};

#endif