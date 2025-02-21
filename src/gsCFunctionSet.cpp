#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCFunctionSet.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT void gsFunctionSet_print(gsCFunctionSet * fs)
{ gsInfo<<*RICAST_F(fs)<<"\n"; }

GISMO_EXPORT void gsFunctionSet_delete(gsCFunctionSet * ptr)
{ delete RICAST_F(ptr); }

GISMO_EXPORT int gsFunctionSet_domainDim(gsCFunctionSet * fs)
{ return RICAST_F(fs)->domainDim(); }

GISMO_EXPORT int gsFunctionSet_targetDim(gsCFunctionSet * fs)
{ return RICAST_F(fs)->targetDim(); }

GISMO_EXPORT int gsFunctionSet_nPieces(gsCFunctionSet * fs)
{ return RICAST_F(fs)->nPieces(); }

GISMO_EXPORT gsCMatrix* gsFunctionSet_support(gsCFunctionSet * fs)
{ return RICAST_CM( new gismo::gsMatrix<double>(RICAST_F(fs)->support()) ); }

GISMO_EXPORT void gsFunctionSet_eval_into(gsCFunctionSet * fs,
                            gsCMatrix * u,
                            gsCMatrix * result)
{ RICAST_F(fs)->eval_into(*RICAST_M(u), *RICAST_M(result) ); }

GISMO_EXPORT void gsFunctionSet_deriv_into(gsCFunctionSet * fs,
                             gsCMatrix * u,
                             gsCMatrix * result)
{ RICAST_F(fs)->deriv_into(*RICAST_M(u), *RICAST_M(result) ); }

GISMO_EXPORT void gsFunctionSet_deriv2_into(gsCFunctionSet * fs,
                             gsCMatrix * u,
                             gsCMatrix * result)
{ RICAST_F(fs)->deriv2_into(*RICAST_M(u), *RICAST_M(result) ); }
#ifdef __cplusplus
}
#endif
