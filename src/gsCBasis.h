
#ifdef __cplusplus
extern "C"
{
#endif

    #include<stdbool.h>

    GISMO_EXPORT gsCBasis * gsBasis_read(char* filename);
    GISMO_EXPORT void       gsBasis_write(gsCBasis * obj, char* filename);

#   define gsBasis_print gsFunctionSet_print
#   define gsBasis_delete gsFunctionSet_delete

    GISMO_EXPORT gsCBasis* gsBSplineBasis_create(gsCKnotVector* knots);

    GISMO_EXPORT gsCBasis* gsTensorBSplineBasis2_create(gsCKnotVector* KV1, gsCKnotVector* KV2);
    GISMO_EXPORT gsCBasis* gsTensorBSplineBasis3_create(gsCKnotVector* KV1, gsCKnotVector* KV2, gsCKnotVector* KV3);
    GISMO_EXPORT gsCBasis* gsTensorBSplineBasis4_create(gsCKnotVector* KV1, gsCKnotVector* KV2, gsCKnotVector* KV3, gsCKnotVector* KV4);

    GISMO_EXPORT gsCBasis* gsTHBSplineBasis1_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* gsTHBSplineBasis2_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* gsTHBSplineBasis3_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* gsTHBSplineBasis4_create(gsCBasis* basis);

    GISMO_EXPORT gsCBasis* gsHBSplineBasis1_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* gsHBSplineBasis2_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* gsHBSplineBasis3_create(gsCBasis* basis);
    GISMO_EXPORT gsCBasis* gsHBSplineBasis4_create(gsCBasis* basis);

    //
    // Methods, gsBasis
    //
    GISMO_EXPORT gsCBasis* gsBasis_clone(gsCBasis * b);

    GISMO_EXPORT void gsBasis_active_into(gsCBasis * b, gsCMatrix * u, gsCMatrixInt * result);

    GISMO_EXPORT void gsBasis_evalSingle_into(gsCBasis * b, int i, gsCMatrix * u, gsCMatrix * result);
    GISMO_EXPORT void gsBasis_derivSingle_into(gsCBasis * b, int i, gsCMatrix * u, gsCMatrix * result);
    GISMO_EXPORT void gsBasis_deriv2Single_into(gsCBasis * b, int i, gsCMatrix * u, gsCMatrix * result);

    GISMO_EXPORT gsCBasis * gsBasis_component(gsCBasis * b, int dir);
    GISMO_EXPORT int gsBasis_degree(gsCBasis * b, int dir);
    GISMO_EXPORT int gsBasis_numElements(gsCBasis * b);
    GISMO_EXPORT int gsBasis_dim(gsCBasis * b);
    GISMO_EXPORT int gsBasis_size(gsCBasis * b);
    GISMO_EXPORT gsCMatrix* gsBasis_support(gsCBasis * b, int i);

    GISMO_EXPORT void gsBasis_uniformRefine(gsCBasis * b, int numKnots, int mul, int dir);
    GISMO_EXPORT void gsBasis_refineElements(gsCBasis * b, int * boxData, int boxSize);
    GISMO_EXPORT void gsBasis_refine(gsCBasis * b, gsCMatrix * boxes, int refExt);

    GISMO_EXPORT void gsBasis_degreeElevate(gsCBasis * b, int i, int dir);

    GISMO_EXPORT void gsBasis_boundary_into(gsCBasis * b, int side, gsCMatrixInt * result);
    GISMO_EXPORT void gsBasis_boundaryOffset_into(gsCBasis * b, int side, int offset, gsCMatrixInt * result);

    GISMO_EXPORT void gsBasis_elements_into(gsCBasis * b, gsCMatrix*);
    GISMO_EXPORT void gsBasis_elementsBdr_into(gsCBasis * b, int, gsCMatrix*);

    GISMO_EXPORT void gsHTensorBasis_elements_into(gsCBasis * b, bool getKnotBoxes,
                                                                 bool getIndexBoxes,
                                                                 bool getLevels,
                                                                 gsCMatrix*    knotBoxes,
                                                                 gsCMatrixInt* indexBoxes,
                                                                 gsCVectorInt* levels);

    // TODO:
    // - DegreeElevate

    //
    // Methods, Other
    //
    GISMO_EXPORT gsCKnotVector * gsBSplineBasis_knots(gsCBasis * b);
    GISMO_EXPORT gsCKnotVector * gsTensorBSplineBasis_knots(gsCBasis * b, int dir);


    GISMO_EXPORT int gsHTensorBasis_numLevels(gsCBasis * b);
    GISMO_EXPORT int gsHTensorBasis_maxLevel(gsCBasis * b);
    GISMO_EXPORT int gsHTensorBasis_levelOf(gsCBasis * b, int i);
    GISMO_EXPORT int gsHTensorBasis_getLevelAtPoint(gsCBasis * b, gsCMatrix * Pt);
    GISMO_EXPORT gsCBasis * gsHTensorBasis_tensorLevel(gsCBasis * b, int l);
    GISMO_EXPORT void gsHTensorBasis_treeLeafSize(gsCBasis * b);
    GISMO_EXPORT void gsHTensorBasis_treePrintLeaves(gsCBasis * b);


#ifdef __cplusplus
}
#endif
