#include "../../Include/lexical_analizer.hpp"

int doLexicalAna(std::string path) {

    return 0;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> __argv(argc);
    std::unordered_map<std::string, int(*)(std::string)> funcMap = {
        {"--l", doLexicalAna}, {"-l", doLexicalAna}
    };
    for (size_t i = 0; i < argc; i++) {
        __argv[i] = argv[i];
    }
    if (funcMap.find(__argv[2]) == funcMap.end()) {
        std::cerr << "parameter unknown";
        return 1;
    } else {
        return funcMap[__argv[2]](__argv[1]);
    }
}