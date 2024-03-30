
#ifdef __cplusplus
extern "C"
{
#endif

#   define gsBasis_print gsFunctionSet_print
#   define gsBasis_delete gsFunctionSet_delete

    GISMO_EXPORT gsCBasis* gsBSplineBasis_create(gsCKnotVector* knots);

    GISMO_EXPORT void* gsTensorBSplineBasis2(gsCKnotVector* KV1, gsCKnotVector* KV2);
    GISMO_EXPORT void* gsTensorBSplineBasis3(gsCKnotVector* KV1, gsCKnotVector* KV2, gsCKnotVector* KV3);
    GISMO_EXPORT void* gsTensorBSplineBasis4(gsCKnotVector* KV1, gsCKnotVector* KV2, gsCKnotVector* KV3, gsCKnotVector* KV4);

    GISMO_EXPORT void* THBSplineBasis1(void* basis);
    GISMO_EXPORT void* THBSplineBasis2(void* basis);
    GISMO_EXPORT void* THBSplineBasis3(void* basis);
    GISMO_EXPORT void* THBSplineBasis4(void* basis);

    GISMO_EXPORT gsCBasis * component(gsCBasis * b, int dir);
    GISMO_EXPORT int degree(gsCBasis * b, int dir);
    GISMO_EXPORT int numElements(gsCBasis * b);
    
#ifdef __cplusplus
}
#endif
