
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCGeometry.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsCBasis.h>
#include <gsCInterface/gsMacros.h>

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCGeometry* gsBSpline_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsBSplineBasis<double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsBSpline<double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline2_create(gsCBasis* b, gsCMatrix * coefs)
{
    gismo::gsTensorBSplineBasis<2,double>* basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<2,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTensorBSpline<2,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline3_create(gsCBasis* b, gsCMatrix * coefs)
{
    gismo::gsTensorBSplineBasis<3,double>* basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<3,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTensorBSpline<3,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline4_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTensorBSplineBasis<4,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTensorBSpline<4,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline1_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTHBSplineBasis<1,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTHBSpline<1,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline2_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTHBSplineBasis<2,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTHBSpline<2,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline3_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTHBSplineBasis<3,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTHBSpline<3,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline4_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gismo::gsTHBSplineBasis<4,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gismo::gsTHBSpline<4,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCBasis* gsGeometry_basis(gsCGeometry * g)
{ return RICAST_CB(&RICAST_G(g)->basis()); }

GISMO_EXPORT void gsGeometry_coefs_into(gsCGeometry * g, gsCMatrix * coefs)
{
    *RICAST_M(coefs) = RICAST_G(g)->coefs();
}

GISMO_EXPORT void gsGeometry_uniformRefine(gsCGeometry * g, int numKnots, int mul, int dir)
{ RICAST_G(g)->uniformRefine(numKnots, mul, dir); }

GISMO_EXPORT void gsGeometry_refineElements(gsCGeometry * g, int * boxData, int boxSize)
{
    std::vector<int> boxes(boxData,boxData+boxSize);
    RICAST_G(g)->refineElements(boxes);
}

GISMO_EXPORT void gsGeometry_recoverPoints(gsCGeometry * g, gsCMatrix * uv, gsCMatrix * xyz,
                                            int k, double accuracy)
{ RICAST_G(g)->recoverPoints(*RICAST_M(xyz), *RICAST_M(uv), k, accuracy); }

GISMO_EXPORT void gsGeometry_recoverPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                               gsCVectorInt * sz,  gsCMatrix * xyz,
                                               gsCMatrix * uv,int c, double accuracy)
{
    gsGridIterator<real_t,CUBE> git(*RICAST_V(a),*RICAST_V(b), *RICAST_Vi(sz));
    RICAST_G(g)->recoverPointGrid(git,*RICAST_M(xyz), *RICAST_M(uv), c, accuracy);
}

GISMO_EXPORT void gsGeometry_invertPoints(gsCGeometry * g, gsCMatrix * points, gsCMatrix * result,
                                double accuracy)
{ RICAST_G(g)->invertPoints(*RICAST_M(points), *RICAST_M(result), accuracy,false); }

GISMO_EXPORT void gsGeometry_invertPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                   gsCVectorInt * sz, gsCMatrix * result,
                                   double accuracy)
{
    gsGridIterator<real_t,CUBE> git(*RICAST_V(a),*RICAST_V(b), *RICAST_Vi(sz));
    RICAST_G(g)->invertPointGrid(git, *RICAST_M(result), accuracy,false);
}

GISMO_EXPORT void gsGeometry_normal_into(gsCGeometry * fs,
                             gsCMatrix * u,
                             gsCMatrix * result)
{
    gsMapData<> mapData;
    mapData.flags = NEED_NORMAL ;
    mapData.points = *RICAST_M(u);
    RICAST_G(fs)->computeMap(mapData);
    *RICAST_M(result) = mapData.normals;
}

GISMO_EXPORT double gsGeometry_closestPointTo(gsCGeometry * fs,
                                 gsCMatrix * pt,
                                 gsCMatrix * result,
                                 double accuracy)
{
    gsVector<> tmp;
    double dist = RICAST_G(fs)->closestPointTo(*RICAST_V(pt),tmp,accuracy,false);
    *RICAST_M(result) = tmp;
    // gsDebugVar(*RICAST_M(result));
    // gsDebugVar(*RICAST_V(result));
    return dist;
}

#ifdef __cplusplus
}
#endif