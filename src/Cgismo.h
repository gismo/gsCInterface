#ifndef CGISMO_H
#define CGISMO_H

#include <gsCore/gsExport.h>
#include <gsCInterface/gsCTypes.h>

#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCVector.h>
#include <gsCInterface/gsCVectorInt.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsCFunctionSet.h>
#include <gsCInterface/gsCBasis.h>
#include <gsCInterface/gsCGeometry.h>
#include <gsCInterface/gsCio.h>

//
// Function Overloads
//
#define print(X) _Generic((X),                                   \
                          gsCKnotVector *: gsKnotVector_print,   \
                          gsCFunctionSet *: gsFunctionSet_print, \
                          gsCMatrix *: gsMatrix_print)(X)

#define rows(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_rows,        \
                         gsCVectorInt *: gsVectorInt_rows,     \
                         gsCMatrix *   : gsMatrix_rows)(X)

#define cols(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_cols,        \
                         gsCVectorInt *: gsVectorInt_cols,     \
                         gsCMatrix *   : gsMatrix_cols)(X)

#define data(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_data,        \
                         gsCVectorInt *: gsVectorInt_data,     \
                         gsCMatrix *   : gsMatrix_data)(X)

#define transposeInPlace(X) _Generic((X),                               \
                                     gsCVector *   : gsVector_transposeInPlace, \
                                     gsCVectorInt *: gsVectorInt_transposeInPlace, \
                                     gsCMatrix *   : gsMatrix_transposeInPlace)(X)

#define setZero(X) _Generic((X),                                  \
                         gsCVector *   : gsVector_setZero,        \
                         gsCVectorInt *: gsVectorInt_setZero,     \
                         gsCMatrix *   : gsMatrix_setZero)(X)

#define destroy(X) _Generic((X),                                        \
                            gsCFunctionSet * : gsFunctionSet_delete,    \
                            gsCKnotVector *  : gsKnotVector_delete,     \
                            gsCVector *      : gsVector_delete,         \
                            gsCVectorInt *   : gsVectorInt_delete,      \
                            gsCMatrix *      : gsMatrix_delete)(X)

#endif // CGISMO_H
