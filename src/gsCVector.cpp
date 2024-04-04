#include <gsCore/gsLinearAlgebra.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCVector.h>

GISMO_EXPORT gsCVector * gsVector_create(void)
{ return reinterpret_cast<gsCVector*>(new gismo::gsVector<double>()); }

GISMO_EXPORT gsCVector * gsVector_create_r(int rows)
{ return reinterpret_cast<gsCVector*>(new gismo::gsVector<double>(rows)); }

GISMO_EXPORT gsCVector * gsVector_create_rd(int rows, double * data)
{ return reinterpret_cast<gsCVector*>(new gismo::gsVector<double>(gismo::gsAsVector<double>(data,rows))); }

GISMO_EXPORT void gsVector_delete(gsCVector * m)
{ delete RICAST_V(m); }

GISMO_EXPORT void gsVector_print(gsCVector * m)
{ gsInfo<<*RICAST_V(m); }

GISMO_EXPORT double * gsVector_data(gsCVector * m)
{ return RICAST_V(m)->data(); }

GISMO_EXPORT void gsVector_transposeInPlace(gsCVector * m)
{ return RICAST_V(m)->transposeInPlace(); }

GISMO_EXPORT int gsVector_rows(gsCVector * m)
{ return RICAST_V(m)->rows(); }

GISMO_EXPORT int gsVector_cols(gsCVector * m)
{ return RICAST_V(m)->cols(); }

GISMO_EXPORT void gsVector_setZero(gsCVector * m)
{ RICAST_V(m)->setZero(); }
