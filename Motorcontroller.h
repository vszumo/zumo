#include <Zumo32U4Motors.h>

class Motorcontroller
{
public:
  Motorcontroller(int);
  void rijdRecht(int);
  void maakBocht(bool);
  void stop();

private: 
  Zumo32U4Motors motors;
  int bochtsnelheid;
};

