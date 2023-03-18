#include "../../inc/namespaces.hpp"
#include <algorithm>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <string>
#include <unordered_map>

namespace Generator {
    
    namespace serialTest {

        template<typename T1, typename T2> using umap = std::unordered_map<T1, T2>;

        umap<int, umap<double, double>> criticalHi {
            {2, {{0.95, 0.352}, {0.9, 0.584}, {0.8, 1.005}, {0.2, 4.6}, {0.1, 6.251}, {0.05, 7.815}}},
            {3, {{0.95, 2.167}, {0.9, 2.833}, {0.8, 3.28}, {0.2, 9.8}, {0.1, 12.017}, {0.05, 14.057}}},
		    {4, {{0.95, 7.261}, {0.9, 8.547}, {0.8, 10.31}, {0.2, 19.31}, {0.1, 22.307}, {0.05, 24.996}}}
        };

        class sTest final{
            private:
                boost::dynamic_bitset<> st_MSeq_;
                int                     st_k_;

                umap<std::string, int> st_Mseries_;
                umap<std::string, double> st_Mfreq_;
                double                  st_hi_;
                size_t                  st_n_;
                double                  st_n_t_;
            
            public:
                sTest(boost::dynamic_bitset<>& MSeq, int k) : st_MSeq_(MSeq), st_k_(k) {
                    st_n_ = st_MSeq_.size() / st_k_;
                }

                ~sTest() {};

            private:
                void countSeries() {
                    
                }

                void countNs() {
                    st_n_t_ = st_n_ / std::pow(2, st_k_);
                    std::for_each(st_Mseries_.begin(), st_Mseries_.end(), [this](std::pair<std::string, int>& curr){ 
                        st_hi_ += std::pow(curr.second - st_n_t_, 2) / st_n_t_;
                    });
                }
        };
    };

    void Register::serialTest() {
    };
}