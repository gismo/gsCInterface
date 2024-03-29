
#include <gsCore/gsGeometry.h>
#include <gsNurbs/gsBSpline.h>
#include <gsIO/gsFileData.h>
#include <gsHSplines/gsTHBSpline.h>
#include <gsCInterface/gsCHelpers.h>
#include <gsTensor/gsGridIterator.h>

using namespace gismo;

extern "C"
{
#include <gsCInterface/gsCInterface.h>
}

extern "C"
{
GISMO_EXPORT void print(void* object)
{
    gismo::gsFunction<>* geom = static_cast< gismo::gsFunction<>* >(object);
    gsInfo<<*geom<<"\n";
}

GISMO_EXPORT void* read(char* filename)
{
    gsInfo << "Loading file: " << filename << std::endl;

    void* result;

    gsFileData<> data(filename);
    if      ( data.hasAny< gsGeometry<>  >() )
    {
        gsGeometry<>::uPtr ptr = data.getAnyFirst< gsGeometry<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gsBasis<>  >() )
    {
        gsBasis<>::uPtr ptr = data.getAnyFirst< gsBasis<>  >();
        result = ptr.release();
    }
    else
    {
        result = NULL;
        std::cout << "File doesn't contain a geometry or a basis." << std::endl;
    }
    return result;
}

GISMO_EXPORT int domainDim(void* object)
{
    gismo::gsFunction<>* geom = static_cast< gismo::gsFunction<>* >(object);
    return geom->domainDim();
}


GISMO_EXPORT int targetDim(void* object)
{
    gismo::gsFunction<>* geom = static_cast< gismo::gsFunction<>* >(object);
    return geom->targetDim();
}

// gs_eval_geometry using new double[]
GISMO_EXPORT void eval_into(void* object,
                                        double* data,
                                        int rows,
                                        int cols,
                                        double* out_data,
                                        int len_data,
                                        int* out_rows,
                                        int* out_cols)
{
    gsFunction<>* fun_ptr = static_cast< gsFunction<>* >(object);
    gsAsConstMatrix<> params(data, rows, cols);
    gsMatrix<> result = fun_ptr->eval(params);
    *out_rows = result.rows();
    *out_cols = result.cols();
    GISMO_ENSURE(len_data >= result.size(),
                 "gs_eval_geometry_mem: len_data=" << len_data << " less than size="
                 << result.size() << " (rows=" << result.rows() << ", cols=" << result.cols() );
    copy_matrix_c_array(result, out_data, len_data);
}

GISMO_EXPORT void* knotVector(double* knots, int size)
{
    std::vector<double> vec(knots,knots+size);
    return new gsKnotVector<double>(vec);
}

GISMO_EXPORT void* bsplineBasis(void* KV)
{
    gsKnotVector<double>* KV_ptr = static_cast< gsKnotVector<double>* >(KV);
    return new gsBSplineBasis<double>(*KV_ptr);
}

GISMO_EXPORT void* tensorBSplineBasis2(void* KV1, void* KV2)
{
    gsKnotVector<double>* KV1_ptr = static_cast< gsKnotVector<double>* >(KV1);
    gsKnotVector<double>* KV2_ptr = static_cast< gsKnotVector<double>* >(KV2);
    return new gsTensorBSplineBasis<2,double>(*KV1_ptr,*KV2_ptr);
}

GISMO_EXPORT void* tensorBSplineBasis3(void* KV1, void* KV2, void* KV3)
{
    gsKnotVector<double>* KV1_ptr = static_cast< gsKnotVector<double>* >(KV1);
    gsKnotVector<double>* KV2_ptr = static_cast< gsKnotVector<double>* >(KV2);
    gsKnotVector<double>* KV3_ptr = static_cast< gsKnotVector<double>* >(KV3);
    return new gsTensorBSplineBasis<3,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr);
}

GISMO_EXPORT void* tensorBSplineBasis4(void* KV1, void* KV2, void* KV3, void* KV4)
{
    gsKnotVector<double>* KV1_ptr = static_cast< gsKnotVector<double>* >(KV1);
    gsKnotVector<double>* KV2_ptr = static_cast< gsKnotVector<double>* >(KV2);
    gsKnotVector<double>* KV3_ptr = static_cast< gsKnotVector<double>* >(KV3);
    gsKnotVector<double>* KV4_ptr = static_cast< gsKnotVector<double>* >(KV4);
    return new gsTensorBSplineBasis<4,double>(*KV1_ptr,*KV2_ptr,*KV3_ptr,*KV4_ptr);
}

GISMO_EXPORT void* bspline(void* basis, double* data, int rows, int cols)
{
    gsBSplineBasis<double>* basis_ptr = static_cast< gsBSplineBasis<double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsBSpline<double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* tensorBSpline2(void* basis, double* data, int rows, int cols)
{
    gsTensorBSplineBasis<2,double>* basis_ptr = static_cast< gsTensorBSplineBasis<2,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTensorBSpline<2,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* tensorBSpline3(void* basis, double* data, int rows, int cols)
{
    gsTensorBSplineBasis<3,double>* basis_ptr = static_cast< gsTensorBSplineBasis<3,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTensorBSpline<3,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* tensorBSpline4(void* basis, double* data, int rows, int cols)
{
    gsTensorBSplineBasis<4,double>* basis_ptr = static_cast< gsTensorBSplineBasis<4,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTensorBSpline<4,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSplineBasis1(void* basis)
{
    gsTensorBSplineBasis<1,double>* basis_ptr = static_cast< gsTensorBSplineBasis<1,double>* >(basis);
    return new  gsTHBSplineBasis<1,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSplineBasis2(void* basis)
{
    gsTensorBSplineBasis<2,double>* basis_ptr = static_cast< gsTensorBSplineBasis<2,double>* >(basis);
    return new  gsTHBSplineBasis<2,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSplineBasis3(void* basis)
{
    gsTensorBSplineBasis<3,double>* basis_ptr = static_cast< gsTensorBSplineBasis<3,double>* >(basis);
    return new  gsTHBSplineBasis<3,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSplineBasis4(void* basis)
{
    gsTensorBSplineBasis<4,double>* basis_ptr = static_cast< gsTensorBSplineBasis<4,double>* >(basis);
    return new  gsTHBSplineBasis<4,double>(*basis_ptr,false);
}

GISMO_EXPORT void* THBSpline1(void* basis, double* data, int rows, int cols)
{
    gsTHBSplineBasis<1,double>* basis_ptr = static_cast< gsTHBSplineBasis<1,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTHBSpline<1,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSpline2(void* basis, double* data, int rows, int cols)
{
    gsTHBSplineBasis<2,double>* basis_ptr = static_cast< gsTHBSplineBasis<2,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTHBSpline<2,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSpline3(void* basis, double* data, int rows, int cols)
{
    gsTHBSplineBasis<3,double>* basis_ptr = static_cast< gsTHBSplineBasis<3,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTHBSpline<3,double>(*basis_ptr,coefs);
}

GISMO_EXPORT void* THBSpline4(void* basis, double* data, int rows, int cols)
{
    gsTHBSplineBasis<4,double>* basis_ptr = static_cast< gsTHBSplineBasis<4,double>* >(basis);
    GISMO_ENSURE(rows==basis_ptr->size(),"Size mismatch between basis and control points");
    gsAsConstMatrix<double> coefs(data, rows, cols);
    return new gsTHBSpline<4,double>(*basis_ptr,coefs);
}

}
