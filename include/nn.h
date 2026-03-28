#ifndef NN_H
#define NN_H
#include "matrix.h"

Matrix *set_param(size_t rows, size_t cols);
Matrix *forward_pass(Matrix *x_data, Matrix *w1, Matrix *b1, Matrix *w2,
                     double b2);
Matrix *dl_dw2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
               Matrix *y);
double dl_db2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
              Matrix *y);
Matrix *dl_dw1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
               Matrix *y);
Matrix *dl_db1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
               Matrix *y);
Matrix *update_w1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                  Matrix *y, double lr);
Matrix *update_b1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                  Matrix *y, double lr);
Matrix *update_w2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                  Matrix *y, double lr);
double update_b2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                 Matrix *y, double lr);

#endif // !NN_H
