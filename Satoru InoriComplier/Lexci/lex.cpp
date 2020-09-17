//GB2312
#ifndef _LEX_HPP_
#define _LEX_HPP_
#include "lex.h"
#include "DFA.h"

lexAna::lexAna(std::string _file) : 
    fileName(_file), 
    lineNumber(1), 
    lastLineNumber(1), 
    nowPoint(-1), 
    lastPoint(-1), 
    bufferSize(4096), 
    listNumber(1),
    lastListNumber(1) {
    infile.open(_file, std::ios::in | std::ios::binary);
    if (!infile) isInfileGood = false;
    dfaProcess = new DFA(this);
    bufferA.resize(bufferSize, 0); // 0作为输入结束标记
    bufferB.resize(bufferSize, 0);
    for (size_t i = 0; i < bufferA.size() && !infile.eof(); i++) {
        bufferA[i] = infile.get();
    }
    for (auto &_keyWord : _remain) { //将保留字插入符号表
        idTable[_keyWord.first] = new remainToken(_keyWord.first, _keyWord.second);
    }
}

bool lexAna::findInIdTable(std::string _str) { 
    return idTable.find(_str) != idTable.end(); 
}

inline std::unordered_map<std::string, token*> lexAna::getIdTable() { 
    return idTable; 
}

char lexAna::getLastChar() {
    return lastChar;
}

bool lexAna::insertTable(idToken* _idT) {
    if (findInIdTable(_idT->getValueString())) return false;
    else idTable[_idT->getValueString()] = _idT;
    return true;
}

token* lexAna::getNextToken() {
    try {
        return this->dfaProcess->getToken();
    } catch (STRExpection e) {
        std::cout << e.what;
        std::cout << " at " << '[' << lineNumber << ',' << listNumber << ']' << "\n";
        return new errToken();
    }
}

char lexAna::getNextChar() {
    if (!isInfileGood) { //未能正确读取文件
        throw(can_not_open_file(fileName));
    }
    lastPoint = nowPoint, lastLineNumber = lineNumber, lastListNumber = listNumber;
    char tempChar = newCharFromBuffer();
    while (isEmptyChar(tempChar) && isEmptyChar(lastChar)) 
        tempChar = newCharFromBuffer();
    if (tempChar == '#') {
        tempChar = newCharFromBuffer();
        while (tempChar != '#' && tempChar != 0)
            tempChar = newCharFromBuffer(); 
    }
    return tempChar; 
}

char lexAna::newCharFromBuffer() {
    lastChar = nowChar;
    char tempChar;
    nowPoint++;
    listNumber++;
    nowPoint = nowPoint % 8192;
    if (nowPoint % 4096 == 0) isRefilled = false;
    if (nowPoint < 4096) {
        tempChar = bufferA[nowPoint];
        if (nowPoint >= 4096 / 2 && !isRefilled) {
            this->fillBuffer(&bufferB);
        }
    } else {
        tempChar = bufferB[nowPoint - 4096];
        if (nowPoint >= 4096 * 3 / 2 && !isRefilled) {
            this->fillBuffer(&bufferA);
        }
    }
    

    if (tempChar == '\n') {
        lineNumber++;
        listNumber = 1;
    }
    nowChar = tempChar;
    return tempChar;
}

void lexAna::pointReturn() {
    if (nowPoint == lastPoint) {
        throw(can_not_return_back(nowPoint));
    }
    nowPoint = lastPoint;
    lineNumber = lastLineNumber;
    listNumber = lastListNumber;
    return;
}

void lexAna::fillBuffer(std::string* _buf) {
    std::for_each(_buf->begin(), _buf->end(), [](auto &temp){ temp = 0; });
    for (size_t i = 0; i < _buf->size() && !infile.eof(); i++) {
        _buf->operator[](i) = infile.get();
    }
    isRefilled = true;
    return;
}
#endif