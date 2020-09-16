#ifndef _LEX_H_
#define _LEX_H_
#include "base.hpp"
#include "token.hpp"
#include "DFA.h"

class DFA;
class lexAna {
private:
    size_t lineNumber, lastLineNumber;
    size_t nowPoint, lastPoint; //np表示刚刚被传入分析的char
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
    bool findInIdTable(std::string _str); //如果是已经有的token，就不再新建 内联函数不可跨文件调用
public:
    lexAna(std::string _file);
    friend class DFA;
    // 向后端的接口
    token* getNextToken();
    // 向DFA的接口
    char getNextChar();
    void pointReturn();

    inline std::unordered_map<std::string, token> getIdTable();
};

#endif