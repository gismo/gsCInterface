
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCQuadRule.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT double gsL2Projection_into( gsCFunctionSet * projectionBasis,
                                         gsCMultiBasis * integrationBasis,
                                         gsCMultiPatch * geometryMap,
                                         gsCFunctionSet * sourceFunction,
                                         gsCMatrix * coefs,
                                         gsCOptionList * options)
{
    auto * projBasis_ptr = RICAST_F(projectionBasis);
    auto * intBasis_ptr = RICAST_MB(integrationBasis);
    auto * geomMap_ptr = RICAST_MP(geometryMap);
    auto * sourceFunc_ptr = RICAST_F(sourceFunction);
    auto * coefs_ptr = RICAST_M(coefs);
    auto * options_ptr = reinterpret_cast<gsOptionList*>(options);
    double error= gsL2Projection<double>::project(*projBasis_ptr, *intBasis_ptr, *geomMap_ptr, *sourceFunc_ptr, *coefs_ptr, *options_ptr);
    return error;
}

#ifdef __cplusplus
}
#endif