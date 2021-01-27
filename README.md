# A very simple sparse matrix/tensor library
(Work in Progress)
## Demo  

### Dependency
 * gcc10 
   
 * C++20
   
 * fast open-source formatting library
   [`{fmt}`](https://github.com/fmtlib/fmt)

### Instruction 
* Copy codes below, save it in a file `testlib.cpp` in a directory parallel to the SparseTensor directory.

* To build, execute `make` from terminal

* To run, execute `./sparse` or `./sparse >file.txt 2>&1` to redirect all terminal output to a file.

```cpp
#include"SparseTensor/include/matrix.h"
#include"SparseTensor/include/SparseTensor.h"
#include"SparseTensor/include/util.h"
#include"SparseTensor/include/Timer.h"
#include<random>
#include<iomanip>
#include<fstream>
#include <iostream>
#include <vector>
using std::vector;
constexpr int M = 5;
constexpr int N = 5;
using SparseTensor::SparseMatrixEntry;
using SparseTensor::operator<<;
using SparseTensor::nested_print;
using SparseTensor::MatMultiply;
using SparseTensor::SparseMul;
using SparseTensor::KroneckersProduct;
using SparseTensor::KroneckersOuterProduct;
using SparseTensor::matrix;
using SparseTensor::Timer;
using SparseTensor::Matrix;
using SparseTensor::Tensor;
int main()
{
      std::cerr << "Convert dense data structure to sparse" << "\n";

    vector<vector<int>> a {{{0, 3, 0, 0, 0}, {22, 0, 0, 0, 17},
                                   {7, 5, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 14, 0, 8}}};

    vector<SparseMatrixEntry> vs;
    vs.emplace_back(SparseMatrixEntry(0, 1, a[0][1]));
    vs.emplace_back(SparseMatrixEntry(1, 0, a[1][0]));
    vs.emplace_back(SparseMatrixEntry(1, 4, a[1][4]));
    vs.emplace_back(SparseMatrixEntry(2, 0, a[2][0]));
    vs.emplace_back(SparseMatrixEntry(2, 1, a[2][1]));
    vs.emplace_back(SparseMatrixEntry(2, 3, a[2][3]));
    vs.emplace_back(SparseMatrixEntry(4, 3, a[4][3]));
    vs.emplace_back(SparseMatrixEntry(4, 4, a[4][4]));
    std::cout << vs << "\n";
    std::cerr << "Convert sparse data structure to dense" << "\n";

    vector<SparseMatrixEntry> d;
    d.emplace_back(SparseMatrixEntry(0, 1, 3));
    d.emplace_back(SparseMatrixEntry(1, 0, 22));
    d.emplace_back(SparseMatrixEntry(1, 4, 17));
    d.emplace_back(SparseMatrixEntry(2, 0, 7));
    d.emplace_back(SparseMatrixEntry(2, 1, 5));
    d.emplace_back(SparseMatrixEntry(2, 3, 1));
    d.emplace_back(SparseMatrixEntry(4, 2, 14));
    d.emplace_back(SparseMatrixEntry(4, 4, 8));
    std::cout << d;
    std::cout << "\n";

    std::vector<std::vector<int>> vd(M, std::vector <int> (N, 0));
    vd[0][1] = d[0].value;
    vd[1][0] = d[1].value;
    vd[1][4] = d[2].value;
    vd[2][0] = d[3].value;
    vd[2][1] = d[4].value;
    vd[2][3] = d[5].value;
    vd[4][2] = d[6].value;
    vd[4][4] = d[7].value;
    std::cout << vd;

    std::cerr << "Perform matrix multiplication of 2D arrays: " << "\n";
    vector<vector<Value>> A {{{0, 3, 0, 0, 0}, {22, 0, 0, 0, 17},
                                     {7, 5, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 14, 0, 8}}};

    vector<vector<Value>> B {{{0, 3, 0, 0, 0}, {0, 0, 0, 0, 17},
                                     {7, 5, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 14, 0, 8}}};

    vector<vector<Value>> C = SparseMul(A, B);
    std::cout << C;

//    vector<vector<Value>> I1 {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
//
//    vector<vector<Value>> I2 {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
//
//    vector<vector<Value>> I3 = SparseMul(I1, I2);
//    std::cout << I3;
    Matrix D = MatMultiply(A, B);
    std::cout << D;

    std::cerr << "Compute kronecker products of 2 multidimensional arrays: " << "\n";
    Matrix m1{{1, 2}, {3, 4}, {1, 0}};
    Matrix m2{{0, 5, 2}, {6, 7, 3}};

    Matrix v(KroneckersProduct(m1, m2));
    std::cout << v;
    std::cerr << "Compute kronecker outer products of 2 multidimensional arrays: " << "\n";

    Tensor m(KroneckersOuterProduct(m1, m2));
    nested_print(std::span(m));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0);
    vector<vector<double>> Matrix(5, vector<double>(7, 0));
    std::ofstream file("matrix.txt");
    for (auto &row : Matrix){
        for (auto &col : row){
            col = dis(gen);
            file << std::setw(4) << col;
        }
        file << '\n';
    }

    matrix mtx { { 1.0, 2.0 }, { 4.0, 5.0 }, { 8.0, 9.0 } } ;
    matrix mty { { 3.0, 2.0, 1.0 }, { 4.0, 2.0, 9.0 } } ;
    std::cerr << "Measure time taken for naive Matrix multiplication: " << "\n";
    Timer t;
    matrix mtz = mtx * mty;
    std::cerr << "Measure time taken for printing naive Matrix multiplication (fmt): " << "\n";
    Timer tt;
    for (int i=0; i!=mtz.num_rows(); ++i) {
        for (int j=0; j!=mtz.num_cols(); ++j) {
            std::cout << mtz(i,j) << " ";
        }
        std::cout << "\n";
    }
}

//g++-10 -std=c++2a -o sparse testlib.cpp SparseTensor/src/SparseTensor.cpp -lfmt
```