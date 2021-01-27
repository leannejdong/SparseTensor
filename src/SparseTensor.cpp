/*!
 * Created by leanne on 1/16/21.
 */

#include "../include/SparseTensor.h"
#include <algorithm>
#include <ranges>

using std::vector;
namespace SparseTensor {
    Matrix MatMultiply(const Matrix &m1, const Matrix &m2) {
// Matrix result(m1.size() * m2.size(), std::vector<double>(m1[0].size() *
//   m2[0].size()));
        Matrix result;
        auto n1 = m1.size();
        auto n2 = m1[0].size();
        auto n3 = m2.size();
        auto n4 = m2[0].size();
        if (n2 != n3) return result;
        result.resize(n1);
        for (auto& v4 : result) {
            v4.resize(n4);
        }
        for (std::size_t row(0); row < result.size(); ++row) {
            for (std::size_t col(0); col < result[0].size(); ++col) {
                for (std::size_t inner = 0; inner < m2.size(); ++inner) {
                    result[row][col] += m1[row][inner] * m2[inner][col];
                }
            }
        }

        return result;
    }

    Matrix SparseMul(const Matrix &A, const Matrix& B) {
        const int m = A.size(), n = A[0].size(), l = B[0].size();
        Matrix res(m, vector<int>(l));
        for (int i = 0; i < m; ++i) {
            for (int k = 0; k < n; ++k) {
                if (A[i][k]) {
                    for (int j = 0; j < l; ++j) {
                        res[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        return res;
    }

    Matrix KroneckersProduct(const Matrix &v1, const Matrix &v2){
        Matrix v(v1.size() * v2.size(), std::vector<Value>(v1[0].size() * v2[0].size()));
        for (std::size_t z1(0); z1 < v1.size(); ++z1) {
            for (std::size_t z2(0); z2 < v2.size(); ++z2) {
                for (std::size_t z3(0); z3 < v1[0].size(); ++z3) {
                    for (std::size_t z4(0); z4 < v2[0].size(); ++z4) {
                        v[z1*v2.size() + z2][z3*v2[0].size() + z4] = v1[z1][z3] * v2[z2][z4];
                    }
                }
            }
        }
        return v;
    }
    using Tensor = std::vector<std::vector<std::vector<std::vector<double>>>>;

    Tensor KroneckersOuterProduct(const Matrix &m1, const Matrix &m2) {
        // Matrix m(m1.size() * m2.size(), std::vector<double>(m1[0].size() *
        // m2[0].size()));
        Tensor result;
        auto n1 = m1.size();
        auto n2 = m1[0].size();
        auto n3 = m2.size();
        auto n4 = m2[0].size();
        result.resize(n1);
        for (auto& v2 : result) {
            v2.resize(n2);
            for (auto& v3 : v2) {
                v3.resize(n3);
                for (auto& v4 : v3) {
                    v4.resize(n4);
                }
            }
        }
        for (std::size_t z1(0); z1 < m1.size(); ++z1) {
            for (std::size_t z2(0); z2 < m1[0].size(); ++z2) {
                for (std::size_t z3(0); z3 < m2.size(); ++z3) {
                    for (std::size_t z4(0); z4 < m2[0].size(); ++z4) {
                        result[z1][z2][z3][z4] = m1[z1][z2] * m2[z3][z4];
                    }
                }
            }
        }
        return result;
    }


}
