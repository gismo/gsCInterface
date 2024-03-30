#include <gsCore/gsLinearAlgebra.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCVectorInt.h>
#include <gsCInterface/gsMacros.h>

GISMO_EXPORT gsCVectorInt * gsVectorInt_create(void)
{ return reinterpret_cast<gsCVectorInt*>(new gismo::gsVector<int>()); }

GISMO_EXPORT gsCVectorInt * gsVectorInt_create_r(int rows)
{ return reinterpret_cast<gsCVectorInt*>(new gismo::gsVector<int>(rows)); }

GISMO_EXPORT gsCVectorInt * gsVectorInt_create_rd(int rows, int * data)
{ return reinterpret_cast<gsCVectorInt*>(new gismo::gsVector<int>(gismo::gsAsVector<int>(data,rows))); }

GISMO_EXPORT void gsVectorInt_delete(gsCVectorInt * m)
{ delete RICAST_Vi(m); }

GISMO_EXPORT void gsVectorInt_print(gsCVectorInt * m)
{ gsInfo<<*RICAST_Vi(m); }

GISMO_EXPORT int * gsVectorInt_data(gsCVectorInt * m)
{ return RICAST_Vi(m)->data(); }

GISMO_EXPORT void gsCVectorInt_transposeInPlace(gsCVectorInt * m)
{ return RICAST_Vi(m)->transposeInPlace(); }

GISMO_EXPORT int gsCVectorInt_rows(gsCVectorInt * m)
{ return RICAST_Vi(m)->rows(); }

GISMO_EXPORT int gsCVectorInt_cols(gsCVectorInt * m)
{ return RICAST_Vi(m)->cols(); }

GISMO_EXPORT void gsCVectorInt_setZero(gsCVectorInt * m)
{ RICAST_Vi(m)->setZero(); }
