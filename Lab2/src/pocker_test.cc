#include "../inc/namespaces.hpp"
#include <iostream>
#include <mutex>
#include <sstream>

namespace Generator {

    namespace Pokertest{

        template<typename T1, typename T2> using umap = std::unordered_map<T1, T2>;
        
        static umap<double, double> criticalHi = {{0.95, 1.645}, {0.9, 2.2}, {0.8, 3.07}, {0.2, 8.56}, {0.1, 10.64}, {0.05, 12.59}};

        class pTest {
            private:
                int                     q_ = 10;
                int                     m_;
                double                  hi_;
                std::vector<uint8_t>    u_;
                u_int                   count_[7];
            
            public:
                pTest(){}
                ~pTest(){}

            private:
                void makeCount(boost::dynamic_bitset<> tmp) {
                    while (tmp.size() % 32 != 0) {
                        tmp = tmp >> 1;
                        tmp.pop_back();
                    }
                    m_ = tmp.size();

                    for (size_t s = tmp.size(), e = 0; s != e; s-=32) {
                        u_int curr = 0;
                        for (size_t i = 0; i != 32; ++i){
                            curr = curr << 1 | tmp[s - i - 1];
                        }
                        curr = (0.0 + curr) / (std::pow(2,32) - 1) * q_;
                        if (curr != 10) {
                            u_.push_back(static_cast<uint8_t>(curr));
                        } else {
                            u_.push_back(static_cast<uint8_t>(9));
                        }
                    }

                    while (u_.size() % 5 != 0) {
                        u_.pop_back();
                    }

                    for (size_t s = 0, e = u_.size(); s != e; s+=5) {
                        std::map<int,int> m;
                        for (size_t i =0; i != 5; ++i){
                            m[u_[s + i]]++;
                        }
                        if (m.size() == 5) {
                            count_[0]++;
                        } else if (m.size() == 4) {
                            count_[1]++;
                        } else if (m.size() == 3) {
                            bool visit = false;
                            for (auto&& c : m) {
                                if (c.second == 3) {
                                    count_[3]++;
                                    visit = true;
                                }
                            }
                            if (visit == false) {
                                count_[2]++;
                            }
                        } else if (m.size() == 2) {
                            if ((*m.begin()).second == 3 || (*m.begin()).second == 2) {
                                count_[4]++;
                            } else {
                                count_[5]++;
                            }
                        } else {
                            count_[6]++;
                        }
                    }

                }

            public:
                void run(const boost::dynamic_bitset<>& MSeq, double alpha) {
                    makeCount(MSeq);
                    double p[7];

                	p[0] = (0.3024 * MSeq.size() / 160);
                	p[1] = (0.504 * MSeq.size() / 160);
                	p[2] = (0.108 * MSeq.size() / 160);
                	p[3] = (0.072 * MSeq.size() / 160);
                	p[4] = (0.009 * MSeq.size() / 160);
                	p[5] = (0.0045 * MSeq.size() / 160);
                	p[6] = (0.0001 * MSeq.size() / 160);

                    hi_ = 0.0;
                    for (int i = 0; i < 7; ++i) {
                        hi_ += std::pow(count_[i] - p[i], 2) / p[i];
                    }

                    std::stringstream s;
                    s << "____________________________\n";
                    s << "_________POKER_TEST_________\n";
                    s << "____________________________\n";
                    s << "_ЭМПИР_И_ЭТАЛОННЫЕ_ЧАСТОТЫ__\n";
                    for (int i = 0; i < 7; ++i) {
                        s << "N_" << i << "=" << count_[i] << "\t--\tP_" << i << "=" << p[i] << std::endl;
                    }
                    s << "________Критерий_Hi^2_______\n";
                    s << "Hi^2 =" << hi_ << '\n';
                    s << "____________________________\n";
                    if (alpha == 0.0) {
                        double Hi_max = criticalHi[0.9];
                        double Hi_min = criticalHi[0.1];
                        if (Hi_max <= hi_ && Hi_min >= hi_) {
                            s << "______POKER_TEST_PASSED!____\n";
                        } else {
                            s << "______POKER_TEST_FAILED!____\n";
                        }
                    } else {
                        double Hi_min = criticalHi[alpha];
                        if (Hi_min >= hi_) {
                            s << "______POKER_TEST_PASSED!____\n";
                        } else {
                            s << "______POKER_TEST_FAILED!____\n";
                        }
                    }
                    s << "____________________________\n\n";
                    std::lock_guard<std::mutex> lock(Generator::mtx_);
                    std::cout << s.str();
                }
        }; //class pTest
    }//namespace Pokertest

    void Register::pokerTest() {
        Pokertest::pTest tmp{};
        tmp.run(MSeq_, settings_.getPokerAlpha());
    }

} //namespace Generator