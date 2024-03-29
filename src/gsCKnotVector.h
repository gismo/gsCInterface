
#ifdef __cplusplus
extern "C"
{
#endif

    struct gsCKnotVector; // Opaque type that we'll use as a handle
    typedef struct gsCKnotVector gsCKnotVector;

    GISMO_EXPORT gsCKnotVector * gsKnotVector_create(double* knots, int size);
    GISMO_EXPORT void gsKnotVector_delete(gsCKnotVector * kv);
    GISMO_EXPORT void gsKnotVector_print(gsCKnotVector * kv);

#ifdef __cplusplus
}
#endif
