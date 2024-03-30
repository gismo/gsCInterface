
#ifdef __cplusplus
extern "C"
{
#endif

    GISMO_EXPORT gsCVector * gsVector_create(void);
    GISMO_EXPORT gsCVector * gsVector_create_rc (int rows, int cols);
    GISMO_EXPORT gsCVector * gsVector_create_rcd(int rows, int cols, double * data);
    GISMO_EXPORT void gsVector_delete(gsCVector * m);
    GISMO_EXPORT void gsVector_print(gsCVector * m);
    GISMO_EXPORT double * gsVector_data(gsCVector * m);

    GISMO_EXPORT void gsVector_transposeInPlace(gsCVector * m);
    GISMO_EXPORT int gsVector_rows(gsCVector * m);
    GISMO_EXPORT int gsVector_cols(gsCVector * m);
    GISMO_EXPORT void gsVector_setZero(gsCVector * m);

#ifdef __cplusplus
}
#endif
