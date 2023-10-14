module converters

using DataTypes

function DistanceFrequencyToDistance(frequencyDistanceList::DistanceFrequency[])::Distance[]
  distanceArray::Distance[] = []
  for frequencyDistance in frequencyDistanceList
    for i=1:frequencyDistance.frequency
      distance = Distance()
      push!(distance, distanceArray)
    end
  end
  return distanceArray
end

export DistanceFrequencyToDistance

end