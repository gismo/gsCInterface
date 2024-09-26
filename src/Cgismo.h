#ifndef CGISMO_H
#define CGISMO_H

#include <gsCore/gsExport.h>
#include <gsCInterface/gsCTypes.h>

// gsMatrix
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCMatrixInt.h>
#include <gsCInterface/gsCVector.h>
#include <gsCInterface/gsCVectorInt.h>

// gsNurbs
#include <gsCInterface/gsCKnotVector.h>

// gsCore
#include <gsCInterface/gsCFunctionSet.h>
#include <gsCInterface/gsCMultiPatch.h>
#include <gsCInterface/gsCMultiBasis.h>
#include <gsCInterface/gsCBasis.h>
#include <gsCInterface/gsCGeometry.h>
#include <gsCInterface/gsCGeometryTransform.h>
#include <gsCInterface/gsCReadFile.h>
#include <gsCInterface/gsCFunctionExpr.h>

// gsPde
#include <gsCInterface/gsCBoundaryConditions.h>

#ifdef gsModule_ENABLED
#include <gsModule/gsCClass.h>
#endif

//
// Function Overloads
//
#define print(X) _Generic((X),                                   \
                          gsCKnotVector *: gsKnotVector_print,   \
                          gsCFunctionSet *: gsFunctionSet_print, \
                          gsCMultiPatch *: gsMultiPatch_print, \
                          gsCMultiBasis *: gsMultiBasis_print, \
                          gsCMatrix *: gsMatrix_print)(X)

#define rows(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_rows,        \
                         gsCVectorInt *: gsVectorInt_rows,     \
                         gsCMatrix *   : gsMatrix_rows,        \
                         gsCMatrixInt *: gsMatrixInt_rows)(X)

#define cols(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_cols,        \
                         gsCVectorInt *: gsVectorInt_cols,     \
                         gsCMatrix *   : gsMatrix_cols,        \
                         gsCMatrixInt *: gsMatrixInt_cols)(X)

#define data(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_data,        \
                         gsCVectorInt *: gsVectorInt_data,     \
                         gsCMatrix *   : gsMatrix_data,        \
                         gsCMatrixInt *: gsMatrixInt_data)(X)

#define transposeInPlace(X) _Generic((X),                                          \
                                     gsCVector *   : gsVector_transposeInPlace,    \
                                     gsCVectorInt *: gsVectorInt_transposeInPlace, \
                                     gsCMatrix *   : gsMatrix_transposeInPlace,    \
                                     gsCMatrixInt *: gsMatrixInt_transposeInPlace)(X)

#define setZero(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_setZero,        \
                         gsCVectorInt *: gsVectorInt_setZero,     \
                         gsCMatrix *   : gsMatrix_setZero,        \
                         gsCMatrixInt *: gsMatrixInt_setZero)(X)

#define destroy(X) _Generic((X),                                        \
                            gsCFunctionSet * : gsFunctionSet_delete,    \
                            gsCMultiPatch * : gsMultiPatch_delete,    \
                            gsCMultiBasis * : gsMultiBasis_delete,    \
                            gsCKnotVector *  : gsKnotVector_delete,     \
                            gsCVector *      : gsVector_delete,         \
                            gsCVectorInt *   : gsVectorInt_delete,      \
                            gsCMatrixInt *   : gsMatrixInt_delete,      \
                            gsCMatrix *      : gsMatrix_delete)(X)

#endif // CGISMO_H
