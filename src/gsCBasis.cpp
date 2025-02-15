
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

GISMO_EXPORT gsCBasis * gsNurbsBasis_create(gsCBasis * b, gsCMatrix * weights)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsBSplineBasis<double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new gismo::gsNurbsBasis<double>(basis_ptr,*w));
}

GISMO_EXPORT gsCBasis* gsTensorNurbsBasis2_create(gsCBasis* b, gsCMatrix * weights)
{ 
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<2,double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new  gismo::gsTensorNurbsBasis<2,double>(basis_ptr,*w));
}

GISMO_EXPORT gsCBasis* gsTensorNurbsBasis3_create(gsCBasis* b, gsCMatrix * weights)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<3,double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new  gismo::gsTensorNurbsBasis<3,double>(basis_ptr,*w));
}

GISMO_EXPORT gsCBasis* gsTensorNurbsBasis4_create(gsCBasis* b, gsCMatrix * weights)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<4,double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new  gismo::gsTensorNurbsBasis<4,double>(basis_ptr,*w));
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

GISMO_EXPORT gsCBasis* gsHBSplineBasis1_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<1,double>* >(b);
    return RICAST_CB(new gismo::gsHBSplineBasis<1,double>(*basis_ptr,false));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis2_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<2,double>* >(b);
    return RICAST_CB(new  gismo::gsHBSplineBasis<2,double>(*basis_ptr,false));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis3_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<3,double>* >(b);
    return RICAST_CB(new  gismo::gsHBSplineBasis<3,double>(*basis_ptr,false));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis4_create(gsCBasis* b)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<4,double>* >(b);
    return RICAST_CB(new  gismo::gsHBSplineBasis<4,double>(*basis_ptr,false));
}

//
// Methods, gsBasis
//

GISMO_EXPORT void gsBasis_active_into(gsCBasis * b,
                              gsCMatrix * u,
                              gsCMatrixInt * result)
{ RICAST_B(b)->active_into(*RICAST_M(u), *RICAST_Mi(result) ); }

GISMO_EXPORT void gsBasis_evalSingle_into(gsCBasis * b,
                                          int i,
                                          gsCMatrix * u,
                                          gsCMatrix * result)
{ RICAST_B(b)->evalSingle_into(i,*RICAST_M(u), *RICAST_M(result) ); }

GISMO_EXPORT void gsBasis_derivSingle_into(gsCBasis * b,
                                           int i,
                                           gsCMatrix * u,
                                           gsCMatrix * result)
{ RICAST_B(b)->derivSingle_into(i,*RICAST_M(u), *RICAST_M(result) ); }

GISMO_EXPORT void gsBasis_deriv2Single_into(gsCBasis * b,
                                            int i,
                                            gsCMatrix * u,
                                            gsCMatrix * result)
{ RICAST_B(b)->deriv2Single_into(i,*RICAST_M(u), *RICAST_M(result) ); }

GISMO_EXPORT gsCBasis * gsBasis_component(gsCBasis * b, int dir)
{
    gismo::gsBasis<double> * c = & RICAST_B(b)->component(dir);
    return reinterpret_cast<gsCBasis*>(c);
}

GISMO_EXPORT int gsBasis_degree(gsCBasis * b, int dir)
{ return RICAST_B(b)->component(dir).degree(dir); }

GISMO_EXPORT int gsBasis_numElements(gsCBasis * b)
{ return RICAST_B(b)->numElements(); }

GISMO_EXPORT int gsBasis_dim(gsCBasis * b)
{ return RICAST_B(b)->dim(); }

GISMO_EXPORT int gsBasis_size(gsCBasis * b)
{ return RICAST_B(b)->size(); }

GISMO_EXPORT gsCMatrix* gsBasis_support(gsCBasis * b, int i)
{ return reinterpret_cast<gsCMatrix*>( new gismo::gsMatrix<double>(RICAST_B(b)->support(i)) ); }

GISMO_EXPORT void gsBasis_uniformRefine(gsCBasis * b, int numKnots, int mul, int dir)
{ RICAST_B(b)->uniformRefine(numKnots, mul, dir); }

GISMO_EXPORT void gsBasis_refineElements(gsCBasis * b, int * boxData, int boxSize)
{
    std::vector<int> boxes(boxData,boxData+boxSize);
    RICAST_B(b)->refineElements(boxes);
}

GISMO_EXPORT void gsBasis_refine(gsCBasis * b, gsCMatrix * boxes, int refExt)
{ RICAST_B(b)->refine(*RICAST_M(boxes),refExt); }

//
// Methods, Other
//

GISMO_EXPORT gsCKnotVector * gsBSplineBasis_knots(gsCBasis * b)
{
    gismo::gsKnotVector<double> * KV= &reinterpret_cast< gismo::gsBSplineBasis<double>* >(b)->knots();
    return reinterpret_cast<gsCKnotVector*>(KV);
}

GISMO_EXPORT gsCKnotVector * gsTensorBSplineBasis_knots(gsCBasis * b, int dir)
{
    gismo::gsKnotVector<double> * KV=NULL;
    GISMO_ASSERT(RICAST_B(b)->domainDim()>=dir,"gsTensorBSplineBasis_knots: dir out of range");
    switch (RICAST_B(b)->domainDim())
    {
        case 2:
            KV = &reinterpret_cast< gismo::gsTensorBSplineBasis<2,double>* >(b)->knots(dir);
        case 3:
            KV = &reinterpret_cast< gismo::gsTensorBSplineBasis<3,double>* >(b)->knots(dir);
        case 4:
            KV = &reinterpret_cast< gismo::gsTensorBSplineBasis<4,double>* >(b)->knots(dir);
    }

    return reinterpret_cast<gsCKnotVector*>(KV);
}

GISMO_EXPORT int gsHTensorBasis_numLevels(gsCBasis * b)
{
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->numLevels();
        case 2:
            return reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->numLevels();
        case 3:
            return reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->numLevels();
        case 4:
            return reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->numLevels();
        default:
            GISMO_ERROR("gsHTensorBasis_numLevels: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_maxLevel(gsCBasis * b)
{
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->maxLevel();
        case 2:
            return reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->maxLevel();
        case 3:
            return reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->maxLevel();
        case 4:
            return reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->maxLevel();
        default:
            GISMO_ERROR("gsHTensorBasis_maxLevel: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_levelOf(gsCBasis * b, int i)
{
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->levelOf(i);
        case 2:
            return reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->levelOf(i);
        case 3:
            return reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->levelOf(i);
        case 4:
            return reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->levelOf(i);
        default:
            GISMO_ERROR("gsHTensorBasis_levelOf: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_getLevelAtPoint(gsCBasis * b, gsCMatrix * Pt)
{
    auto * m = RICAST_M(Pt);
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->getLevelAtPoint(*m);
        case 2:
            return reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->getLevelAtPoint(*m);
        case 3:
            return reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->getLevelAtPoint(*m);
        case 4:
            return reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->getLevelAtPoint(*m);
        default:
            GISMO_ERROR("gsHTensorBasis_getLevelAtPoint: domainDim not supported");
    }
}

GISMO_EXPORT gsCBasis * gsHTensorBasis_tensorLevel(gsCBasis * b, int l)
{
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return RICAST_CB(new  gismo::gsBSplineBasis<double>(reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->tensorLevel(l)));
        case 2:
            return RICAST_CB(new  gismo::gsTensorBSplineBasis<2,double>(reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->tensorLevel(l)));
        case 3:
            return RICAST_CB(new  gismo::gsTensorBSplineBasis<3,double>(reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->tensorLevel(l)));
        case 4:
            return RICAST_CB(new  gismo::gsTensorBSplineBasis<4,double>(reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->tensorLevel(l)));
        default:
            GISMO_ERROR("gsHTensorBasis_tensorLevel: domainDim not supported");
    }
}

GISMO_EXPORT void gsHTensorBasis_treeLeafSize(gsCBasis * b)
{
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->tree().leafSize();
        case 2:
            reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->tree().leafSize();
        case 3:
            reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->tree().leafSize();
        case 4:
            reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->tree().leafSize();
        default:
            GISMO_ERROR("gsHTensorBasis_treeLeaveSize: domainDim not supported");
    }
}

GISMO_EXPORT void gsHTensorBasis_treePrintLeaves(gsCBasis * b)
{
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            reinterpret_cast< gismo::gsHTensorBasis<1,double>* >(b)->tree().printLeaves();
        case 2:
            reinterpret_cast< gismo::gsHTensorBasis<2,double>* >(b)->tree().printLeaves();
        case 3:
            reinterpret_cast< gismo::gsHTensorBasis<3,double>* >(b)->tree().printLeaves();
        case 4:
            reinterpret_cast< gismo::gsHTensorBasis<4,double>* >(b)->tree().printLeaves();
        default:
            GISMO_ERROR("gsHTensorBasis_treePrintLeaves: domainDim not supported");
    }
}

#ifdef __cplusplus
}
#endif