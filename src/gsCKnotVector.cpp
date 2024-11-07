
#include <gsNurbs/gsKnotVector.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCKnotVector.h>

GISMO_EXPORT gsCKnotVector * gsKnotVector_create(double* knots, int size)
{
    return reinterpret_cast<gsCKnotVector*>(new gismo::gsKnotVector<double>(-1,knots,knots+size));
}

GISMO_EXPORT void gsKnotVector_delete(gsCKnotVector * kv)
{
    delete reinterpret_cast<gismo::gsKnotVector<double>*>(kv);
}

GISMO_EXPORT void gsKnotVector_print(gsCKnotVector * kv)
{
    reinterpret_cast<gismo::gsKnotVector<double>*>(kv)->print(gsInfo);
}

// GISMO_EXPORT double* gsKnotVector_data(gsCKnotVector * kv)
// {
//     return reinterpret_cast<gismo::gsKnotVector<double>*>(kv)->get().data();
// }

GISMO_EXPORT int gsKnotVector_size(gsCKnotVector * kv)
{
    return reinterpret_cast<gismo::gsKnotVector<double>*>(kv)->size();
}

GISMO_EXPORT int gsKnotVector_uSize(gsCKnotVector * kv)
{
    return reinterpret_cast<gismo::gsKnotVector<double>*>(kv)->uSize();
}

GISMO_EXPORT int gsKnotVector_numElements(gsCKnotVector * kv)
{
    return reinterpret_cast<gismo::gsKnotVector<double>*>(kv)->numElements();
}

// GISMO_EXPORT double* gsKnotVector_unique(gsCKnotVector * kv)
// {
//     return reinterpret_cast<gismo::gsKnotVector<double>*>(kv)->unique().data();
// }

//GISMO_EXPORT double * greville(void * kv)
//{
//    gismo::gsKnotVector<double>* _kv = static_cast<gismo::gsKnotVector<double>*>(kv);
//}

