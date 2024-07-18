using Plots
include("../Gismo/src/Gismo.jl")
using .Gismo

KV = Gismo.KnotVector([0.,0.,0.,1.,1.,1.])
TBB = Gismo.TensorBSplineBasis(KV,KV)
print("The size of the basis is: ",Gismo.size(TBB),"\n")
Gismo.uniformRefine(TBB)
print("The size of the basis is: ",Gismo.size(TBB),"\n")

# Create a matrix of random coefficients
coefs = rand(Gismo.size(TBB),3)
# Create a BSpline geometry
TB = Gismo.TensorBSpline(TBB,coefs)

# Create a matrix of linearly spaced evaluation points
N = 10
points1D = range(0,stop=1,length=N)
points2D = zeros(2,N*N)
# points1D[1,:] = range(0,stop=1,length=N)
# Create a meshgrid of evaluation points
points2D[1,:] = repeat(points1D, N)
points2D[2,:] = repeat(points1D, inner=N)

ev = Gismo.asMatrix(Gismo.eval(TB,points2D))

# Plot the geometry
surface!(ev[1,:],ev[2,:],ev[3,:],legend=false)
plot!(coefs[:,1],coefs[:,2],coefs[:,3],legend=false,seriestype=:scatter)
gui()


