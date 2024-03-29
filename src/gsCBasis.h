
#ifdef __cplusplus
extern "C"
{
#endif
    struct gsCFunctionSet; // Opaque type that we'll use as a handle
    typedef struct gsCFunctionSet gsCBasis;

    GISMO_EXPORT void gsBasis_delete(gsCBasis* object);

    GISMO_EXPORT gsCBasis* gsBSplineBasis_create(gsCKnotVector* knots);
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

#ifdef __cplusplus
}
#endif
