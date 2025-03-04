#include <gsCore/gsLinearAlgebra.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCSparseMatrix.h>

GISMO_EXPORT gsCSparseMatrix * gsSparseMatrix_create(void)
{ return RICAST_CSM(new gismo::gsSparseMatrix<double>()); }

GISMO_EXPORT void gsSparseMatrix_delete(gsCSparseMatrix * m)
{ delete RICAST_SM(m); }

GISMO_EXPORT void gsSparseMatrix_print(gsCSparseMatrix * m)
{ gsInfo<<*RICAST_SM(m); }

// GISMO_EXPORT double * gsSparseMatrix_data(gsCSparseMatrix * m)
// { return RICAST_SM(m)->data(); }

GISMO_EXPORT void gsSparseMatrix_setFromTriplets(gsCSparseMatrix * m, gsCVectorInt * rows, gsCVectorInt * cols, gsCVector * values)
{
    auto * R = RICAST_Vi(rows);
    auto * C = RICAST_Vi(cols);
    auto * V = RICAST_V(values);

    GISMO_ENSURE(R->size() == C->size() && R->size() == V->size(), "Input vectors must have the same size.");

    gismo::gsSparseEntries<double> entries;
    entries.reserve(R->size());
    for (int i = 0; i < R->size(); i++)
        entries.add((*R)[i], (*C)[i], (*V)[i]);

    RICAST_SM(m)->resize(R->size(), C->size());
    RICAST_SM(m)->setFrom(entries);
}

GISMO_EXPORT void gsSparseMatrix_intoTriplets(gsCSparseMatrix * m, gsCVectorInt * rows, gsCVectorInt * cols, gsCVector * vals)
{
    auto * sm = RICAST_SM(m);
    auto * R = RICAST_Vi(rows);
    auto * C = RICAST_Vi(cols);
    auto * V = RICAST_V(vals);

    R->resize(sm->nonZeros());
    C->resize(sm->nonZeros());
    V->resize(sm->nonZeros());
    auto R_it = R->begin();
    auto C_it = C->begin();
    auto V_it = V->begin();

    for (int i = 0; i!=sm->outerSize(); i++)
    {
        for (typename gismo::gsSparseMatrix<double>::InnerIterator it(*sm,i); it;
                    ++it, ++R_it, ++C_it, ++V_it)
        {
            *R_it = it.row();
            *C_it = it.col();
            *V_it = it.value();
        }
    }
}

GISMO_EXPORT int gsSparseMatrix_rows(gsCSparseMatrix * m)
{ return RICAST_SM(m)->rows(); }

GISMO_EXPORT int gsSparseMatrix_cols(gsCSparseMatrix * m)
{ return RICAST_SM(m)->cols(); }

GISMO_EXPORT int gsSparseMatrix_nnz(gsCSparseMatrix * m)
{ return RICAST_SM(m)->nonZeros(); }