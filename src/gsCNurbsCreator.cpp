
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

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineUnitInterval(int deg)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineUnitInterval(deg).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineRectangle(double low_x, double low_y, double upp_x, double upp_y, double turndeg)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineRectangle(low_x, low_y, upp_x, upp_y, turndeg).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineTrapezium(double Lbot, double Ltop, double H, double d, double turndeg)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineTrapezium(Lbot, Ltop, H, d, turndeg).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineSquare(double r, double x, double y)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineSquare(r, x, y).release());
}

GISMO_EXPORT gsCMultiPatch* gsNurbsCreator_BSplineSquareGrid(int n, int m, double r, double lx, double ly)
{
    return RICAST_CMP(new gismo::gsMultiPatch<double>(gismo::gsNurbsCreator<double>::BSplineSquareGrid(n, m, r, lx, ly)));
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineCube(double r, double x, double y, double z)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineCube(r, x, y, z).release());
}

GISMO_EXPORT gsCMultiPatch* gsNurbsCreator_BSplineCubeGrid(int n, int m, int p, double r, double lx, double ly, double lz)
{
    return RICAST_CMP(new gismo::gsMultiPatch<double>(gismo::gsNurbsCreator<double>::BSplineCubeGrid(n, m, p, r, lx, ly, lz)));
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_NurbsQuarterAnnulus(double r0, double r1)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::NurbsQuarterAnnulus(r0, r1).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_NurbsAnnulus(double r0, double r1)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::NurbsAnnulus(r0, r1).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineSaddle()
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineSaddle().release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_NurbsSphere(double r, double x, double y, double z)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::NurbsSphere(r, x, y, z).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_NurbsCircle(double r, double x, double y)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::NurbsCircle(r, x, y).release());
}

GISMO_EXPORT gsCGeometry* gsNurbsCreator_BSplineTriangle(double H, double W)
{
    return RICAST_CG(gismo::gsNurbsCreator<double>::BSplineTriangle(H, W).release());
}

GISMO_EXPORT gsCMultiPatch* gsNurbsCreator_BSplineStar(int N, double R0, double R1)
{
    return RICAST_CMP(new gismo::gsMultiPatch<double>(gismo::gsNurbsCreator<double>::BSplineStar(N, R0, R1)));
}

#ifdef __cplusplus
}
#endif
