#include <fstream>
#include <gmpxx.h>
#include <chrono>
#include <iostream>

class KeyGenerator {
    public:
        KeyGenerator(int L, bool task_3 = false) {
            int n = L / 2;

            gmp_randstate_t state;
            gmp_randinit_default(state);
            gmp_randseed_ui(state, std::chrono::system_clock::now().time_since_epoch().count());

            mpz_urandomb(p_.get_mpz_t(), state, n);
            mpz_urandomb(q_.get_mpz_t(), state, n);

            while (!mpz_probab_prime_p(p_.get_mpz_t(), 100))
                mpz_urandomb(p_.get_mpz_t(), state, n);

            if (!task_3) {
                while (!mpz_probab_prime_p(q_.get_mpz_t(), 100))
                    mpz_urandomb(q_.get_mpz_t(), state, n);
            } else {
                while (mpz_probab_prime_p(q_.get_mpz_t(), 100))
                    mpz_urandomb(q_.get_mpz_t(), state, n);
            }
            n_ = p_ * q_;
            phi_ = (q_ - 1) * (p_ - 1);
            choose_e();
            std::cout << "orig p: " << p_ << "\norig q: " << q_ << '\n';
            mpz_invert(d_.get_mpz_t(), e_.get_mpz_t(), phi_.get_mpz_t());
            gmp_randclear(state);
        }

        ~KeyGenerator() = default;

        mpz_class getP() const      { return p_; }
        mpz_class getQ() const      { return q_; }
        mpz_class getN() const      { return n_; }
        mpz_class getPhi() const    { return phi_; }
        mpz_class getE() const      { return e_; }
        mpz_class getD() const      { return d_; }

        void encrypt_str(const std::string &s_pl_file, const std::string& pub_file);
        void decrypt_str(const std::string &s_enc_file, const std::string& pvt_file);
        



    private:
        void choose_e() {
            mpz_class e {65337};
            mpz_class gcd;

            while ((mpz_gcd(gcd.get_mpz_t(), phi_.get_mpz_t(), e.get_mpz_t())), gcd != 1){
                e += 2;
            }
            e_ = e;
        }

        mpz_class convertStingToNum(std::string& in) {
            mpz_class tmp;
            mpz_class tmp_data;
            for (auto&& c : in) {
                if (c == 0) {
                    break;
                }
                tmp= c;
                tmp += 100;
                tmp_data = tmp_data * 1000 + tmp;
            }
            return tmp_data;
        }

    private:
        mpz_class p_;
        mpz_class q_;
        mpz_class phi_;

        mpz_class n_;
        mpz_class e_;
        mpz_class d_;
};