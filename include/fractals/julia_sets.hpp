#ifndef JULIA_SETS_HPP
#define JULIA_SETS_HPP

#include <complex>

const size_t DEFAULT_ITER_CNT = 100;

class julia_sets {
    using Number = std::complex<double>;

    const size_t MAX_ITER_CNT;


public:
    Number z0;


    julia_sets(Number z0, size_t max_cnt = DEFAULT_ITER_CNT)
    : MAX_ITER_CNT {max_cnt}, z0 {z0}  {}



    size_t fits_cnt(Number z) {
        size_t i = 0;
        for(; i < MAX_ITER_CNT; ++i) {
            if(std::norm(z) >= 2) return i;
            z = z * z + z0;
        }
        return i;
    }
};


#endif
