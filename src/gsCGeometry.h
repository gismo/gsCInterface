
#ifdef __cplusplus
extern "C"
{
#endif

#   define gsGeometry_print gsFunctionSet_print
#   define gsGeometry_delete gsFunctionSet_delete
#   define gsBSpline_delete gsFunctionSet_delete
    
    GISMO_EXPORT gsCGeometry* gsBSpline_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTensorBSpline2_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTensorBSpline3_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTensorBSpline4_create(gsCBasis* b, gsCMatrix * coef);

    GISMO_EXPORT gsCGeometry* gsTHBSpline1_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTHBSpline2_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTHBSpline3_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTHBSpline4_create(gsCBasis* b, gsCMatrix * coef);

    GISMO_EXPORT gsCBasis* basis(gsCGeometry * g);
    
    GISMO_EXPORT void recoverPoints(gsCGeometry * g, gsCMatrix * uv, int k, double accuracy);
    GISMO_EXPORT void recoverPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                       gsCMatrix * xyz, gsCMatrix * uv, int c, double accuracy);

#ifdef __cplusplus
}
#endif
