#include "token.hpp"
#ifndef _LEX_HPP_
#define _LEX_HPP_

class lexAna {
private:
    size_t lineNumber = 0;
    std::unordered_map<std::string, token> idTable;

    void insertTable(idToken _idT);
    bool findInIdTable(std::string _str); //如果是已经有的token，就不再新建
public:
    token getNextToken();
    inline std::unordered_map<std::string, token> getIdTable() { return idTable; }
};

#endif