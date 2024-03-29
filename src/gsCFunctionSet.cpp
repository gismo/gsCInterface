#include <gismo.h>
#include <gsCInterface/gsCFunctionSet.h>
#include <gsCInterface/gsCMemory.h>


GISMO_EXPORT void gsFunctionSet_print(gsCFunctionSet * fs)
{
    reinterpret_cast<gismo::gsFunctionSet<double>*>(fs)->print(gsInfo);
}

GISMO_EXPORT int domainDim(void* object)
{
    gismo::gsFunctionSet<double>* geom = static_cast< gismo::gsFunctionSet<>* >(object);
    return geom->domainDim();
}


GISMO_EXPORT int targetDim(void* object)
{
    gismo::gsFunctionSet<>* geom = static_cast< gismo::gsFunctionSet<>* >(object);
    return geom->targetDim();
}

// gs_eval_geometry using new double[]
GISMO_EXPORT void eval_into(void* object,
                                        double* data,
                                        int rows,
                                        int cols,
                                        double* out_data,
                                        int len_data,
                                        int* out_rows,
                                        int* out_cols)
{
    gismo::gsFunctionSet<>* fun_ptr = static_cast< gismo::gsFunctionSet<>* >(object);
    gismo::gsAsConstMatrix<> params(data, rows, cols);
    gismo::gsMatrix<> result = fun_ptr->eval(params);
    *out_rows = result.rows();
    *out_cols = result.cols();
    GISMO_ENSURE(len_data >= result.size(),
                 "gs_eval_geometry_mem: len_data=" << len_data << " less than size="
                 << result.size() << " (rows=" << result.rows() << ", cols=" << result.cols() );
    copy_matrix_c_array(result, out_data, len_data);
}
