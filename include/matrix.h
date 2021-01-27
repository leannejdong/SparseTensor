#ifndef SPARSETENSORLIB_LIBRARY_H
#define SPARSETENSORLIB_LIBRARY_H

#include <utility>
#include <iostream>
#include <cassert>
#include <map>
using std::cerr;
namespace SparseTensor {
    class matrix {
    private:
        std::map<std::pair<int, int>, double> element_map;
        int n_rows;
        int n_cols;
    public:
        matrix(std::size_t nrows, std::size_t ncols, double v );

        matrix(std::initializer_list<std::initializer_list<double>> values);

        int num_rows() const;

        int num_cols() const;

        double operator()(int row, int col) const;

        double &operator()(int row, int col);

    };

    matrix operator*(const matrix &m1, const matrix &m2);
}

//void test();
#endif ///SPARSETENSORLIB_LIBRARY_H
