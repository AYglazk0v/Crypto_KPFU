#include "../inc/namespaces.hpp"

namespace {
    std::map<wchar_t, wchar_t> scanKey_()
    {
        std::cout << "Укажите путь к файлу с ключом для расшифровки:\n";
        std::string keyPath;
        std::cin >> keyPath;

        std::wifstream f(keyPath);
        std::map<wchar_t, wchar_t> retKey;
        if (f.is_open()) {
            f.imbue(std::locale("ru_RU.UTF-8"));
            std::wstring line;
            while (std::getline(f, line)) {
                if (line.begin() != line.end() - 1) {
                    retKey[*(line.end() - 1)] = *line.begin();
                }
            }
        }
        else {
            throw std::runtime_error("Не удалось открыть файл с ключевой комбинацией");
        }
        return retKey;
    }

    void createDecrypted_(std::map<wchar_t, wchar_t>& key) {
        std::cout << "Укажите путь к шифротексту\n";
        std::string pathTxt;
        std::cin >> pathTxt;

        std::wifstream fileIn(pathTxt);
        if (fileIn.is_open()) {
            fileIn.imbue(std::locale("ru_RU.UTF-8"));
            
            std::wofstream fileOut("./return/decrypted.txt", std::ios::trunc);
            if (fileOut.is_open()) {
                fileOut.imbue(std::locale("ru_RU.UTF-8"));
                
                std::wstring line;
                while (std::getline(fileIn, line)) {
                    for (auto it = line.begin(), ite = line.end(); it != ite; ++it) {
                        if (key.count(*it)) {
                            fileOut << key[*it];
                        } else {
                            fileOut << *it;
                        }
                    }
                }
                fileOut.close();
            } else {
                throw std::runtime_error("Не удалось создать файл decrypted.txt");
            }
            fileIn.close();
            std::cout << "Все ок! Проверяй файлы!\n";
        } else {
            throw std::runtime_error("Не удалось открыть исходный файл");
        }
    }
}

namespace decryption {
    void decrypto()
    {
        try {
            std::map<wchar_t, wchar_t> key = scanKey_();
            createDecrypted_(key);
        } catch (std::exception& e) {
            std::cerr << e.what();
        }
    }
}