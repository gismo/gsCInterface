
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

using namespace gismo;

GISMO_EXPORT gsCGeometry * gsGeometry_read(char* filename)
{
    gsFileData<> data(filename);
    if (data.hasAny< gsGeometry<> >())
    {
        gsGeometry<>::uPtr ptr = data.getAnyFirst< gsGeometry<> >();
        return RICAST_CG(ptr.release());
    }
    else
    {
        gsWarn<<"[G+Smo] No gsGeometry found in file "<<filename<<"\n";
        return NULL;
    }
}

GISMO_EXPORT void gsGeometry_write(gsCGeometry * obj, char* filename)
{
    gsFileData<> data;
    data.add(*RICAST_G(obj));
    data.save(filename);
}

GISMO_EXPORT gsCGeometry* gsBSpline_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsBSplineBasis<double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsBSpline<double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline2_create(gsCBasis* b, gsCMatrix * coefs)
{
    gsTensorBSplineBasis<2,double>* basis_ptr = reinterpret_cast< gsTensorBSplineBasis<2,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTensorBSpline<2,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline3_create(gsCBasis* b, gsCMatrix * coefs)
{
    gsTensorBSplineBasis<3,double>* basis_ptr = reinterpret_cast< gsTensorBSplineBasis<3,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTensorBSpline<3,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline4_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsTensorBSplineBasis<4,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTensorBSpline<4,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsNurbs_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsNurbsBasis<double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsNurbs<double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorNurbs2_create(gsCBasis* b, gsCMatrix * coefs)
{
    gsTensorNurbsBasis<2,double>* basis_ptr = reinterpret_cast< gsTensorNurbsBasis<2,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTensorNurbs<2,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorNurbs3_create(gsCBasis* b, gsCMatrix * coefs)
{
    gsTensorNurbsBasis<3,double>* basis_ptr = reinterpret_cast< gsTensorNurbsBasis<3,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTensorNurbs<3,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorNurbs4_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsTensorNurbsBasis<4,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTensorNurbs<4,double>(*basis_ptr,*m));
}


GISMO_EXPORT gsCGeometry* gsTHBSpline1_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsTHBSplineBasis<1,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTHBSpline<1,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline2_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsTHBSplineBasis<2,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTHBSpline<2,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline3_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsTHBSplineBasis<3,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTHBSpline<3,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTHBSpline4_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsTHBSplineBasis<4,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsTHBSpline<4,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsHBSpline1_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsHBSplineBasis<1,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsHBSpline<1,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsHBSpline2_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsHBSplineBasis<2,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsHBSpline<2,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsHBSpline3_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsHBSplineBasis<3,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsHBSpline<3,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsHBSpline4_create(gsCBasis* b, gsCMatrix * coefs)
{
    auto * basis_ptr = reinterpret_cast< gsHBSplineBasis<4,double>* >(b);
    auto * m = RICAST_M(coefs);
    return RICAST_CG(new gsHBSpline<4,double>(*basis_ptr,*m));
}

GISMO_EXPORT gsCGeometry* gsTensorBSpline2_slice(gsCGeometry * g, int direction, double parameter)
{
    auto * g_ptr = reinterpret_cast< gsTensorBSpline<2,double>* >(g);
    typedef typename gsTensorBSpline<2,double>::BoundaryGeometryType GeometryBdr;
    GeometryBdr * bdr = new GeometryBdr();
    g_ptr->slice(direction, parameter, *bdr);
    return RICAST_CG(bdr);
}

GISMO_EXPORT gsCGeometry* gsGeometry_clone(gsCGeometry * g)
{
    return RICAST_CG(RICAST_G(g)->clone().release());
}

GISMO_EXPORT gsCBasis* gsGeometry_basis(gsCGeometry * g)
{
    return RICAST_CB(RICAST_G(g)->basis().clone().release());
}

GISMO_EXPORT void gsGeometry_coefs_into(gsCGeometry * g, gsCMatrix * coefs)
{
    *RICAST_M(coefs) = RICAST_G(g)->coefs();
}

GISMO_EXPORT void gsGeometry_setCoefs(gsCGeometry * g, gsCMatrix * coefs)
{
    RICAST_G(g)->coefs() = *RICAST_M(coefs);
}

GISMO_EXPORT void gsGeometry_uniformRefine(gsCGeometry * g, int numKnots, int mul, int dir)
{ RICAST_G(g)->uniformRefine(numKnots, mul, dir); }

GISMO_EXPORT void gsGeometry_refineElements(gsCGeometry * g, int * boxData, int boxSize)
{
    std::vector<int> boxes(boxData,boxData+boxSize);
    RICAST_G(g)->refineElements(boxes);
}

GISMO_EXPORT void gsGeometry_refine(gsCGeometry * g, gsCMatrix * boxes, int refExt)
{
    std::vector<int> boxData = RICAST_G(g)->basis().asElements(*RICAST_M(boxes),refExt);
    RICAST_G(g)->refineElements(boxData);
}

GISMO_EXPORT void gsGeometry_degreeElevate(gsCGeometry * g, int i, int dir)
{ RICAST_G(g)->degreeElevate(i, dir); }

GISMO_EXPORT void gsGeometry_recoverPoints(gsCGeometry * g, gsCMatrix * uv, gsCMatrix * xyz,
                                            int k, double accuracy)
{ RICAST_G(g)->recoverPoints(*RICAST_M(xyz), *RICAST_M(uv), k, accuracy); }

GISMO_EXPORT void gsGeometry_recoverPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                               gsCVectorInt * sz,  gsCMatrix * xyz,
                                               gsCMatrix * uv,int c, double accuracy)
{
    gismo::gsGridIterator<real_t,gismo::CUBE> git(*RICAST_V(a),*RICAST_V(b), *RICAST_Vi(sz));
    RICAST_G(g)->recoverPointGrid(git,*RICAST_M(xyz), *RICAST_M(uv), c, accuracy);
}

GISMO_EXPORT void gsGeometry_invertPoints(gsCGeometry * g, gsCMatrix * points, gsCMatrix * result,
                                double accuracy)
{ RICAST_G(g)->invertPoints(*RICAST_M(points), *RICAST_M(result), accuracy,false); }

GISMO_EXPORT void gsGeometry_invertPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                   gsCVectorInt * sz, gsCMatrix * result,
                                   double accuracy)
{
    gismo::gsGridIterator<real_t,gismo::CUBE> git(*RICAST_V(a),*RICAST_V(b), *RICAST_Vi(sz));
    RICAST_G(g)->invertPointGrid(git, *RICAST_M(result), accuracy,false);
}

GISMO_EXPORT void gsGeometry_normal_into(gsCGeometry * fs,
                             gsCMatrix * u,
                             gsCMatrix * result)
{
    gismo::gsMapData<> mapData;
    mapData.flags = gismo::NEED_NORMAL ;
    mapData.points = *RICAST_M(u);
    RICAST_G(fs)->computeMap(mapData);
    *RICAST_M(result) = mapData.normals;
}

GISMO_EXPORT double gsGeometry_closestPointTo(gsCGeometry * fs,
                                 gsCMatrix * pt,
                                 gsCMatrix * result,
                                 double accuracy)
{
    gismo::gsVector<> tmp;
    double dist = RICAST_G(fs)->closestPointTo(*RICAST_V(pt),tmp,accuracy,false);
    *RICAST_M(result) = tmp;
    // gsDebugVar(*RICAST_M(result));
    // gsDebugVar(*RICAST_V(result));
    return dist;
}

#ifdef __cplusplus
}
#endif
