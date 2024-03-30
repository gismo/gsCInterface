
#ifdef __cplusplus
extern "C"
{
#endif
    struct gsCFunctionSet; // Opaque type that we use as a handle
    typedef struct gsCFunctionSet gsCFunctionSet;

    GISMO_EXPORT void gsFunctionSet_delete(gsCFunctionSet * ptr);

    GISMO_EXPORT void gsFunctionSet_print(gsCFunctionSet * fs);
    GISMO_EXPORT int domainDim(gsCFunctionSet * fs);
    GISMO_EXPORT int targetDim(gsCFunctionSet * fs);

    GISMO_EXPORT void eval_into(gsCFunctionSet * fs,
                                gsCMatrix * u,
                                gsCMatrix * result);

    GISMO_EXPORT void deriv_into(gsCFunctionSet * fs,
                                 gsCMatrix * u,
                                 gsCMatrix * result);

#ifdef __cplusplus
}
#endif
