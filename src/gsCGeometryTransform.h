
#ifdef __cplusplus
extern "C"
{
#endif

#   define gsGeometryTransofrm_print gsFunctionSet_print
#   define gsGeometryTransofrm_delete gsFunctionSet_delete
    
    GISMO_EXPORT gsCGeometryTranform* gsGeometrtTransform_create(gsCBasis* b, gsCMatrix * m,
                                                                 gsCVector * v);
    
#ifdef __cplusplus
}
#endif
