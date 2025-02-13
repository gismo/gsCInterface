#include <gsCore/gsLinearAlgebra.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCSparseMatrix.h>

GISMO_EXPORT gsCSparseMatrix * gsSparseMatrix_create(void)
{ return RICAST_CSM(new gismo::gsMatrix<double>()); }

GISMO_EXPORT void gsSparseMatrix_delete(gsCSparseMatrix * m)
{ delete RICAST_SM(m); }

GISMO_EXPORT void gsSparseMatrix_print(gsCSparseMatrix * m)
{ gsInfo<<*RICAST_SM(m); }

// GISMO_EXPORT double * gsSparseMatrix_data(gsCSparseMatrix * m)
// { return RICAST_SM(m)->data(); }

GISMO_EXPORT void gsSparseMatrix_setFromTriplets(gsCSparseMatrix * m, int nrows, int ncols, int * rows, int * cols, double * values, int nnz)
{
    std::vector<int> rows_vec(rows, rows + nnz);
    std::vector<int> cols_vec(cols, cols + nnz);
    std::vector<double> values_vec(values, values + nnz);

    gismo::gsSparseEntries<double> entries;
    entries.reserve(nnz);
    for (int i = 0; i < nnz; i++)
        entries.add(rows_vec[i], cols_vec[i], values_vec[i]);

    RICAST_SM(m)->resize(nrows, ncols);
    RICAST_SM(m)->setFrom(entries);
}

GISMO_EXPORT void gsSparseMatrix_intoTriplets(gsCSparseMatrix * m, int * rows, int * cols, double * values)
{
    auto * sm = RICAST_SM(m);
    for (int i = 0; i!=sm->outerSize(); i++)
    {
        for (typename gismo::gsSparseMatrix<double>::InnerIterator it(*sm,i); it; ++it)
        {
            *rows = it.row();
            *cols = it.col();
            *values = it.value();
            ++rows; ++cols; ++values;
        }
    }
}

GISMO_EXPORT int gsSparseMatrix_rows(gsCSparseMatrix * m)
{ return RICAST_SM(m)->rows(); }

GISMO_EXPORT int gsSparseMatrix_cols(gsCSparseMatrix * m)
{ return RICAST_SM(m)->cols(); }
