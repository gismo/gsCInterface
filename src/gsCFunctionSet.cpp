#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCFunctionSet.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

using namespace gismo;

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
{ return RICAST_CM( new gsMatrix<double>(RICAST_F(fs)->support()) ); }

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

GISMO_EXPORT void gsFunctionSet_evalAllDers1_into(gsCFunctionSet * fs,
                                                  gsCMatrix * u,
                                                  gsCMatrix * values,
                                                  gsCMatrix * deriv)
{
    std::vector<gsMatrix<> > result(2);
    RICAST_F(fs)->evalAllDers_into(*RICAST_M(u), 1, result, false);
    *RICAST_M(values) = give(result[0]);
    *RICAST_M(deriv) = give(result[1]);
}

GISMO_EXPORT void gsFunctionSet_evalAllDers2_into(gsCFunctionSet * fs,
                                                  gsCMatrix * u,
                                                  gsCMatrix * values,
                                                  gsCMatrix * deriv,
                                                  gsCMatrix * deriv2)
{
    std::vector<gsMatrix<> > result(3);
    RICAST_F(fs)->evalAllDers_into(*RICAST_M(u), 2, result, false);
    *RICAST_M(values) = give(result[0]);
    *RICAST_M(deriv) = give(result[1]);
    *RICAST_M(deriv2) = give(result[2]);
}

#ifdef __cplusplus
}
#endif
