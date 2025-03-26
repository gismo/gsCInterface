
#include <gsNurbs/gsKnotVector.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCKnotVector.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCKnotVector * gsKnotVector_create(double* knots, int size)
{
    return reinterpret_cast<gsCKnotVector*>(new gsKnotVector<double>(-1,knots,knots+size));
}

GISMO_EXPORT void gsKnotVector_delete(gsCKnotVector * kv)
{
    delete reinterpret_cast<gsKnotVector<double>*>(kv);
}

GISMO_EXPORT void gsKnotVector_print(gsCKnotVector * kv)
{
    reinterpret_cast<gsKnotVector<double>*>(kv)->print(gsInfo);
}

GISMO_EXPORT double* gsKnotVector_data(gsCKnotVector * kv)
{
    return const_cast<double *>(reinterpret_cast<gsKnotVector<double>*>(kv)->get().data());
}

GISMO_EXPORT int gsKnotVector_size(gsCKnotVector * kv)
{
    return reinterpret_cast<gsKnotVector<double>*>(kv)->size();
}

GISMO_EXPORT int gsKnotVector_uSize(gsCKnotVector * kv)
{
    return reinterpret_cast<gsKnotVector<double>*>(kv)->uSize();
}

GISMO_EXPORT int gsKnotVector_numElements(gsCKnotVector * kv)
{
    return reinterpret_cast<gsKnotVector<double>*>(kv)->numElements();
}

// GISMO_EXPORT double* gsKnotVector_unique(gsCKnotVector * kv)
// {
//     return reinterpret_cast<gsKnotVector<double>*>(kv)->unique().data();
// }

//GISMO_EXPORT double * greville(void * kv)
//{
//    gsKnotVector<double>* _kv = static_cast<gsKnotVector<double>*>(kv);
//}

#ifdef __cplusplus
}
#endif