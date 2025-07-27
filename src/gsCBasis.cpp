
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCBasis.h>

using namespace gismo;

template <int dim>
void gsHTensorBasis_elements_into_impl(gsCBasis * b, bool getKnotBoxes,
                                                     bool getIndexBoxes,
                                                     bool getLevels,
                                                     gsCMatrix*    knotBoxes,
                                                     gsCMatrixInt* indexBoxes,
                                                     gsCVectorInt* levels)
{
    int N   = RICAST_B(b)->numElements();

    auto * el = RICAST_M(knotBoxes);
    auto * bx = RICAST_Mi(indexBoxes);
    auto * lv = RICAST_Vi(levels);

    if (getKnotBoxes) el->resize(dim,2*N);
    if (getIndexBoxes) bx->resize(2*dim+1,N);
    if (getLevels) lv->resize(N);

    auto domain = RICAST_B(b)->domain();
    auto domIt  = domain->beginAll();
    auto domEnd = domain->endAll();

    GISMO_ENSURE((dynamic_cast<gsHDomainIterator<double,dim> *>(domIt.get())),"The domain iterator is not a hierarchical domain iterator");
    gsHTensorBasis<dim,double> * basis = dynamic_cast<gsHTensorBasis<dim,double> *>(RICAST_B(b));

    int id=0;
    gsVector<double,dim> low, upp;
    for (; domIt<domEnd; ++domIt, ++id)
    {
        gsHDomainIterator<double,dim> * domItH = dynamic_cast<gsHDomainIterator<double,dim> *>(domIt.get());
        low = domIt.lowerCorner();
        upp = domIt.upperCorner();
        if (getKnotBoxes)
        {
            el->col(2*id) = low;
            el->col(2*id+1) = upp;
        }
        if (getLevels)
        {
            lv->at(id) = domItH->getLevel();
        }
        if (getIndexBoxes)
        {
            for(int j = 0; j < dim;j++)
            {
                // Convert the parameter coordinates to (unique) knot indices
                const gsKnotVector<real_t> & kv = basis->tensorLevel(domItH->getLevel()).knots(j);
                int k1 = (std::upper_bound(kv.domainUBegin(), kv.domainUEnd(),
                                        low[j] ) - 1).uIndex();
                int k2 = (std::upper_bound(kv.domainUBegin(), kv.domainUEnd()+1,
                                        upp[j] ) - 1).uIndex();

                // Trivial cells trigger some refinement
                if ( k1 == k2)
                {
                    if (0!=k1) {--k1;}
                    ++k2;
                }

                // Store the data...
                (*bx)(0,id) = domItH->getLevel();
                (*bx)(1+j,id) = k1;
                (*bx)(1+j+dim,id) = k2;
            }
        }
    }
}


#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCBasis * gsBasis_read(char* filename)
{
    gsFileData<> data(filename);
    if (data.hasAny< gsBasis<> >())
    {
        gsBasis<>::uPtr ptr = data.getAnyFirst< gsBasis<> >();
        return RICAST_CB(ptr.release());
    }
    else
    {
        gsWarn<<"[G+Smo] No gsBasis found in file "<<filename<<"\n";
        return NULL;
    }
}

GISMO_EXPORT void gsBasis_write(gsCBasis * obj, char* filename)
{
    if (obj == nullptr)
    {
        gsWarn << "gsBasis_write: obj is NULL, nothing to do.\n";
        return;
    }
    gsFileData<> data;
    data.add(*RICAST_B(obj));
    data.save(filename);
}

GISMO_EXPORT gsCBasis * gsBSplineBasis_create(gsCKnotVector * KV)
{
    if (KV == nullptr)
    {
        gsWarn << "gsBSplineBasis_create: KV is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * KV_ptr = RICAST_KV (KV);
    return RICAST_CB (new gsBSplineBasis<double>(*KV_ptr) );
}

GISMO_EXPORT gsCBasis* gsTensorBSplineBasis2_create(gsCKnotVector* KV1, gsCKnotVector* KV2)
{
    if (KV1 == nullptr || KV2 == nullptr)
    {
        gsWarn << "gsTensorBSplineBasis2_create: One or more KV are NULL, nothing to do.\n";
        return nullptr;
    }
    auto * KV1_ptr = RICAST_KV (KV1);
    auto * KV2_ptr = RICAST_KV (KV2);
    return RICAST_CB(new gsTensorBSplineBasis<2,double>(*KV1_ptr,*KV2_ptr) );
}

GISMO_EXPORT gsCBasis* gsTensorBSplineBasis3_create(gsCKnotVector* KV1, gsCKnotVector* KV2,
                                                    gsCKnotVector* KV3)
{
    if (KV1 == nullptr || KV2 == nullptr || KV3 == nullptr)
    {
        gsWarn << "gsTensorBSplineBasis3_create: One or more KV are NULL, nothing to do.\n";
        return nullptr;
    }
    auto * KV1_ptr = RICAST_KV (KV1);
    auto * KV2_ptr = RICAST_KV (KV2);
    auto * KV3_ptr = RICAST_KV (KV3);
    return RICAST_CB(new gsTensorBSplineBasis<3,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr));
}

GISMO_EXPORT gsCBasis* gsTensorBSplineBasis4_create(gsCKnotVector* KV1, gsCKnotVector* KV2,
                                                    gsCKnotVector* KV3, gsCKnotVector* KV4)
{
    if (KV1 == nullptr || KV2 == nullptr || KV3 == nullptr || KV4 == nullptr)
    {
        gsWarn << "gsTensorBSplineBasis4_create: One or more KV are NULL, nothing to do.\n";
        return nullptr;
    }
    auto * KV1_ptr = RICAST_KV (KV1);
    auto * KV2_ptr = RICAST_KV (KV2);
    auto * KV3_ptr = RICAST_KV (KV3);
    auto * KV4_ptr = RICAST_KV (KV4);
    return RICAST_CB(new gsTensorBSplineBasis<4,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr,*KV4_ptr));
}

GISMO_EXPORT gsCBasis * gsNurbsBasis_create(gsCBasis * b, gsCMatrix * weights)
{
    if (b == nullptr || weights == nullptr)
    {
        gsWarn << "gsNurbsBasis_create: b or weights is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsBSplineBasis<double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new gsNurbsBasis<double>(basis_ptr,*w));
}

GISMO_EXPORT gsCBasis* gsTensorNurbsBasis2_create(gsCBasis* b, gsCMatrix * weights)
{
    if (b == nullptr || weights == nullptr)
    {
        gsWarn << "gsTensorNurbsBasis2_create: b or weights is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<2,double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new  gsTensorNurbsBasis<2,double>(basis_ptr,*w));
}

GISMO_EXPORT gsCBasis* gsTensorNurbsBasis3_create(gsCBasis* b, gsCMatrix * weights)
{
    if (b == nullptr || weights == nullptr)
    {
        gsWarn << "gsTensorNurbsBasis3_create: b or weights is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<3,double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new  gsTensorNurbsBasis<3,double>(basis_ptr,*w));
}

GISMO_EXPORT gsCBasis* gsTensorNurbsBasis4_create(gsCBasis* b, gsCMatrix * weights)
{
    if (b == nullptr || weights == nullptr)
    {
        gsWarn << "gsTensorNurbsBasis4_create: b or weights is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<4,double>* >(b);
    auto * w = RICAST_M(weights);
    return RICAST_CB(new  gsTensorNurbsBasis<4,double>(basis_ptr,*w));
}


GISMO_EXPORT gsCBasis* gsTHBSplineBasis1_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsTHBSplineBasis1_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<1,double>* >(b);
    return RICAST_CB(new gsTHBSplineBasis<1,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis2_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsTHBSplineBasis2_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<2,double>* >(b);
    return RICAST_CB(new  gsTHBSplineBasis<2,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis3_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsTHBSplineBasis3_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<3,double>* >(b);
    return RICAST_CB(new  gsTHBSplineBasis<3,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsTHBSplineBasis4_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsTHBSplineBasis4_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<4,double>* >(b);
    return RICAST_CB(new  gsTHBSplineBasis<4,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis1_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsHBSplineBasis1_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<1,double>* >(b);
    return RICAST_CB(new gsHBSplineBasis<1,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis2_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsHBSplineBasis2_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<2,double>* >(b);
    return RICAST_CB(new  gsHBSplineBasis<2,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis3_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsHBSplineBasis3_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<3,double>* >(b);
    return RICAST_CB(new  gsHBSplineBasis<3,double>(*basis_ptr,manualLevels));
}

GISMO_EXPORT gsCBasis* gsHBSplineBasis4_create(gsCBasis* b, int manualLevels)
{
    if (b == nullptr)
    {
        gsWarn << "gsHBSplineBasis4_create: b is NULL, nothing to do.\n";
        return nullptr;
    }
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<4,double>* >(b);
    return RICAST_CB(new  gsHBSplineBasis<4,double>(*basis_ptr,manualLevels));
}

//
// Methods, gsBasis
//

GISMO_EXPORT gsCBasis* gsBasis_clone(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_clone: b is NULL, nothing to do.\n";
        return nullptr;
    }
    return RICAST_CB(RICAST_B(b)->clone().release());
}

GISMO_EXPORT void gsBasis_active_into(gsCBasis * b,
                              gsCMatrix * u,
                              gsCMatrixInt * result)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_active_into: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->active_into(*RICAST_M(u), *RICAST_Mi(result) );
}

GISMO_EXPORT void gsBasis_evalSingle_into(gsCBasis * b,
                                          int i,
                                          gsCMatrix * u,
                                          gsCMatrix * result)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_evalSingle_into: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->evalSingle_into(i,*RICAST_M(u), *RICAST_M(result) );
}

GISMO_EXPORT void gsBasis_derivSingle_into(gsCBasis * b,
                                           int i,
                                           gsCMatrix * u,
                                           gsCMatrix * result)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_derivSingle_into: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->derivSingle_into(i,*RICAST_M(u), *RICAST_M(result) );
}

GISMO_EXPORT void gsBasis_deriv2Single_into(gsCBasis * b,
                                            int i,
                                            gsCMatrix * u,
                                            gsCMatrix * result)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_deriv2Single_into: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->deriv2Single_into(i,*RICAST_M(u), *RICAST_M(result) );
}

GISMO_EXPORT gsCBasis * gsBasis_component(gsCBasis * b, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_component: b is NULL, nothing to do.\n";
        return nullptr;
    }
    gsBasis<double> * c = & RICAST_B(b)->component(dir);
    return reinterpret_cast<gsCBasis*>(c);
}

GISMO_EXPORT int gsBasis_degree(gsCBasis * b, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_degree: b is NULL, nothing to do.\n";
        return -1;
    }
    return RICAST_B(b)->component(dir).degree(dir);
}

GISMO_EXPORT int gsBasis_numElements(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_numElements: b is NULL, nothing to do.\n";
        return -1;
    }
    return RICAST_B(b)->numElements();
}

GISMO_EXPORT int gsBasis_dim(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_dim: b is NULL, nothing to do.\n";
        return -1;
    }
    return RICAST_B(b)->dim();
}

GISMO_EXPORT int gsBasis_size(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_size: b is NULL, nothing to do.\n";
        return -1;
    }
    return RICAST_B(b)->size();
}

GISMO_EXPORT gsCMatrix* gsBasis_support(gsCBasis * b, int i)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_support: b is NULL, nothing to do.\n";
        return nullptr;
    }
    return reinterpret_cast<gsCMatrix*>( new gsMatrix<double>(RICAST_B(b)->support(i)) );
}

GISMO_EXPORT void gsBasis_uniformRefine(gsCBasis * b, int numKnots, int mul, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_uniformRefine: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->uniformRefine(numKnots, mul, dir);
}

GISMO_EXPORT void gsBasis_refineElements(gsCBasis * b, int * boxData, int boxSize)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_refineElements: b is NULL, nothing to do.\n";
        return;
    }
    std::vector<int> boxes(boxData,boxData+boxSize);
    RICAST_B(b)->refineElements(boxes);
}

GISMO_EXPORT void gsBasis_refine(gsCBasis * b, gsCMatrix * boxes, int refExt)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_refine: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->refine(*RICAST_M(boxes),refExt);
}

GISMO_EXPORT void gsBasis_degreeElevate(gsCBasis * b, int i, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_degreeElevate: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->degreeElevate(i,dir);
}

GISMO_EXPORT void gsBasis_degreeReduce(gsCBasis * b, int i, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_degreeReduce: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->degreeReduce(i,dir);
}

GISMO_EXPORT void gsBasis_degreeIncrease(gsCBasis * b, int i, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_degreeIncrease: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->degreeIncrease(i,dir);
}

GISMO_EXPORT void gsBasis_degreeDecrease(gsCBasis * b, int i, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_degreeDecrease: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->degreeDecrease(i,dir);
}

GISMO_EXPORT void gsBasis_elevateContinuity(gsCBasis * b, int i)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_elevateContinuity: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->elevateContinuity(i);
}

GISMO_EXPORT void gsBasis_reduceContinuity(gsCBasis * b, int i)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_reduceContinuity: b is NULL, nothing to do.\n";
        return;
    }
    RICAST_B(b)->reduceContinuity(i);
}

GISMO_EXPORT void gsBasis_boundary_into(gsCBasis * b, int side, gsCMatrixInt * result)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_boundary_into: b is NULL, nothing to do.\n";
        return;
    }
    *RICAST_Mi(result) = RICAST_B(b)->boundary(side);
}

GISMO_EXPORT void gsBasis_boundaryOffset_into(gsCBasis * b, int side, int offset, gsCMatrixInt * result)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_boundaryOffset_into: b is NULL, nothing to do.\n";
        return;
    }
    *RICAST_Mi(result) = RICAST_B(b)->boundaryOffset(side,offset);
}

GISMO_EXPORT void gsBasis_elements_into(gsCBasis * b, gsCMatrix* elements)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_elements_into: b is NULL, nothing to do.\n";
        return;
    }
    auto * el = RICAST_M(elements);
    el->resize(RICAST_B(b)->domainDim(),2*RICAST_B(b)->numElements());
    auto domain = RICAST_B(b)->domain();
    auto domIt  = domain->beginAll();
    auto domEnd = domain->endAll();
    int id=0;
    for (; domIt<domEnd; ++domIt, ++id)
    {
        el->col(2*id) = domIt.lowerCorner();
        el->col(2*id+1) = domIt.upperCorner();
    }
}

GISMO_EXPORT void gsBasis_elementsBdr_into(gsCBasis * b, int side, gsCMatrix* elements)
{
    if (b == nullptr)
    {
        gsWarn << "gsBasis_elementsBdr_into: b is NULL, nothing to do.\n";
        return;
    }
    auto * el = RICAST_M(elements);
    el->resize(RICAST_B(b)->domainDim(),2*RICAST_B(b)->numElements());
    auto domain = RICAST_B(b)->domain();
    auto domIt  = domain->beginBdr(side);
    auto domEnd = domain->endBdr(side);
    int id=0;
    for (; domIt<domEnd; ++domIt, ++id)
    {
        el->col(2*id) = domIt.lowerCorner();
        el->col(2*id+1) = domIt.upperCorner();
    }
}

GISMO_EXPORT void gsHTensorBasis_elements_into(gsCBasis * b, bool getKnotBoxes,
                                                             bool getIndexBoxes,
                                                             bool getLevels,
                                                             gsCMatrix*    knotBoxes,
                                                             gsCMatrixInt* indexBoxes,
                                                             gsCVectorInt* levels)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_elements_into: b is NULL, nothing to do.\n";
        return;
    }
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            gsHTensorBasis_elements_into_impl<1>(b,getKnotBoxes,getIndexBoxes,getLevels,knotBoxes,indexBoxes,levels);
            break;
        case 2:
            gsHTensorBasis_elements_into_impl<2>(b,getKnotBoxes,getIndexBoxes,getLevels,knotBoxes,indexBoxes,levels);
            break;
        case 3:
            gsHTensorBasis_elements_into_impl<3>(b,getKnotBoxes,getIndexBoxes,getLevels,knotBoxes,indexBoxes,levels);
            break;
        case 4:
            gsHTensorBasis_elements_into_impl<4>(b,getKnotBoxes,getIndexBoxes,getLevels,knotBoxes,indexBoxes,levels);
            break;
        default:
            GISMO_ERROR("gsHTensorBasis_elements_into: Dimension not supported");
    }
}

//
// Methods, Other
//

GISMO_EXPORT gsCKnotVector * gsBSplineBasis_knots(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsBSplineBasis_knots: b is NULL, nothing to do.\n";
        return nullptr;
    }
    gsKnotVector<double> * KV= &reinterpret_cast< gsBSplineBasis<double>* >(b)->knots();
    return reinterpret_cast<gsCKnotVector*>(KV);
}

GISMO_EXPORT gsCKnotVector * gsTensorBSplineBasis_knots(gsCBasis * b, int dir)
{
    if (b == nullptr)
    {
        gsWarn << "gsTensorBSplineBasis_knots: b is NULL, nothing to do.\n";
        return nullptr;
    }
    gsKnotVector<double> * KV=NULL;
    GISMO_ASSERT(RICAST_B(b)->domainDim()>=dir,"gsTensorBSplineBasis_knots: dir out of range");
    switch (RICAST_B(b)->domainDim())
    {
        case 2:
            KV = &reinterpret_cast< gsTensorBSplineBasis<2,double>* >(b)->knots(dir);
        case 3:
            KV = &reinterpret_cast< gsTensorBSplineBasis<3,double>* >(b)->knots(dir);
        case 4:
            KV = &reinterpret_cast< gsTensorBSplineBasis<4,double>* >(b)->knots(dir);
    }

    return reinterpret_cast<gsCKnotVector*>(KV);
}

GISMO_EXPORT int gsHTensorBasis_numLevels(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_numLevels: b is NULL, nothing to do.\n";
        return -1;
    }
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gsHTensorBasis<1,double>* >(b)->numLevels();
        case 2:
            return reinterpret_cast< gsHTensorBasis<2,double>* >(b)->numLevels();
        case 3:
            return reinterpret_cast< gsHTensorBasis<3,double>* >(b)->numLevels();
        case 4:
            return reinterpret_cast< gsHTensorBasis<4,double>* >(b)->numLevels();
        default:
            GISMO_ERROR("gsHTensorBasis_numLevels: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_maxLevel(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_maxLevel: b is NULL, nothing to do.\n";
        return -1;
    }
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gsHTensorBasis<1,double>* >(b)->maxLevel();
        case 2:
            return reinterpret_cast< gsHTensorBasis<2,double>* >(b)->maxLevel();
        case 3:
            return reinterpret_cast< gsHTensorBasis<3,double>* >(b)->maxLevel();
        case 4:
            return reinterpret_cast< gsHTensorBasis<4,double>* >(b)->maxLevel();
        default:
            GISMO_ERROR("gsHTensorBasis_maxLevel: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_levelOf(gsCBasis * b, int i)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_levelOf: b is NULL, nothing to do.\n";
        return -1;
    }
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gsHTensorBasis<1,double>* >(b)->levelOf(i);
        case 2:
            return reinterpret_cast< gsHTensorBasis<2,double>* >(b)->levelOf(i);
        case 3:
            return reinterpret_cast< gsHTensorBasis<3,double>* >(b)->levelOf(i);
        case 4:
            return reinterpret_cast< gsHTensorBasis<4,double>* >(b)->levelOf(i);
        default:
            GISMO_ERROR("gsHTensorBasis_levelOf: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_getLevelAtPoint(gsCBasis * b, gsCMatrix * Pt)
{
    if (b == nullptr || Pt == nullptr)
    {
        gsWarn << "gsHTensorBasis_getLevelAtPoint: b or Pt is NULL, nothing to do.\n";
        return -1;
    }
    auto * m = RICAST_M(Pt);
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return reinterpret_cast< gsHTensorBasis<1,double>* >(b)->getLevelAtPoint(*m);
        case 2:
            return reinterpret_cast< gsHTensorBasis<2,double>* >(b)->getLevelAtPoint(*m);
        case 3:
            return reinterpret_cast< gsHTensorBasis<3,double>* >(b)->getLevelAtPoint(*m);
        case 4:
            return reinterpret_cast< gsHTensorBasis<4,double>* >(b)->getLevelAtPoint(*m);
        default:
            GISMO_ERROR("gsHTensorBasis_getLevelAtPoint: domainDim not supported");
    }
}

GISMO_EXPORT gsCBasis * gsHTensorBasis_tensorLevel(gsCBasis * b, int l)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_tensorLevel: b is NULL, nothing to do.\n";
        return nullptr;
    }
    switch (RICAST_B(b)->domainDim())
    {
        case 1:
            return RICAST_CB(new  gsBSplineBasis<double>(reinterpret_cast< gsHTensorBasis<1,double>* >(b)->tensorLevel(l)));
        case 2:
            return RICAST_CB(new  gsTensorBSplineBasis<2,double>(reinterpret_cast< gsHTensorBasis<2,double>* >(b)->tensorLevel(l)));
        case 3:
            return RICAST_CB(new  gsTensorBSplineBasis<3,double>(reinterpret_cast< gsHTensorBasis<3,double>* >(b)->tensorLevel(l)));
        case 4:
            return RICAST_CB(new  gsTensorBSplineBasis<4,double>(reinterpret_cast< gsHTensorBasis<4,double>* >(b)->tensorLevel(l)));
        default:
            GISMO_ERROR("gsHTensorBasis_tensorLevel: domainDim not supported");
    }
}

GISMO_EXPORT int gsHTensorBasis_treeLeafSize(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_treeLeafSize: b is NULL, nothing to do.\n";
        return -1;
    }
    gsInfo<<"domainDim==1? "<<(RICAST_B(b)->domainDim()==1)<<"\n";
    gsInfo<<"domainDim==2? "<<(RICAST_B(b)->domainDim()==2)<<"\n";
    gsInfo<<"domainDim==3? "<<(RICAST_B(b)->domainDim()==3)<<"\n";
    gsInfo<<"domainDim==4? "<<(RICAST_B(b)->domainDim()==4)<<"\n";

    index_t domainDim = RICAST_B(b)->domainDim();
    if (domainDim==1)
        return reinterpret_cast< gsHTensorBasis<1,double>* >(b)->tree().leafSize();
    else if (domainDim==2)
        return reinterpret_cast< gsHTensorBasis<2,double>* >(b)->tree().leafSize();
    else if (domainDim==3)
        return reinterpret_cast< gsHTensorBasis<3,double>* >(b)->tree().leafSize();
    else if (domainDim==4)
        return reinterpret_cast< gsHTensorBasis<4,double>* >(b)->tree().leafSize();
    else
        GISMO_ERROR("gsHTensorBasis_treeLeafSize: domainDim " << RICAST_B(b)->domainDim() << " not supported");
}

GISMO_EXPORT void gsHTensorBasis_treePrintLeaves(gsCBasis * b)
{
    if (b == nullptr)
    {
        gsWarn << "gsHTensorBasis_treePrintLeaves: b is NULL, nothing to do.\n";
        return;
    }
    index_t domainDim = RICAST_B(b)->domainDim();
    if (domainDim==1)
        reinterpret_cast< gsHTensorBasis<1,double>* >(b)->tree().printLeaves();
    else if (domainDim==2)
        reinterpret_cast< gsHTensorBasis<2,double>* >(b)->tree().printLeaves();
    else if (domainDim==3)
        reinterpret_cast< gsHTensorBasis<3,double>* >(b)->tree().printLeaves();
    else if (domainDim==4)
        reinterpret_cast< gsHTensorBasis<4,double>* >(b)->tree().printLeaves();
    else
        GISMO_ERROR("gsHTensorBasis_treePrintLeaves: domainDim " << RICAST_B(b)->domainDim() << " not supported");
}

GISMO_EXPORT void gsHTensorBasis_addLevel(gsCBasis * b, gsCBasis * lvl)
{
    if (b==nullptr || lvl==nullptr)
    {
        gsWarn<<"gsHTensorBasis_addLevel: b or lvl is NULL, nothing to do.\n";
        return;
    }

    if (dynamic_cast<gsTensorBSplineBasis<1,double>*>(RICAST_B(lvl)) == nullptr &&
        dynamic_cast<gsTensorBSplineBasis<2,double>*>(RICAST_B(lvl)) == nullptr &&
        dynamic_cast<gsTensorBSplineBasis<3,double>*>(RICAST_B(lvl)) == nullptr &&
        dynamic_cast<gsTensorBSplineBasis<4,double>*>(RICAST_B(lvl)) == nullptr)
    {
        gsWarn<<"gsHTensorBasis_addLevel: cannot add a level that is not a gsTensorBSplineBasis\n";
        return;
    }

    index_t domainDim = RICAST_B(b)->domainDim();
    if (domainDim != RICAST_B(lvl)->domainDim())
    {
        gsWarn<<"gsHTensorBasis_addLevel: cannot add a level with different domainDim\n";
        return;
    }

    if (domainDim==1)
    {
        reinterpret_cast< gsHTensorBasis<1,double>* >(b)->addLevel(
            *reinterpret_cast< gsTensorBSplineBasis<1,double>* >(lvl)
        );
    }
    else if (domainDim==2)
    {
        reinterpret_cast< gsHTensorBasis<2,double>* >(b)->addLevel(
            *reinterpret_cast< gsTensorBSplineBasis<2,double>* >(lvl)
        );
    }
    else if (domainDim==3)
    {
        reinterpret_cast< gsHTensorBasis<3,double>* >(b)->addLevel(
            *reinterpret_cast< gsTensorBSplineBasis<3,double>* >(lvl)
        );
    }
    else if (domainDim==4)
    {
        reinterpret_cast< gsHTensorBasis<4,double>* >(b)->addLevel(
            *reinterpret_cast< gsTensorBSplineBasis<4,double>* >(lvl)
        );
    }
    else
    {
        GISMO_ERROR("gsHTensorBasis_addLevel: domainDim not supported");
    }
}

#ifdef __cplusplus
}
#endif