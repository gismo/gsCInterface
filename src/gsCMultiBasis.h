
#ifdef __cplusplus
extern "C"
{
#endif
    GISMO_EXPORT gsCMultiBasis * gsMultiBasis_create(gsCMultiPatch* mp);

    GISMO_EXPORT void gsMultiBasis_addBasis(gsCMultiBasis* mp, gsCGeometry* geo);

    GISMO_EXPORT gsCBasis * gsMultiBasis_basis(gsCMultiBasis * mp, int i);

    GISMO_EXPORT void gsMultiBasis_delete(gsCMultiBasis * mb);

#ifdef __cplusplus
}
#endif
