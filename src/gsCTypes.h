// Opaque types that we use as a handles
#ifdef __cplusplus
extern "C"
{
#endif
    struct gsCMatrix;
    typedef struct gsCMatrix gsCMatrix;

    struct gsCMatrixInt;
    typedef struct gsCMatrixInt gsCMatrixInt;

    struct gsCVector;
    typedef struct gsCVector gsCVector;

    struct gsCVectorInt;
    typedef struct gsCVectorInt gsCVectorInt;

    struct gsCFunctionSet; // Opaque type that we use as a handle
    typedef struct gsCFunctionSet gsCFunctionSet;

    typedef struct gsCFunctionSet gsCMultiPatch;
    typedef struct gsCFunctionSet gsCBasis;
    typedef struct gsCFunctionSet gsCGeometry;
    typedef struct gsCFunctionSet gsCGeometryTransform;

    struct gsCKnotVector;
    typedef struct gsCKnotVector gsCKnotVector;

    //struct gsCGridIteratorCube; 
    //typedef struct gsCGridIteratorCube gsCGridIteratorCube;
    
#ifdef __cplusplus
}
#endif
