/*!
 * @author Leanne Dong
 */
#ifndef SPARSETENSOR_SPARSETENSOR_H
#define SPARSETENSOR_SPARSETENSOR_H
#include "matrix.h"
#include "util.h"
#include <unordered_map>
#include <vector>
namespace SparseTensor{
    using std::unordered_map;
    using Matrix = std::vector<std::vector<int>>;
    using Tensor = std::vector<std::vector<std::vector<std::vector<double>>>>;



//Value SparseDotProd(const SparseTensor &m1, const SparseTensor &m2);
    Matrix MatMultiply(const Matrix &m1, const Matrix &m2);
    Matrix SparseMul(const Matrix &A, const Matrix& B);
    Matrix KroneckersProduct(const Matrix &v1, const Matrix &v2);
    Tensor KroneckersOuterProduct(const Matrix &m1, const Matrix &m2);


    void forEachElement(Matrix &m, const auto &f)
    {
        for (size_t row(0); row < m.size(); ++row) {
            for (size_t col(0); col < m[0].size(); ++col) {
                f(m[row][col], row, col);
            }
        }
    }

}

#endif //SPARSETENSOR_SPARSETENSOR_H
