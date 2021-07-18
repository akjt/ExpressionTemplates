# ExpressionTemplates

A C++ skeleton for arithmetic operations using expression templates. Only the add operator is for now supported using the dynamic 2D container - with no simd vectorisation. 

Idea is to have a generic high performance math library which can support multiple platforms, parallel strategies such as using accelerators. Currently, the main C++ design patterns have been implemented for dense matrices and currently having the add expression only.


tested with gcc/clang++ using std=c++17
