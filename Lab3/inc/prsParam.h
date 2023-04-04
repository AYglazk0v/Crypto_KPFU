#include <iostream>
#include <functional>
#include <unordered_map>

struct Settings{
    int         l_{1024};
    int         task_{1};
    std::string file_{};
    std::string key_{};

    void parseSettings(int argc, char** argv);
};

typedef std::function<void()> NoArgHandle;
typedef std::function<void(Settings&, const std::string&)> OneArgHandle;

const std::unordered_map<std::string, NoArgHandle> NoArgs {
        {"--help", [](){std::cout << "--L args {default 1024}\n--task args {default 1}\n--file arg \n--key arg";}},
        {"-h", [](){std::cout << "--L args {default 1024}\n--task args {default 1}\n--file arg \n--key arg";}},
};

#define S(str, f, v) {str, [](Settings& s, const std::string& arg) { s.f = std::v; }}
    const std::unordered_map<std::string, OneArgHandle> OneArgs {
      S("--task", task_, stoi(arg)),
      S("--L", l_, stoi(arg)),
      {"--file", [](Settings& s, const std::string& arg){s.file_ = arg;}},
      {"--key", [](Settings& s, const std::string& arg){s.key_ = arg;}},
    };
#undef S

inline void Settings::parseSettings(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        std::string opt{argv[i]};

        if (auto j {NoArgs.find(opt)}; j != NoArgs.end()) {
            j->second();
        } else if (auto k {OneArgs.find(opt)}; k != OneArgs.end()) {
            if (++i < argc) {
                k->second(*this, {argv[i]});
            }
            else {
                std::cout << "--L args {default 1024}\n--task args {default 1}\n";
                exit(1);
            }
        } else {
                std::cout << "--L args {default 1024}\n--task args {default 1}\n";
                exit(1);
        }
    }
}