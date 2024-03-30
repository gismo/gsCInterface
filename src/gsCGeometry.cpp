
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCGeometry.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsCBasis.h>
#include <gsCInterface/gsMacros.h>

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

GISMO_EXPORT gsCBasis* basis(gsCGeometry * g)
{ return RICAST_CB(&RICAST_G(g)->basis()); }

GISMO_EXPORT void recoverPoints(gsCGeometry * g, gsCMatrix * uv, gsCMatrix * xyz,
                                int k, double accuracy)
{ RICAST_G(g)->recoverPoints(*RICAST_M(xyz), *RICAST_M(uv), k, accuracy); }

GISMO_EXPORT void recoverPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                   gsCVectorInt * sz,  gsCMatrix * xyz,
                                   gsCMatrix * uv,int c, double accuracy)
{
    gsGridIterator<real_t,CUBE> git(*RICAST_V(a),*RICAST_V(b), *RICAST_Vi(sz));
    RICAST_G(g)->recoverPointGrid(git,*RICAST_M(xyz), *RICAST_M(uv), c, accuracy);
}
