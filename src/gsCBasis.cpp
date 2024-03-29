
#include <gismo.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsCBasis.h>

GISMO_EXPORT void gsBasis_delete(gsCBasis* ptr)
{
    gismo::gsBasis<double>* p = reinterpret_cast< gismo::gsBasis<double>* >(ptr);
    delete p;
}

GISMO_EXPORT gsCBasis * gsBSplineBasis_create(gsCKnotVector * KV)
{
    gismo::gsKnotVector<double>* KV_ptr = reinterpret_cast< gismo::gsKnotVector<double>* >(KV);
    return reinterpret_cast<gsCBasis*>(new gismo::gsBSplineBasis<double>(*KV_ptr));
}

GISMO_EXPORT void* tensorBSplineBasis2(void* KV1, void* KV2)
{
    gismo::gsKnotVector<double>* KV1_ptr = static_cast< gismo::gsKnotVector<double>* >(KV1);
    gismo::gsKnotVector<double>* KV2_ptr = static_cast< gismo::gsKnotVector<double>* >(KV2);
    return new gismo::gsTensorBSplineBasis<2,double>(*KV1_ptr,*KV2_ptr);
}

GISMO_EXPORT void* tensorBSplineBasis3(void* KV1, void* KV2, void* KV3)
{
    gismo::gsKnotVector<double>* KV1_ptr = static_cast< gismo::gsKnotVector<double>* >(KV1);
    gismo::gsKnotVector<double>* KV2_ptr = static_cast< gismo::gsKnotVector<double>* >(KV2);
    gismo::gsKnotVector<double>* KV3_ptr = static_cast< gismo::gsKnotVector<double>* >(KV3);
    return new gismo::gsTensorBSplineBasis<3,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr);
}

GISMO_EXPORT void* tensorBSplineBasis4(void* KV1, void* KV2, void* KV3, void* KV4)
{
    gismo::gsKnotVector<double>* KV1_ptr = static_cast< gismo::gsKnotVector<double>* >(KV1);
    gismo::gsKnotVector<double>* KV2_ptr = static_cast< gismo::gsKnotVector<double>* >(KV2);
    gismo::gsKnotVector<double>* KV3_ptr = static_cast< gismo::gsKnotVector<double>* >(KV3);
    gismo::gsKnotVector<double>* KV4_ptr = static_cast< gismo::gsKnotVector<double>* >(KV4);
    return new gismo::gsTensorBSplineBasis<4,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr,*KV4_ptr);
}

GISMO_EXPORT void* bspline(void* basis, double* data, int rows, int cols)
{
    gismo::gsBSplineBasis<double>* basis_ptr = static_cast< gismo::gsBSplineBasis<double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsBSpline<double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* tensorBSpline2(void* basis, double* data, int rows, int cols)
{
    gismo::gsTensorBSplineBasis<2,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<2,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTensorBSpline<2,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* tensorBSpline3(void* basis, double* data, int rows, int cols)
{
    gismo::gsTensorBSplineBasis<3,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<3,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTensorBSpline<3,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* tensorBSpline4(void* basis, double* data, int rows, int cols)
{
    gismo::gsTensorBSplineBasis<4,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<4,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTensorBSpline<4,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSplineBasis1(void* basis)
{
    gismo::gsTensorBSplineBasis<1,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<1,double>* >(basis);
    return new  gismo::gsTHBSplineBasis<1,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSplineBasis2(void* basis)
{
    gismo::gsTensorBSplineBasis<2,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<2,double>* >(basis);
    return new  gismo::gsTHBSplineBasis<2,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSplineBasis3(void* basis)
{
    gismo::gsTensorBSplineBasis<3,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<3,double>* >(basis);
    return new  gismo::gsTHBSplineBasis<3,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSplineBasis4(void* basis)
{
    gismo::gsTensorBSplineBasis<4,double>* basis_ptr = static_cast< gismo::gsTensorBSplineBasis<4,double>* >(basis);
    return new  gismo::gsTHBSplineBasis<4,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSpline1(void* basis, double* data, int rows, int cols)
{
    gismo::gsTHBSplineBasis<1,double>* basis_ptr = static_cast< gismo::gsTHBSplineBasis<1,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTHBSpline<1,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSpline2(void* basis, double* data, int rows, int cols)
{
    gismo::gsTHBSplineBasis<2,double>* basis_ptr = static_cast< gismo::gsTHBSplineBasis<2,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTHBSpline<2,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSpline3(void* basis, double* data, int rows, int cols)
{
    gismo::gsTHBSplineBasis<3,double>* basis_ptr = static_cast< gismo::gsTHBSplineBasis<3,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTHBSpline<3,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSpline4(void* basis, double* data, int rows, int cols)
{
    gismo::gsTHBSplineBasis<4,double>* basis_ptr = static_cast< gismo::gsTHBSplineBasis<4,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gismo::gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gismo::gsTHBSpline<4,double>(*basis_ptr,coefs);
}
