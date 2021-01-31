#ifndef SPARSETENSORLIB_LIBRARY_H
#define SPARSETENSORLIB_LIBRARY_H

#include <utility>
#include <iostream>
#include <cassert>
#include <map>
#include <vector>
using std::cerr;
namespace SparseTensor {
    template<typename T1, typename T2>
    class matrix {
    private:
        std::map<std::pair<T1,T1>,T2> element_map;
        int n_rows;
        int n_cols;
    public:
        matrix(std::size_t nrows, std::size_t ncols, T2 v = 0)
                :n_rows(nrows), n_cols(ncols){};

        matrix(std::initializer_list<std::initializer_list<T2>> values)
        {
            int i = 0;
            for (const auto &row : values) {
                int j = 0;
                for (double element : row) {
                    element_map[std::pair(i,j)] = element;
                    ++j;
                }
                ++i;
            }

            cerr << "values.size(): " << values.size() << "\n";
            cerr << "values.begin()->size(): " << values.begin()->size() << "\n";
            n_rows = values.size();
            n_cols = values.begin()->size();
        }

        T1 num_rows() const
        {
            return n_rows;
        }

        T1 num_cols() const
        {
            return n_cols;
        }

        T2 operator()(int row, int col) const
        {
            return element_map.find(std::pair(row,col))->second;
        }

        T2 &operator()(int row, int col)
        {
            return element_map[{row,col}];
        }

    };

    template<typename T1, typename T2>
    matrix<T1, T2>operator* (const matrix<T1, T2> &m1, const matrix<T1, T2> &m2)
    {
        matrix<T1, T2> result(m1.num_rows(), m2.num_cols(), 0);
        std::cerr << "start multiply" << "\n";
        //result.insert({{0, 0}, 2.0});
        cerr << "result.num_rows()=" << result.num_rows() << "\n";
        for (std::size_t row(0); row < result.num_rows(); ++ row) {
            for (std::size_t col(0); col < result.num_cols(); ++col) {
                for (std::size_t inner(0); inner < m2.num_rows(); ++inner) {
                    auto a = m1(row,inner);
                    auto b = m2(inner,col);
                    result(row, col) += a * b;
                }

            }
        }
        return result;
    }

}

#endif ///SPARSETENSORLIB_LIBRARY_H
