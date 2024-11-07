#include <gsCore/gsLinearAlgebra.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCMatrix.h>

GISMO_EXPORT gsCMatrix * gsMatrix_create(void)
{ return RICAST_CM(new gismo::gsMatrix<double>()); }

GISMO_EXPORT gsCMatrix * gsMatrix_create_rc(int rows, int cols)
{ return RICAST_CM(new gismo::gsMatrix<double>(rows,cols)); }

GISMO_EXPORT gsCMatrix * gsMatrix_create_rcd(int rows, int cols, double * data)
{ return RICAST_CM(new gismo::gsMatrix<double>(gismo::gsAsMatrix<double>(data,rows,cols))); }

GISMO_EXPORT void gsMatrix_delete(gsCMatrix * m)
{ delete RICAST_M(m); }

GISMO_EXPORT void gsMatrix_print(gsCMatrix * m)
{ gsInfo<<*RICAST_M(m); }

GISMO_EXPORT double * gsMatrix_data(gsCMatrix * m)
{ return RICAST_M(m)->data(); }

GISMO_EXPORT void gsMatrix_transposeInPlace(gsCMatrix * m)
{ return RICAST_M(m)->transposeInPlace(); }

GISMO_EXPORT int gsMatrix_rows(gsCMatrix * m)
{ return RICAST_M(m)->rows(); }

GISMO_EXPORT int gsMatrix_cols(gsCMatrix * m)
{ return RICAST_M(m)->cols(); }

GISMO_EXPORT void gsMatrix_setZero(gsCMatrix * m)
{ RICAST_M(m)->setZero(); }
