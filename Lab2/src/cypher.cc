#include "../inc/namespaces.hpp"
#include <algorithm>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <cstddef>
#include <fstream>
#include <vector>

namespace Generator {

    namespace Cypher {

        std::vector<u_char> readFileBin(std::string filename) {
            std::ifstream f(filename, std::ios::binary);
            if (!f.is_open()) {
                throw std::runtime_error("Error ifstream " + filename);
            }
            std::vector<u_char> retVal;
            retVal.reserve(4097);
            std::string s;
            while (std::getline(f, s)) {
                std::for_each(s.begin(), s.end(), [&retVal](u_char curr){retVal.push_back(curr);});
            }
            f.close();
            retVal.shrink_to_fit();
            return retVal;
        }

        std::vector<u_char> perfomingXOR(std::vector<u_char>& src, std::vector<u_char>& key, std::string filename) {
            std::vector<u_char> ret(src.size());
            for (size_t s = 0, e = src.size(); s != e; ++s) {
                ret[s] = src[s] ^ key[s];
            }

            std::ofstream f(filename, std::ios::binary);
            if (!f.is_open()) {
                throw std::runtime_error("Error ofstream " + filename);
            }
            std::for_each(ret.begin(), ret.end(), [&f](u_char curr){f << curr;});
            f.close();
            return ret;
        }

        void encrypt(boost::dynamic_bitset<> MSeq_, std::string filename)  {
            try {
                std::vector<u_char> src = readFileBin(filename);
                std::vector<u_char> key;
                key.reserve(src.size());

                if (MSeq_.size() < 8) {
                    throw std::runtime_error("BAD MSeq");
                }

                while (MSeq_.size() % 8 != 0) {
                    MSeq_.pop_back();
                }

                for (size_t s = MSeq_.size(), e = 0; s != e; s-=8) {
                    u_char curr = 0;
                    for (size_t i = 0; i != 8; ++i){
                        curr = curr << 1 | MSeq_[s - i - 1];
                    }
                    key.push_back(static_cast<uint8_t>(curr));
                }

                size_t i = 0;
                while (src.size() > key.size()){
                    key.push_back(key[i]);
                }

                std::vector<u_char> enctypted = perfomingXOR(src, key, "encrypted.txt");
                perfomingXOR(enctypted, key, "decrypted.txt");
            } catch (const std::exception& e) {
                std::cerr << e.what();
            }
        }
    }
}