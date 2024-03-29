
#include <gsCore/gsGeometry.h>
#include <gsCApi/gsCHelpers.h>

namespace gismo
{

void fill_matrix_colwise(gsMatrix<>& mat,
                         double* data,
                         int rows,
                         int cols)
{
    // this should be equivalent to
    // mat = gsAsMatrix<>(data,cols,rows);

    mat.resize(rows, cols);
    for (int c = 0; c != cols; c++)
    {
        for (int r = 0; r != rows; r++)
        {
            mat(r, c) = data[c * rows + r];
        }
    }
}

void fill_matrix_rowwise(gsMatrix<>& mat,
                         double* data,
                         int rows,
                         int cols)
{
    // this should be equivalent to
    // mat = gsAsMatrix<>(data,cols,rows).transpose();
    //
    // That is not true when rows != cols !

    mat.resize(rows, cols);
    for (int r = 0; r != rows; r++)
    {
        for (int c = 0; c != cols; c++)
        {
            mat(r, c) = data[r * cols + c];
        }
    }
}

void copy_matrix_c_array(const gsMatrix<>& matrix,
                 double* result,
                 int len_result)
{
    // copy matrix with check on amount of result elements provided

    for (int col = 0; col != matrix.cols(); col++)
    {
        for (int row = 0; row != matrix.rows(); row++)
        {
            int i = col * matrix.rows() + row;
            if (i < len_result)
            {
                result[i] = matrix(row, col);
            }
        }
    }
}

double* make_c_array(const gsMatrix<>& matrix)
{
    // code below is equivalent to
    // double* result = new double[matrix.size()];
    // copyRange(matrix.data(), result, matrix.size());
    //
    // I prefer to use the code below, because it is independent
    // of row or column mode of Eigen.

    double* result = new double[matrix.rows() * matrix.cols()];
    for (int col = 0; col != matrix.cols(); col++)
    {
        for (int row = 0; row != matrix.rows(); row++)
        {
            result[col * matrix.rows() + row] = matrix(row, col);
        }
    }

    return result;
}

double* make_c_array(const std::vector<double>& vector)
{
    double* data = new double[vector.size()];

    for (size_t i = 0; i != vector.size(); i++)
    {
        data[i] = vector[i];
    }

    return data;
}

int* make_c_array_int(const gsVector<int>& vector)
{
    int* data = new int[vector.rows()];

    for (size_t i = 0; i != static_cast<unsigned>(vector.rows()); i++)
    {
        data[i] = vector(i);
    }

    return data;
}

} // namespace gismo
