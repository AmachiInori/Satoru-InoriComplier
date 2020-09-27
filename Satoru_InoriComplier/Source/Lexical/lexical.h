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
    size_t nowPoint, lastPoint; //np表示刚刚被传入分析的char
    char lastChar, nowChar;
    const size_t bufferSize;
    bool isInfileGood = true;

    std::unordered_map<std::string, token*> idTable; //应当确保所有idTable中的元素均在堆空间
    std::ifstream infile;
    std::string fileName;
    DFA* dfaProcess;
    std::string bufferA, bufferB;
    
    void _pointReturn();
    void fillBuffer(std::string* _buf);
    char newCharFromBuffer();
    bool insertTable(idToken* _idT);
    bool findInIdTable(std::string _str); //如果是已经有的token，就不再新建 内联函数不可跨文件调用

    lexAna(const lexAna& banned);
    lexAna& operator=(const lexAna& banned);

    // 向DFA的接口
    friend class DFA;
    char getNextChar();
    char getLastChar();
    void pointReturn();
public:
    lexAna(std::string _file);
    ~lexAna();

    // 向后端的接口 因为需要通过此处调试所以没有声明为友元+私有的形式
    token* getNextToken();
    std::unordered_map<std::string, token*> getIdTable();
};

#endif