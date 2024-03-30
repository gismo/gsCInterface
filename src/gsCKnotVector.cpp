
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

//GISMO_EXPORT double * greville(void * kv)
//{
//    gismo::gsKnotVector<double>* _kv = static_cast<gismo::gsKnotVector<double>*>(kv);
//}

