LUD (LU Decomposition)
========================

In numerical analysis, LU decomposition (where 'LU' stands for 'Lower Upper', and also called LU factorization) factors a matrix as the product of a lower triangular matrix and an upper triangular matrix. The product sometimes includes a permutation matrix as well. The LU decomposition can be viewed as the matrix form of Gaussian elimination. Computers usually solve square systems of linear equations using the LU decomposition, and it is also a key step when inverting a matrix, or computing the determinant of a matrix.

Note: Original benchmark taken from the [Rodinia Benchmark Suite]  (https://www.cs.virginia.edu/~skadron/wiki/rodinia/index.php/Rodinia:Accelerating_Compute-Intensive_Applications_with_Accelerators)

Implementations:
  * c: C implementation
  * js: JavaScript implementation
  * matlab: Matlab implementation using the same algorithm as C and JS
  * matlab-native: Matlab implementation using the builtin 'lud' library call. Note that the result produced by the library is correct but different, it therefore not checked for consistency with the other 3 implementations.


