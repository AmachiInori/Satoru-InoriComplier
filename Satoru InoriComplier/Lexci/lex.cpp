#ifndef _LEX_HPP_
#define _LEX_HPP_
#include "lex.h"
#include "DFA.h"

lexAna::lexAna(std::string _file) 
    : fileName(_file), lineNumber(1), lastLineNumber(1), nowPoint(-1), lastPoint(-1), bufferSize(4096) {
    infile.open(_file, std::ios::in | std::ios::binary);
    if (!infile) isInfileGood = false;
    dfaProcess = new DFA(this);
    bufferA.resize(bufferSize, 0); // 0��Ϊ����������
    bufferB.resize(bufferSize, 0);
    for (size_t i = 0; i < bufferA.size() && !infile.eof(); i++) {
        bufferA[i] = infile.get();
    }
    for (auto &_keyWord : _remain) { //�������ֲ�����ű�
        idTable[_keyWord.first] = remainToken(_keyWord.first, _keyWord.second);
    }
}

bool lexAna::findInIdTable(std::string _str) { 
    return idTable.find(_str) != idTable.end(); 
}

inline std::unordered_map<std::string, token> lexAna::getIdTable() { 
    return idTable; 
}

token* lexAna::getNextToken() {
    return this->dfaProcess->getToken();
}

char lexAna::getNextChar() {
    if (!isInfileGood) { //δ����ȷ��ȡ�ļ�
        throw(can_not_open_file(fileName));
    }
    lastPoint = nowPoint, lastLineNumber = lineNumber;
    char tempChar = newCharFromBuffer();
    while (isEmptyChar(tempChar) && isEmptyChar(lastChar)) 
        tempChar = newCharFromBuffer();
    if (tempChar == '#') {
        tempChar = newCharFromBuffer();
        while (tempChar != '#' && tempChar != 0)
            tempChar = newCharFromBuffer(); //ע�ʹ�������
    }
    return tempChar; 
}

char lexAna::newCharFromBuffer() {
    lastChar = nowChar;
    char tempChar;
    nowPoint++;
    if (nowPoint < 4096) {
        tempChar = bufferA[nowPoint];
        if (nowPoint >= 4096 / 2) {
            this->fillBuffer(&bufferB);
        }
    } else {
        tempChar = bufferB[nowPoint - 4096];
        if (nowPoint >= 4096 * 3 / 2) {
            this->fillBuffer(&bufferA);
        }
    }
    nowPoint = nowPoint % 8192;

    if (tempChar == '\n') lineNumber++;
    nowChar = tempChar;
    return tempChar;
}

void lexAna::pointReturn() {
    if (nowPoint == lastPoint) {
        throw(can_not_return_back(nowPoint));
    }
    nowPoint = lastPoint;
    lineNumber = lastLineNumber;
    return;
}

void lexAna::fillBuffer(std::string* _buf) {
    _buf->resize(bufferSize, 0);
    for (size_t i = 0; i < _buf->size() && !infile.eof(); i++) {
        _buf->operator[](i) = infile.get();
    }
    return;
}
#endif