/*
 * @Description: 
 * @Version: Do not edit
 * @Autor: AmachiInori
 * @Date: 2020-09-14 01:03:56
 * @LastEditors: AmachiInori
 */
//comment by GB2312
#ifndef _LEX_HPP_
#define _LEX_HPP_
#include "lex.h"
#include "DFA.h"

token _emptyToken(0);
token _errToken(-1);
token _fatalToken(-2);

lexAna::lexAna(std::string _file) : 
    fileName(_file), 
    lineNumber(1), 
    lastLineNumber(1), 
    nowPoint(-1), 
    lastPoint(-1), 
    bufferSize(4096), 
    listNumber(1),
    lastListNumber(1), 
    nowChar(0), 
    lastChar(0) {
        
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

std::unordered_map<std::string, token*> lexAna::getIdTable() { 
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
    token* resToken;
    try {
        resToken = this->dfaProcess->getToken();
    } catch (const no_mode_matched &e) {
        std::cerr << e.what;
        std::cout << " at " << '[' << lineNumber << ',' << listNumber << ']' << "\n";
        return &_errToken;
    }
    if (!resToken) return &_fatalToken; // 表示词法分析出现严重故障，需后端立即终止词法分析并析构
    else return resToken;
}

char lexAna::getNextChar() {
    if (!isInfileGood) { //未能正确读取文件
        infile.close();
        throw(fatal_can_not_open_file(fileName));
    }
    lastPoint = nowPoint, lastLineNumber = lineNumber, lastListNumber = listNumber;
    char tempChar = newCharFromBuffer();
/*
    while (isEmptyChar(tempChar) && isEmptyChar(lastChar)) 
        tempChar = newCharFromBuffer();
*/
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
    nowPoint = nowPoint % (bufferSize * 2);
    if (nowPoint % bufferSize == 0) isRefilled = false;
    if (nowPoint < bufferSize) {
        tempChar = bufferA[nowPoint];
        if (nowPoint >= bufferSize / 2 && !isRefilled) {
            this->fillBuffer(&bufferB);
        }
    } else {
        tempChar = bufferB[nowPoint - bufferSize];
        if (nowPoint >= bufferSize * 3 / 2 && !isRefilled) {
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

void lexAna::_pointReturn() {
    if (nowPoint == lastPoint) {
        infile.close();
        throw(fatal_can_not_return_back(nowPoint));
    }
    nowPoint = lastPoint;
    lineNumber = lastLineNumber;
    listNumber = lastListNumber;
    return;
}

void lexAna::pointReturn() {
    this->_pointReturn();
}

void lexAna::fillBuffer(std::string* _buf) {
    std::for_each(_buf->begin(), _buf->end(), [](auto &temp){ temp = 0; });
    for (size_t i = 0; i < _buf->size() && !infile.eof(); i++) {
        _buf->operator[](i) = infile.get();
    }
    isRefilled = true;
    return;
}

lexAna::~lexAna(){
    delete this->dfaProcess;
    infile.close();
}
#endif