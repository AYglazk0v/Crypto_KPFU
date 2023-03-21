#include "../../inc/namespaces.hpp"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <vector>

namespace Generator {

    namespace Corrtest {
        template<typename T1, typename T2> using umap = std::unordered_map<T1, T2>;
        class cTest final{
            
            friend class Generator::Register;
            
            private:
                std::vector<int> k_{1,2,8,9};
                umap<int, double> r_;
            
            public:
                cTest(){}
                ~cTest(){}
            
            private:
                void autoCorr(const boost::dynamic_bitset<>& MSeq) {
                    for (auto curr : k_) {
                        double m_i = 0.0;
                        for (size_t j = 0; j < MSeq.size() - curr; ++j) {
                            m_i += MSeq[j];
                        }
                        m_i*= 1.0 / (MSeq.size() - curr);
                        
                        double m_i_k = 0.0;
                        for (size_t j = 0; j < MSeq.size(); ++j) {
                            m_i_k += MSeq[j];
                        }
                        m_i_k *= 1.0 / (MSeq.size() - curr);

                        double d_i = 0.0;
                        for (size_t j = 0; j < MSeq.size() - curr; ++j) {
                            d_i += std::pow(MSeq[j]-m_i, 2);
                        }
                        d_i *= 1.0 / (MSeq.size() - curr - 1);

                        double d_i_k = 0.0;
                        for (size_t j = 0; j < MSeq.size(); ++j) {
                            d_i_k += std::pow(MSeq.size() - m_i_k, 2);
                        }
                        d_i_k *= 1.0 / (MSeq.size() - curr - 1);

                        for (size_t j = 0; j < MSeq.size() - curr; ++j){
                            r_[curr] += (MSeq[j] - m_i) * (MSeq[j + curr] - m_i_k);
                        }
                        r_[curr] /= (MSeq.size() - curr) * std::sqrt(d_i *d_i_k);
                        r_[curr] = std::abs(r_[curr]);
                    }
                }

            public:
                void run(const boost::dynamic_bitset<>& MSeq, std::mutex& mtx_){
                    autoCorr(MSeq);
                    double n = MSeq.size();
                    double r_cr = 1.0 /(n-1) + 2.0/(n-2)*std::sqrt((n * (n - 3))/(n + 1));
                    std::lock_guard<std::mutex> lock(mtx_);
                    std::cout << "____________________________\n";
                    std::cout << "__________CORR_TEST_________\n";
                    std::cout << "____________________________\n";
                    bool pass = true;
                    std::cout << "_АВТОКОРРЕЛЯЦИОННАЯ_ФУНКЦИЯ_\n";
                    for (auto&& curr : r_) {
                        if (curr.second > r_cr) {
                            pass = false;
                        }
                        std::cout << "R[" << curr.first << "]: " << curr.second << '\n'; 
                    }
                    std::cout << "____________________________\n";
                    std::cout << "_____КРИТИЧЕСКОЕ_ЗНАЧЕНИЕ___\n";
                    std::cout << "R[k]_cr: " << r_cr;
                    std::cout << "____________________________\n";
                    if (pass){
                        std::cout << "____CORR_TEST_PASSED!___\n";
                    } else {
                        std::cout << "____CORR_TEST_FAILED!___\n";
                    }
                }
        }; //class cTest

    } //namespace Corrtest

    void Register::corrTest(const Register& r) {
        Corrtest::cTest tmp{};
        tmp.run(r.MSeq_, mtx_);
    }

    void Register::crutches() {
        Corrtest::cTest tmp{};
        tmp.k_ = std::vector<int>{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        tmp.autoCorr(MSeq_);
        for (auto&& curr : tmp.r_) {
            std::cout << "R[" << curr.first << "]: " << curr.second << '\n'; 
        }
    }

}//namespace Generator