#pragma once

#include "namespaces.hpp"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <fstream>
#include <vector>

namespace NSRegister {
    class Register final {
        private:
            ParserSettings::Settings settings_;
            std::vector<int> polynome_;
            boost::dynamic_bitset<> digits_;
        public:
            Register(int argc, char** argv);
            ~Register() = default;
            
            Register(const Register&) = delete;
            Register(Register&&) = delete;
            Register& operator=(const Register&) = delete;
            Register& operator=(Register&&) = delete;            
        
        private:
            void readFile();
            void genDigits();
            void parsePoly();

    };
} //Register