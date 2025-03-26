
#include <gismo.h>
#include <gsCInterface/gsCTypes.h>
#include <gsCInterface/gsMacros.h>
#include <gsCInterface/gsCQuadRule.h>

using namespace gismo;

#ifdef __cplusplus
extern "C"
{
#endif

GISMO_EXPORT gsCQuadRule* gsQuadrature_get(gsCBasis * basis, gsCOptionList* options, int fixDir)
{
    auto * basis_ptr = RICAST_B(basis);
    auto * options_ptr = reinterpret_cast<gsOptionList*>(options);
    return reinterpret_cast<gsCQuadRule*>(gsQuadrature::getPtr(*basis_ptr, *options_ptr, fixDir).release());
}

GISMO_EXPORT gsCQuadRule* gsGaussRule_create(int d, int* numNodes, int digits)
{
    std::vector<int> nodes(numNodes, numNodes + d);
    return reinterpret_cast<gsCQuadRule*>(new gsGaussRule<double>(gsAsVector<int>(nodes), digits));
}

GISMO_EXPORT gsCQuadRule* gsLobattoRule_create(int d, int* numNodes, int digits)
{
    std::vector<int> nodes(numNodes, numNodes + d);
    return reinterpret_cast<gsCQuadRule*>(new gsLobattoRule<double>(gsAsVector<int>(nodes), digits));
}

GISMO_EXPORT void gsQuadRule_delete(gsCQuadRule * qr)
{
    delete reinterpret_cast<gsQuadRule<double>*>(qr);
}

GISMO_EXPORT int gsQuadRule_numNodes(gsCQuadRule * qr)
{
    return reinterpret_cast<gsQuadRule<double>*>(qr)->numNodes();
}

GISMO_EXPORT int gsQuadRule_dim(gsCQuadRule * qr)
{
    return reinterpret_cast<gsQuadRule<double>*>(qr)->dim();
}

GISMO_EXPORT void gsQuadRule_mapTo(gsCQuadRule* qr, gsCVector* lower, gsCVector* upper, gsCMatrix* nodes, gsCVector* weights)
{
    reinterpret_cast<gsQuadRule<double>*>(qr)->mapTo(*RICAST_V(lower), *RICAST_V(upper), *RICAST_M(nodes), *RICAST_V(weights));
}

GISMO_EXPORT void gsQuadRule_mapToScalar(gsCQuadRule* qr, double startVal, double endVal, gsCMatrix* nodes, gsCVector* weights)
{
    reinterpret_cast<gsQuadRule<double>*>(qr)->mapTo(startVal, endVal, *RICAST_M(nodes), *RICAST_V(weights));
}


#ifdef __cplusplus
}
#endif