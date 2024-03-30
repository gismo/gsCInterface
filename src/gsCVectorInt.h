
#ifdef __cplusplus
extern "C"
{
#endif

    GISMO_EXPORT gsCVectorInt * gsVectorInt_create(void);
    GISMO_EXPORT gsCVectorInt * gsVectorInt_create_rc (int rows, int cols);
    GISMO_EXPORT gsCVectorInt * gsVectorInt_create_rcd(int rows, int cols, double * data);

    GISMO_EXPORT void gsVectorInt_delete(gsCVectorInt * m);
    GISMO_EXPORT void gsVectorInt_print(gsCVectorInt * m);
    GISMO_EXPORT int * gsVectorInt_data(gsCVectorInt * m);

    GISMO_EXPORT void gsVectorInt_transposeInPlace(gsCVectorInt * m);
    GISMO_EXPORT int gsVectorInt_rows(gsCVectorInt * m);
    GISMO_EXPORT int gsVectorInt_cols(gsCVectorInt * m);
    GISMO_EXPORT void gsVectorInt_setZero(gsCVectorInt * m);
    
#ifdef __cplusplus
}
#endif
