#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMemory.h>
#include <gsCInterface/gsMacros.h>

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCBoundaryConditions * gsBoundaryConditions_create()
{
    return RICAST_CBC(new gismo::gsBoundaryConditions<double>());
}

GISMO_EXPORT void gsBoundaryConditions_addCondition(gsCBoundaryConditions * bc,
                                                    int patch,
                                                    int side,
                                                    int ctype,
                                                    gsCFunctionSet * fun,
                                                    int unknown,
                                                    int component,
                                                    bool parametric)
{
    gismo::boxSide bside(side);
    gsFunctionSet<double> * f_ptr = RICAST_F(fun);
    RICAST_BC(bc)->addCondition(patch,
                                bside,
                                (gismo::condition_type::type)ctype,
                                f_ptr,
                                unknown,
                                component,
                                parametric);
}

GISMO_EXPORT void gsBoundaryConditions_addCornerValue(gsCBoundaryConditions * bc,
                                                      int corner,
                                                      double value,
                                                      int patch,
                                                      int unknown,
                                                      int component)
{
    gismo::boxCorner bcorner(corner);
    RICAST_BC(bc)->addCornerValue(bcorner, value, patch, unknown, component);
}

GISMO_EXPORT void gsBoundaryConditions_setGeoMap(gsCBoundaryConditions * bc, gsCFunctionSet * gm)
{
    RICAST_BC(bc)->setGeoMap(*RICAST_F(gm));
}

GISMO_EXPORT void gsBoundaryConditions_print(gsCBoundaryConditions * bc)
{
    RICAST_BC(bc)->print(gsInfo);
}

GISMO_EXPORT void gsBoundaryConditions_delete(gsCBoundaryConditions * bc)
{
    delete RICAST_BC(bc);
}

#ifdef __cplusplus
}
#endif
