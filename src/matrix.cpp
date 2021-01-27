#include "../include/matrix.h"
#include "../include/SparseTensor.h"
#include "../include/util.h"
#include<random>
#include<iomanip>
#include<fstream>

namespace SparseTensor
{
    SparseTensor::matrix::matrix(std::size_t nrows, std::size_t ncols, double v = 0)
    : n_rows(nrows), n_cols(ncols) {};

    SparseTensor::matrix::matrix(std::initializer_list<std::initializer_list<double>> values) {
    int i = 0;
    for (const auto &row : values) {
        int j = 0;
        for (double element : row) {
            element_map[std::pair(i, j)] = element;
            ++j;
        }
        ++i;
    }

    cerr << "values.size(): " << values.size() << "\n";
    cerr << "values.begin()->size(): " << values.begin()->size() << "\n";
    n_rows = values.size();
    n_cols = values.begin()->size();
}

    int SparseTensor::matrix::num_rows() const {
        return n_rows;
    }

    int SparseTensor::matrix::num_cols() const {
        return n_cols;
    }

    double SparseTensor::matrix::operator()(int row, int col) const
    {
        return element_map.find(std::pair(row,col))->second;
    }

    double &SparseTensor::matrix::operator()(int row, int col) {
        return element_map[{row, col}];
    }

    SparseTensor::matrix operator*(const matrix &m1, const matrix &m2) {
        matrix result(m1.num_rows(), m2.num_cols(), 0);
        std::cerr << "start multiply" << "\n";
        //result.insert({{0, 0}, 2.0});
        cerr << "result.num_rows()=" << result.num_rows() << "\n";
        for (std::size_t row(0); row < result.num_rows(); ++row) {
            for (std::size_t col(0); col < result.num_cols(); ++col) {
                for (std::size_t inner(0); inner < m2.num_rows(); ++inner) {
                    auto a = m1(row, inner);
                    auto b = m2(inner, col);
                    result(row, col) += a * b;
                }

            }
        }
        return result;
    }
}

