#include <gsCore/gsLinearAlgebra.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCMatrixInt.h>

GISMO_EXPORT gsCMatrixInt * gsMatrixInt_create(void)
{ return reinterpret_cast<gsCMatrixInt*>(new gismo::gsMatrix<int>()); }

GISMO_EXPORT gsCMatrixInt * gsMatrixInt_create_rc(int rows, int cols)
{ return reinterpret_cast<gsCMatrixInt*>(new gismo::gsMatrix<int>(rows,cols)); }

GISMO_EXPORT gsCMatrixInt * gsMatrixInt_create_rcd(int rows, int cols, int * data)
{ return reinterpret_cast<gsCMatrixInt*>(new gismo::gsMatrix<int>(gismo::gsAsMatrix<int>(data,rows,cols))); }

GISMO_EXPORT void gsMatrixInt_delete(gsCMatrixInt * m)
{ delete RICAST_Mi(m); }

GISMO_EXPORT void gsMatrixInt_print(gsCMatrixInt * m)
{ gsInfo<<*RICAST_Mi(m); }

GISMO_EXPORT int * gsMatrixInt_data(gsCMatrixInt * m)
{ return RICAST_Mi(m)->data(); }

GISMO_EXPORT void transposeInPlace(gsCMatrixInt * m)
{ return RICAST_Mi(m)->transposeInPlace(); }

GISMO_EXPORT int gsMatrixInt_rows(gsCMatrixInt * m)
{ return RICAST_Mi(m)->rows(); }

GISMO_EXPORT int gsMatrixInt_cols(gsCMatrixInt * m)
{ return RICAST_Mi(m)->cols(); }

GISMO_EXPORT void gsMatrixInt_setZero(gsCMatrixInt * m)
{ RICAST_Mi(m)->setZero(); }
