#include "namespaces.hpp"

#include <random>

namespace {

    std::random_device rd;
    std::mt19937 gen(rd());
    
    int random_(int low, int high)
    {      
        std::uniform_int_distribution<> dist(low, high);
        return (dist(gen));
    }

    std::map<wchar_t, wchar_t> genereationReplAlphabet_()
    {
        std::wstring alpha = L"ЙФЯЦЫЧУВСКАМЕПИНРТГОЬШЛБЩДЗЖЮЭХЪабвгдежзийклмнопрстуфхцчшщъыьэюя ,.!?";
        std::map<wchar_t, wchar_t> retAlpha;
        for (auto c : alpha)
        {
            retAlpha[c] = L'0';
        }
        int sz_alpha = alpha.size() - 1;
        for (auto it = retAlpha.begin(), ite = retAlpha.end(); it != ite; ++it)
        {
            int index_remove_c = random_(0, sz_alpha);
            (*it).second = alpha[index_remove_c];
            alpha.erase(std::remove(alpha.begin(), alpha.end(), alpha[index_remove_c]), alpha.end());
            sz_alpha--;
        }
        return retAlpha;
    }

    void cryptoFile_(std::map<wchar_t, wchar_t>& key, std::wifstream& file)
    {
        std::wofstream f("encrypted.txt", std::ios::trunc);
        if (f.is_open()) {
            f.imbue(std::locale("ru_RU.UTF-8"));

            std::wstring line;
            while(std::getline(file, line)) 
            {
                for (auto curr : line)
                {
                    if (key.count(curr)) 
                    {
                        f << key[curr];
                    } else {
                        f << curr;
                    }
                }
                f << std::endl;
            }
            f.close();
        } else {
            throw std::runtime_error("Не удалось открыть файл encrypted.txt");
        }
    }

    void keyFile_(std::map<wchar_t, wchar_t>& key)
    {
        std::wofstream f("key.txt", std::ios::trunc);
        if (f.is_open()) {
            f.imbue(std::locale("ru_RU.UTF-8"));
            for (auto curr : key) {
                f << curr.first << "-" << curr.second << std::endl;
            }
            f.close();
        }
        else {
            throw std::runtime_error("Не удалось создать файл для записи key.txt");
        }
    }
}

namespace encryption {

    void crypto()
    {
        std::cout << "Укажите путь к файлу, который хотите зашифровать\n";

        std::string path;
        std::cin >> path;

        std::wifstream file(path);
        file.imbue(std::locale("ru_RU.UTF-8"));
        if (file.is_open())
        {
            std::map<wchar_t,wchar_t> key = genereationReplAlphabet_();
            try {
                keyFile_(key);
                cryptoFile_(key, file);
                file.close();
                std::cout << "OK!\n";
            } catch (std::exception& e) {
                std::cerr << e.what();
            }
        } else {
            std::cerr << "Файл не был открыт.";
        }
    }

}// encryption