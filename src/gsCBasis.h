
#ifdef __cplusplus
extern "C"
{
#endif

#   define gsBasis_print gsFunctionSet_print
#   define gsBasis_delete gsFunctionSet_delete

    GISMO_EXPORT gsCBasis* gsBSplineBasis_create(gsCKnotVector* knots);

    GISMO_EXPORT gsCBasis* gsTensorBSplineBasis2_create(gsCKnotVector* KV1, gsCKnotVector* KV2);
    GISMO_EXPORT gsCBasis* gsTensorBSplineBasis3_create(gsCKnotVector* KV1, gsCKnotVector* KV2, gsCKnotVector* KV3);
    GISMO_EXPORT gsCBasis* gsTensorBSplineBasis4_create(gsCKnotVector* KV1, gsCKnotVector* KV2, gsCKnotVector* KV3, gsCKnotVector* KV4);

    GISMO_EXPORT gsCBasis* THBSplineBasis1_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* THBSplineBasis2_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* THBSplineBasis3_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* THBSplineBasis4_create(gsCBasis* basis);

    GISMO_EXPORT void gsBasis_active_into(gsCBasis * b, gsCMatrix * u, gsCMatrixInt * result);

    GISMO_EXPORT gsCBasis * gsBasis_component(gsCBasis * b, int dir);
    GISMO_EXPORT int gsBasis_degree(gsCBasis * b, int dir);
    GISMO_EXPORT int gsBasis_numElements(gsCBasis * b);
    GISMO_EXPORT int gsBasis_size(gsCBasis * b);
    
    GISMO_EXPORT void gsBasis_uniformRefine(gsCBasis * b, int numKnots, int mul, int dir);
    GISMO_EXPORT void gsBasis_refineElements(gsCBasis * b, int * boxData, int boxSize);

#ifdef __cplusplus
}
#endif
