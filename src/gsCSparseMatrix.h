
#ifdef __cplusplus
extern "C"
{
#endif

    GISMO_EXPORT gsCSparseMatrix * gsSparseMatrix_create(void);                     // create matrix object

    GISMO_EXPORT void gsSparseMatrix_delete(gsCSparseMatrix * m);
    GISMO_EXPORT void gsSparseMatrix_print(gsCSparseMatrix * m);
    // GISMO_EXPORT double* gsSparseMatrix_data(gsCSparseMatrix * m);   // get pointer to matrix data

    GISMO_EXPORT void gsSparseMatrix_setFromTriplets(gsCSparseMatrix * m, gsCVectorInt * rows, gsCVectorInt * cols, gsCVector * values);
    GISMO_EXPORT void gsSparseMatrix_intoTriplets(gsCSparseMatrix * m, gsCVectorInt * rows, gsCVectorInt * cols, gsCVector * vals);

    GISMO_EXPORT int gsSparseMatrix_rows(gsCSparseMatrix * m);
    GISMO_EXPORT int gsSparseMatrix_cols(gsCSparseMatrix * m);
    GISMO_EXPORT int gsSparseMatrix_nnz(gsCSparseMatrix * m);

#ifdef __cplusplus
}
#endif
