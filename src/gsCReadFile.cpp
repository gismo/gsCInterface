#include <gismo.h>
#include <gsCInterface/gsCReadFile.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif
GISMO_EXPORT void* gsCReadFile(char* filename)
{
    gsInfo << "[G+Smo] Loading file: " << filename << std::endl;

    void* result = NULL;

    gsFileData<> data(filename);
    if      ( data.hasAny< gsGeometry<>  >() )
    {
        gsGeometry<>::uPtr ptr = data.getAnyFirst< gsGeometry<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gsBasis<>  >() )
    {
        gsBasis<>::uPtr ptr = data.getAnyFirst< gsBasis<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gsMultiPatch<>  >() )
    {
        gsMultiPatch<>::uPtr ptr = data.getAnyFirst< gsMultiPatch<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gsMultiBasis<>  >() )
    {
        gsMultiBasis<>::uPtr ptr = data.getAnyFirst< gsMultiBasis<>  >();
        result = ptr.release();
    }
    else
    {
        result = NULL;
        std::cout << "File doesn't contain a geometry or a basis." << std::endl;
    }
    return result;
}

#ifdef __cplusplus
}
#endif