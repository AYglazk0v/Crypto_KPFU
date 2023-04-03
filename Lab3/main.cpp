#include "inc/generator.h"
#include "inc/prsParam.h"
#include <exception>
#include <fstream>
#include <stdexcept>

namespace {
    void task1(const Settings& s) {
        KeyGenerator genKey{s.l_};
        std::ofstream pub("public.txt");
        if (pub.is_open()) {
            pub << "E:" << genKey.getE()
                <<"\nN:" << genKey.getN();
            pub.close();
        } else {
            throw std::runtime_error("Could not open the file public.txt");
        }
        std::ofstream priv("private.txt");
        if (priv.is_open()) {
            priv << "D:" << genKey.gedD()
                << "\nN:" << genKey.getN();
            priv.close();
        } else {
            throw std::runtime_error("Could not open the file private.txt");
        }
    }

    void solveTask (Settings& s) {
        switch (s.task_) {
            case 1: {
                task1(s);
            }
            break;
            case 2: {
                
            }
            break;
        }
    }

}

int main(int argc, char** argv) {
    Settings s;
    s.parseSettings(argc, argv);

    try {
        solveTask(s);
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }

    return 0;
}
