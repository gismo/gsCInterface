
#ifdef __cplusplus
extern "C"
{
#endif
    GISMO_EXPORT gsCMultiBasis * gsMultiBasis_create(gsCMultiPatch* mp);

    GISMO_EXPORT gsCBasis * gsMultiBasis_basis(gsCMultiBasis * mp, int i);

    GISMO_EXPORT void gsMultiBasis_delete(gsCMultiBasis * mp);

#ifdef __cplusplus
}
#endif
