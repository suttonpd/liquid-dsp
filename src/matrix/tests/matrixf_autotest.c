/*
 * Copyright (c) 2007, 2008, 2009, 2010, 2013 Joseph Gaeddert
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "autotest/autotest.h"
#include "liquid.h"

// autotest data definitions
#include "src/matrix/tests/matrix_data.h"

// test matrix addition
void autotest_matrixf_add()
{
    float tol = 1e-6f;

    // x [size: 5 x 4]
    // y [size: 5 x 4]
    // z [size: 5 x 4]
    float z[20];
    matrixf_add(matrixf_data_add_x,
                matrixf_data_add_y,
                z,
                5, 4);

    unsigned int i;
    for (i=0; i<20; i++)
        CONTEND_DELTA( matrixf_data_add_z[i], z[i], tol );
}

// test matrix augmentation
void autotest_matrixf_aug()
{
    float tol = 1e-6f;

    // x [size: 5 x 4]
    // y [size: 5 x 3]
    // z [size: 5 x 7]
    float z[35];
    matrixf_aug(matrixf_data_aug_x, 5, 4,
                matrixf_data_aug_y, 5, 3,
                z,                  5, 7);
    
    // print result
    if (liquid_autotest_verbose) {
        printf("augment:\n");
        printf("  x: ");        matrixf_print(matrixf_data_aug_x,5,4);
        printf("  y: ");        matrixf_print(matrixf_data_aug_y,5,3);
        printf("  expected: "); matrixf_print(matrixf_data_aug_z,5,7);
        printf("  z: ");        matrixf_print(z,5,3);
    }

    unsigned int i;
    for (i=0; i<35; i++)
        CONTEND_DELTA( matrixf_data_aug_z[i], z[i], tol );
}

// conjugate gradient solver
void autotest_matrixf_cgsolve()
{
    float tol = 0.01;  // error tolerance

    // A [size: 8 x 8], symmetric positive definite matrx
    // x [size: 8 x 1]
    // b [size: 8 x 1]
    float x[8];
    matrixf_cgsolve(matrixf_data_cgsolve_A, 8,
                    matrixf_data_cgsolve_b,
                    x, NULL);

    if (liquid_autotest_verbose) {
        printf("cgsolve:\n");
        printf("  A: ");        matrixf_print(matrixf_data_cgsolve_A, 8, 8);
        printf("  b: ");        matrixf_print(matrixf_data_cgsolve_b, 8, 1);
        printf("  expected: "); matrixf_print(matrixf_data_cgsolve_x, 8, 1);
        printf("  x: ");        matrixf_print(x,                      8, 1);
    }

    unsigned int i;
    for (i=0; i<8; i++)
        CONTEND_DELTA( matrixf_data_cgsolve_x[i], x[i], tol );
}

// Cholesky decomposition
void autotest_matrixf_chol()
{
    float tol = 1e-4f;  // error tolerance

    // A [size: 4 x 4]
    // L [size: 4 x 4]
    float L[16];

    // run decomposition
    matrixf_chol(matrixf_data_chol_A, 4, L);

    if (liquid_autotest_verbose) {
        printf("chol:\n");
        printf("  A: ");        matrixf_print(matrixf_data_chol_A, 4, 4);
        printf("  expected: "); matrixf_print(matrixf_data_chol_L, 4, 4);
        printf("  L: ");        matrixf_print(L,                   4, 4);
    }

    unsigned int i;
    for (i=0; i<16; i++)
        CONTEND_DELTA( matrixf_data_chol_L[i], L[i], tol );
}

// Gram-Schmidt Orthonormalization
void autotest_matrixf_gramschmidt()
{
    float tol = 1e-6f;  // error tolerance

    // A [size: 4 x 3]
    // V [size: 4 x 3]
    float V[12];
    matrixf_gramschmidt(matrixf_data_gramschmidt_A, 4, 3, V);

    if (liquid_autotest_verbose) {
        printf("gramschmidt:\n");
        printf("  A: ");        matrixf_print(matrixf_data_gramschmidt_A, 4, 3);
        printf("  expected: "); matrixf_print(matrixf_data_gramschmidt_V, 4, 3);
        printf("  V: ");        matrixf_print(V,                          4, 3);
    }

    unsigned int i;
    for (i=0; i<12; i++)
        CONTEND_DELTA( matrixf_data_gramschmidt_V[i], V[i], tol );
}


// matrix inversion
void autotest_matrixf_inv()
{
    float tol = 1e-6f;  // error tolerance

    // x [size: 5 x 5]
    // y [size: 5 x 5]
    float y[25];
    memmove(y, matrixf_data_inv_x, 5*5*sizeof(float));
    matrixf_inv(y, 5, 5);

    if (liquid_autotest_verbose) {
        printf("inv:\n");
        printf("  x: ");        matrixf_print(matrixf_data_inv_x, 5, 5);
        printf("  expected: "); matrixf_print(matrixf_data_inv_y, 5, 5);
        printf("  y: ");        matrixf_print(y,                  5, 5);
    }

    unsigned int i;
    for (i=0; i<25; i++)
        CONTEND_DELTA( matrixf_data_inv_y[i], y[i], tol );
}

// linsolve (solve linear system of equations)
void autotest_matrixf_linsolve()
{
    float tol = 1e-6f;  // error tolerance

    // A [size: 5 x 5]
    // x [size: 5 x 1]
    // b [size: 5 x 1]
    float x[5];
    
    // run solver
    matrixf_linsolve(matrixf_data_linsolve_A, 5,
                     matrixf_data_linsolve_b,
                     x, NULL);

    if (liquid_autotest_verbose) {
        printf("linsolve:\n");
        printf("  A: ");        matrixf_print(matrixf_data_linsolve_A, 5, 5);
        printf("  b: ");        matrixf_print(matrixf_data_linsolve_b, 5, 1);
        printf("  expected: "); matrixf_print(matrixf_data_linsolve_x, 5, 1);
        printf("  x: ");        matrixf_print(x,                       5, 1);
    }

    unsigned int i;
    for (i=0; i<5; i++)
        CONTEND_DELTA( matrixf_data_linsolve_x[i], x[i], tol );
}


// L/U decomp (Crout)
void autotest_matrixf_ludecomp_crout()
{
    float tol = 1e-6f;  // error tolerance

    float L[64];
    float U[64];
    float P[64];

    float LU_test[64];

    // run decomposition
    matrixf_ludecomp_crout(matrixf_data_ludecomp_A, 8, 8, L, U, P);

    // multiply LU
    matrixf_mul(L,       8, 8,
                U,       8, 8,
                LU_test, 8, 8);

    if (liquid_autotest_verbose) {
        printf("ludecomp_crout:\n");
        printf("  A: ");        matrixf_print(matrixf_data_ludecomp_A,8,8);
        printf("  L: ");        matrixf_print(L,                      8,8);
        printf("  U: ");        matrixf_print(U,                      8,8);
        printf("  LU: ");       matrixf_print(LU_test,                8,8);
    }

    unsigned int r,c;
    for (r=0; r<8; r++) {
        for (c=0; c<8; c++) {
            if (r < c) {
                CONTEND_DELTA( matrix_access(L,8,8,r,c), 0.0f, tol );
            } else if (r==c) {
                CONTEND_DELTA( matrix_access(U,8,8,r,c), 1.0f, tol );
            } else {
                CONTEND_DELTA( matrix_access(U,8,8,r,c), 0.0f, tol );
            }
        }
    }

    unsigned int i;
    for (i=0; i<64; i++)
        CONTEND_DELTA( matrixf_data_ludecomp_A[i], LU_test[i], tol );
}

// L/U decomp (Doolittle)
void autotest_matrixf_ludecomp_doolittle()
{
    float tol = 1e-6f;  // error tolerance

    float L[64];
    float U[64];
    float P[64];

    float LU_test[64];

    // run decomposition
    matrixf_ludecomp_doolittle(matrixf_data_ludecomp_A, 8, 8, L, U, P);

    // multiply LU
    matrixf_mul(L,       8, 8,
                U,       8, 8,
                LU_test, 8, 8);

    if (liquid_autotest_verbose) {
        printf("ludecomp_doolittle:\n");
        printf("  A: ");        matrixf_print(matrixf_data_ludecomp_A,8,8);
        printf("  L: ");        matrixf_print(L,                      8,8);
        printf("  U: ");        matrixf_print(U,                      8,8);
        printf("  LU: ");       matrixf_print(LU_test,                8,8);
    }

    unsigned int r,c;
    for (r=0; r<8; r++) {
        for (c=0; c<8; c++) {
            if (r < c) {
                CONTEND_DELTA( matrix_access(L,8,8,r,c), 0.0f, tol );
            } else if (r==c) {
                CONTEND_DELTA( matrix_access(L,8,8,r,c), 1.0f, tol );
            } else {
                CONTEND_DELTA( matrix_access(U,8,8,r,c), 0.0f, tol );
            }
        }
    }

    unsigned int i;
    for (i=0; i<64; i++)
        CONTEND_DELTA( matrixf_data_ludecomp_A[i], LU_test[i], tol );
}

// test matrix multiplication
void autotest_matrixf_mul()
{
    float tol = 1e-6f;

    // x [size: 5 x 4]
    // y [size: 4 x 3]
    // z [size: 5 x 3]
    float z[35];
    matrixf_mul(matrixf_data_mul_x, 5, 4,
                matrixf_data_mul_y, 4, 3,
                z,                  5, 3);

    // print result
    if (liquid_autotest_verbose) {
        printf("multiplication:\n");
        printf("  x: ");        matrixf_print(matrixf_data_mul_x,5,4);
        printf("  y: ");        matrixf_print(matrixf_data_mul_y,4,3);
        printf("  expected: "); matrixf_print(matrixf_data_mul_z,5,3);
        printf("  z: ");        matrixf_print(z,5,3);
    }

    unsigned int i;
    for (i=0; i<15; i++)
        CONTEND_DELTA( matrixf_data_mul_z[i], z[i], tol );
}

// Q/R decomp (Gram-Schmidt)
void autotest_matrixf_qrdecomp()
{
    float tol = 1e-4f;  // error tolerance

    float Q[16];
    float R[16];

    float QR_test[16];  // Q*R
    float QQT_test[16]; // Q*Q^T

    // run decomposition
    matrixf_qrdecomp_gramschmidt(matrixf_data_qrdecomp_A, 4, 4, Q, R);

    // compute Q*R
    matrixf_mul(Q,       4, 4,
                R,       4, 4,
                QR_test, 4, 4);

    // compute Q*Q^T
    matrixf_mul_transpose(Q, 4, 4, QQT_test);

    if (liquid_autotest_verbose) {
        printf("qrdecomp_gramschmidt:\n");
        printf("  A: ");          matrixf_print(matrixf_data_qrdecomp_A,4,4);
        printf("  Q: ");          matrixf_print(Q,                      4,4);
        printf("  R: ");          matrixf_print(R,                      4,4);
        printf("  Q expected: "); matrixf_print(matrixf_data_qrdecomp_Q,4,4);
        printf("  R expected: "); matrixf_print(matrixf_data_qrdecomp_R,4,4);
        printf("  QR: ");         matrixf_print(QR_test,                4,4);
        printf("  QQ: ");         matrixf_print(QQT_test,               4,4);
    }

    unsigned int i;

    // ensure Q*R = A
    for (i=0; i<16; i++)
        CONTEND_DELTA( matrixf_data_qrdecomp_A[i], QR_test[i], tol );

    // ensure Q*Q = I(4)
    float I4[16];
    matrixf_eye(I4,4);
    for (i=0; i<16; i++)
        CONTEND_DELTA( QQT_test[i], I4[i], tol );

    // ensure Q and R are correct
    for (i=0; i<16; i++) {
        CONTEND_DELTA( matrixf_data_qrdecomp_Q[i], Q[i], tol );
        CONTEND_DELTA( matrixf_data_qrdecomp_R[i], R[i], tol );
    }
}



