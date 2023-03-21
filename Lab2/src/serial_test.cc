#include "../inc/namespaces.hpp"
#include <iterator>
#include <mutex>
#include <sstream>

namespace Generator {
    
    namespace Serialtest {

        template<typename T1, typename T2> using umap = std::unordered_map<T1, T2>;

        static umap<int, umap<double, double>> criticalHi {
            {2, {{0.95, 0.352}, {0.9, 0.584}, {0.8, 1.005}, {0.2, 4.6}, {0.1, 6.251}, {0.05, 7.815}}},
            {3, {{0.95, 2.167}, {0.9, 2.833}, {0.8, 3.28}, {0.2, 9.8}, {0.1, 12.017}, {0.05, 14.057}}},
		    {4, {{0.95, 7.261}, {0.9, 8.547}, {0.8, 10.31}, {0.2, 19.31}, {0.1, 22.307}, {0.05, 24.996}}}
        };

        class sTest final{
            private:
                boost::dynamic_bitset<> st_MSeq_;
                int                     st_k_;

                std::map<int, int>      st_Mseries_;
                umap<int, double>       st_Mfreq_;
                double                  st_hi_;
                size_t                  st_n_;
                double                  st_n_t_;
            
            public:
                sTest(const boost::dynamic_bitset<>& MSeq, int k) : st_MSeq_(MSeq), st_k_(k) {
                    st_n_ = st_MSeq_.size() / st_k_;
                    countSeries();
                    countNs();
                }

                ~sTest() {};

                void run(double alpha) const {
                    std::stringstream s;

                    s << "____________________________\n";
                    s << "_______SERIAL_TEST__________\n";
                    s << "____________________________\n";
                    s << "___ЭМПИРИЧЕСКИЕ_ЧАСТОТЫ_____\n";
                    for (auto&& curr : st_Mseries_) {
                        for (int i = st_k_; i != 0; --i) {
                            s << (curr.first >> (i - 1) & 1);
                        }
                        s << " " << curr.second << '\n';
                    }
                    s << "_____ЭТАЛОННАЯ_ЧАСТОТА______\n";
                    s << "N_t = " << st_n_t_ << '\n';
                    s << "________Критерий_Hi^2_______\n";
                    s << "Hi^2 = " << st_hi_ << '\n';
                    s << "____________________________\n";
                    if (alpha == 0) {
                        double Hi_min = criticalHi[st_k_][0.1];
                        double Hi_max = criticalHi[st_k_][0.9];
                        if (Hi_max <= st_hi_ && Hi_min >= st_hi_) {
                            s << "_____SERIAL_TEST_PASSED!____\n";
                        } else {
                            s << "_____SERIAL_TEST_FAILED!____\n";
                        }
                    } else {
                        double Hi_min = criticalHi[st_k_][alpha];
                        if (Hi_min >= st_hi_) {
                            s << "_____SERIAL_TEST_PASSED!____\n";
                        } else {
                            s << "_____SERIAL_TEST_FAILED!____\n";
                        }
                    }
                    s << "____________________________\n\n";
                    std::lock_guard<std::mutex> lock(Generator::mtx_);
                    std::cout << s.str();
                }

            private:

                void countSeries() {
                    while (st_MSeq_.size() % st_k_ != 0) {
                        st_MSeq_ = st_MSeq_ >> 1;
                        st_MSeq_.pop_back();
                    }
                    for (size_t s = st_MSeq_.size(), e = 0; s != e; s -= st_k_) {
                        int tmp = 0;
                        for (size_t i = 0; i != st_k_; ++i) {
                            tmp = tmp << 1 | st_MSeq_[s - i - 1];
                        }
                        st_Mseries_[tmp]++;
                    }
                    for (auto&& curr : st_Mfreq_) {
                        st_Mfreq_[curr.first] = (0.0 + curr.second) / ((0.0 + st_MSeq_.size()) / st_k_);
                    }

                }

                void countNs() {
                    st_n_t_ = (0.0 + st_n_) / std::pow(2, st_k_);
                    for (auto&& curr : st_Mseries_){
                        st_hi_ += (0.0 + std::pow(0.0 + curr.second - st_n_t_, 2)) / st_n_t_;
                    }
                }

        };//class sTest

    }; //namespace Serialtest

    void Register::serialTest() {
        Serialtest::sTest tmp{MSeq_, settings_.getSerialK()};
        tmp.run(settings_.getSerialAlpha());
    };

}//namespace Generator