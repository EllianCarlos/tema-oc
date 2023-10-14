using MyPackage

using Formatting
# include(format(FormatExpr("{1:s}/uDGP/instance_generator.jl"), @__DIR__))
# calculation()

# using Instance_5/Instance/...1 of pertrabartmeyer

instance_path = format(
  FormatExpr("{1:s}/uDGP/Instance_5/Instances/distance_frequency_size5_instance1.dat"), @__DIR__
)


function readInstanceFile(path)
  io = open(path)

  io_read = read(io, String)

  lines = split(io_read, "\n")

  print(lines)

  for line in lines
    if line != ""
      frequency, distance = split(line, ".0 ")
      println(parse(Int64, frequency))
      println(parse(Float64, distance))
    end
  end
end

#readInstanceFile(instance_path)

print(DistanceFrequencyToDistance([DistanceFrequency(5, 1.34)]))