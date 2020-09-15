#include "base.hpp"
#include "token.hpp"
#ifndef _LEX_HPP_
#define _LEX_HPP_

class lexAna {
private:
    size_t lineNumber = 0, lastLineNumber = 0;
    size_t nowPoint = 0, lastPoint = 0; //np��ʾ�ոձ����������char
    static const size_t bufferSize = 4096;
    std::unordered_map<std::string, token> idTable;
    std::ifstream infile;
    DFA* dfaProcess;
    
    std::string bufferA, bufferB;
    
    void fillBuffer(std::string* _buf);
    char newCharFromBuffer();
    void insertTable(idToken _idT);
    bool findInIdTable(std::string _str) { return idTable.find(_str) != idTable.end(); } //������Ѿ��е�token���Ͳ����½�
public:
    lexAna(std::string _file) {
        infile.open(_file); // ע�� �˴�δ�ж��Ƿ�ɹ���ȡ�ļ�
        dfaProcess = new DFA(this);
        bufferA.resize(bufferSize);
        bufferB.resize(bufferSize);
        for (int i = 0; i < bufferA.size() && !infile.eof(); i++) {
            bufferA[i] = infile.get();
        }
    }
    friend class DFA;

    token getNextToken();

    char getNextChar();
    void pointReturn();

    inline std::unordered_map<std::string, token> getIdTable() { return idTable; }
};

class DFA {
private:
    lexAna* const host;
    _DFAstate state = DFAstate::START;
    _DFAstate lastState = DFAstate::START;
    
    inline void stateTo(_DFAstate newState) {
        lastState = state;
        state = newState;
    }
    bool trans(char _iptc);
    token bulidToken(_ACCstate _accKind, std::string _accString);

    DFA(const DFA& _a); //���θ��ƹ��캯��
    DFA& operator=(const DFA& _a); //���θ�ֵ
public:
    DFA(lexAna* _host) : host(_host) {};
    void reset() { state = lastState = DFAstate::START; }
    token getToken();
};

bool DFA::trans(char _iptc) {
    using namespace DFAstate;
    switch (this->state) {
    case START: // 0
        if (isDigit(_iptc) && _iptc != '0') {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        else if (_iptc == '+' || _iptc == '-') {
            stateTo(NUM_MAIN_PONE_IN);
            return true;
        } 
        else if (_iptc == '0') {
            stateTo(NUM_MAIN_FIRST_ZERO_IN);
            return true;
        } 
        else return false;
        break;

    case NUM_MAIN_PONE_IN: // 1
        if (isDigit(_iptc)) {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        else return false;
        break;

    case NUM10_MAIN_INPUTING_DIGIT: // 2
        if (isDigit(_iptc)) {
            stateTo(NUM10_MAIN_INPUTING_DIGIT);
            return true;
        } 
        else if (_iptc == 'U' || _iptc == 'u') {
            stateTo(NUM10_ACCEPT_UNSIGNED_INT);
            return true;
        }
        else if (_iptc == '.') {
            stateTo(NUM10_FLT_DOT_IN);
            return true;
        }

    case NUM10_ACCEPT_UNSIGNED_INT:

    }
}

token DFA::getToken(){
    this->reset();
    std::string tempToken;
    char tempChar;
    while (tempChar = host->getNextChar()) {
        if (isEmptyChar(tempChar)) { // ���հ׷��ָ��Ĵ���Ϊ����token
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(state);
                return bulidToken(tempAcc.first, tempToken);
            } else {
                throw(no_mode_matched(tempToken));
            }
        }

        tempToken.push_back(tempChar); // �հ׷�������β��ܽ���token��
        if (this->trans(tempChar)) {
            if (DFAstate::isStateAcc(state)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(lastState);
                if (tempAcc.second == 0) {
                    return bulidToken(tempAcc.first, tempToken);
                }
            }
        } else {
            if (DFAstate::isStateAcc(lastState)) {
                std::pair<_ACCstate, _ACCaction> tempAcc = DFAstate::getAccState(lastState);
                if (tempAcc.second == 1) {
                    tempToken.pop_back();
                    host->pointReturn();
                }
                return bulidToken(tempAcc.first, tempToken);
            } else {
                throw(no_mode_matched(tempToken));
            }
        }
    }

    return token();
}

token DFA::bulidToken(_ACCstate _accKind, std::string _accString) {
    using namespace DFAstate;
    if (host->findInIdTable(_accString)) return host->idTable[_accString];
    switch (_accKind) {
    case _NUM10_INT:
        return intToken(_accString);
        break;
    
    default:
        break;
    }
}

token lexAna::getNextToken() {

}

char lexAna::getNextChar() {
    lastPoint = nowPoint, lastLineNumber = lineNumber;
    char tempChar = newCharFromBuffer();
    while (tempChar == ' ' || tempChar == '\t' || tempChar == '\n') 
        tempChar = newCharFromBuffer();
    if (tempChar == '#') {
        tempChar = newCharFromBuffer();
        while (tempChar != '#')
            tempChar = newCharFromBuffer();
    }
    return tempChar;
}

char lexAna::newCharFromBuffer() {
    char tempChar;
    nowPoint++;
    if (nowPoint < 4096) {
        tempChar = bufferA[nowPoint];
        if (tempChar >= 4096 / 2) {
            this->fillBuffer(&bufferB);
        }
    } else {
        tempChar = bufferB[nowPoint - 4096];
        if (tempChar >= 4096 * 3 / 2) {
            this->fillBuffer(&bufferA);
        }
    }
    nowPoint = nowPoint % 8192;

    if (tempChar == '\n') lineNumber++;
    return tempChar;
}

void lexAna::pointReturn() {
    if (nowPoint == lastPoint) {
        throw(can_not_return_back(nowPoint));
    }
    nowPoint = lastPoint;
    lineNumber = lastLineNumber;
}

#endif