#include <fstream>
#include <map>
#include <iostream>

int main(int argc, char** argv)
{
    std::wifstream f(argv[1]), f1(argv[2]);
    f.imbue(std::locale("ru_RU.UTF8")), f1.imbue(std::locale("ru_RU.UTF8"));
    
    std::map<wchar_t, wchar_t> pairs;

    std::wstring s, s1;
    while(std::getline(f,s) && std::getline(f1,s1)) {
        for (auto it = s.begin(), ite = s.end(), it1 = s1.begin(), ite1 = s1.end(); it != ite && it1 != ite1; ++it, ++it1) {
            pairs[*it] = *it1;
        }
    }
    f1.close(), f.close();

    std::wofstream fOut("pairs.txt", std::ios::trunc);
    fOut.imbue(std::locale("ru_RU.UTF-8"));
    for (auto&& curr : pairs) {
        fOut << curr.first << "-" << curr.second << std::endl;
    }
    fOut.close();
    return 0;
}