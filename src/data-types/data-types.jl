module MyPackage
  include("Distance.jl")
  include("DistanceFrequency.jl")

  export Distance, DistanceFrequency
end