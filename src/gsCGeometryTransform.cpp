
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsCMatrix.h>
#include <gsCInterface/gsCGeometry.h>
#include <gsCInterface/gsCGeometryTransform.h>
#include <gsCInterface/gsCKnotVector.h>
#include <gsCInterface/gsCBasis.h>
#include <gsCInterface/gsMacros.h>

#ifdef __cplusplus
extern "C"
{
#endif

    GISMO_EXPORT gsCGeometryTransform * gsGeometryTransform_create(gsCGeometry* g, gsCMatrix * m,
                                                                   gsCVector * v)
    {
        auto * g_ptr = RICAST_G(g);
        auto * mm = RICAST_M(m);
        auto * vv = RICAST_V(v);  
        return RICAST_CG(new gismo::gsGeometryTransform<double>(g_ptr,*mm, *vv));
    }

    
#ifdef __cplusplus
}
#endif
