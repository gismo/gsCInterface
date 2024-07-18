
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

    GISMO_EXPORT gsCGeometry* gsNurbs_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTensorNurbs2_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTensorNurbs3_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTensorNurbs4_create(gsCBasis* b, gsCMatrix * coef);

    GISMO_EXPORT gsCGeometry* gsTHBSpline1_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTHBSpline2_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTHBSpline3_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsTHBSpline4_create(gsCBasis* b, gsCMatrix * coef);

    GISMO_EXPORT gsCGeometry* gsHBSpline1_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsHBSpline2_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsHBSpline3_create(gsCBasis* b, gsCMatrix * coef);
    GISMO_EXPORT gsCGeometry* gsHBSpline4_create(gsCBasis* b, gsCMatrix * coef);

    GISMO_EXPORT gsCBasis* gsGeometry_basis(gsCGeometry * g);
    
    GISMO_EXPORT void gsGeometry_coefs_into(gsCGeometry * g, gsCMatrix * coef);


    GISMO_EXPORT void gsGeometry_uniformRefine(gsCGeometry * b, int numKnots, int mul, int dir);
    GISMO_EXPORT void gsGeometry_refineElements(gsCGeometry * b, int * boxData, int boxSize);

    GISMO_EXPORT void gsGeometry_recoverPoints(gsCGeometry * g, gsCMatrix * uv, gsCMatrix * xyz,
                                                int k, double accuracy);
    GISMO_EXPORT void gsGeometry_recoverPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                                    gsCVectorInt * sz, gsCMatrix * xyz,
                                                    gsCMatrix * uv, int c, double accuracy);

    GISMO_EXPORT void gsGeometry_invertPointGrid(gsCGeometry * g, gsCVector * a, gsCVector * b,
                                       gsCVectorInt * sz,  gsCMatrix * result, double accuracy);
    GISMO_EXPORT void gsGeometry_invertPoints(gsCGeometry * g, gsCMatrix * points, gsCMatrix * result,
                                    double accuracy);

    GISMO_EXPORT void gsGeometry_normal_into(gsCGeometry * fs,
                                 gsCMatrix * u,
                                 gsCMatrix * result);


    GISMO_EXPORT double gsGeometry_closestPointTo(gsCGeometry * fs,
                                       gsCMatrix * pt,
                                       gsCMatrix * result,
                                       double accuracy);


#ifdef __cplusplus
}
#endif
