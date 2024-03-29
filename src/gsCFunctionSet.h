
#ifdef __cplusplus
extern "C"
{
#endif
    struct gsCFunctionSet; // Opaque type that we'll use as a handle
    typedef struct gsCFunctionSet gsCFunctionSet;

    GISMO_EXPORT void gsFunctionSet_print(gsCFunctionSet * fs);
    GISMO_EXPORT int domainDim(void* object);
    
    GISMO_EXPORT int targetDim(void* object);
    
    GISMO_EXPORT void eval_into(void* object,
                                double* data,
                                int rows,
                                int cols,
                                double* out_data,
                                int len_data,
                                int* out_rows,
                                int* out_cols);
    
#ifdef __cplusplus
}
#endif
