#include "../../Include/lexical_analizer.hpp"

class Satoru {
private:
    lexicalAnalysis* LexProcess;
    std::string _pth;
    bool doLexicalAna() {
        LexProcess = new lexicalAnalysis(_pth);
        return LexProcess->isPrecdictGood();
    }
    bool doParserAna() {
        do {
            if (!this->doLexicalAna()) break;
            return true;
        } while(0);
        return false;
    }
    std::unordered_map<std::string, bool(Satoru::*)()> funcMap = {
        {"--l", &doLexicalAna}, {"-l", &doLexicalAna}
    };
public:
    explicit Satoru(std::string path) : _pth(path) {}
    bool run(std::string argv_2) {
        if (funcMap.find(argv_2) == funcMap.end()) {
            std::cerr << "parameter unknown";
            return false;
        } else {
            return (this->*funcMap[argv_2])();
        }
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> __argv(argc);
    for (size_t i = 0; i < argc; i++) {
        __argv[i] = argv[i];
    }
    return !(Satoru(std::string{__argv[1]}).run(__argv[2]));
}