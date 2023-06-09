#include <Zumo32U4Motors.h>

class Motorcontroller
{
public:
  void rijdVooruit(int);
  void maakBocht(bool);
  void stop();

private: 
  Zumo32U4Motors motors;
};

