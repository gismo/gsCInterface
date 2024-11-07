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

GISMO_EXPORT int gsSparseMatrix_rows(gsCSparseMatrix * m)
{ return RICAST_SM(m)->rows(); }

GISMO_EXPORT int gsSparseMatrix_cols(gsCSparseMatrix * m)
{ return RICAST_SM(m)->cols(); }
