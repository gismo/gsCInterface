
#ifdef __cplusplus
extern "C"
{
#endif
    GISMO_EXPORT gsCMultiPatch* gsMultiPatch_create();

    GISMO_EXPORT void gsMultiPatch_addPatch(gsCMultiPatch* mp, gsCGeometry* geo);

    GISMO_EXPORT gsCBasis * gsMultiPatch_basis(gsCMultiPatch * mp, int i);

    GISMO_EXPORT gsCGeometry * gsMultiPatch_patch(gsCMultiPatch * mp, int i);

    GISMO_EXPORT void gsMultiPatch_computeTopology(gsCMultiPatch * mp);

    GISMO_EXPORT gsCMultiPatch * gsMultiPatch_read(char* filename);
    GISMO_EXPORT void            gsMultiPatch_write(gsCMultiPatch * obj, char* filename);

#ifdef __cplusplus
}
#endif
