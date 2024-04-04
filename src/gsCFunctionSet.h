
#ifdef __cplusplus
extern "C"
{
#endif
    GISMO_EXPORT void gsFunctionSet_delete(gsCFunctionSet * ptr);

    GISMO_EXPORT void gsFunctionSet_print(gsCFunctionSet * fs);
    GISMO_EXPORT int gsFunctionSet_domainDim(gsCFunctionSet * fs);
    GISMO_EXPORT int gsFunctionSet_targetDim(gsCFunctionSet * fs);

    GISMO_EXPORT gsCBasis * gsFunctionSet_basis(gsCFunctionSet * fs, int i);

    GISMO_EXPORT void gsFunctionSet_eval_into(gsCFunctionSet * fs,
                                              gsCMatrix * u,
                                              gsCMatrix * result);

    GISMO_EXPORT void gsFunctionSet_deriv_into(gsCFunctionSet * fs,
                                               gsCMatrix * u,
                                               gsCMatrix * result);

    GISMO_EXPORT void gsFunctionSet_normal_into(gsCFunctionSet * fs,
                                                gsCMatrix * u,
                                                gsCMatrix * result);

#ifdef __cplusplus
}
#endif
