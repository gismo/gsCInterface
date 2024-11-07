#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCMultiBasis.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCMultiBasis * gsMultiBasis_create(gsCMultiPatch * mp)
{
    auto * mp_ptr = RICAST_MP(mp);
    return RICAST_CMP(new gismo::gsMultiBasis<double>(*mp_ptr));
}

GISMO_EXPORT void gsMultiBasis_addBasis(gsCMultiBasis* mb, gsCBasis* basis)
{
    auto * mb_ptr = RICAST_MB(mb);
    auto * basis_ptr = RICAST_B(basis);
    mb_ptr->addBasis(basis_ptr);
}

GISMO_EXPORT gsCBasis * gsMultiBasis_basis(gsCMultiBasis * mb, int i)
{
    auto * mb_ptr = RICAST_MB(mb);
    return RICAST_CB(&mb_ptr->basis(i));
}

GISMO_EXPORT void gsMultiBasis_delete(gsCMultiBasis * mb)
{
    auto * mb_ptr = RICAST_MB(mb);
    mb_ptr->clear();
}

#ifdef __cplusplus
}
#endif
