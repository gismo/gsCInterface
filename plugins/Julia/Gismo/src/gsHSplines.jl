
########################################################################
# gsTHBSplineBasis
########################################################################

function THBSplineBasis(basis::Basis)::Basis
    if (domainDim(basis)==1)
        b = ccall((:gsTHBSplineBasis1_create,libgismo),Ptr{gsCBasis},(Ptr{gsCBasis},),basis.ptr)
    elseif (domainDim(basis)==2)
        b = ccall((:gsTHBSplineBasis2_create,libgismo),Ptr{gsCBasis},(Ptr{gsCBasis},),basis.ptr)
    elseif (domainDim(basis)==3)
        b = ccall((:gsTHBSplineBasis3_create,libgismo),Ptr{gsCBasis},(Ptr{gsCBasis},),basis.ptr)
    elseif (domainDim(basis)==4)
        b = ccall((:gsTHBSplineBasis4_create,libgismo),Ptr{gsCBasis},(Ptr{gsCBasis},),basis.ptr)
    else
        error("THBSplineBasis not implemented for this dimension")
    end
    return Basis(b)
end
