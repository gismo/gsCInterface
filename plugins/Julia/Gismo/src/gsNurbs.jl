export
    KnotVector,
    BSplineBasis,
    BSpline,
    TensorBSplineBasis,
    TensorBSpline

########################################################################
# gsKnotVector
########################################################################

"""
    KnotVector(filename::String)

# Arguments
- `filename::String`: the name of the file containing the knot vector

    KnotVector(a::Vector{Float64})

# Arguments
- `a::Vector{Float64}`: the knot vector

# Examples
```jldoctest myKnotVector
julia> kv = KnotVector(Float64[0.,0.,0.,0.,0.5,1.,1.,1.,1.])
```
"""
mutable struct KnotVector
    ptr::Ptr{gsCKnotVector}

    function KnotVector(filename::String)
        g = new(ccall((:gsCReadFile,libgismo),Ptr{gsCKnotVector},(Cstring,),filename) )
        finalizer(destroy, g)
        return g
    end

    function KnotVector(a::Vector{Float64})
        kv = new(ccall((:gsKnotVector_create,libgismo),Ptr{gsCKnotVector},(Ptr{Cdouble},Cint),a, length(a)) )
        finalizer(destroy, kv)
        return kv
    end

    function destroy(kv::KnotVector)
        ccall((:gsKnotVector_delete,libgismo),Cvoid,(Ptr{gsCKnotVector},),kv.ptr)
    end
end

Base.show(io::IO, obj::KnotVector) = ccall((:gsKnotVector_print,libgismo),Cvoid,(Ptr{gsCKnotVector},),obj.ptr)

"""
    size(kv::KnotVector)

Returns the number of elements in the knot vector.

# Arguments
- `kv::KnotVector`: the knot vector

# Examples
```jldoctest myKnotVector
julia> print(Gismo.size(kv))
# output
9
```
"""
function size(kv::KnotVector)::Int64
    return ccall((:gsKnotVector_size,libgismo),Cint,(Ptr{gsCKnotVector},),kv.ptr)
end

function uSize(kv::KnotVector)::Int64
    return ccall((:gsKnotVector_uSize,libgismo),Cint,(Ptr{gsCKnotVector},),kv.ptr)
end

function numElements(kv::KnotVector)::Int64
    return ccall((:gsKnotVector_numElements,libgismo),Cint,(Ptr{gsCKnotVector},),kv.ptr)
end

# function unique(kv::KnotVector)::Vector{Float64}
#     return ccall((:gsKnotVector_unique,libgismo),Vector{Float64},(Ptr{gsCKnotVector},),kv.ptr)
# end

########################################################################
# gsBSplineBasis
########################################################################

"""
    BSplineBasis(kv::KnotVector)

Defines a B-spline basis.

# Arguments
- `kv::KnotVector`: the knot vector
"""
function BSplineBasis(kv::KnotVector)::Basis
    b = ccall((:gsBSplineBasis_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},),kv.ptr)
    return Basis(b)
end

########################################################################
# gsBSpline
########################################################################

"""
    BSpline(basis::Basis,coefs::Matrix{Cdouble})

Defines a B-spline geometry.

# Arguments
- `basis::Basis`: the basis
- `coefs::Matrix{Cdouble}`: the coefficients
"""
function BSpline(basis::Basis,coefs::Matrix{Cdouble})::Geometry
    @assert Base.size(coefs,1)==Gismo.size(basis) "Number of rows of the coefficients should be equal to the number of elements of the basis"
    cc = EigenMatrix(Base.size(coefs,1), Base.size(coefs,2), pointer(coefs) )
    g = ccall((:gsBSpline_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    return Geometry(g)
end

########################################################################
# gsTensorBSplineBasis
########################################################################

"""
    TensorBSplineBasis(kv1::KnotVector,kv2::KnotVector)

Defines a 2D tensor B-spline basis.

# Arguments
- `kv1::KnotVector`: the first knot vector
- `kv2::KnotVector`: the second knot vector
"""
function TensorBSplineBasis(kv1::KnotVector,kv2::KnotVector)::Basis
    b = ccall((:gsTensorBSplineBasis2_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},Ptr{gsCKnotVector},),kv1.ptr,kv2.ptr)
    return Basis(b)
end

"""
    TensorBSplineBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector)

Defines a 3D tensor B-spline basis.

# Arguments
- `kv1::KnotVector`: the first knot vector
- `kv2::KnotVector`: the second knot vector
- `kv3::KnotVector`: the third knot vector
"""
function TensorBSplineBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector)::Basis
    b = ccall((:gsTensorBSplineBasis3_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},),
                                                                        kv1.ptr,
                                                                        kv2.ptr,
                                                                        kv3.ptr)
    return Basis(b)
end

"""
    TensorBSplineBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector,kv4::KnotVector)

Defines a 4D tensor B-spline basis.

# Arguments
- `kv1::KnotVector`: the first knot vector
- `kv2::KnotVector`: the second knot vector
- `kv3::KnotVector`: the third knot vector
- `kv4::KnotVector`: the fourth knot vector
"""
function TensorBSplineBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector,kv4::KnotVector)::Basis
    b = ccall((:gsTensorBSplineBasis3_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},),
                                                                        kv1.ptr,
                                                                        kv2.ptr,
                                                                        kv3.ptr,
                                                                        kv4.ptr)
    return Basis(b)
end


########################################################################
# gsTensorBSpline
########################################################################

"""
    TensorBSpline(basis::Basis,coefs::Matrix{Cdouble})

Defines a tensor B-spline geometry.

# Arguments
- `basis::Basis`: the basis
- `coefs::Matrix{Cdouble}`: the coefficients
"""
function TensorBSpline(basis::Basis,coefs::Matrix{Cdouble})::Geometry
    @assert Base.size(coefs,1)==Gismo.size(basis) "Number of rows of the coefficients should be equal to the number of elements of the basis"
    cc = EigenMatrix(Base.size(coefs,1), Base.size(coefs,2), pointer(coefs) )
    if (domainDim(basis)==2)
        g = ccall((:gsTensorBSpline2_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    elseif (domainDim(basis)==3)
        g = ccall((:gsTensorBSpline3_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    elseif (domainDim(basis)==4)
        g = ccall((:gsTensorBSpline4_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    else
        error("TensorBSpline not implemented for this dimension")
    end
    return Geometry(g)
end


########################################################################
# gsNurbsBasis
########################################################################

"""
    NurbsBasis(kv::KnotVector)

Defines a NURBS basis.

# Arguments
- `kv::KnotVector`: the knot vector
"""
function NurbsBasis(kv::KnotVector)::Basis
    b = ccall((:gsNurbsBasis_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},),kv.ptr)
    return Basis(b)
end

########################################################################
# gsNurbs
########################################################################

"""
    Nurbs(basis::Basis,coefs::Matrix{Cdouble})

Defines a NURBS geometry.

# Arguments
- `basis::Basis`: the basis
- `coefs::Matrix{Cdouble}`: the coefficients
"""
function Nurbs(basis::Basis,coefs::Matrix{Cdouble})::Geometry
    @assert Base.size(coefs,1)==Gismo.size(basis) "Number of rows of the coefficients should be equal to the number of elements of the basis"
    cc = EigenMatrix(Base.size(coefs,1), Base.size(coefs,2), pointer(coefs) )
    g = ccall((:gsNurbs_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    return Geometry(g)
end

########################################################################
# gsTensorNurbsBasis
########################################################################

"""
    TensorNurbsBasis(kv1::KnotVector,kv2::KnotVector)

Defines a 2D tensor NURBS basis.

# Arguments
- `kv1::KnotVector`: the first knot vector
- `kv2::KnotVector`: the second knot vector
"""
function TensorNurbsBasis(kv1::KnotVector,kv2::KnotVector)::Basis
    b = ccall((:gsTensorNurbsBasis2_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},Ptr{gsCKnotVector},),kv1.ptr,kv2.ptr)
    return Basis(b)
end

"""
    TensorNurbsBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector)

Defines a 3D tensor NURBS basis.

# Arguments
- `kv1::KnotVector`: the first knot vector
- `kv2::KnotVector`: the second knot vector
- `kv3::KnotVector`: the third knot vector
"""
function TensorNurbsBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector)::Basis
    b = ccall((:gsTensorNurbsBasis3_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},),
                                                                        kv1.ptr,
                                                                        kv2.ptr,
                                                                        kv3.ptr)
    return Basis(b)
end

"""
    TensorNurbsBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector,kv4::KnotVector)

Defines a 4D tensor NURBS basis.

# Arguments
- `kv1::KnotVector`: the first knot vector
- `kv2::KnotVector`: the second knot vector
- `kv3::KnotVector`: the third knot vector
- `kv4::KnotVector`: the fourth knot vector
"""
function TensorNurbsBasis(kv1::KnotVector,kv2::KnotVector,kv3::KnotVector,kv4::KnotVector)::Basis
    b = ccall((:gsTensorNurbsBasis3_create,libgismo),Ptr{gsCBasis},(Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},
                                                                         Ptr{gsCKnotVector},),
                                                                        kv1.ptr,
                                                                        kv2.ptr,
                                                                        kv3.ptr,
                                                                        kv4.ptr)
    return Basis(b)
end


########################################################################
# gsTensorNurbs
########################################################################

"""
    TensorNurbs(basis::Basis,coefs::Matrix{Cdouble})

Defines a tensor NURBS geometry.

# Arguments
- `basis::Basis`: the basis
- `coefs::Matrix{Cdouble}`: the coefficients
"""
function TensorNurbs(basis::Basis,coefs::Matrix{Cdouble})::Geometry
    @assert Base.size(coefs,1)==Gismo.size(basis) "Number of rows of the coefficients should be equal to the number of elements of the basis"
    cc = EigenMatrix(Base.size(coefs,1), Base.size(coefs,2), pointer(coefs) )
    if (domainDim(basis)==2)
        g = ccall((:gsTensorNurbs2_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    elseif (domainDim(basis)==3)
        g = ccall((:gsTensorNurbs3_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    elseif (domainDim(basis)==4)
        g = ccall((:gsTensorNurbs4_create,libgismo),Ptr{gsCGeometry},
              (Ptr{gsCBasis},Ptr{gsCMatrix},),
              basis.ptr,cc.ptr)
    else
        error("TensorNurbs not implemented for this dimension")
    end
    return Geometry(g)
end
