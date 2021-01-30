# Naïve sparse matrix/tensor library
(Work in Progress)

## Dependency
 * GCC10 

 * GNU Build System (a.k.a. Make)
   
 * C++20
   
 * fast open-source formatting library
   [`{fmt}`](https://github.com/fmtlib/fmt)

(CMake was used to generate documentation, can be safely ignored)

## Instruction 
* Copy codes below, save it in a file `testlib.cpp` in a directory parallel to the SparseTensor directory.

* To build, use the following makefile
```makefile
CXX=g++-10
CXXFLAGS=-std=c++2a -MD
sparse: testlib.o SparseTensor/src/SparseTensor.o
>-------$(CXX) -o $@ $^ -lfmt

clean:
>-------rm -f *.o sparse SparseTensor/src/*.o

-include *.d
-include SparseTensor/src/*.d
```
execute `make` from terminal to build. Use `make clean` to clean auxiliary files (if needed).

* To run, execute `./sparse` or `./sparse >file.txt 2>&1` to redirect all terminal output to a file. (Demo 1) Or 
`./sparse 2>&1 | tee file.txt` to redirect all terminal output to a file (Demo 2)

## Demo 1

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

    vector<std::vector<int>> vd(M, vector <int> (N, 0));
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

## Demo 2 (Read user inputs)

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
using std::cout;
using std::vector;
constexpr int M = 5;
constexpr int N = 5;
constexpr int K = 8;
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

void case1();
void case2();
void case3();
void case4();
void case5();
void case6();

int main()
{
    int choice;
    do
    {
        cout << "\n";
        cout << "Please choose an operation from the following: " << "\n";
        cout << "\n";
        cout << "\t 1. Convert dense data structure to sparse" << "\n";
        cout << "\t 2. Convert sparse data structure to dense" << "\n";
        cout << "\t 3. Perform matrix multiplication of 2D arrays: " << "\n";
        cout << "\t 4. Compute kronecker products of 2 multidimensional arrays: " << "\n";
        cout << "\t 5. Compute kronecker outer products of 2 multidimensional arrays: " << "\n";
        cout << "\t 6. Measure time taken for naive sparse Matrix multiplication: " << "\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                case1();
                break;
            case 2:
                case2();
                break;
            case 3:
                case3();
                break;
            case 4:
                case4();
                break;
            case 5:
                case5();
                break;
            case 6:
                case6();
                break;
            default:
                cout << " We're done " << "\n";
                return 0;
        }
    }
    while(choice != 0);
}

void case1()
{
    vector<vector<int>> a(M, vector<int>(N, 0));

    cout << "Please enter a 2D array: " << "\n";

    for (auto &row : a)
    {
        for (auto &col : row)
        {
            std::cin >> col;
        }
    }
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
}
void case2()
{
    vector<SparseMatrixEntry> d;
    int i, j, k;

    for (int ii = 0; ii < 8; ++ii)
    {
        cout << "Please enter row position, column position and element value: ";
        std::cin >> i >> j >> k;
        d.emplace_back(SparseMatrixEntry(i, j, k));
    }
//    d.emplace_back(SparseMatrixEntry(0, 1, 3));
//    d.emplace_back(SparseMatrixEntry(1, 0, 22));
//    d.emplace_back(SparseMatrixEntry(1, 4, 17));
//    d.emplace_back(SparseMatrixEntry(2, 0, 7));
//    d.emplace_back(SparseMatrixEntry(2, 1, 5));
//    d.emplace_back(SparseMatrixEntry(2, 3, 1));
//    d.emplace_back(SparseMatrixEntry(4, 2, 14));
//    d.emplace_back(SparseMatrixEntry(4, 4, 8));
    std::cout << d;
    std::cout << "\n";

    std::vector<std::vector<int>> vd(M, std::vector<int>(N, 0));
    vd[0][1] = d[0].value;
    vd[1][0] = d[1].value;
    vd[1][4] = d[2].value;
    vd[2][0] = d[3].value;
    vd[2][1] = d[4].value;
    vd[2][3] = d[5].value;
    vd[4][2] = d[6].value;
    vd[4][4] = d[7].value;
    std::cout << vd;
}

void case3()
{
    vector<vector<int>> A(M, vector<int>(N, 0));
    vector<vector<int>> B(M, vector<int>(N, 0));

    cout << "Please enter a 2D array A: " << "\n";

    for (auto &row : A)
    {
        for (auto &col : row)
        {
            std::cin >> col;
        }
    }

    cout << "Please enter a 2D array B: " << "\n";

    for (auto &row : B)
    {
        for (auto &col : row)
        { 
            std::cin >> col;
        }
    }

//    vector<vector<Value>> A{{{0, 3, 0, 0, 0}, {22, 0, 0, 0, 17},
//                                    {7, 5, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 14, 0, 8}}};
//
//    vector<vector<Value>> B{{{0, 3, 0, 0, 0}, {0, 0, 0, 0, 17},
//                                    {7, 5, 0, 1, 0}, {0, 0, 0, 0, 0}, {0, 0, 14, 0, 8}}};
    cout << "The multiplication result from SparMul() is: " << "\n";
    vector<vector<Value>> C = SparseMul(A, B);
    std::cout << C;
    cout << "The multiplication result from MatMultiply() is: " << "\n";
    Matrix D = MatMultiply(A, B);
    std::cout << D;

}
void case4()
{
    Matrix m1(M, vector<int>(N, 0));
    Matrix m2(M, vector<int>(N, 0));
    cout << "Please enter the first matrix for KroneckersProduct: " << "\n";
    for (auto &row : m1)
    {
        for (auto &col : row)
        { 
            std::cin >> col;
        }
    }
    cout << "Please enter the second matrix for KroneckersProduct: " << "\n";
    for (auto &row : m2)
    {
        for (auto &col : row)
        { 
            std::cin >> col;
        }
    }

    Matrix v(KroneckersProduct(m1, m2));
    std::cout << v;
}
void case5()
{
    Matrix m1(M, vector<int>(N, 0));
    Matrix m2(M, vector<int>(N, 0));
    cout << "Please enter the first matrix for KroneckersOuterProduct: " << "\n";
    for (auto &row : m1)
    {
        for (auto &col : row)
        {
            std::cin >> col;
        }
    }
    cout << "Please enter the second matrix for KroneckersOuterProduct: " << "\n";
    for (auto &row : m2)
    {
        for (auto &col : row))
        {
            std::cin >> col;
        }
    }
    
    Tensor m(KroneckersOuterProduct(m1, m2));
    nested_print(std::span(m));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10.0);
    vector<vector<double>> Matrix(5, vector<double>(7, 0));
    std::ofstream file("matrix.txt");
    for (auto &row : Matrix) {
        for (auto &col : row) {
            col = dis(gen);
            file << std::setw(4) << col;
        }
        file << '\n';
    }
}
void case6()
{
    matrix<int, double> mtx(M, N, 0);
    matrix<int, double> mty(M, N, 0);

    cout << "Please enter element of sparse matrix A" << "\n";
    for (int i = 0; i != mtx.num_rows(); ++i) {
        for (int j = 0; j != mtx.num_cols(); ++j) {
            std::cin >> mtx(i, j) ;
        }
    }
    cout << "Please enter element of sparse matrix B" << "\n";
    for (int i = 0; i != mty.num_rows(); ++i) {
        for (int j = 0; j != mty.num_cols(); ++j) {
            std::cin >> mty(i, j) ;
        }
    }
    Timer t;
    matrix<int, double> mtz = mtx * mty;
    std::cerr << "Measure time taken for printing naive Matrix multiplication (fmt): " << "\n";
    Timer tt;
    for (int i = 0; i != mtz.num_rows(); ++i) {
        for (int j = 0; j != mtz.num_cols(); ++j) {
            std::cout << mtz(i, j) << " ";
        }
        std::cout << "\n";
    }
}



//g++-10 -std=c++2a -o sparse testlib.cpp SparseTensor/src/SparseTensor.cpp -lfmt


```


