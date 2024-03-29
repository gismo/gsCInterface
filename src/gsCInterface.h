
#ifndef GSCINTERFACE_H
#define GSCINTERFACE_H

#include <gsCore/gsExport.h>


extern "C"
{
    GISMO_EXPORT void print(void* object);

    GISMO_EXPORT void* read(char* filename);
    
    GISMO_EXPORT int domainDim(void* object);
    
    GISMO_EXPORT int targetDim(void* object);
    
    GISMO_EXPORT void eval_into(void* object,
                                double* data,
                                int rows,
                                int cols,
                                double* out_data,
                                int len_data,
                                int* out_rows,
                                int* out_cols);

    GISMO_EXPORT void* knotVector(double* knots, int size);

    GISMO_EXPORT void* bsplineBasis(void* knots);
    GISMO_EXPORT void* tensorBSplineBasis2(void* KV1, void* KV2);
    GISMO_EXPORT void* tensorBSplineBasis3(void* KV1, void* KV2, void* KV3);
    GISMO_EXPORT void* tensorBSplineBasis4(void* KV1, void* KV2, void* KV3, void* KV4);

    GISMO_EXPORT void* bspline(void* basis, double* data, int rows, int cols);
    GISMO_EXPORT void* tensorBSpline2(void* basis, double* data, int rows, int cols);
    GISMO_EXPORT void* tensorBSpline3(void* basis, double* data, int rows, int cols);
    GISMO_EXPORT void* tensorBSpline4(void* basis, double* data, int rows, int cols);

    GISMO_EXPORT void* THBSplineBasis1(void* basis);
    GISMO_EXPORT void* THBSplineBasis2(void* basis);
    GISMO_EXPORT void* THBSplineBasis3(void* basis);
    GISMO_EXPORT void* THBSplineBasis4(void* basis);

    GISMO_EXPORT void* THBSpline1(void* basis, double* data, int rows, int cols);
    GISMO_EXPORT void* THBSpline2(void* basis, double* data, int rows, int cols);
    GISMO_EXPORT void* THBSpline3(void* basis, double* data, int rows, int cols);
    GISMO_EXPORT void* THBSpline4(void* basis, double* data, int rows, int cols);

#endif // GSCINTERFACE_H
}
