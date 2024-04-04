
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCBasis.h>

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCBasis * gsBSplineBasis_create(gsCKnotVector * KV)
{
    auto * KV_ptr = RICAST_KV (KV);
    return RICAST_CB (new gismo::gsBSplineBasis<double>(*KV_ptr) );
}

GISMO_EXPORT gsCBasis* gsTensorBSplineBasis2_create(gsCKnotVector* KV1, gsCKnotVector* KV2)
{
    auto * KV1_ptr = RICAST_KV (KV1);
    auto * KV2_ptr = RICAST_KV (KV2);
    return RICAST_CB(new gismo::gsTensorBSplineBasis<2,double>(*KV1_ptr,*KV2_ptr) );
}

GISMO_EXPORT gsCBasis* gsTensorBSplineBasis3_create(gsCKnotVector* KV1, gsCKnotVector* KV2,
                                                    gsCKnotVector* KV3)
{
    auto * KV1_ptr = RICAST_KV (KV1);
    auto * KV2_ptr = RICAST_KV (KV2);
    auto * KV3_ptr = RICAST_KV (KV3);
    return RICAST_CB(new gismo::gsTensorBSplineBasis<3,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr));
}

GISMO_EXPORT gsCBasis* gsTensorBSplineBasis4_create(gsCKnotVector* KV1, gsCKnotVector* KV2,
                                                    gsCKnotVector* KV3, gsCKnotVector* KV4)
{
    auto * KV1_ptr = RICAST_KV (KV1);
    auto * KV2_ptr = RICAST_KV (KV2);
    auto * KV3_ptr = RICAST_KV (KV3);
    auto * KV4_ptr = RICAST_KV (KV4);
    return RICAST_CB(new gismo::gsTensorBSplineBasis<4,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr,*KV4_ptr));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis1_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<1,double>* >(b);
    return RICAST_CB(new gismo::gsTHBSplineBasis<1,double>(*basis_ptr,false));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis2_create(gsCBasis* b)
{ 
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<2,double>* >(b);
    return RICAST_CB(new  gismo::gsTHBSplineBasis<2,double>(*basis_ptr,false));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis3_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<3,double>* >(b);
    return RICAST_CB(new  gismo::gsTHBSplineBasis<3,double>(*basis_ptr,false));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis4_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<4,double>* >(b);
    return RICAST_CB(new  gismo::gsTHBSplineBasis<4,double>(*basis_ptr,false));
}

//
// Methods
//

GISMO_EXPORT void gsBasis_active_into(gsCBasis * b,
                              gsCMatrix * u,
                              gsCMatrixInt * result)
{ RICAST_B(b)->active_into(*RICAST_M(u), *RICAST_Mi(result) ); }

GISMO_EXPORT gsCBasis * gsBasis_component(gsCBasis * b, int dir)
{
    gismo::gsBasis<double> * c = & RICAST_B(b)->component(dir);
    return reinterpret_cast<gsCBasis*>(c);
}

GISMO_EXPORT int gsBasis_degree(gsCBasis * b, int dir)
{ return RICAST_B(b)->component(dir).degree(dir); }

GISMO_EXPORT int gsBasis_numElements(gsCBasis * b)
{ return RICAST_B(b)->numElements(); }

GISMO_EXPORT int gsBasis_size(gsCBasis * b)
{ return RICAST_B(b)->size(); }

GISMO_EXPORT void gsBasis_uniformRefine(gsCBasis * b, int numKnots, int mul, int dir)
{ RICAST_B(b)->uniformRefine(numKnots, mul, dir); }

GISMO_EXPORT void gsBasis_refineElements(gsCBasis * b, int * boxData, int boxSize)
{
    std::vector<int> boxes(boxData,boxData+boxSize);
    RICAST_B(b)->refineElements(boxes);
}

#ifdef __cplusplus
}
#endif