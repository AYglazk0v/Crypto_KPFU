#include "inc/generator.h"
#include "inc/prsParam.h"
#include <cmath>

void KeyGenerator::encrypt_str(const std::string &s_pl_file, const std::string& s_pub_file) {
    std::ofstream enc("encrypted.txt");
    std::ifstream pl_file(s_pl_file, std::ios::binary | std::ios::ate);
    std::ifstream pub_file(s_pub_file);
    if (!pl_file.is_open() || !pub_file.is_open()) {
        throw std::runtime_error("Error: failed open plain text file or pubfile");
    }

    pub_file >> e_ >> n_;
    int f_size = pl_file.tellg();
    --f_size;
    char bytes[4];
    std::string tmp;
    mpz_class M, enc_data;
    int i,k;
    k = 0;
    pl_file.seekg(0);
    while (k <= f_size/4) {
        i = 0;
        if (k == f_size/4) {
            pl_file.read(bytes, f_size%4);
        } else {
            pl_file.read(bytes, 4);
        }
        while (i < 4) {
            tmp += bytes[i++];
        }
        ++k;
        pl_file.seekg(4 * k);
        for (int j = 0; j < 4; ++j) {
            bytes[j] = 32;
        }
        M = convertStingToNum(tmp);
        mpz_powm(enc_data.get_mpz_t(), M.get_mpz_t(), e_.get_mpz_t(), n_.get_mpz_t());
        enc << enc_data << " ";
        tmp = "";
    }
    enc.close();
    pl_file.close();
    pub_file.close();
}

void KeyGenerator::decrypt_str(const std::string &s_enc_file, const std::string &s_pvt_file) {
    std::ofstream dec("decrypted.txt");
    std::ifstream enc_file(s_enc_file);
    std::ifstream pvt_file(s_pvt_file);
    if (!enc_file.is_open() || !pvt_file.is_open()){
        throw std::runtime_error("Error: failed open file enc or pvt_file");
    }

    mpz_class tmp, num;
    pvt_file >> d_ >> n_;
    int t, i;
    std::string dec_text;
    while (enc_file >> tmp) {
        mpz_powm(num.get_mpz_t(), tmp.get_mpz_t(), d_.get_mpz_t(), n_.get_mpz_t());
        i = 1;
        while (i < 5) {
            tmp = num / std::pow(10, 12 - 3 * i);
            num = num % std::pow(10, 12 - 3 * i);
            tmp -= 100;
            t = mpz_get_ui(tmp.get_mpz_t());
            dec_text += static_cast<char>(t);
            i++;
        }
        dec << dec_text;
        dec_text = "";
    }
    dec.close();
    enc_file.close();
    pvt_file.close();
}