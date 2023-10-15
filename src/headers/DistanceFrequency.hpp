#ifndef __DISTANCE_FREQUENCY
#define __DISTANCE_FREQUENCY

class DistanceFrequency
{
private:
  int frequency;
  double distance;
public:
  DistanceFrequency(int, double);
  double getDistance();
  int getFrequency();
};

#endif // __DISTANCE_FREQUENCY
