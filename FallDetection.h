#ifndef FALLDETECTION_H
#define FALLDETECTION_H

#include "vector.h"

class FallDetection
{
  public:
	  FallDetection();
	  ~FallDetection();
	  bool isFall(vec3 accel, vec3 gyro);

  private: 
	  vec3* LPFAccel;
	  vec3* LPFGyro;
	  unsigned char spot = 0;
	  int history[HISTORY_SIZE];

};


#endif //FALLDETECTION_H
