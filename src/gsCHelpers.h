
#ifndef GSCHELPERS_H
#define GSCHELPERS_H

#include <gsCore/gsGeometry.h>

namespace gismo
{

/// Resizes \a mat to \a rows x \a cols and fills it with \a data col-wise.
void fill_matrix_colwise(gsMatrix<>& mat,
                         double* data,
                         int rows,
                         int cols);

/// Resizes \a mat to \a rows x \a cols and fills it with \a data col-wise.
void fill_matrix_rowwise(gsMatrix<>& mat,
                         double* data,
                         int rows,
                         int cols);

void copy_matrix_c_array(const gsMatrix<>& matrix,
                 double* result,
                 int len_result);

double* make_c_array(const gsMatrix<>& matrix);

double* make_c_array(const std::vector<double>& vector);

int* make_c_array_int(const gsVector<int>& vector);

} // namespace gismo

#endif // GSCHELPERS_H
