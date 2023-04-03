#include <fstream>
#include <iostream>
#include <gmpxx.h>
#include <chrono>
#include <stdexcept>
#include <string>

class KeyGenerator {
    public:
        KeyGenerator(int L) {
            int n = L / 2;

            gmp_randstate_t state;
            gmp_randinit_default(state);
            gmp_randseed_ui(state, std::chrono::system_clock::now().time_since_epoch().count());

            mpz_class p, q;
            mpz_urandomb(p.get_mpz_t(), state, n);
            mpz_urandomb(q.get_mpz_t(), state, n);

            while (!mpz_probab_prime_p(p.get_mpz_t(), 100))
                mpz_urandomb(p.get_mpz_t(), state, n);

            while (!mpz_probab_prime_p(q.get_mpz_t(), 100))
                mpz_urandomb(q.get_mpz_t(), state, n);

            n_ = p * q;
            phi_ = (q_ - 1) * (p_ - 1);
            choose_e(); 
            mpz_invert(d_.get_mpz_t(), e_.get_mpz_t(), phi_.get_mpz_t());
            p_ = p;
            q_ = q;

            gmp_randclear(state);
        }

        ~KeyGenerator() = default;

        void setDFromFile(const std::string& file) {
            std::ifstream f(file);
            if (f.is_open()) {
                std::string s;
                std::getline(f,s);
                d_ = mpz_class{s.substr(2)};
                f.close();
            } else {
                throw std::runtime_error("Erorr in setDFromFile(): Could not open the file");
            }
        }

        void setEFromFile(const std::string& file) {
            std::ifstream f(file);
            if (f.is_open()) {
                std::string s;
                std::getline(f,s);
                e_ = mpz_class{s.substr(2)};
                f.close();
            } else {
                throw std::runtime_error("Erorr in setEFromFile(): Could not open the file");
            }
        }

        void setNFromFile(const std::string& file) {
            std::ifstream f(file);
            if (f.is_open()) {
                std::string s;
                std::getline(f,s);
                std::getline(f,s);
                n_ = mpz_class{s.substr(2)};
                f.close();
            } else {
                throw std::runtime_error("Erorr in setNFromFile(): Could not open the file");
            }
        }

        mpz_class getP() const      { return p_; }
        mpz_class getQ() const      { return q_; }
        mpz_class getN() const      { return n_; }
        mpz_class getPhi() const    { return phi_; }
        mpz_class getE() const      { return e_; }
        mpz_class gedD() const      { return d_; }

    private:
        void choose_e() {
            mpz_class e {65337};
            mpz_class gcd;

            while ((mpz_gcd(gcd.get_mpz_t(), phi_.get_mpz_t(), e.get_mpz_t())), gcd != 1){
                e += 2;
            }
            e_ = e;
        }

    private:
        mpz_class p_;
        mpz_class q_;
        mpz_class phi_;

        mpz_class n_;
        mpz_class e_;
        mpz_class d_;
};