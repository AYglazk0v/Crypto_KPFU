#include "inc/generator.h"
#include "inc/prsParam.h"
#include <fstream>
#include <gmpxx.h>

namespace {
    void task1(const Settings& s, KeyGenerator& genKey) {
        std::ofstream pub("public.txt");
        if (pub.is_open()) {
            pub << genKey.getE()
                << '\n' << genKey.getN();
            pub.close();
        } else {
            throw std::runtime_error("Could not open the file public.txt");
        }
        std::ofstream priv("private.txt");
        if (priv.is_open()) {
            priv << genKey.getD()
                << '\n' << genKey.getN();
            priv.close();
        } else {
            throw std::runtime_error("Could not open the file private.txt");
        }
    }
    mpz_class pollard_rho(mpz_class n) {
        mpz_class x = 2, y = 2, d = 1;
        while (d == 1) {
            x = (x * x + 1) % n;
            y = (y * y + 1) % n;
            y = (y * y + 1) % n;
            d = gcd(abs(x - y), n);
        }
        if (d == n) {
            return 0;
        }
            return d;
    }

    void task4() {
        std::ifstream f("public.txt");
        mpz_class n;
        f >> n >> n;
        mpq_class q,p;
        p = pollard_rho(n);
        q = n / p;
        std::cout << "p: " << p << "\nq: " << q << '\n';
    }

    void solveTask (Settings& s) {
        switch (s.task_) {
            case 1: {
                KeyGenerator genKey{s.l_};
                task1(s, genKey);
            }
            break;
            case 2: {
                KeyGenerator k(s.l_);
                task1(s, k);
                k.encrypt_str(s.file_, s.key_);
                std::string tmp{"encrypted.txt"};
                std::string tmp1{"private.txt"};
                k.decrypt_str(tmp, tmp1);
            }
            break;
            case 3: {
                KeyGenerator k{s.l_, true};
                task1(s, k);
                k.encrypt_str(s.file_, s.key_);
                std::string tmp{"encrypted.txt"};
                std::string tmp1{"private.txt"};
                k.decrypt_str(tmp, tmp1);
            }
            break;
            case 4: {
                task4();
            }
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
