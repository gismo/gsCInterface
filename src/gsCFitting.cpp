
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCFitting.h>

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCFitting * gsFitting_create(gsCMatrix * param_values, gsCMatrix * points, gsCBasis * basis)
{
    auto * param_values_ptr = RICAST_M(param_values);
    auto * points_ptr = RICAST_M(points);
    auto * basis_ptr = RICAST_B(basis);
    return reinterpret_cast<gsCFitting*>(new gismo::gsFitting<double>(*param_values_ptr, *points_ptr, *basis_ptr));
}

GISMO_EXPORT void gsFitting_delete(gsCFitting * fitter)
{
    delete reinterpret_cast<gismo::gsFitting<double>*>(fitter);
}

GISMO_EXPORT void gsFitting_compute(gsCFitting * fitter, double lambda)
{
    reinterpret_cast<gismo::gsFitting<double>*>(fitter)->compute(lambda);
}

GISMO_EXPORT void gsFitting_parameterCorrection(gsCFitting * fitter, double accuracy, int maxIter, double tolOrth)
{
    reinterpret_cast<gismo::gsFitting<double>*>(fitter)->parameterCorrection(accuracy, maxIter, tolOrth);
}

GISMO_EXPORT void gsFitting_computeErrors(gsCFitting * fitter)
{
    reinterpret_cast<gismo::gsFitting<double>*>(fitter)->computeErrors();
}

GISMO_EXPORT double gsFitting_minPointError(gsCFitting * fitter)
{
    return reinterpret_cast<gismo::gsFitting<double>*>(fitter)->minPointError();
}

GISMO_EXPORT double gsFitting_maxPointError(gsCFitting * fitter)
{
    return reinterpret_cast<gismo::gsFitting<double>*>(fitter)->maxPointError();
}

GISMO_EXPORT double* gsFitting_pointWiseErrors(gsCFitting * fitter)
{
    const double * errors = reinterpret_cast< const double* >(reinterpret_cast<gismo::gsFitting<double>*>(fitter)->pointWiseErrors().data());
    return const_cast<double *>(errors);
}

GISMO_EXPORT int gsFitting_numPointsBelow(gsCFitting * fitter, double threshold)
{
    return reinterpret_cast<gismo::gsFitting<double>*>(fitter)->numPointsBelow(threshold);
}

GISMO_EXPORT gsCGeometry* gsFitting_result(gsCFitting * fitter)
{
    auto * result = reinterpret_cast<gismo::gsFitting<double>*>(fitter)->result();
    return RICAST_CG(result->clone().release());
}

#ifdef __cplusplus
}
#endif