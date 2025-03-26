#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCMultiPatch.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCMultiPatch* gsMultiPatch_create()
{
    return RICAST_CMP(new gsMultiPatch<double>());
}

GISMO_EXPORT void gsMultiPatch_addPatch(gsCMultiPatch* mp, gsCGeometry* geo)
{
    auto * mp_ptr = RICAST_MP(mp);
    auto * geo_ptr = RICAST_G(geo);
    mp_ptr->addPatch(*geo_ptr);
}

GISMO_EXPORT gsCBasis * gsMultiPatch_basis(gsCMultiPatch * mp, int i)
{
    auto * mp_ptr = RICAST_MP(mp);
    return RICAST_CB(&mp_ptr->basis(i));
}

GISMO_EXPORT gsCGeometry * gsMultiPatch_patch(gsCMultiPatch * mp, int i)
{
    auto * mp_ptr = RICAST_MP(mp);
    return RICAST_CG(&mp_ptr->patch(i));
}

GISMO_EXPORT void gsMultiPatch_computeTopology(gsCMultiPatch * mp)
{
    auto * mp_ptr = RICAST_MP(mp);
    mp_ptr->computeTopology();
}

#ifdef __cplusplus
}
#endif
