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

GISMO_EXPORT gsCMultiPatch* gsMultiPatch_create_geometry(gsCGeometry * geo)
{
    auto * geo_ptr = RICAST_G(geo);
    return RICAST_CMP(new gsMultiPatch<double>(*geo_ptr));
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

GISMO_EXPORT void gsMultiPatch_embed(gsCMultiPatch * mp, int dim)
{
    auto * mp_ptr = RICAST_MP(mp);
    mp_ptr->embed(dim);
}

GISMO_EXPORT void gsMultiPatch_uniformRefine(gsCMultiPatch * mp, int numKnots, int mul, int dir)
{
    auto * mp_ptr = RICAST_MP(mp);
    mp_ptr->uniformRefine(numKnots, mul, dir);
}

GISMO_EXPORT void gsMultiPatch_degreeElevate(gsCMultiPatch * mp, int i, int dir)
{
    auto * mp_ptr = RICAST_MP(mp);
    mp_ptr->degreeElevate(i, dir);
}

GISMO_EXPORT gsCMultiPatch * gsMultiPatch_read(char* filename)
{
    gsFileData<> data(filename);
    if (data.hasAny< gsMultiPatch<> >())
    {
        gsMultiPatch<>::uPtr ptr = data.getAnyFirst< gsMultiPatch<> >();
        return RICAST_CMP(ptr.release());
    }
    else
    {
        gsWarn<<"[G+Smo] No gsMultiPatch found in file "<<filename<<"\n";
        return NULL;
    }
}

GISMO_EXPORT void gsMultiPatch_write(gsCMultiPatch * obj, char* filename)
{
    gsFileData<> data;
    data.add(*RICAST_MP(obj));
    data.save(filename);
}

#ifdef __cplusplus
}
#endif
