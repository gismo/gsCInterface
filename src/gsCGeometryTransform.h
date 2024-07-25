
#ifdef __cplusplus
extern "C"
{
#endif

#   define gsGeometryTransofrm_print gsFunctionSet_print
#   define gsGeometryTransofrm_delete gsFunctionSet_delete

    GISMO_EXPORT gsCGeometryTransform * gsGeometryTransform_create(gsCGeometry* g, gsCMatrix * m,
                                                                   gsCVector * v);
    
#ifdef __cplusplus
}
#endif
