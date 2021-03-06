/**
 * @file    jacobi.cpp
 * @author  Patrick Flick <patrick.flick@gmail.com>
 * @brief   Implements matrix vector multiplication and Jacobi's method.
 *
 * Copyright (c) 2014 Georgia Institute of Technology. All Rights Reserved.
 */
#include "jacobi.h"

/*
 * TODO: Implement your solutions here
 */

// Calculates ||Ax-b|| 
double l2norm(const int n, const double* A,  const double* b, const double* x, double* y);

//update x, x = (b-Rx)/d
void update_x(const int n, const double* b, double* x, const double* d, const double* R, double* y);

// my implementation:
#include <iostream>
#include <math.h>
#include <vector>
#include <iostream>

// Calculates y = A*x for a square n-by-n matrix A, and n-dimensional vectors x
// and y
void matrix_vector_mult(const int n, const double* A, const double* x, double* y) {
    // TODO
    for (int i = 0; i < n; i++)
    {
        y[i] = 0.0;
        for(int j = 0; j< n; j++)
            y[i] = y[i] + A[i*n+j] * x[j];
    }
}

// Calculates y = A*x for a n-by-m matrix A, a m-dimensional vector x
// and a n-dimensional vector y
void matrix_vector_mult(const int n, const int m, const double* A, const double* x, double* y) {
    // TODO
    for (int i = 0; i < n; i++)
    {
        y[i] = 0.0;
        for (int j = 0; j < m; j++){
            y[i] = y[i] + A[i*m +j] * x[j];
        }
    }
}

// implements the sequential jacobi method
void jacobi(const int n, double* A, double* b, double* x, int max_iter, double l2_termination) {
    // TODO
    std::vector<double> D(n);
    std::vector<double> R(A, A + n*n);
    // fill D and remove corresponding elements from R
    for (int i = 0; i < n; i++) {
        D[i] = A[n*i + i];
        R[n*i + i] = 0.0;
    }
    // temporary buffer used by functions for storing intermediate values
    std::vector<double> y(n);
    // iterate until a maximum number of iterations has been reached
    for (int iter = 0; iter < max_iter; iter++) {
        // calculate l2 norm
        double l2_norm = l2norm(n, A, b, x, &y[0]);
        // check the distance
        if (l2_norm < l2_termination)
            break;
        update_x(n, b, x, &D[0], &R[0], &y[0]);
    }
}

// Calculates ||Ax-b|| 
double l2norm(const int n, const double* A,  const double* b, const double* x, double* y) {
    double ans = 0.0;
    matrix_vector_mult(n,A,x,y);
    for(int i = 0; i<n; i++)
        ans += pow(y[i] - b[i], 2.0);
    return sqrt(ans); 
}

//update x, x = (b-Rx)/d
void update_x(const int n, const double* b, double* x, const double* d, const double* R, double* y) {
    matrix_vector_mult(n, R, x, y);
    for (int i = 0; i < n; i++)
        x[i] = (b[i] - y[i]) / d[i];
  
}
