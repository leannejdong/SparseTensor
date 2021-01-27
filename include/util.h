/*!
 * Created by leanne on 1/19/21.
 */

#ifndef SPARSETENSOR_UTIL_H
#define SPARSETENSOR_UTIL_H
#include <iostream>
#include <sstream>
#include <vector>
#include <span>
#include <type_traits>
#include <fmt/format.h>
//#include "format.h"
//#include "core.h"
//#include "format-inl.h"
//#include "format.cc"
using Value = int;
using std::array;
namespace SparseTensor {
    struct SparseMatrixEntry {
        int row;
        int col;
        Value value;

        SparseMatrixEntry(const int x, const int y, const Value c)
                : row(x), col(y), value(c) {}
    };

    inline std::ostream &operator<<(std::ostream &os, const std::vector<SparseTensor::SparseMatrixEntry> &sparsemat) {
        bool last = true;
        for (const SparseTensor::SparseMatrixEntry &item : sparsemat) {
            if (last) {
                last = false;
            } else {
                os << ",";
            }
            os << "[" << item.row << " " << item.col << " " << item.value << "]";
        }
        return os;
    }

    inline std::ostream &operator<<(std::ostream &os1, const std::vector<std::vector<Value>> &container) {
        for (const std::vector<Value> &row : container) {
            for (const Value &col : row) {
                os1 << col << " ";
            }
            os1 << "\n";
        }
        return os1;
    }

    template<typename T>
    concept Arithmetic = std::floating_point<T> || std::integral<T>;

    template<Arithmetic T>
    inline void nested_print(std::span<T> vector) {
//    inline void nested_print(const std::vector<double>& vector) {
        fmt::print("[{}]", fmt::join(vector.begin(), vector.end(), ", "));
    }

    template<typename T>
    inline void nested_print(std::span<T> tensor) requires (!Arithmetic<T>) {
 //   inline void nested_print(const T& tensor) {
        fmt::print("[");
        for (std::span curr_tensor : tensor) {
      //for (auto &curr_tensor : tensor) {
            nested_print(curr_tensor);
            fmt::print("\n");
        }
        fmt::print("]");
        fmt::print("\n");
    }

}

#endif //SPARSETENSOR_UTIL_H
