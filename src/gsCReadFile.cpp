#include <gismo.h>
#include <gsCInterface/gsCReadFile.h>

GISMO_EXPORT void* gsCReadFile(char* filename)
{
    gsInfo << "Loading file: " << filename << std::endl;

    void* result = NULL;

    gismo::gsFileData<> data(filename);
    if      ( data.hasAny< gismo::gsGeometry<>  >() )
    {
        gismo::gsGeometry<>::uPtr ptr = data.getAnyFirst< gismo::gsGeometry<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gismo::gsBasis<>  >() )
    {
        gismo::gsBasis<>::uPtr ptr = data.getAnyFirst< gismo::gsBasis<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gismo::gsMultiPatch<>  >() )
    {
        gismo::gsMultiPatch<>::uPtr ptr = data.getAnyFirst< gismo::gsMultiPatch<>  >();
        result = ptr.release();
    }
    else if ( data.hasAny< gismo::gsMultiBasis<>  >() )
    {
        gismo::gsMultiBasis<>::uPtr ptr = data.getAnyFirst< gismo::gsMultiBasis<>  >();
        result = ptr.release();
    }
    else
    {
        result = NULL;
        std::cout << "File doesn't contain a geometry or a basis." << std::endl;
    }
    return result;
}
