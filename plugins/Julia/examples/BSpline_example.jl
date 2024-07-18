using Plots
include("../Gismo/src/Gismo.jl")
using .Gismo

KV = Gismo.KnotVector([0.,0.,0.,1.,1.,1.])
BB = Gismo.BSplineBasis(KV)
Gismo.uniformRefine(BB)
Gismo.uniformRefine(BB)

# Create a matrix of random coefficients
coefs = rand(Gismo.size(BB),2)
# Create a BSpline geometry
B = Gismo.BSpline(BB,coefs)

# Create a matrix of linearly spaced evaluation points
points1D = zeros(1,100)
points1D[1,:] = range(0,stop=1,length=100)
ev = Gismo.asMatrix(Gismo.eval(B,points1D))

# Plot the geometry
plot(ev[1,:],ev[2,:],legend=false)
plot!(coefs[:,1],coefs[:,2],legend=false)
plot!(coefs[:,1],coefs[:,2],legend=false,seriestype=:scatter)
gui()


