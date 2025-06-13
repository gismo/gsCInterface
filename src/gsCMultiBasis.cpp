#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCMultiBasis.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCMultiBasis * gsMultiBasis_create()
{
    return RICAST_CMP(new gsMultiBasis<double>());
}

GISMO_EXPORT gsCMultiBasis * gsMultiBasis_create_basis(gsCBasis * basis)
{
    auto * basis_ptr = RICAST_B(basis);
    return RICAST_CMP(new gsMultiBasis<double>(*basis_ptr));
}

GISMO_EXPORT gsCMultiBasis * gsMultiBasis_create_patches(gsCMultiPatch * mp)
{
    auto * mp_ptr = RICAST_MP(mp);
    return RICAST_CMP(new gsMultiBasis<double>(*mp_ptr));
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

GISMO_EXPORT gsCMultiBasis * gsMultiBasis_read(char* filename)
{
    gsFileData<> data(filename);
    if (data.hasAny< gsMultiBasis<> >())
    {
        gsMultiBasis<>::uPtr ptr = data.getAnyFirst< gsMultiBasis<> >();
        return RICAST_CMB(ptr.release());
    }
    else
    {
        gsWarn<<"[G+Smo] No gsMultiBasis found in file "<<filename<<"\n";
        return NULL;
    }
}

GISMO_EXPORT void gsMultiBasis_write(gsCMultiBasis * obj, char* filename)
{
    gsFileData<> data;
    data.add(*RICAST_MB(obj));
    data.save(filename);
}


#ifdef __cplusplus
}
#endif
