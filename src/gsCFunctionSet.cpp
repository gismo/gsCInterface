#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCFunctionSet.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

GISMO_EXPORT void gsFunctionSet_print(gsCFunctionSet * fs)
{ RICAST_G(fs)->print(gsInfo); }

GISMO_EXPORT void gsFunctionSet_delete(gsCFunctionSet * ptr)
{ delete RICAST_F(ptr); }

GISMO_EXPORT int domainDim(gsCFunctionSet * fs)
{ return RICAST_G(fs)->domainDim(); }

GISMO_EXPORT int targetDim(gsCFunctionSet * fs)
{ return RICAST_G(fs)->targetDim(); }

GISMO_EXPORT void eval_into(gsCFunctionSet * fs,
                            gsCMatrix * u,
                            gsCMatrix * result)
{ RICAST_F(fs)->eval_into(*RICAST_M(u), *RICAST_M(result) ); }

GISMO_EXPORT void deriv_into(gsCFunctionSet * fs,
                             gsCMatrix * u,
                             gsCMatrix * result)
{ RICAST_F(fs)->deriv_into(*RICAST_M(u), *RICAST_M(result) ); }
